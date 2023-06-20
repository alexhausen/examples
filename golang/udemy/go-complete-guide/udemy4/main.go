// https://www.udemy.com/course/go-the-complete-developers-guide/learn/practice/9958/introduction#questions
package main

import (
	"fmt"
	"io"
	"os"
)

func main() {
	// fmt.Println(os.Args)
	if len(os.Args) != 2 {
		os.Exit(1)
	}
	file, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer file.Close() // defer will close file at the end of the scope
	io.Copy(os.Stdout, file)
}
