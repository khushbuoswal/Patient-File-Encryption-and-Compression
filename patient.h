#ifndef PATIENT_H
#define PATIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_LEN 32
#define MAX_ADDRESS_LEN 1024
#define MAX_NOTE_SIZE 1024
#define MAX_DATE_LEN 12


/* Struct definitions */

struct patient {
    /* Name of patient */
    char name[MAX_NAME_LEN];
     char address[MAX_ADDRESS_LEN];
    /* Patient's birthdate */
    char birthdate[MAX_DATE_LEN];
    /* Patient's last visit */
    char lastVisit[MAX_DATE_LEN];
    /* Patient's medicare number */
    int medicare;
    /* Patient's phone number */
    int phone;
    /* Notes on patient */
    char note[MAX_NOTE_SIZE];
    /* Pointer to the next patient */
    struct patient *next;
};

/*******************************************************************************
 * This function frees the patient management system
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
void freePatient(struct patient *patient);

/*******************************************************************************
 * This function creates a new patient
 * inputs:
 * -  char name[MAX_NAME_LEN],
 * outputs:
 * - patients
*******************************************************************************/
struct patient *createPatient(char name[MAX_NAME_LEN],
    char address[MAX_ADDRESS_LEN],
    char birthdate[MAX_DATE_LEN],
    char lastVisit[MAX_DATE_LEN],
    int medicare,
    int phone,
    char note[MAX_NOTE_SIZE]
);


#endif /* PATIENT_H */
