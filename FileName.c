#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 100
#define PASSWORD_LENGTH 6
#define FLEET_FILE "fleet.txt"
#define LOGIN_FILE "login.txt"

// Structure for login credentials
typedef struct Login {
    char username[MAX_STRING];
    char password[PASSWORD_LENGTH + 1];
    struct Login* next;
} Login;

// Structure for machinery details
typedef struct Machinery {
    char chassisNumber[MAX_STRING];
    char make[MAX_STRING];
    char model[MAX_STRING];
    int year;
    double cost;
    double valuation;
    int mileage;
    int nextServiceMileage;
    char ownerName[MAX_STRING];
    char ownerEmail[MAX_STRING];
    char ownerPhone[MAX_STRING];
    char machineType[MAX_STRING];
    char breakdowns[MAX_STRING];
    struct Machinery* next;
} Machinery;

// Function prototypes
void loadLoginData(Login** head);
int authenticateUser(Login* head);
void loadFleetData(Machinery** head);
void saveFleetData(Machinery* head);
void addMachine(Machinery** head);
void displayAllMachines(Machinery* head);
void displayMachineDetails(Machinery* head);
void updateMachine(Machinery* head);
void deleteMachine(Machinery** head);
void generateStatistics(Machinery* head);
void printReport(Machinery* head);
void listByValuation(Machinery* head);
void menu(Machinery** fleetHead);
void freeLoginData(Login* head);
void freeFleetData(Machinery* head);

void addMachine(Machinery** head) {
    Machinery* newMachine = (Machinery*)malloc(sizeof(Machinery));
    if (!newMachine) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter Chassis Number: ");
    scanf("%s", newMachine->chassisNumber);
    printf("Enter Make: ");
    scanf("%s", newMachine->make);
    printf("Enter Model: ");
    scanf("%s", newMachine->model);
    printf("Enter Year: ");
    scanf("%d", &newMachine->year);
    printf("Enter Cost: ");
    scanf("%lf", &newMachine->cost);
    printf("Enter Valuation: ");
    scanf("%lf", &newMachine->valuation);
    printf("Enter Mileage: ");
    scanf("%d", &newMachine->mileage);
    printf("Enter Next Service Mileage: ");
    scanf("%d", &newMachine->nextServiceMileage);
    printf("Enter Owner Name: ");
    scanf("%s", newMachine->ownerName);
    printf("Enter Owner Email: ");
    scanf("%s", newMachine->ownerEmail);
    printf("Enter Owner Phone: ");
    scanf("%s", newMachine->ownerPhone);
    printf("Enter Machine Type: ");
    scanf("%s", newMachine->machineType);
    printf("Enter Breakdown History: ");
    scanf("%s", newMachine->breakdowns);

    newMachine->next = *head;
    *head = newMachine;

    printf("Machine added successfully!\n");
}

int main() {
    ggggggggggggg
}