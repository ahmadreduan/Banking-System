#include "../banking_system.h"

double get_account_balance(const char *account_number) {
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf(BRED "Error: Could not open account file for reading.\n" RESET);
        return -1; // Return an error code
    }

    User temp_user;
    fscanf(file, "Account Number : %s\n", temp_user.account_number);
    fscanf(file, "Balance : %lf\n", &temp_user.balance); // Assuming this is the format in the file
    fclose(file);

    return temp_user.balance;
}
