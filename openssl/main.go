package main

// #cgo CFLAGS: -I/usr/local/opt/openssl/include
// #cgo LDFLAGS: -lcrypto -lssl -L/usr/local/opt/openssl/lib
// #include <openssl/evp.h>
// #include <openssl/aes.h>
// #include <openssl/err.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include "gmp.h"
//
// static const unsigned char key[] = {
//     0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
//     0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
//     0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
// };
//
// int init_ssl() {
//     unsigned char text[]="hello world!";
//     unsigned char enc_out[80];
//     unsigned char dec_out[80];
//
//     AES_KEY enc_key, dec_key;
//
//     AES_set_encrypt_key(key, 128, &enc_key);
//     AES_encrypt(text, enc_out, &enc_key);
//
//     AES_set_decrypt_key(key,128,&dec_key);
//     AES_decrypt(enc_out, dec_out, &dec_key);
//
//     int i;
//
//     printf("original:\t");
//     for(i=0;*(text+i)!=0x00;i++)
//         printf("%X ",*(text+i));
//     printf("\nencrypted:\t");
//     for(i=0;*(enc_out+i)!=0x00;i++)
//         printf("%X ",*(enc_out+i));
//     printf("\ndecrypted:\t");
//     for(i=0;*(dec_out+i)!=0x00;i++)
//         printf("%X ",*(dec_out+i));
//     printf("\n");
//     return 1;
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
	/* compilation: gcc -o client client.c -lssl -lcrypto */
	f2 := C.intFunc(C.init_ssl)
	fmt.Println(int(C.bridge_int_func(f2)))
	f := C.intFunc(C.fortytwo)
	fmt.Println(int(C.bridge_int_func(f)))
	// Output: 42
}
