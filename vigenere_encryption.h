#ifndef VIGENERE_CIPHER_H
#define VIGENERE_CIPHER_H

/*******************************************************************************
 * Preprocessing directives
*******************************************************************************/
#define ALPHABET_SIZE 26
#define NUMBERS_SIZE 10

/*******************************************************************************
 * Function prototypes
*******************************************************************************/
void vigenereEncrypt(char* text, const char* key);
void vigenereDecrypt(char* text, const char* key);
void vignereProcessKey(char* key);

#endif
