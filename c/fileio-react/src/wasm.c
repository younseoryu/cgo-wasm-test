#include <emscripten.h>
#include <stdlib.h>
#include <stdio.h>

EMSCRIPTEN_KEEPALIVE int add(int a, int b)
{
    // trivial function for testing
    return a + b;
}


EMSCRIPTEN_KEEPALIVE int writeFile(char* buffer, char* filename)
{
    FILE* f = fopen(filename, "a");
    if (f == NULL)
    {
        printf("Error! File cannot be opened.");
        return 0;
    }
    printf("writing text buffer from JS to MEMFS via WASM...\n");
    fprintf(f, "%s\n", buffer);
    fclose(f);
    return 1;
}


EMSCRIPTEN_KEEPALIVE int printFile(char* filename)
{
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("Error! File cannot be opened.");
        return 0;
    }

    // Read contents from file
    printf("buffer from the file: \n");
    char c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);

    return 1;
}


EMSCRIPTEN_KEEPALIVE char* getFile(char* filename)
{
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("Error! File cannot be opened.");
        return 0;
    }

    // Read contents from file
    char* buffer = NULL;
    size_t len;
    ssize_t bytes_read = getdelim( &buffer, &len, '\0', fptr);
    if ( bytes_read == -1) {
        printf("There was an error reading file - getFile()");
        return 0;
    }

    return buffer;
}

EMSCRIPTEN_KEEPALIVE int ifFileExists(char* filename)
{
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("Error! File cannot be opened.");
        return 0;
    } else {
        return 1;
    }
}