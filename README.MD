# MINIMUM GO, CGO, GMP, OPENSSL examples for testing purpose

# TO BUILD .exe (works for all)
go build -o output

# TO BUILD .wasm (works for go & regression & bcrypt. Does not work for cgo & gmp & openssl)
GOOS=js GOARCH=wasm go build -o main.wasm

# TO BUILD .wasm with TINYGO (works for go & regression & bcrypt. Does not work for cgo & gmp & openssl)
tinygo build -o wasm.wasm -target wasm ./main.go
1. https://tinygo.org/docs/guides/webassembly/