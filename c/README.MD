# MINIMUM C-WASM examples for testing purpose

# TO BUILD aes, ecdh
gcc main.c -o output -lcrypto -L/usr/local/opt/openssl@1.1/lib -I/usr/local/opt/openssl@1.1/include

# TO BUILD fileio-react
make (generate wasm (.mjs))
npm install
npm start