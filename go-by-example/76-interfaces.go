package main
import (
    "fmt"
    "math"
)

type shape interface{
	area() float64
	perimeter() float64
}

type rect struct {
    width, height float64
}
 
func (r *rect) area() float64 { //面积
    return r.width * r.height
}
 
func (r *rect) perimeter() float64 { //周长
    return 2*(r.width + r.height)
}
 
//----------- 圆  形 ----------//
type circle struct {
    radius float64
}
 
func (c *circle) area() float64 { //面积
    return math.Pi * c.radius * c.radius
}
 
func (c *circle) perimeter() float64 { //周长
    return 2 * math.Pi * c.radius
}

func interface_test(){
	r := rect{2.9, 4.8}
	c := circle{4.3}

	s:= []shape{&r, &c}

	for _, sh:= range s{
		fmt.Println(sh)
		fmt.Println(sh.area())
		fmt.Println(sh.perimeter())
	}
}

func main(){
    interface_test()
}
