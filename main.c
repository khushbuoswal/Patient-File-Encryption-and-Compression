/*
 Instructions to run:
 - Compile with: make all
 - Run with: ./main.out
 - Enter password: Abcd1234
*/

/*
 48430 Assignment 3 - Group Project
 Lab 4
 Members:
 - Kian O'Mahony-Green, 24660779
 > Worked on vigenere_encryption.c, Report

 - P. P. Moneli S. Peries, 14483984
 > Worked on main.c, Report

 - Xintong Li, 24502344
 > Worked on main.c, patient.c, Report

 - Khushbu Oswal, 14098887
 > Worked on rle_compression.c, patient_encryption.c, Report
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "patient.h"
#include "patient_encryption.h"
#include "rle_compression.h"
#include "vigenere_encryption.h"

/* ================================ Defines ================================ */ 
#define MAX_BUFFER_SIZE 256

/* ===========================Function Prototypes=========================== */ 
struct patient *loadPatients();
int authorisation(char* password);
void printMenu(void);
void addPatient(struct patient **head);
void viewAllPatients(struct patient *head);
void viewPatient(struct patient *head);
void updatePatient(struct patient *head);
void updatePatientFile(struct patient *head);
void countPatients(struct patient *head);
struct patient *nextPatient(struct patient *cur, struct patient *head);
struct patient *prevPatient(struct patient *cur, struct patient *head);
void deletePatients(struct patient **head);
void deletePatientsFile();
int fileCheck();

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void) {
    char password[] = "Abcd1234";

    printf("Welcome to the patient management system!\n");
    
    if (!authorisation(password)) {
        return 1;
    }

    vignereProcessKey(password);

    struct patient *head = NULL; 
    struct patient *selected = NULL;

    selected = loadPatients(&head);
    head = selected;

    printMenu();
    char command;
    printf("Enter command: ");
    while(scanf(" %c", &command) != EOF) {
        if (command == '?') {
            printMenu();
        } else if (command == 'a') {
            /* Add patient details */
            addPatient(&head);
            if (head != NULL) {
                selected = head;
            }
        } else if (command == 'V') {
            /* View all patients */
            viewAllPatients(head);
        } else if (command == 'v') {
            /* View patient details*/
            viewPatient(selected);
        } else if (command == 'u') {
            /* Update selected patient */
            updatePatient(selected);
        } else if (command == 'c') {
            /* Count patients */
            countPatients(head);
        } else if (command == '>') {
            /* Select next patient */
            selected = nextPatient(selected, head);
        } else if (command == '<') {
            /* Select prev patient */
            selected = prevPatient(selected, head);
        } else if (command == 'e') {
            /* Encrypt patient details */
            if (!fileCheck()) {
                printf("Enter command: ");
                continue;
            }
            encrypt(password);
            selected = loadPatients(&head);
            head = selected;
        } else if (command == 'd') {
            /* Decrpyt patient details */
            if (!fileCheck()) {
                printf("Enter command: ");
                continue;
            }
            decrypt(password);
            selected = loadPatients(&head);
            head = selected;
        } else if (command == 'C') { 
            /* Compress patient details */
            if (!fileCheck()) {
                printf("Enter command: ");
                continue;
            }
            compress();
        } else if (command == 'D') {
            /* Decompress patient details */
            if (!fileCheck()) {
                printf("Enter command: ");
                continue;
            }
            decompress();
        } else if (command == 'x') {
            /* Delete patient */
            if (!fileCheck()) {
                printf("Enter command: ");
                continue;
            }
            deletePatients(&head);
            selected = head;
        } else if (command == 'q') {
            printf("Thank you for using the patient management system!\n");
            return 0;
        }
        printf("Enter command: ");
    }

    printf("Thank you for using the patient management system!\n");

    return 0;
}

/*******************************************************************************
 * Helper functions
*******************************************************************************/

/*******************************************************************************
 * This function loads all the patients from patients.txt
 * inputs:
 * - none
 * outputs:
 * - struct patient
*******************************************************************************/
struct patient *loadPatients() {
    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        printf("Error opening patients.txt.\n");
        return NULL;
    }

    struct patient *head = NULL;

    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '\0') {
            continue;
        }

        char name[MAX_NAME_LEN];
        int medicare;
        char address[MAX_ADDRESS_LEN];
        char birthdate[MAX_DATE_LEN];
        char lastVisit[MAX_DATE_LEN];
        int phone;
        char note[MAX_NOTE_SIZE];

        if (sscanf(buffer, "| %[^|] | %d | %[^|] | %[^|] | %[^|] | %d | %[^\n] |", 
                    name, &medicare, address, birthdate, lastVisit, &phone, note) == 7) {
            struct patient *newPatient = createPatient(name, address, birthdate, lastVisit, 0, phone, note);
            if (head == NULL) {
                head = newPatient;
            } else {
                struct patient *cur = head;
                while (cur->next != NULL) {
                    cur = cur->next;
                }
                cur->next = newPatient;
            }
        }
    }

    fclose(file);

    return head;
}
/*******************************************************************************
 * This function authorises access to the program
 * inputs:
 * - none
 * outputs:
 * - int
*******************************************************************************/
int authorisation(char* password) {
    char input[100];
    int attempts = 0;

    printf("Enter password: ");
    while (attempts < 3) {
        scanf("%s", input);
        if (strcmp(input, password) == 0) {
            return 1;
        } else {
            attempts++;
            if (attempts < 3) {
                printf("Incorrect password. Please try again: ");
            }
        }
    }
    printf("Too many incorrect attempts. Please try again later.");
    return 0;
}

/*******************************************************************************
 * This function prints the menu of the PIM system to the logged in clinician.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printMenu(void) {
    printf(
    "------------------------- MENU -------------------------\n"
    "           (?)  Show Menu\n"
    "           (a)  Add Patient Details\n"
    "           (c)  Count Patients\n"
    "           (V)  View All Patient Details\n"
    "           (v)  View Patient Details\n"
    "           (u)  Update Patient\n"
    "           (>)  Select Next Patient\n"
    "           (<)  Select Previous Patient\n"
    "           (e)  Encrypt Patient Information\n"
    "           (d)  Decrypt Patient Information\n"
    "           (C)  Compress Patient Information\n"
    "           (D)  Decompress Patient Information\n"
    "           (x)  Delete All Patients\n"
    "           (q)  Exit Patient Management System\n");
    printf("--------------------------------------------------------");
    printf("\n");
}

/*******************************************************************************
 * This function adds a patient to the management system
 * inputs:
 * -  char name[MAX_NAME_LEN];
 * -  char address[MAX_ADDRESS_LEN];
 * -  char birthdate[MAX_DATE_LEN];
 * -  char lastVisit[MAX_DATE_LEN];
 * -  int medicare;
 * -  int phone;
 * -  char note[MAX_NOTE_SIZE];
 * outputs:
 * - none
*******************************************************************************/
void addPatient(struct patient **head) {
    char name[MAX_NAME_LEN];
    char address[MAX_ADDRESS_LEN];
    char birthdate[MAX_DATE_LEN];
    char lastVisit[MAX_DATE_LEN];
    int medicare;
    int phone;
    char note[MAX_NOTE_SIZE];

    printf("Name: ");
    scanf(" %[^\n]", name);
    while (getchar() != '\n');
    printf("Address: ");
    scanf(" %[^\n]", address);
    while (getchar() != '\n');
    printf("Birthdate (DD/MM/YYYY): ");
    scanf(" %[^\n]", birthdate);
    while (getchar() != '\n');
    printf("Last visit (DD/MM/YYYY): ");
    scanf(" %[^\n]", lastVisit);
    while (getchar() != '\n');
    printf("Medicare number: ");
    scanf("%d", &medicare);
    while (getchar() != '\n');
    printf("Phone number: ");
    scanf("%d", &phone);
    while (getchar() != '\n');
    printf("Notes: ");
    scanf(" %[^\n]", note);
    while (getchar() != '\n');
    struct patient *newPatient = createPatient(name, address, birthdate, lastVisit, medicare, phone, note);

    FILE *file = fopen("patients.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "| %-16s | %-8d | %-19s | %-10s | %-10s | %-15d | %-12s |\n",
            name, medicare, address, birthdate, lastVisit, phone, note);

    fclose(file);

    if (*head == NULL) {
        *head = newPatient;
    } else {
        struct patient *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPatient;
    }

    printf("Patient has been successfully added!\n");
}

/*******************************************************************************
 * This function views all the patients in the system
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
void viewAllPatients(struct patient *head) {
    if (head == NULL) {
        printf("There are no patients in the system.\n");
        return;
    }

    printf("Patients:\n");
    struct patient *current = head;
    while (current != NULL) {
        printf("- %s\n", current->name);
        current = current->next;
    }
}

/*******************************************************************************
 * This function views the selected patient information
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
void viewPatient(struct patient *head) {
    if (head == NULL) {
        printf("No patient found.\n");
        return;
    }
    printf("\n");
    printf("--------------------------------------------------- \n");
    printf("| %-15s Patient Details:%-15s |\n", " ", " ");
    printf("| Name: %-41s |\n", head->name);
    printf("| Address: %-38s |\n", head->address);
    printf("| Birthdate: %-36s |\n", head->birthdate);
    printf("| Last Visit: %-35s |\n", head->lastVisit);
    printf("| Medicare Number: %-30d |\n", head->medicare);
    printf("| Phone Number: %-33d |\n", head->phone);
    printf("| Notes: %-40s |\n", head->note);
    printf("--------------------------------------------------- \n");
    printf("\n");
}

/*******************************************************************************
 * This function updates the selected patient information
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
void updatePatient(struct patient *head) {

    if (head == NULL) {
        printf("No patient found.\n");
        return;
    }

    printf("Updated address: ");
    scanf(" %[^\n]", head->address);
    while (getchar() != '\n');

    printf("Updated last visit (DDMMYYYY): ");
    scanf(" %[^\n]", head->lastVisit);
    while (getchar() != '\n');

    printf("Updated phone number: ");
    scanf("%d", &head->phone);
    while (getchar() != '\n');

    printf("Updated notes: ");
    scanf(" %[^\n]", head->note);
    
    printf("Patient details have been updated successfully.\n");

    updatePatientFile(head);
}

/*******************************************************************************
 * This function updates the patient in patient.txt
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
void updatePatientFile(struct patient *head) {
    FILE *file = fopen("patients.txt", "w"); 
    if (file == NULL) {
        printf("Error opening patients.txt.\n");
        return;
    }

    struct patient *current = head;
    while (current != NULL) {
        fprintf(file, "| %-16s | %-8d | %-19s | %-10s | %-10s | %-15d | %-12s |\n",
                current->name, current->medicare, current->address, current->birthdate, current->lastVisit, current->phone, current->note);
        current = current->next;
    }

    fclose(file);
}

/*******************************************************************************
 * This function counts the number of patients in the system
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
void countPatients(struct patient *head) {
    if (head == NULL) {
        printf("There are no patients in the system.\n");
        return;
    }
    int count = 0;
    struct patient *cur = head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }

    if (count == 1) {
        printf("There is %d patient in the system.\n", count);
    } else {
        printf("There are %d patients in the system.\n", count);
    }

}

/*******************************************************************************
 * This function selects the next patient
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
struct patient *nextPatient(struct patient *cur, struct patient *head) {
    if (cur == NULL) {
        printf("There are no patients in the system.\n");
        return head;
    }
    if (cur->next == NULL) {
        return head;
    }
    return cur->next;
}

/*******************************************************************************
 * This function selects the previous patient
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
struct patient *prevPatient(struct patient *cur, struct patient *head) {
    if (cur == NULL) {
        printf("There are no patients in the system.\n");
        return head;
    }
    struct patient *curPatient = head;
    if (cur == head) {
        while (cur->next != NULL) {
            cur = cur->next;
        }
        return cur;
    }

    while (curPatient->next != cur) {
        curPatient = curPatient->next;       
    }   
    return curPatient;
}

/*******************************************************************************
 * This function deletes the selected patient
 * inputs:
 * -  struct patient
 * outputs:
 * - none
*******************************************************************************/
void deletePatients(struct patient **head) {
    printf("Please enter CONFIRM to delete all patients: ");
    char input[100];
    char *confirmation = "CONFIRM";
    scanf("%s", input);
    if (strcmp(input, confirmation) != 0) {
        printf("Unable to delete patients.\n");
        return;
    }

    freePatient(*head);
    *head = NULL; 

    printf("Patients have been deleted!\n");

    deletePatientsFile();
}

/*******************************************************************************
 * This function deletes the selected patient in the file
 * inputs:
 * -  none
 * outputs:
 * - none
*******************************************************************************/
void deletePatientsFile() {
FILE *file = fopen("patients.txt", "w"); // Open file in write mode to truncate (clear) it
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    fclose(file);
}

/*******************************************************************************
 * This function checks whether the file is empty
 * inputs:
 * -  const char *filename
 * outputs:
 * - int
*******************************************************************************/
int fileCheck() {
    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1; 
    }
    fseek(file, 0, SEEK_END); 
    long size = ftell(file);  
    fclose(file);             
    
    if (size <= 0) {
        printf("There are no patients in the system.\n");
        return 0;
    }    

    return 1;
}
