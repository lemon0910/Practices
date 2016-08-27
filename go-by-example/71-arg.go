package main
import "os"
import "fmt"

func main(){
    args := os.Args
    fmt.Println(args)
    fmt.Println(args[1:])
}
