package main

import (
        "fmt"
        "bytes"
        "encoding/binary"
)

type A struct {
    One int32
    Two int32
}

func main() {
	var a A
	a.One = int32(1)
	a.Two = int32(2)
	
	buf := new(bytes.Buffer)
	fmt.Println("a's size is ", binary.Size(a))
	binary.Write(buf, binary.LittleEndian, a)
	fmt.Println("after write, buf is ", buf.Bytes())
	
	var aa A
	binary.Read(buf,binary.LittleEndian,&aa)
	fmt.Println("after aa is ",aa)
}