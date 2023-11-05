package main

import (
	"bytes"
	"context"
	"crypto/tls"
	"fmt"
	"image"
	"image/png"
	"io"
	"mime/multipart"
	"net/http"
	"net/http/httptest"
	"net/url"
	"os"
	"path"
	"strings"
	"sync"
	"testing"
	"webapp/pkg/data"
)

func Test_application_handlers(t *testing.T) {
	var theTests = []struct {
		name                    string
		url                     string
		expectStatusCode        int
		expectedURL             string
		expectedFirstStatusCode int
	}{
		{"home", "/", http.StatusOK, "/", http.StatusOK},
		{"404", "/fish", http.StatusNotFound, "/fish", http.StatusNotFound},
		{"profile", "/user/profile", http.StatusOK, "/", http.StatusTemporaryRedirect},
	}

	routes := app.routes()

	// test server
	ts := httptest.NewTLSServer(routes)
	defer ts.Close()

	tr := &http.Transport{
		TLSClientConfig: &tls.Config{InsecureSkipVerify: true},
	}
	client := &http.Client{
		Transport: tr,
		CheckRedirect: func(req *http.Request, via []*http.Request) error {
			return http.ErrUseLastResponse
		},
	}

	for _, e := range theTests {
		resp, err := ts.Client().Get(ts.URL + e.url)
		if err != nil {
			t.Log(err)
			t.Fatal(err)
		}
		if resp.StatusCode != e.expectStatusCode {
			t.Errorf("for %s: expected status %d, but got %d", e.name, e.expectStatusCode, resp.StatusCode)
		}
		if resp.Request.URL.Path != e.expectedURL {
			t.Errorf("%s: expected final URL of %s, but got %s", e.name, e.expectedURL, resp.Request.URL.Path)
		}
		resp2, _ := client.Get(ts.URL + e.url)
		if resp2.StatusCode != e.expectedFirstStatusCode {
			t.Errorf("%s: expected first status code %d, but got %d", e.name, e.expectedFirstStatusCode, resp2.StatusCode)
		}
	}
}

func TestAppHome(t *testing.T) {
	var tests = []struct {
		name         string
		putInSession string
		expectedHTML string
	}{
		{"first visit", "", "<small>From Session:"},
		{"second visit", "hello, world!", "<small>From Session: hello, world!"},
	}
	for _, e := range tests {
		req, _ := http.NewRequest("GET", "/", nil)
		req = addContextAndSessionToRequest(req, app)
		_ = app.Session.Destroy(req.Context())
		if e.putInSession != "" {
			app.Session.Put(req.Context(), "test", e.putInSession)
		}
		rr := httptest.NewRecorder()
		handler := http.HandlerFunc(app.Home)
		handler.ServeHTTP(rr, req)
		if rr.Code != http.StatusOK {
			t.Errorf("Got unexpected status code %d", rr.Code)
		}

		body, _ := io.ReadAll(rr.Body)
		if !strings.Contains(string(body), e.expectedHTML) {
			t.Errorf("%s: didn't find %s in response body", e.name, e.expectedHTML)
		}
	}
}

func TestApp_renderWithBadTemplate(t *testing.T) {
	pathToTemplates = "./testdata/"
	req, _ := http.NewRequest("GET", "/", nil)
	req = addContextAndSessionToRequest(req, app)
	rr := httptest.NewRecorder()
	err := app.render(rr, req, "bad.page.gohtml", &TemplateData{})
	if err == nil {
		t.Error("expected error from bad template")
	}
	pathToTemplates = "../../templates/"
}

func getCtx(req *http.Request) context.Context {
	ctx := context.WithValue(req.Context(), contextUserKey, "unknown")
	return ctx
}

func addContextAndSessionToRequest(req *http.Request, app application) *http.Request {
	req = req.WithContext(getCtx(req))
	ctx, _ := app.Session.Load(req.Context(), req.Header.Get("X-Session"))
	return req.WithContext(ctx)
}

func Test_app_Login(t *testing.T) {
	var tests = []struct {
		name               string
		postedData         url.Values
		expectedStatusCode int
		expectedLoc        string
	}{
		{
			name: "valid login",
			postedData: url.Values{
				"email":    {"admin@example.com"},
				"password": {"secret"},
			},
			expectedStatusCode: http.StatusSeeOther,
			expectedLoc:        "/user/profile",
		},
		{
			name: "missing form data",
			postedData: url.Values{
				"email":    {""},
				"password": {""},
			},
			expectedStatusCode: http.StatusSeeOther,
			expectedLoc:        "/",
		},
		{
			name: "user not found",
			postedData: url.Values{
				"email":    {"my@bad.com"},
				"password": {"secret"},
			},
			expectedStatusCode: http.StatusSeeOther,
			expectedLoc:        "/",
		},
		{
			name: "bad credentials",
			postedData: url.Values{
				"email":    {"admin@example.com"},
				"password": {"fail"},
			},
			expectedStatusCode: http.StatusSeeOther,
			expectedLoc:        "/",
		},
	}

	for _, e := range tests {
		req, _ := http.NewRequest("POST", "/login", strings.NewReader(e.postedData.Encode()))
		req = addContextAndSessionToRequest(req, app)
		req.Header.Set("Content-Type", "application/x-www-form-urlencoded")
		rr := httptest.NewRecorder()
		handler := http.HandlerFunc(app.Login)
		handler.ServeHTTP(rr, req)
		if rr.Code != e.expectedStatusCode {
			t.Errorf("%s: returned wrong status. Expected %d, got %d", e.name, e.expectedStatusCode, rr.Code)
		}
		actualLoc, err := rr.Result().Location()
		if err != nil {
			t.Errorf("%s: no location header set", e.name)
		}
		if actualLoc.String() != e.expectedLoc {
			t.Errorf("%s: expected location %s, got %s", e.name, e.expectedLoc, actualLoc.String())
		}
	}
}

func Test_app_UploadFiles(t *testing.T) {
	// set up pipes
	pr, pw := io.Pipe()
	// create a new writer
	writer := multipart.NewWriter(pw)
	// create a waitgroup
	wg := &sync.WaitGroup{}
	wg.Add(1)
	// simulate uploading a file using a goroutine and the writer above
	go simulatePNGUpload("./testdata/img.png", writer, t, wg)
	// read from the pipe which receives data
	request := httptest.NewRequest("POST", "/", pr)
	request.Header.Add("Content-Type", writer.FormDataContentType())
	// call app.UploadFiles
	uploadedFiles, err := app.UploadFiles(request, "./testdata/uploads/")
	if err != nil {
		t.Error(err)
	}
	// perform tests
	if _, err := os.Stat(fmt.Sprintf("./testdata/uploads/%s", uploadedFiles[0].OriginalFileName)); os.IsNotExist(err) {
		t.Errorf("expect file to exist: %s", err.Error())
	}
	// clean up
	_ = os.Remove(fmt.Sprintf("./testdata/uploads/%s", uploadedFiles[0].OriginalFileName))
	wg.Wait()
}

func simulatePNGUpload(fileToUpload string, writer *multipart.Writer, t *testing.T, wg *sync.WaitGroup) {
	defer writer.Close()
	defer wg.Done()

	// create a form data field 'file'
	part, err := writer.CreateFormFile("file", path.Base(fileToUpload))
	if err != nil {
		t.Error(err)
	}
	// open the file
	f, err := os.Open(fileToUpload)
	if err != nil {
		t.Error(err)
	}
	defer f.Close()
	// decode image
	img, _, err := image.Decode(f)
	if err != nil {
		t.Error("error decoding image", err)
	}
	// write png to writer
	err = png.Encode(part, img)
	if err != nil {
		t.Error(err)
	}
}

func Test_app_UploadProfilePic(t *testing.T) {
	uploadPath = "./testdata/uploads"
	filePath := "./testdata/img.png"
	// specify a field name for the form
	fieldName := "file"
	// create a bytes.Buffer to act as the request body
	body := new(bytes.Buffer)
	// create a new writer
	mw := multipart.NewWriter(body)
	file, err := os.Open(filePath)
	if err != nil {
		t.Fatal(err)
	}
	w, err := mw.CreateFormFile(fieldName, filePath)
	if err != nil {
		t.Fatal(err)
	}
	if _, err := io.Copy(w, file); err != nil {
		t.Fatal(err)
	}
	mw.Close()
	req := httptest.NewRequest(http.MethodPost, "/upload", body)
	req = addContextAndSessionToRequest(req, app)
	app.Session.Put(req.Context(), "user", data.User{ID: 1})
	req.Header.Add("Content-Type", mw.FormDataContentType())
	rr := httptest.NewRecorder()
	handler := http.HandlerFunc(app.UploadProfilePic)
	handler.ServeHTTP(rr, req)
	if rr.Code != http.StatusSeeOther {
		t.Errorf("wrong status code: %d", rr.Code)
	}
	_ = os.Remove("./testdata/uploads/img.png")
}
