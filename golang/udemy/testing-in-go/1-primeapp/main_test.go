package main

import (
	"bufio"
	"bytes"
	"io"
	"os"
	"strings"
	"testing"
)

func Test_isPrime(t *testing.T) {
	primeTests := []struct {
		name     string
		testNum  int
		expected bool
		msg      string
	}{
		{"prime", 7, true, "7 is a prime number!"},
		{"not prime", 8, false, "8 is not a prime number because it is divisible by 2"},
		{"zero", 0, false, "0 is not prime, by definition!"},
		{"one", 1, false, "1 is not prime, by definition!"},
		{"negative", -2, false, "Negative numbers are not prime, by definition!"},
	}

	for _, e := range primeTests {
		result, msg := isPrime(e.testNum)
		if result != e.expected {
			t.Errorf("%s: expected %t but got %t", e.name, e.expected, result)
		}
		if msg != e.msg {
			t.Errorf("%s: expected %s but got %s", e.name, e.msg, msg)
		}
	}
}

func Test_prompt(t *testing.T) {
	// save Stdout
	oldOut := os.Stdout
	// create a read and a write pipe
	r, w, _ := os.Pipe()
	// set Stdout to write pipe
	os.Stdout = w
	prompt()
	_ = w.Close()
	// restore Stdout
	os.Stdout = oldOut

	// test
	out, _ := io.ReadAll(r)
	if string(out) != "-> " {
		t.Errorf("incorrect prompt: expected -> got %s", string(out))
	}
}

func Test_intro(t *testing.T) {
	// save Stdout
	oldOut := os.Stdout
	// create a read and a write pipe
	r, w, _ := os.Pipe()
	// set Stdout to write pipe
	os.Stdout = w
	intro()
	_ = w.Close()
	// restore Stdout
	os.Stdout = oldOut
	// read all output
	out, _ := io.ReadAll(r)
	// test
	if !strings.Contains(string(out), "Enter a whole number") {
		t.Errorf("intro text not correct: got %s", string(out))
	}
}

func Test_checkNumbers(t *testing.T) {
	tests := []struct {
		name     string
		input    string
		expected string
	}{
		{name: "empty", input: "", expected: "Please enter a whole number!"},
		{name: "zero", input: "0", expected: "0 is not prime, by definition!"},
		{name: "one", input: "1", expected: "1 is not prime, by definition!"},
		{name: "negative", input: "-1", expected: "Negative numbers are not prime, by definition!"},
		{name: "prime", input: "7", expected: "7 is a prime number!"},
		{name: "not prime", input: "9", expected: "9 is not a prime number because it is divisible by 3"},
		{name: "quit", input: "q", expected: ""},
		{name: "Quit", input: "Q", expected: ""},
	}
	for _, e := range tests {
		input := strings.NewReader(e.input)
		reader := bufio.NewScanner(input)
		res, _ := checkNumbers(reader)
		if !strings.EqualFold(res, e.expected) {
			t.Errorf("%s: incorrect return value, got %s", e.name, res)
		}
	}
}

func Test_readUserInput(t *testing.T) {
	doneChan := make(chan bool)
	var stdin bytes.Buffer
	stdin.Write([]byte("1\nq\n"))
	go readUserInput(&stdin, doneChan)
	<-doneChan
	close(doneChan)
}
