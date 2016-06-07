package main
import "os/exec"
import "fmt"

func main(){
	cmd := exec.Command("ls")
	out, err := cmd.Output()
	if err!= nil{
		println("Command Error!", err.Error())
		return
	}
	fmt.Println(string(out))
}
