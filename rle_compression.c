#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define DEBUG */

struct EncodedData {
    char character;
    int count;
};

/* ===========================Function Prototypes=========================== */ 
char *compressRLE(char* input);
char *decompressRLE(char* input);

/* =============================== Functions =============================== */ 
int compress() {
    FILE *inputFile = fopen("patients.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    /* Allocate memory for file content */
    char* buffer = malloc((fileSize + 1) * sizeof(char)); 
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(buffer, sizeof(char), fileSize, inputFile);
    /* Null terminate the string */
    buffer[fileSize] = '\0'; 
    fclose(inputFile);

    #ifdef DEBUG
    printf("Original content:\n%s\n", buffer);
    #endif

    /* Compress the content of the file using RLE */
    char* compressed = compressRLE(buffer);
    /* Free the memory allocated for the input buffer */
    free(buffer); 

    if (compressed == NULL) {
        fprintf(stderr, "Error compressing data\n");
        return 1;
    }

    #ifdef DEBUG
    printf("Compressed content:\n%s\n", compressed);
    #endif

    /* Write compressed data */
    FILE *outputFile = fopen("patients.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error creating compressed file\n");
        free(compressed); 
        return 1;
    }

    fprintf(outputFile, "%s", compressed);
    fclose(outputFile);
    free(compressed); 

    printf("File compressed successfully.\n");

    return 0;
}

int decompress() {
    FILE *inputFile = fopen("patients.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    /* Allocate memory for file content */
    char *buffer = malloc((fileSize + 1) * sizeof(char)); 
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    fread(buffer, sizeof(char), fileSize, inputFile);
    /* Null terminate the string */
    buffer[fileSize] = '\0'; 
    fclose(inputFile);
    
    #ifdef DEBUG
    printf("Compressed content:\n%s\n", buffer);
    #endif

    /* Decompress the content of the file using RLE */
    char *decompressed = decompressRLE(buffer);
    /* Free the memory allocated for the input buffer*/
    free(buffer); 

    if (decompressed == NULL) {
        fprintf(stderr, "Error decompressing data\n");
        return 1;

    }

    #ifdef DEBUG
    printf("Decompressed content:\n%s\n", decompressed);
    #endif

    /* Write compressed data */
    FILE *outputFile = fopen("patients.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error creating decompressed file\n");
        free(decompressed); 
        return 1;
    }

    fprintf(outputFile, "%s", decompressed);
    fclose(outputFile);
    free(decompressed); 

    printf("File decompressed successfully.\n");

    return 0;
}

/*******************************************************************************
 * Helper functions
*******************************************************************************/

/*******************************************************************************
 * This function uses Run-Length-Encoding to compress data
 * inputs:
 * - char *input
 * outputs:
 * - compressed
*******************************************************************************/
char *compressRLE(char *input) {
    int length = strlen(input);
    if (length == 0) {
        return NULL; 
    }
    /* Allocate memory for compressed string */
    /*  Max size could be double the input length */
    char *compressed = malloc(2 * length * sizeof(char)); 
    if (compressed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    int compressedIndex = 0;
    int i = 0;
    while (i < length) {
        int count = 1;
        while (i < length - 1 && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        /* Append character and its count to the compressed string */
        compressed[compressedIndex++] = input[i];
        /* Convert count to character */
        compressed[compressedIndex++] = count + '0'; 
        i++;
    }
    /* Add NULL terminator */
    compressed[compressedIndex] = '\0';

    #ifdef DEBUG
    printf("CompressRLE - Compressed string: %s\n", compressed);
    #endif

    return compressed;
}

/*******************************************************************************
 * This function uses Run-Length-Encoding to decompress data
 * inputs:
 * - char *input
 * outputs:
 * - compressed
*******************************************************************************/
char *decompressRLE(char *input) {
    int length = strlen(input);
    if (length == 0) {
        return NULL; 
    }
    /* Allocate memory for decompressed string */
    char *decompressed = malloc((2 * length + 1) * sizeof(char)); 
    if (decompressed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int decompressedIndex = 0;
    int i = 0;
    while (i < length) {
        /* Append character to the decompressed string */
        decompressed[decompressedIndex++] = input[i];
        int count = input[i + 1] - '0';
        for (int j = 1; j < count; j++) {
            decompressed[decompressedIndex++] = input[i];
        }

        i += 2;
    }
    /* Add NULL terminator */
    decompressed[decompressedIndex] = '\0';
    
    #ifdef DEBUG
    printf("DecompressRLE - Decompressed string: %s\n", decompressed);
    #endif

    return decompressed;
}
