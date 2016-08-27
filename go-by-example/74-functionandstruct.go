package main
import "fmt"

type rect struct{
	width, height int
}

func(r *rect) area() int{
	return r.width * r.height
}

func (r *rect) perimeter() int{
	return 2*(r.width + r.height)
}

func main(){
	r := rect{10, 15}

	fmt.Println("面积：", r.area())
	fmt.Println("周长: ", r.perimeter())

	rp := &r
	fmt.Println("面积: ", rp.area())
	fmt.Println("周长: ", rp.perimeter())
}