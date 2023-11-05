package main

import (
	"os"
	"testing"
	"webapp/pkg/repository/dbrepo"
)

var app application
var expiredToken = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhZG1pbiI6dHJ1ZSwiYXVkIjoiZXhhbXBsZS5jb20iLCJleHAiOjE2ODkyMzgxMzksImlzcyI6ImV4YW1wbGUuY29tIiwibmFtZSI6IkpvaG4gRG9lIiwic3ViIjoiMSJ9.Mlo4-vNH27TgP8amI7_TPFn1cNM9dn5Kqi6PLJAkJu4"

func TestMain(m *testing.M) {
	app.DB = &dbrepo.FakeDBRepo{}
	app.Domain = "example.com"
	app.JWTSecret = "very secretive"
	os.Exit(m.Run())
}
