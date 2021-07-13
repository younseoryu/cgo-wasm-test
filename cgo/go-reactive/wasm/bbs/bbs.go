package bbs

import (
	"encoding/hex"
	"errors"
	"fmt"
	"log"
	"math/big"
	"os"

	"github.com/tsdtsdtsd/gobbs"
)

const (
	mPermission = 0777
	base        = 10
)

//ConcurrentProcess func
func ConcurrentProcess(prime1 []string, prime2 []string, sd []string, length []int) {

}

//Process func
func Process(prime1 string, prime2 string, sd string, length int) (string, error) {
	p := new(big.Int)
	p.SetString(prime1, base)

	q := new(big.Int)
	q.SetString(prime2, base)

	seed := new(big.Int)
	seed.SetString(sd, base)

	bits := 1024 // Not sure what this does

	//Configure config variabble with p,q, and seed
	config := gobbs.Config{
		PrimeP: p,
		PrimeQ: q,
		Seed:   seed,
		Bits:   bits,
	}

	generator, _ := gobbs.NewWithConfig(&config)

	buf := make([]byte, 1)

	var data []byte
	var dataret string
	for i := 0; i < length; i++ {
		if _, err := generator.Read(buf); err != nil {
			fmt.Println(err)
		}

		for _, val := range buf {
			data = append(data, val)
		}

		// fmt.Println(data[len(data)-1], " vs ", buf)
		// fmt.Printf("%c", buf) // RAW: "%c"
		// fmt.Printf("%02x.", buf) // HEX "%02x."
		// fmt.Printf("%08b", buf) // ASCII "%03i"
	}
	dataret = hex.EncodeToString(data)
	if len(data) != length {
		return "", errors.New("Length of key does not match desired length.")
	}
	// bytes2hex2file(filename, data)
	// filename := "test.txt"
	// bytes2File(filename, data)

	return dataret, nil
	// bytes2hex2file(filename, data)

	/*
	 *	Formating Info:
	 *
	 *	GENERAL
	 *	"%v"	the value in a default format when printing structs, the plus flag (%+v) adds field names
	 *	"%#v"	a Go-syntax representation of the value
	 *	"%T"	a Go-syntax representation of the type of the value
	 *	"%%"	a literal percent sign; consumes no value
	 *
	 *	BOOLEAN
	 *	"%t"	the word true or false
	 *
	 *	INTEGERS
	 *	"%b"	base 2
	 *	"%c"	the character represented by the corresponding Unicode code point
	 *	"%d"	base 10
	 *	"%o"	base 8
	 *	"%O"	base 8 with 0o prefix
	 *	"%q"	a single-quoted character literal safely escaped with Go syntax.
	 *	"%x"	base 16, with lower-case letters for a-f
	 *	"%X"	base 16, with upper-case letters for A-F
	 *	"%U"	Unicode format: U+1234; same as "U+%04X"
	 *
	 *	String and slice of bytes (treated equivalently with these verbs):
	 *	"%s"	the uninterpreted bytes of the string or slice
	 *	"%q"	a double-quoted string safely escaped with Go syntax
	 *	"%x"	base 16, lower-case, two characters per byte
	 *	"%X"	base 16, upper-case, two characters per byte
	 */

	// format := "%b\n"
	// bytes2format2file(filename, format, data)
}

// func bytes2File(filename string, data []byte) {
// 	// Open a new file for writing only
// 	file, err := os.OpenFile(
// 		filename,
// 		os.O_WRONLY|os.O_TRUNC|os.O_CREATE,
// 		mPermission,
// 	)

// 	if err != nil {
// 		log.Fatal(err)
// 	}

// 	defer file.Close()

// 	// Write bytes to file
// 	bytesWritten, err := file.Write(data)
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// 	log.Printf("Wrote %d bytes.\n", bytesWritten)
// }

func bytes2hex2file(filename string, data []byte) {
	hexData := hex.EncodeToString(data)

	file, err := os.OpenFile(
		filename,
		os.O_WRONLY|os.O_TRUNC|os.O_CREATE,
		mPermission,
	)

	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	// Write bytes to file
	bytesWritten, err := file.WriteString(hexData)
	if err != nil {
		log.Fatal(err)
	}
	log.Printf("Wrote %d bytes.\n", bytesWritten)
}

// func Bytes2format2file(filename string, format string, data []byte) {
// 	file, err := os.OpenFile(
// 		filename,
// 		os.O_WRONLY|os.O_TRUNC|os.O_CREATE,
// 		mPermission,
// 	)

// 	if err != nil {
// 		log.Fatal(err)
// 	}

// 	defer file.Close()

// 	for _, v := range data {
// 		fmt.Fprintf(file, format, v)
// 	}
// 	file.Close()
// }
