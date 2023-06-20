package main

import "fmt"

func WriteToChannel(c chan string) {
	c <- "ok"
}

func main() {
	c := make(chan string)
	go WriteToChannel(c)
	/*
		x := ""
		x <- c
		//: invalid operation: cannot send to non-channel x (variable of type string)
	*/
	x := <-c
	fmt.Println(x)
}
