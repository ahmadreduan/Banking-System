#define NUM_ADMIN_USERS 3
// Predefines admin usernames and passwords
const char *admin_usernames[NUM_ADMIN_USERS] = {"reduan", "asraful", "trisha"};
const char *admin_passwords[NUM_ADMIN_USERS] = {"23235016", "23235214", "23235292"};

/**
 * Handles the admin login process by verifying the provided credentials.
 * @return 1 if login is successful, 0 otherwise.
 */
int admin_login()
{
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];

    printf("Enter admin username : ");
    fgets(username, MAX_STRING_LENGTH, stdin);
    remove_newline(username);

    printf("Enter admin password : ");
    fgets(password, MAX_STRING_LENGTH, stdin);
    remove_newline(password);

    for (int i = 0; i < NUM_ADMIN_USERS; i++)
    {
        if (strcmp(username, admin_usernames[i]) == 0 && strcmp(password, admin_passwords[i]) == 0)
        {
            return 1; // successful login
        }
    }
    printf("Invalid username or password.\n");
    return 0; // Failed login
}