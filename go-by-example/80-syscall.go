package main
import "os"
import "strings"
import "fmt"

func main(){
	os.Setenv("WEB", "http://coolshell.cn")
	fmt.Println(os.Getenv("WEB"))

	for _, env := range os.Environ(){
		e := strings.Split(env, "=")
		fmt.Println(e[0], "=", e[1])
	}
}