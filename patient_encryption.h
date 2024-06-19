#ifndef PATIENT_ENCRYPTION_H
#define PATIENT_ENCRYPTION_H

/*******************************************************************************
 * This function encrypts data from patients.txt using Vigenere
 * inputs:
 * - char* key
 * outputs:
 * - none
*******************************************************************************/
int encrypt(char* key);

/*******************************************************************************
 * This function decrypts data from patients.txt using Vigenere
 * inputs:
 * - char* key
 * outputs:
 * - none
*******************************************************************************/
int decrypt(char* key);

#endif /* PATIENT_ENCRYPTION_H */
