#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vigenere_encryption.h"

/* ===========================Function Prototypes=========================== */ 
int encrypt(char* key);
int decrypt(char* key);

/* =============================== Functions =============================== */ 
int encrypt(char* key) {
    char inputFileName[] = "patients.txt";
    FILE *inputFile = fopen(inputFileName, "r+");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    /* Encrypt contents */
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), inputFile)) {
        vigenereEncrypt(buffer, key);
        fseek(inputFile, -strlen(buffer), SEEK_CUR);
        fputs(buffer, inputFile);
    }

    fclose(inputFile);

    printf("Encryption complete. Encrypted content saved in %s\n", inputFileName);

    return 0;
}

int decrypt(char* key) {
    char inputFileName[] = "patients.txt";
    FILE *inputFile = fopen(inputFileName, "r+");
    if (inputFile == NULL) {
        perror("Error opening file");
        return 1;
    }
 
    /* Decrypt contents */
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), inputFile)) {
        vigenereDecrypt(buffer, key);
        fseek(inputFile, -strlen(buffer), SEEK_CUR);
        fputs(buffer, inputFile);
    }

    fclose(inputFile);

    printf("Decryption complete. Decrypted content saved in %s\n", inputFileName);

    return 0;
}
