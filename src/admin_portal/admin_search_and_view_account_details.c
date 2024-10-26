#include"../banking_system.h"
/**
 * Searches for a user account based on the provided account number.
 * Loads and displays the user details from the corresponding file.
 * @param account_number The account number to search for.
 */

void search_and_view_account(const char *account_number)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf(BRED"No account found with the account number: %s\n"RESET, account_number);
        return;
    }

    User temp_user;

    // Read user details from the file
    fscanf(file, "Account Number : %s\n", temp_user.account_number);
    fgets(temp_user.full_name, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.full_name);
    fgets(temp_user.date_of_birth, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.date_of_birth);
    fgets(temp_user.phone, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.phone);
    fgets(temp_user.email, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.email);
    fgets(temp_user.nid_or_birth_cert, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.nid_or_birth_cert);
    fgets(temp_user.username, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.username);
    fgets(temp_user.password, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.password);
    fgets(temp_user.account_type, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.account_type);
    fscanf(file, "Initial Deposit: %lf\n", &temp_user.initial_deposit);
    fgets(temp_user.pin, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.pin);
    fgets(temp_user.nominee_name, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.nominee_name);
    fgets(temp_user.nominee_nid, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.nominee_nid);
    fgets(temp_user.address, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.address);

    fclose(file);

    // Display the user details
    printf(BYEL"\n\n+-----------------------------------------+\n"RESET);
    printf(BGRN"| %s\n"RESET, temp_user.full_name);
    printf(BYEL"+-----------------------------------------+\n"RESET);
    printf(BGRN"| Account Number: %s                     \n"RESET, temp_user.account_number);
    printf(BBLU"| %s                     \n"RESET, temp_user.date_of_birth);
    printf(BBLU"| %s                     \n"RESET, temp_user.phone);
    printf(BBLU"| %s                     \n"RESET, temp_user.email);
    printf(BBLU"| %s                     \n"RESET, temp_user.account_type);
    printf(BBLU"| Initial Deposit: %.2lf \n"RESET, temp_user.initial_deposit);
    printf(BBLU"| %s                     \n"RESET, temp_user.nominee_name);
    printf(BBLU"| %s                     \n"RESET, temp_user.nominee_nid);
    printf(BBLU"| %s                     \n"RESET, temp_user.address);
    printf(BYEL"+-----------------------------------------+\n"RESET);
}