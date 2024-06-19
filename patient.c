#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_LEN 32
#define MAX_ADDRESS_LEN 1024
#define MAX_NOTE_SIZE 1024
#define MAX_DATE_LEN 12

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

/* ===========================Function Prototypes=========================== */ 
void freePatient(struct patient *patient);
struct patient *createPatient(char name[MAX_NAME_LEN],
    char address[MAX_ADDRESS_LEN],
    char birthdate[MAX_DATE_LEN],
    char lastVisit[MAX_DATE_LEN],
    int medicare,
    int phone,
    char note[MAX_NOTE_SIZE]
);


/* =============================== Functions =============================== */ 
void freePatient(struct patient *patient) {
    struct patient *curPatient = patient;
    while (curPatient != NULL) {
        struct patient *nextPatient = curPatient->next;
        free(curPatient);
        curPatient = nextPatient;
    }
    // printf("Debug: freePatient() executed successfully\n"); 
}

struct patient *createPatient(char name[MAX_NAME_LEN],
    char address[MAX_ADDRESS_LEN],
    char birthdate[MAX_DATE_LEN],
    char lastVisit[MAX_DATE_LEN],
    int medicare,
    int phone,
    char note[MAX_NOTE_SIZE]
) {
    /* Allocate memory for a new patient */
    struct patient *newPatient = malloc(sizeof(struct patient));
    if (newPatient == NULL) {
        fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
    }

    strcpy(newPatient->name, name);
    strcpy(newPatient->address, address);
    strcpy(newPatient->birthdate, birthdate);
    strcpy(newPatient->lastVisit, lastVisit);
    newPatient->medicare = medicare;
    newPatient->phone = phone;
    strcpy(newPatient->note, note);

    newPatient->next = NULL;

    // printf("Debug: createPatient() executed successfully\n");

    return newPatient;
}
