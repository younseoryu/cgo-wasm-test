package main

// #cgo CFLAGS: -g -Wall
// #cgo LDFLAGS: -lgmp
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include "gmp.h"
// int gmpSqrt () {
// 	   printf("%s", "hello from gmp");
//     mpf_t sq_me, sq_out, test;
//     mpf_set_default_prec (10000);
//     mpf_init(sq_me);
//     mpf_init(sq_out);
//     mpf_init(test);
//     mpf_set_str (sq_me, "2", 10);
//     mpf_sqrt(sq_out, sq_me);
//     mpf_mul(test,sq_out,sq_out);
//     gmp_printf ("Input:       %Ff\n\n", sq_me);
//     gmp_printf ("Square root: %.200Ff\n\n", sq_out);
//     gmp_printf ("Re-squared:  %Ff\n\n", test);
//     return 0;
// }
// typedef int (*intFunc) ();
//
// int
// bridge_int_func(intFunc f)
// {
//		return f();
// }
//
// int fortytwo()
// {
// 	    printf("%s", "hello");
//	    return 42;
// }
import "C"
import "fmt"

func main() {
	f2 := C.intFunc(C.gmpSqrt)
	fmt.Println(int(C.bridge_int_func(f2)))
	f := C.intFunc(C.fortytwo)
	fmt.Println(int(C.bridge_int_func(f)))
	// Output: 42
}
