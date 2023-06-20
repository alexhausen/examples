// go test

package main

import "testing"

func TestEvenOdd(t *testing.T) {
	if even_odd(0) != "even" {
		t.Errorf("Zero is even")
	}
	if even_odd(1) != "odd" {
		t.Errorf("Zero is odd")
	}
	if even_odd(2) != "even" {
		t.Errorf("Zero is even")
	}
}
