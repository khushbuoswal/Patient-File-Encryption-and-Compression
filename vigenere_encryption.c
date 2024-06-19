/*******************************************************************************
 * Header files
*******************************************************************************/
#include <string.h>
#include "vigenere_encryption.h"

/*******************************************************************************
 * Encrypts text in-place using Vigenere Cipher with provided key,
 * with alterations to further support capitalisation and numbers.
 * inputs:
 * - char* text
 * - const char* key
 * outputs:
 * - none
*******************************************************************************/
void vigenereEncrypt(char* text, const char* key) {
    int i = 0;
    int shift = 0;
    int len = strlen(text);

    /* Loop through the entire string */
    for (; i < len; ++i) {
        char c = text[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            /* get factor to shift by from the key */
            int shifted = ((key[shift % strlen(key)] - 'A') % ALPHABET_SIZE);

            /* handle lowercase */
            if (c >= 'a' && c <= 'z') {
                /* for purposes of calculation, start from 0 (a) to 25 (z) */
                int code = c - 'a';
                /* apply the shift to the char code */
                code += shifted;
                /* wrap to alphabet size via modulo, convert back to ASCII */
                c = (code % ALPHABET_SIZE) + 'a';
            /* same as above for UPPERCASE */
            } else {
                int code = c - 'A';
                code += shifted;
                c = (code % ALPHABET_SIZE) + 'A';
            }

            ++shift;
        /* handle digits separately, as they range from 0 to 9, not 0 to 26. */
        } else if (c >= '0' && c <= '9') {
            int shifted = ((key[shift % strlen(key)] - 'A') % NUMBERS_SIZE);

            int code = c - '0';
            code += shifted;
            c = (code % NUMBERS_SIZE) + '0';
            
            ++shift;
        }

        /* assign encrypted character to text */
        text[i] = c;
    }
}

/*******************************************************************************
 * Decrypts text in-place using Vigenere Cipher with provided key,
 * with alterations to further support capitalisation and numbers.
 * inputs:
 * - char* text
 * - const char* key
 * outputs:
 * - none
*******************************************************************************/
void vigenereDecrypt(char* text, const char* key) {
    int i = 0;
    int shift = 0;
    int len = strlen(text);

    /* Loop through the entire string */
    for (; i < len; ++i) {
        char c = text[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            /* get factor to shift by from the key, modulo to "wrap" number around */
            int shifted = ((key[shift % strlen(key)] - 'A') % ALPHABET_SIZE);

            /* handle lowercase */
            if (c >= 'a' && c <= 'z') {
                /* for purposes of calculation, start from 0 (a) to 25 (z) */
                int code = c - 'a';
                /* reverse the shift */
                code -= shifted;
                /* then revert back to correct ASCII */
                c = (code + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
            /* same as above for UPPERCASE */
            } else {
                int code = c - 'A';
                code -= shifted;
                c = (code + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
            }

            ++shift;
        /* handle digits separately, as they range from 0 to 9, not 0 to 26. */
        } else if (c >= '0' && c <= '9') {
            int shifted = ((key[shift % strlen(key)] - 'A') % NUMBERS_SIZE);

            int code = c - '0';
            code -= shifted;
            c = (code + NUMBERS_SIZE) % NUMBERS_SIZE + '0';
            
            ++shift;
        }

        /* assign decrypted character to text */
        text[i] = c;
    }
}

/*******************************************************************************
 * Modifies provided key in-place to ensure it is a valid key for the cipher.
 * inputs:
 * - char* key
 * outputs:
 * - none
*******************************************************************************/
void vignereProcessKey(char* key) {
    int i = 0;
    int len = strlen(key);

    for (; i < len; ++i) {
        char c = key[i];
        /* skip capitals to prevent errors w/ nums */
        if (c >= 'A' && c <= 'Z') {
            continue;
        /* convert lower to upper */
        } else if (c >= 'a' && c <= 'z') {
            key[i] = c - 'a' + 'A';
        /* convert numbers to letters */
        } else if (c >= '0' && c <= '9') {
            key[i] = 'A' + (c - '0');
        /* anything else, convert to alphabet based on code + index */
        } else {
            int code = c;
            key[i] = 'A' + ((code + i) % ALPHABET_SIZE);
        }
    }
}
