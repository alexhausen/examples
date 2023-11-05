package main

import (
	"net/http"
	"net/http/httptest"
	"net/url"
	"testing"
)

func TestForm_Has(t *testing.T) {
	form := NewForm(nil)
	has := form.Has("whatever")
	if has {
		t.Error("invalid field")
	}

	postedData := url.Values{}
	postedData.Add("a", "a")
	form = NewForm(postedData)
	has = form.Has("a")
	if !has {
		t.Error("should have field a")
	}
}

func TestForm_Require(t *testing.T) {
	r := httptest.NewRequest("Post", "/whatever", nil)
	form := NewForm(r.PostForm)
	form.Required("a", "b", "c")
	if form.Valid() {
		t.Error("form should be invalid")
	}

	postedData := url.Values{}
	postedData.Add("a", "a")
	postedData.Add("b", "b")
	postedData.Add("c", "c")
	r, _ = http.NewRequest("POST", "/whatever", nil)
	r.PostForm = postedData
	form = NewForm(r.PostForm)
	form.Required("a", "b", "c")
	if !form.Valid() {
		t.Error("form should be valid")
	}
}

func TestForm_Check(t *testing.T) {
	form := NewForm(nil)
	form.Check(false, "password", "password required")
	if form.Valid() {
		t.Error("should not be valid")
	}
}

func TestForm_ErrorGet(t *testing.T) {
	form := NewForm(nil)
	form.Check(false, "password", "password required")
	s := form.Errors.Get("password")
	if len(s) == 0 {
		t.Error("should get an error")
	}

	s = form.Errors.Get("whatever")
	if len(s) != 0 {
		t.Error("should not get an error")
	}
}
