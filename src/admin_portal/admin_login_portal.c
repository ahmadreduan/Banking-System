#include <conio.h>  // For getch() on Windows
#include "../banking_system.h"


// Predefined admin usernames and passwords
const char *admin_usernames[NUM_ADMIN_USERS] = {"reduan", "asraful", "trisha"};
const char *admin_passwords[NUM_ADMIN_USERS] = {"23235016", "23235214", "23235292"};

/**
 * Handles the admin login process by verifying the provided credentials.
 * @return 1 if login is successful, 0 otherwise.
 */
int admin_login() {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    int i = 0;
    char ch;

    printf("Enter admin username : ");
    fgets(username, MAX_STRING_LENGTH, stdin);
    remove_newline(username);

    printf("Enter admin password : ");
    while ((ch = getch()) != '\r') {  // '\r' is Enter key in Windows
        if (ch == '\b') {  // Handle backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // Remove last '*'
            }
        } else if (i < MAX_STRING_LENGTH - 1) {  // Limit password length
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';  // Null-terminate the password
    printf("\n");  // Move to the next line after password input

    for (int j = 0; j < NUM_ADMIN_USERS; j++) {
        if (strcmp(username, admin_usernames[j]) == 0 && strcmp(password, admin_passwords[j]) == 0) {
            return 1;  // Successful login
        }
    }

    printf("Invalid username or password.\n");
    return 0;  // Failed login
}
