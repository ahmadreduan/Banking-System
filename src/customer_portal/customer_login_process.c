#include "../banking_system.h"


/**
 * Handles the customer login process by verifying the provided account number and password.
 * @param account_number_out A buffer to store the logged-in account number.
 * @return 1 if login is successful, 0 otherwise.
 */
int customer_login(char *account_number_out)
{
    char input_password[MAX_PASSWORD_LENGTH];
    char stored_password[MAX_PASSWORD_LENGTH];
    int password_found = 0;

    // Ask the user to input their account number
    printf(BGRN"Enter your account number: "RESET);
    fgets(account_number_out, ACCOUNT_NUMBER_LENGTH + 1, stdin);
    remove_newline(account_number_out);  // Remove newline from account number
    fflush(stdin);

    // Construct the filename based on the account number
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number_out);

    // Check if the account exists by trying to open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(BRED "No account found with account number: %s\n" RESET, account_number_out);
        return 0; // Failed login, no account found
    }

    // If account exists, read the stored password from the file
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "Password : %s", stored_password) == 1) {
            password_found = 1;
            break;
        }
    }

    fclose(file); // Close the file after reading

    // Ask the user to input their password
    if (password_found) {
        printf(BGRN"Enter your password: "RESET);
        fgets(input_password, sizeof(input_password), stdin);
        remove_newline(input_password); // Remove newline from input password
        fflush(stdin);

        // Compare the input password with the stored password
        if (strcmp(input_password, stored_password) == 0) {
            printf(GREEN "Login successful!\n" RESET);
            return 1; // Successful login
        } else {
            printf(RED "Invalid password.\n" RESET);
            return 0; // Failed login, wrong password
        }
    } else {
        printf(RED "Password not found in the account file.\n" RESET);
        return 0; // Failed login, no password found
    }
}