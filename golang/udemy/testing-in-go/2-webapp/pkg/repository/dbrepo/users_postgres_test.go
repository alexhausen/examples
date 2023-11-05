//go:build integration

package dbrepo

import (
	"database/sql"
	"fmt"
	"log"
	"os"
	"testing"
	"time"
	"webapp/pkg/data"
	"webapp/pkg/repository"

	_ "github.com/jackc/pgconn"
	_ "github.com/jackc/pgx/v4"
	_ "github.com/jackc/pgx/v4/stdlib"
	"github.com/ory/dockertest/v3"
	"github.com/ory/dockertest/v3/docker"
)

var (
	host     = "localhost"
	user     = "postgres"
	password = "postgres"
	dbName   = "users_test"
	port     = "5435" // avoid conflict with actual db
	dsn      = "host=%s port=%s user=%s password=%s dbname=%s sslmode=disable timezone=UTC connect_timeout=1"
)

var resouce *dockertest.Resource
var pool *dockertest.Pool
var testDB *sql.DB
var testRepo repository.DataBaseRepo

func TestMain(m *testing.M) {
	// connect to docker; fail if docker not running
	p, err := dockertest.NewPool("unix:///var/run/docker.sock")
	if err != nil {
		log.Fatalf("could not connect to docker. Is it running? %s", err)
	}
	pool = p
	err = pool.Client.Ping()
	if err != nil {
		log.Fatalf("Could not connect to Docker: %s", err)
	}
	// set up docker options
	opts := dockertest.RunOptions{
		Repository: "postgres",
		Tag:        "14.5",
		Env: []string{
			"POSTGRES_USER=" + user,
			"POSTGRES_PASSWORD=" + password,
			"POSTGRES_DB=" + dbName,
		},
		ExposedPorts: []string{"5432"},
		PortBindings: map[docker.Port][]docker.PortBinding{
			"5432": {
				{HostIP: "0.0.0.0", HostPort: port},
			},
		},
	}

	// get a resource (docker image)
	resouce, err = pool.RunWithOptions(&opts)
	if err != nil {
		log.Fatalf("could not start resource: %s", err)
		// _ = pool.Purge(resouce)
	}

	// start the image and wait it's ready
	if err := pool.Retry(func() error {
		var err error
		testDB, err = sql.Open("pgx", fmt.Sprintf(dsn, host, port, user, password, dbName))
		if err != nil {
			log.Println("Error:", err)
			return err
		}
		return testDB.Ping()
	}); err != nil {
		log.Fatalf("could not connect to database: %s", err)
		// _ = pool.Purge(resouce)
	}

	// create tables
	err = createTables()
	if err != nil {
		log.Fatalf("error creating tables: %s", err)
	}

	testRepo = &PostgresDBRepo{DB: testDB}

	// run tests
	code := m.Run()

	// clean up
	if err = pool.Purge(resouce); err != nil {
		log.Fatalf("could not purge resouce: %s", err)
	}

	os.Exit(code)
}

func createTables() error {
	tableSQL, err := os.ReadFile("./fakedata/users_fake.sql")
	if err != nil {
		fmt.Println(err)
		return err
	}
	_, err = testDB.Exec(string(tableSQL))
	if err != nil {
		fmt.Println(err)
		return err
	}
	return nil
}

func Test_pingDB(t *testing.T) {
	err := testDB.Ping()
	if err != nil {
		t.Error("can't ping database")
	}
}

func Test_PostgresDBRepo_InsertUser(t *testing.T) {
	testUser := data.User{
		FirstName: "Admin",
		LastName:  "User",
		Email:     "admin@example.com",
		Password:  "secret",
		IsAdmin:   1,
		CreatedAt: time.Now(),
		UpdatedAt: time.Now(),
	}
	id, err := testRepo.InsertUser(testUser)
	if err != nil {
		t.Errorf("insert user returned an error: %s", err)
	}
	if id != 1 {
		t.Errorf("insert user returned wrong id. Expected 1, but got %d", id)
	}
}

func Test_PostgresDBRepo_AllUsers(t *testing.T) {
	users, err := testRepo.AllUsers()
	if err != nil {
		t.Errorf("all users reports an error: %s", err)
	}
	if len(users) != 1 {
		t.Errorf("all users reports wrong size. Expected 1, but got %d", len(users))
	}
	testUser := data.User{
		FirstName: "Jack",
		LastName:  "Smith",
		Email:     "jack@smith.com",
		Password:  "secret",
		IsAdmin:   1,
		CreatedAt: time.Now(),
		UpdatedAt: time.Now(),
	}
	var id int
	id, err = testRepo.InsertUser(testUser)
	if err != nil {
		t.Errorf("insert user returned an error: %s", err)
	}
	if id != 2 {
		t.Errorf("insert user returned wrong id. Expected 2, but got %d", id)
	}
	users, err = testRepo.AllUsers()
	if err != nil {
		t.Errorf("all users reports an error: %s", err)
	}
	if len(users) != 2 {
		t.Errorf("all users reports wrong size. Expected 2, but got %d", len(users))
	}
}

func Test_PostgresDBRepo_GetUser(t *testing.T) {
	user, err := testRepo.GetUser(1)
	if err != nil {
		t.Errorf("error getting user by id: %s", err)
	}
	if user.Email != "admin@example.com" {
		t.Errorf("wrong e-mail. Expected adming@example.com, got %s", user.Email)
	}
	_, err = testRepo.GetUser(3)
	if err == nil {
		t.Error("unexpected user")
	}
}

func Test_PostgresDBRepo_GetUserByEmail(t *testing.T) {
	user, err := testRepo.GetUserByEmail("jack@smith.com")
	if err != nil {
		t.Errorf("error getting user by e-mail: %s", err)
	}
	if user.ID != 2 {
		t.Errorf("wrong ID. Expected 2, got %d", user.ID)
	}
}

func Test_PostgresDBRepo_UpdateUser(t *testing.T) {
	user, _ := testRepo.GetUser(2)
	user.FirstName = "Jane"
	user.Email = "jane@smith.com"
	err := testRepo.UpdateUser(*user)
	if err != nil {
		t.Errorf("error updating the user 2:%s", err)
	}
	user, _ = testRepo.GetUser(2)
	if user.FirstName != "Jane" || user.Email != "jane@smith.com" {
		t.Errorf("database was not updated. %s, %s", user.FirstName, user.Email)
	}
}

func Test_PostgresDBRepo_DeleteUser(t *testing.T) {
	err := testRepo.DeleteUser(2)
	if err != nil {
		t.Errorf("error deleting user id 2: %s", err)
	}
	_, err = testRepo.GetUser(2)
	if err == nil {
		t.Error("retrieved user who should have been deleted")
	}
}

func Test_PostgresDBRepo_ResetPassword(t *testing.T) {
	err := testRepo.ResetPassword(1, "password")
	if err != nil {
		t.Errorf("error reseting password: %s", err)
	}
	user, _ := testRepo.GetUser(1)
	matches, err := user.PasswordMatches("password")
	if err != nil {
		t.Error(err)
	}
	if !matches {
		t.Error("password doesn't match")
	}
}

func Test_PostgresDBRepo_InsertUserImage(t *testing.T) {
	var image data.UserImage
	image.UserID = 1
	image.FileName = "test.jpg"
	image.CreatedAt = time.Now()
	image.UpdatedAt = time.Now()
	newID, err := testRepo.InsertUserImage(image)
	if err != nil {
		t.Errorf("insert user image failed: %s", err)
	}
	if newID != 1 {
		t.Errorf("got wrong id for image. Expected 1, got %d", newID)
	}

	image.UserID = 100
	_, err = testRepo.InsertUserImage(image)
	if err == nil {
		t.Error("err")
	}
}
