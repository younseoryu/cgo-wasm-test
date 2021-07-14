package main

import (
	"fmt"
	"syscall/js"

	"lab.crownsterling.io/crown/hybridapp/bbs"
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
	fmt.Println("hello")
	p := "99839842085451247175204607156151044981964545565652494610250826763301042300100351940113921061251920679817487844217126737222677444818832605206406368834355787"
	q := "66333257838526561017350877790102691682608106259566145646996599849805182137660428654423005378215460173521248336614156822889435069733388575260814340428480837"
	seed := "20632068808524367466720189053998721301256237945553241367507874265301550792091"

	byteString, _ := bbs.Process(p, q, seed, 100)

	fmt.Println(byteString)
	return nil
}
