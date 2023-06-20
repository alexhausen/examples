// https://www.udemy.com/course/go-the-complete-developers-guide/learn/practice/9178/introduction#questions
// go mod init udemy1
// go run main.go even_odd.go

package main

import "fmt"

func main() {
	numbers := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	for _, number := range numbers {
		fmt.Printf("%d is %s\n", number, even_odd(number))
	}
}
