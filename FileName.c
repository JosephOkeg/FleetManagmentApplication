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

void displayAllMachines(Machinery* head) {
    if (!head) {
        printf("No machinery data available.\n");
        return;
    }

    printf("\n--- Fleet Machinery List ---\n");
    while (head) {
        printf("Chassis Number: %s, Make: %s, Model: %s, Year: %d\n",
            head->chassisNumber, head->make, head->model, head->year);
        head = head->next;
    }
}

void displayMachineDetails(Machinery* head) {
    char chassis[MAX_STRING];
    printf("Enter Chassis Number: ");
    scanf("%s", chassis);

    while (head) {
        if (strcmp(head->chassisNumber, chassis) == 0) {
            printf("\nMachine Details:\n");
            printf("Make: %s\nModel: %s\nYear: %d\nCost: %.2lf\n",
                head->make, head->model, head->year, head->cost);
            printf("Valuation: %.2lf\nMileage: %d\nNext Service: %d\n",
                head->valuation, head->mileage, head->nextServiceMileage);
            printf("Owner: %s, Email: %s, Phone: %s\n",
                head->ownerName, head->ownerEmail, head->ownerPhone);
            printf("Machine Type: %s\nBreakdowns: %s\n", head->machineType, head->breakdowns);
            return;
        }
        head = head->next;
    }

    printf("Machine not found.\n");
}

void updateMachine(Machinery* head) {
    char chassis[MAX_STRING];
    printf("Enter Chassis Number to update: ");
    scanf("%s", chassis);

    while (head) {
        if (strcmp(head->chassisNumber, chassis) == 0) {
            printf("Enter New Mileage: ");
            scanf("%d", &head->mileage);
            printf("Enter New Next Service Mileage: ");
            scanf("%d", &head->nextServiceMileage);
            printf("Enter New Valuation: ");
            scanf("%lf", &head->valuation);
            printf("Machine details updated successfully!\n");
            return;
        }
        head = head->next;
    }

    printf("Machine not found.\n");
}

void deleteMachine(Machinery** head) {
    char chassis[MAX_STRING];
    printf("Enter Chassis Number to delete: ");
    scanf("%s", chassis);

    Machinery* temp = *head, * prev = NULL;

    while (temp) {
        if (strcmp(temp->chassisNumber, chassis) == 0) {
            if (prev) {
                prev->next = temp->next;
            }
            else {
                *head = temp->next;
            }
            free(temp);
            printf("Machine deleted successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Machine not found.\n");
}

void generateStatistics(Machinery* head) {
    if (!head) {
        printf("No machinery data available.\n");
        return;
    }

    int count = 0, totalMileage = 0;
    double totalValuation = 0.0;

    while (head) {
        totalMileage += head->mileage;
        totalValuation += head->valuation;
        count++;
        head = head->next;
    }

    printf("\n--- Fleet Statistics ---\n");
    printf("Total Machines: %d\n", count);
    printf("Average Valuation: %.2lf\n", (count > 0) ? (totalValuation / count) : 0);
    printf("Total Fleet Mileage: %d\n", totalMileage);
}

void printReport(Machinery* head) {
    FILE* file = fopen("fleet_report.txt", "w");
    if (!file) {
        printf("Error creating report file.\n");
        return;
    }

    fprintf(file, "Fleet Management Report\n-------------------------\n");
    while (head) {
        fprintf(file, "Chassis: %s | Make: %s | Model: %s | Year: %d | Valuation: %.2lf\n",
            head->chassisNumber, head->make, head->model, head->year, head->valuation);
        head = head->next;
    }

    fclose(file);
    printf("Report generated successfully.\n");
}

void listByValuation(Machinery* head) {
    if (!head) {
        printf("No machinery data available.\n");
        return;
    }

    // Convert linked list to array
    int count = 0;
    Machinery* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }

    Machinery** machines = malloc(count * sizeof(Machinery*));
    temp = head;
    for (int i = 0; i < count; i++) {
        machines[i] = temp;
        temp = temp->next;
    }

    // Sort array by valuation
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (machines[j]->valuation < machines[j + 1]->valuation) {
                Machinery* swap = machines[j];
                machines[j] = machines[j + 1];
                machines[j + 1] = swap;
            }
        }
    }

    // Display sorted list
    printf("\n--- Machines Sorted by Valuation ---\n");
    for (int i = 0; i < count; i++) {
        printf("Chassis: %s | Make: %s | Valuation: %.2lf\n",
            machines[i]->chassisNumber, machines[i]->make, machines[i]->valuation);
    }

    free(machines);
}

// Function to authenticate user
int authenticateUser(Login* head) {
    char username[MAX_STRING], password[PASSWORD_LENGTH + 1];
    printf("Enter Username: ");
    scanf("%99s", username);
    printf("Enter Password: ");
    scanf("%6s", password);

    while (head) {
        if (strcmp(head->username, username) == 0 && strcmp(head->password, password) == 0) {
            printf("Login Successful!\n");
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void saveFleetData(Machinery* head) {
    FILE* file = fopen(FLEET_FILE, "w");
    if (!file) {
        printf("Error opening fleet file for writing.\n");
        return;
    }
    Machinery* temp = head;
    while (temp) {
        fprintf(file, "%s,%s,%s,%d,%.2lf,%.2lf,%d,%d,%s,%s,%s,%s,%s\n",
            temp->chassisNumber, temp->make, temp->model, temp->year, temp->cost,
            temp->valuation, temp->mileage, temp->nextServiceMileage,
            temp->ownerName, temp->ownerEmail, temp->ownerPhone,
            temp->machineType, temp->breakdowns);
        temp = temp->next;
    }
    fclose(file);
}

// Function to load login data from file
void loadLoginData(Login** head) {
    FILE* file = fopen(LOGIN_FILE, "r");
    if (!file) {
        printf("Error opening login file. No users loaded.\n");
        return;
    }

    while (!feof(file)) {
        Login* newLogin = (Login*)malloc(sizeof(Login));
        if (!newLogin) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }
        if (fscanf(file, "%s %s", newLogin->username, newLogin->password) == 2) {
            newLogin->next = *head;
            *head = newLogin;
        }
        else {
            free(newLogin);
        }
    }
    fclose(file);
}

// Function to load fleet data from file
void loadFleetData(Machinery** head) {
    FILE* file = fopen(FLEET_FILE, "r");
    if (!file) {
        printf("Error opening fleet file. No data loaded.\n");
        return;
    }

    while (!feof(file)) {
        Machinery* newMachine = (Machinery*)malloc(sizeof(Machinery));
        if (!newMachine) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }
        if (fscanf(file, "%99s %99s %99s %d %lf %lf %d %d %99s %99s %99s %99s %99s",
            newMachine->chassisNumber, newMachine->make, newMachine->model, &newMachine->year,
            &newMachine->cost, &newMachine->valuation, &newMachine->mileage, &newMachine->nextServiceMileage,
            newMachine->ownerName, newMachine->ownerEmail, newMachine->ownerPhone,
            newMachine->machineType, newMachine->breakdowns) == 13) {
            newMachine->next = *head;
            *head = newMachine;
        }
        else {
            free(newMachine);
        }
    }
    fclose(file);
}

void freeLoginData(Login* head) {
    while (head) {
        Login* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeFleetData(Machinery* head) {
    while (head) {
        Machinery* temp = head;
        head = head->next;
        free(temp);
    }
}

void menu(Machinery** fleetHead) {
    int choice;
    do {
        printf("\nFleet Management System\n");
        printf("1) Add Machine\n");
        printf("2) Display All Machines\n");
        printf("3) Display Machine Details\n");
        printf("4) Update Machine Details\n");
        printf("5) Delete Machine\n");
        printf("6) Generate Statistics\n");
        printf("7) Print Report\n");
        printf("8) List by Valuation\n");
        printf("9) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear input buffer

        switch (choice) {
        case 1: addMachine(fleetHead); break;
        case 2: displayAllMachines(*fleetHead); break;
        case 3: displayMachineDetails(*fleetHead); break;
        case 4: updateMachine(*fleetHead); break;
        case 5: deleteMachine(fleetHead); break;
        case 6: generateStatistics(*fleetHead); break;
        case 7: printReport(*fleetHead); break;
        case 8: listByValuation(*fleetHead); break;
        case 9: printf("Exiting...\n"); break;
        default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 9);
}

int main() {
    
}