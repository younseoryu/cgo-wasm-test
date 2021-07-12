//gcc main.c -o output -lcrypto -L/usr/local/opt/openssl@1.1/lib -I/usr/local/opt/openssl@1.1/include
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/evp.h>
#include <openssl/engine.h>
#include <openssl/ossl_typ.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>



int ecdhkey(char *privfilename, char *pubfilename, char *seed)
{
    OpenSSL_add_all_algorithms();

    ERR_load_crypto_strings();

    // ENGINE_load_dynamic();
    // ENGINE *ring_engine = ENGINE_by_id("dynamic");
    // ENGINE_ctrl_cmd_string(ring_engine, "SO_PATH", sopath, 0);
    // ENGINE_ctrl_cmd_string(ring_engine, "LIST_ADD", "1", 0);
    // ENGINE_ctrl_cmd_string(ring_engine, "LOAD", NULL, 0);
    // int init_res = ENGINE_init(ring_engine);
    // printf("init result : %d \n", init_res);

    RAND_seed(seed, sizeof(seed));
    FILE *pubfile;
    FILE *privfile;
    EC_KEY *myecc = NULL;
    BIO *outbio = NULL;
    pubfile = fopen(pubfilename, "w");
    privfile = fopen(privfilename, "w");

    //Create the Input/Output BIO's.
    outbio = BIO_new(BIO_s_file());
    outbio = BIO_new_fp(stdout, BIO_NOCLOSE);

    //Create a EC key sructure, setting the group type from NID
    int eccgrp = OBJ_txt2nid("secp521r1");
    myecc = EC_KEY_new_by_curve_name(eccgrp);

    //Cert signing
    EC_KEY_set_asn1_flag(myecc, OPENSSL_EC_NAMED_CURVE);

    //Create the public/private EC key pair
    if (!(EC_KEY_generate_key(myecc)))
        BIO_printf(outbio, "Error generating the ECC key.");

    //Converting the EC key into a PKEY structure
    EVP_PKEY *pkey = EVP_PKEY_new();
    if (!EVP_PKEY_assign_EC_KEY(pkey, myecc))
        BIO_printf(outbio, "Error assigning ECC key to EVP_PKEY structure.");

    //Extract EC-specifics from the key
    myecc = EVP_PKEY_get1_EC_KEY(pkey);
    const EC_GROUP *ecgrp = EC_KEY_get0_group(myecc);

    //Print the key length, and extract the curve type
    // BIO_printf(outbio, "ECC Key size: %d bit\n", EVP_PKEY_bits(pkey));
    // BIO_printf(outbio, "ECC Key type: %s\n", OBJ_nid2sn(EC_GROUP_get_curve_name(ecgrp)));

    //Print the private/public key data in PEM format and to file
    int ret;
    // if (!PEM_write_bio_PrivateKey(outbio, pkey, NULL, NULL, 0, 0, NULL))
        // BIO_printf(outbio, "Error writing private key data in PEM format");

    ret = PEM_write_PrivateKey(privfile, pkey, NULL, NULL, 0, 0, NULL);
    if (ret == 0)
    {
        printf("Error writing private key to file");
        return 0;
    }

    // if (!PEM_write_bio_PUBKEY(outbio, pkey))
    //     BIO_printf(outbio, "Error writing public key data in PEM format");

    ret = PEM_write_PUBKEY(pubfile, pkey);
    if (ret == 0)
    {
        printf("Error writing public key to file");
        return 0;
    }

    //Free up and close
    EVP_PKEY_free(pkey);
    EC_KEY_free(myecc);
    BIO_free_all(outbio);
    fclose(privfile);
    fclose(pubfile);
    // ENGINE_free(ring_engine);
    // ENGINE_cleanup();
    return ret;
}

int main(int argc, char *argv[])
{
    int result = ecdhkey("privatekey1.pem", "publickey1.pem", "exampleseed");
    printf("result: %d\n", result);
}
