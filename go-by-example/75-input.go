package main
 
import (
    "fmt"
    "os"
)
 
func main() {
    v := GetInput()
    fmt.Println(v)
}
 
func GetInput() [4][4]int {
    var v[4][4]int
    l := 0
    for {
        var a[4]int
        i, err := fmt.Scanf("%d,%d,%d,%d\n", &a[0], &a[1], &a[2], &a[3])
        if i == 4 {
            for r := 0; r < 4; r++ {
                v[l][r] = a[r]
            }
        } else if i == 0 {
            break
        } else {
            fmt.Fprintln(os.Stderr, err)
            os.Exit(1)
        }
        l++

        if l == 4{
            break
        }
    }
    return v
}
