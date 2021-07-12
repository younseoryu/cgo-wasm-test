//gcc main.c -o output -lcrypto -L/usr/local/opt/openssl@1.1/lib -I/usr/local/opt/openssl@1.1/include
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/evp.h>
#include <openssl/engine.h>
#include <openssl/ossl_typ.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/aes.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/**
 * Encrypt or decrypt, depending on flag 'should_encrypt'
 */
void en_de_crypt(int should_encrypt, FILE *ifp, FILE *ofp, unsigned char *ckey, unsigned char *ivec)
{

    const unsigned BUFSIZE = 4096;
    unsigned char *read_buf = malloc(BUFSIZE);
    unsigned char *cipher_buf;
    unsigned blocksize;
    int out_len;
    EVP_CIPHER_CTX  *ctx =  EVP_CIPHER_CTX_new();
    EVP_CipherInit(ctx, EVP_aes_256_cbc(), ckey, ivec, should_encrypt);
    blocksize = EVP_CIPHER_CTX_block_size(ctx);
    cipher_buf = malloc(BUFSIZE + blocksize);

    while (1)
    {

        // Read in data in blocks until EOF. Update the ciphering with each read.
        int numRead = fread(read_buf, sizeof(unsigned char), BUFSIZE, ifp);
        EVP_CipherUpdate(ctx, cipher_buf, &out_len, read_buf, numRead);
        fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);
        if (numRead < BUFSIZE)
        { // EOF
            break;
        }
    }

    // Now cipher the final block and write it out.
    EVP_CipherFinal(ctx, cipher_buf, &out_len);
    fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);

    // Free memory

    free(cipher_buf);
    free(read_buf);
}

int aes(char *mode, char *sharedkeylib, char *infile,char *outfile)
{
    //argv[2] shared key lib
    //argv[1] encrypt/decrypt
    //argv[3] encrypt: file to be encrypted decrypt: file to be read.
    //argv[4] file to be written
    //Set up engine
    OpenSSL_add_all_algorithms();

    ERR_load_crypto_strings();

    // ENGINE_load_dynamic();
    // ENGINE *ring_engine = ENGINE_by_id("dynamic");
    // ENGINE_ctrl_cmd_string(ring_engine, "SO_PATH", sopath, 0);
    // ENGINE_ctrl_cmd_string(ring_engine, "LIST_ADD", "1", 0);
    // ENGINE_ctrl_cmd_string(ring_engine, "LOAD", NULL, 0);
    // int init_res = ENGINE_init(ring_engine);
    // printf("init result : %d \n", init_res);

    // ENGINE_set_default_RAND(ring_engine);
    // RAND_set_rand_engine(ring_engine);

    FILE *sharedKey;
    int lsize;
    sharedKey = fopen(sharedkeylib, "r");
    fseek(sharedKey, 0, SEEK_END);
    lsize = ftell(sharedKey);
    rewind(sharedKey);
    unsigned char *ckey = (char *)malloc(sizeof(char) * lsize);
    if (ckey == NULL)
    {
        fputs("Memory error", stderr);
        exit(2);
    }
    size_t result = fread(ckey, 1, lsize, sharedKey);
    if (result != lsize)
    {
        fputs("Reading error", stderr);
        exit(3);
    }

    /* Setup IV */
    rewind(sharedKey);
    char *ivec = (char *)malloc(sizeof(char) * lsize);
    if (ivec == NULL)
    {
        fputs("Memory error", stderr);
        exit(2);
    }
    result = fread(ivec, 1, lsize, sharedKey);

    FILE *fIN, *fOUT;

    if (!(strncmp(mode, "encrypt", 2)))
    {
        // First encrypt the file
        fIN = fopen(infile, "rb");  //File to be encrypted; plain text
        fOUT = fopen(outfile, "wb"); //File to be written; cipher text

        en_de_crypt(TRUE, fIN, fOUT, ckey, ivec);

        fclose(fIN);
        fclose(fOUT);
    }
    else if (!(strncmp(mode, "decrypt", 2)))
    {
        //Decrypt file now
        fIN = fopen(infile, "rb");  //File to be read; cipher text
        fOUT = fopen(outfile, "wb"); //File to be written; cipher text

        en_de_crypt(FALSE, fIN, fOUT, ckey, ivec);

        fclose(fIN);
        fclose(fOUT);
    }
    else
    {
        printf("First argument must be 'encrypt' or 'decrypt'");
        // return 0;
    }
    fclose(sharedKey);
    ENGINE_cleanup();
    return 0;
}
int main(int argc, char *argv[])
{
    int result = aes("encrypt", "sharedkey.txt", "infile.txt", "outfile.txt");
    printf("result: %d\n", result);
}
