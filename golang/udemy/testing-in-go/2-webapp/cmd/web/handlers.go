package main

import (
	"fmt"
	"html/template"
	"io"
	"log"
	"net/http"
	"os"
	"path"
	"path/filepath"
	"time"
	"webapp/pkg/data"
)

var pathToTemplates = "./templates/"
var uploadPath = "./static/img"

func (app *application) Home(w http.ResponseWriter, r *http.Request) {
	var td = make(map[string]any)
	if app.Session.Exists(r.Context(), "test") {
		msg := app.Session.GetString(r.Context(), "test")
		td["test"] = msg
	} else {
		app.Session.Put(r.Context(), "test", "Hit this page at "+time.Now().UTC().String())
	}
	_ = app.render(w, r, "home.page.gohtml", &TemplateData{Data: td})
}

func (app *application) Profile(w http.ResponseWriter, r *http.Request) {
	_ = app.render(w, r, "profile.page.gohtml", &TemplateData{})
}

type TemplateData struct {
	IP    string
	Data  map[string]any
	Error string
	Flash string
	User  data.User
}

func (app *application) render(w http.ResponseWriter, r *http.Request, t string, td *TemplateData) error {
	// parse template
	parsedTemplate, err := template.ParseFiles(path.Join(pathToTemplates, t), path.Join(pathToTemplates, "base.layout.gohtml"))
	if err != nil {
		http.Error(w, "bad request", http.StatusBadRequest)
		return err
	}

	td.IP = app.ipFromContext(r.Context())
	td.Error = app.Session.PopString(r.Context(), "error")
	td.Flash = app.Session.PopString(r.Context(), "flash")

	if app.Session.Exists(r.Context(), "user") {
		td.User = app.Session.Get(r.Context(), "user").(data.User)
	}

	// execute template, passing data
	err = parsedTemplate.Execute(w, td)
	if err != nil {
		return err
	}
	return nil
}

func (app *application) Login(w http.ResponseWriter, r *http.Request) {
	err := r.ParseForm()
	if err != nil {
		log.Println(err)
		http.Error(w, "bad request", http.StatusBadRequest)
		return
	}
	// data validation
	form := NewForm(r.PostForm)
	form.Required("email", "password")
	if !form.Valid() {
		// fmt.Fprint(w, "failed validation")
		// redirect to the login page with error message
		app.Session.Put(r.Context(), "error", "Invalid login credentials")
		http.Redirect(w, r, "/", http.StatusSeeOther)
		return
	}

	email := r.Form.Get("email")
	password := r.Form.Get("password")
	user, err := app.DB.GetUserByEmail(email)
	if err != nil {
		app.Session.Put(r.Context(), "error", "Invalid login")
		http.Redirect(w, r, "/", http.StatusSeeOther)
		return

	}
	if !app.authenticate(r, user, password) {
		app.Session.Put(r.Context(), "error", "Invalid login")
		http.Redirect(w, r, "/", http.StatusSeeOther)
		return
	}
	// prevent fixation attack
	_ = app.Session.RenewToken(r.Context())
	// redirect to some other page
	app.Session.Put(r.Context(), "flash", "Successfully logged in")
	http.Redirect(w, r, "/user/profile", http.StatusSeeOther)
}

func (app *application) authenticate(r *http.Request, user *data.User, password string) bool {
	if valid, err := user.PasswordMatches(password); err != nil || !valid {
		return false
	}
	app.Session.Put(r.Context(), "user", user)
	return true
}

func (app *application) UploadProfilePic(w http.ResponseWriter, r *http.Request) {
	// extract file from request
	files, err := app.UploadFiles(r, uploadPath)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}
	// get user from session
	user := app.Session.Get(r.Context(), "user").(data.User)
	// create UserImage
	var img = data.UserImage{
		UserID:   user.ID,
		FileName: files[0].OriginalFileName,
	}
	// insert
	_, err = app.DB.InsertUserImage(img)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}
	// refresh the session for "user"
	updatedUser, err := app.DB.GetUser(user.ID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}
	app.Session.Put(r.Context(), "user", updatedUser)
	// redirect back to profile page
	http.Redirect(w, r, "/user/profile", http.StatusSeeOther)
}

type UploadedFile struct {
	OriginalFileName string
	FileSize         int64
}

func (app *application) UploadFiles(r *http.Request, uploadDir string) ([]*UploadedFile, error) {
	var uploadFiles []*UploadedFile

	err := r.ParseMultipartForm(int64(1024 * 1024 * 5))
	if err != nil {
		return nil, fmt.Errorf("file too big: size > 5 MiB")
	}
	for _, fileHeaders := range r.MultipartForm.File {
		for _, header := range fileHeaders {
			// function (app *application) uploadFileFromHeader(header) ([]*UploadedFile, error)
			uploadFiles, err = func(uploadFiles []*UploadedFile) ([]*UploadedFile, error) {
				var uploadFile UploadedFile
				infile, err := header.Open()
				if err != nil {
					return nil, err
				}
				defer infile.Close()
				uploadFile.OriginalFileName = header.Filename
				var outfile *os.File
				defer outfile.Close()
				if outfile, err = os.Create(filepath.Join(uploadDir, uploadFile.OriginalFileName)); nil != err {
					return nil, err
				} else {
					fileSize, err := io.Copy(outfile, infile)
					if err != nil {
						return nil, err
					}
					uploadFile.FileSize = fileSize
				}
				uploadFiles = append(uploadFiles, &uploadFile)
				return uploadFiles, nil
			}(uploadFiles)
			if err != nil {
				return uploadFiles, err
			}
		}
	}
	return uploadFiles, nil
}
