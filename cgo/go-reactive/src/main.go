package main

import (
	"fmt"
	"syscall/js"
)

var c chan bool

func init() {
	fmt.Println("Hello, WebAssembly!")
	c = make(chan bool)
}

func main() {
	js.Global().Set("sayHelloJS", js.FuncOf(SayHello))
	js.Global().Set("test1JS", js.FuncOf(test1))
	println("Done.. done.. done...")
	<-c
}

// SayHello simply set the textConent of our element based on the value it receives (i.e the value from the input box)
// the element MUST exist else it'll throw an exception
func SayHello(jsV js.Value, inputs []js.Value) interface{} {
	message := inputs[0].String()
	// h := js.Global().Get("document").Call("getElementById", "message")
	// h.Set("textContent", message)
	fmt.Println(message)
	return nil
}

// test1 - test function
func test1(jsV js.Value, inputs []js.Value) interface{} {
	input0 := inputs[0].String()
	fmt.Println(input0)
	return nil
}
