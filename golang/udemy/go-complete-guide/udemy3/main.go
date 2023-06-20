// https://www.udemy.com/course/go-the-complete-developers-guide/learn/practice/9944/introduction#questions/14196906

package main

import "fmt"

type triangle struct {
	h float64
	b float64
}

type square struct {
	side float64
}

func (t triangle) area() float64 {
	return 0.5 * t.b * t.h
}

func (s square) area() float64 {
	return s.side * s.side
}

type shape interface {
	area() float64
}

func printArea(s shape) {
	fmt.Println(s.area())
}

func main() {
	t := triangle{3, 5}
	printArea(t)

	s := square{3}
	printArea(s)
}
