#include "../banking_system.h"

void updateAccount(const char *account_number)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r+");
    if (file == NULL)
    {
        printf(BRED "No account found with the account number: %s\n" RESET, account_number);
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
    fgets(temp_user.pin, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.pin);
    fgets(temp_user.nominee_name, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.nominee_name);
    fgets(temp_user.nominee_nid, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.nominee_nid);
    fgets(temp_user.address, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.address);


    // Display the user details
    printf(BYEL "\n\n+-----------------------------------------+\n" RESET);
    printf(BBLU "| %s\n" RESET, temp_user.full_name);
    printf(BBLU "| Account Number: %s                     \n" RESET, temp_user.account_number);
    printf(BBLU "| %s                     \n" RESET, temp_user.date_of_birth);
    printf(BBLU "| %s                     \n" RESET, temp_user.phone);
    printf(BBLU "| %s                     \n" RESET, temp_user.email);
    printf(BBLU "| %s                     \n" RESET, temp_user.account_type);
    printf(BBLU "| %s                     \n" RESET, temp_user.nominee_name);
    printf(BBLU "| %s                     \n" RESET, temp_user.nominee_nid);
    printf(BBLU "| %s                     \n" RESET, temp_user.address);
    printf(BYEL "+-----------------------------------------+\n" RESET);

    // Update specific fields
    int choice;
    char input[MAX_STRING_LENGTH];

    do
    {
        printf(BYEL "\nSelect the field you want to update:\n" RESET);
        printf(BGRN "1. Full Name\n" RESET);
        printf(BGRN "2. Date of Birth\n" RESET);
        printf(BGRN "3. Phone\n" RESET);
        printf(BGRN "4. Email\n" RESET);
        printf(BGRN "5. Address\n" RESET);
        printf(BRED "0. Exit\n" RESET);
        printf(BGRN "Enter your choice: " RESET);
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice)
        {
        case 1:
            updateFullName(&temp_user);
            break;
        case 2:
            updateDateOfBirth(&temp_user);
            break;
        case 3:
            updatePhone(&temp_user);
            break;
        case 4:
            updateEmail(&temp_user);
            break;
        case 5:
           updateAddress(&temp_user);
            break;
        case 0:
            printf(BYEL "Exiting update menu.\n" RESET);
            break;
        default:
            printf(BRED "Invalid choice. Please try again.\n" RESET);
        }
    } while (choice != 0);

    
    fprintf(file, "Account Number : %s\n", temp_user.account_number);
    fprintf(file, "%s\n", temp_user.full_name);
    fprintf(file, "%s\n", temp_user.date_of_birth);
    fprintf(file, "%s\n", temp_user.phone);
    fprintf(file, "%s\n", temp_user.email);
    fprintf(file, "%s\n", temp_user.nid_or_birth_cert);
    fprintf(file, "%s\n", temp_user.username);
    fprintf(file, "%s\n", temp_user.password);
    fprintf(file, "%s\n", temp_user.account_type);
    fprintf(file, "%s\n", temp_user.pin);
    fprintf(file, "%s\n", temp_user.nominee_name);
    fprintf(file, "%s\n", temp_user.nominee_nid);
    fprintf(file, "%s\n", temp_user.address);

    fclose(file);

    printf(BGRN "Account details updated successfully.\n" RESET);
}


// Functions to update each field

void updateFullName(User *user)
{
    char input[MAX_STRING_LENGTH];
    printf("Enter new full name: ");
    fgets(input, sizeof(input), stdin);
    remove_newline(input);
    strncpy(user->full_name, input, MAX_STRING_LENGTH - 1);
   
}

void updateDateOfBirth(User *user)
{
    char input[MAX_STRING_LENGTH];
    printf("Enter new date of birth (DD/MM/YYYY): ");
    fgets(input, sizeof(input), stdin);
    remove_newline(input);
    strncpy(user->date_of_birth, input, MAX_STRING_LENGTH - 1);
   
}
void updatePhone(User *user)
{
    char input[MAX_STRING_LENGTH];
    printf("Enter new phone number: ");
    fgets(input, sizeof(input), stdin);
    remove_newline(input);
    strncpy(user->phone, input, MAX_STRING_LENGTH - 1);
    
}

void updateEmail(User *user)
{
    char input[MAX_STRING_LENGTH];
    printf("Enter new email: ");
    fgets(input, sizeof(input), stdin);
    remove_newline(input);
    strncpy(user->email, input, MAX_STRING_LENGTH - 1);
   
}

void updateAddress(User *user)
{
    char input[MAX_STRING_LENGTH];
    printf("Enter new address: ");
    fgets(input, sizeof(input), stdin);
    remove_newline(input);
    strncpy(user->address, input, MAX_STRING_LENGTH - 1);
   
}