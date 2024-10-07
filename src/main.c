#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>  // Add this for mkdir  Required for creating directories
#include <sys/types.h> // Also include this for POSIX systems
#include <ctype.h>
#include <windows.h>

// Regular text and style definitions as per your list
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

// Bold text definitions
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

// Reset color
#define RESET "\x1B[0m"

// ANSI escape codes for colors
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

#define ACCOUNT_NUMBER_LENGTH 8
#define ACCOUNT_START 232
#define MAX_STRING_LENGTH 100

#define NUM_ADMIN_USERS 3

#define BORDER_CHAR '*'
#define WIDTH 35

#define PHONE_PREFIX "+880"
#define PHONE_DIGITS 10
#define PHONE_LENGTH (strlen(PHONE_PREFIX) + PHONE_DIGITS + 1) // +1 for null terminator
#define MAX_PASSWORD_LENGTH 100
#define MAX_PIN_LENGTH 5 // 4 digits + null terminator


typedef struct
{
    char account_number[ACCOUNT_NUMBER_LENGTH + 1]; // 8 digits + null terminator
    char full_name[100];
    char dob[100]; // Date of birth in DD/MM/YYYY format
    char address[100];
    char phone[100];
    char email[100];
    char nid_or_birth_cert[100];
    char username[100];
    char password[100];
    char account_type[100];
    double initial_deposit;
    char pin[100];
    char nominee_name[100];
    char nominee_nid[100];
} User;

// Dynamic array to store users
User *users = NULL;
size_t user_count = 0;    // Current number of users
size_t user_capacity = 0; // Current allocated capacity of the users array

// Predefines admin usernames and passwords
const char *admin_usernames[NUM_ADMIN_USERS] = {"reduan", "asraful", "trisha"};
const char *admin_passwords[NUM_ADMIN_USERS] = {"23235016", "23235214", "23235292"};

/**
 * Generates a random account number starting from 232 and having a length of 8 digits.
 * @param account_number Pointer to a string where the generated account number will be stored.
 */
void generate_account_number(char *account_number)
{
    srand(time(NULL)); // Seed random number generator

    int random_part = rand() % 100000;                                           // Generate a random number between 00000 and 99999
    snprintf(account_number, ACCOUNT_NUMBER_LENGTH + 1, "232%05d", random_part); // Format as "232" followed by a 5-digit number
}

/**
 * Ensures that there is enough capacity in the users array to accommodate new users.
 * If the current capacity is insufficient, it reallocates the memory.
 * @param new_capacity The required capacity for the users array.
 */
void ensure_capacity(size_t new_capacity)
{
    if (new_capacity > user_capacity)
    {
        User *temp_users = realloc(users, new_capacity * sizeof(User));
        if (temp_users == NULL)
        {
            printf(BRED "Memory allocation failed!\n" RESET);
            exit(1);
        }
        users = temp_users;
        user_capacity = new_capacity; // Update user_capacity
    }
}

/**
 * Removes the newline character from the end of a string, if it exists.
 * @param str The string from which the newline character should be removed.
 */
void remove_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0'; // Replace newline with null terminator
    }
}
// Function to check if the input contains only alphabets
int is_valid_name(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        // Check if each character is either alphabetic or a space
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return 0; // Invalid if any character is not an alphabet or space
        }
    }
    return 1; // Valid if all characters are alphabets or spaces
}

// Function to check if a string contains only digits
int is_valid_digit(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; // Not a digit
        }
    }
    return 1; // All characters are digits
}

// Function to check if a given date is valid
int is_valid_date(int day, int month, int year)
{
    // Check for valid year
    if (year < 1900 || year > 2024)
    {
        return 0;
    }

    // Check for valid month
    if (month < 1 || month > 12)
    {
        return 0;
    }

    // Check for valid day based on month
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust for leap years
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
    {
        days_in_month[1] = 29; // February has 29 days in leap year
    }

    if (day < 1 || day > days_in_month[month - 1])
    {
        return 0; // Invalid day for the given month
    }

    return 1; // Date is valid
}

// Function to input and validate the Date of Birth
void input_and_validate_dob(char *dob)
{
    int day, month, year;

    while (1)
    {
        printf(BGRN "Enter date of birth (DD/MM/YYYY): " RESET);
        fgets(dob, 100, stdin);         // Read input
        dob[strcspn(dob, "\n")] = '\0'; // Remove newline character

        // Validate format (length should be 10: "DD/MM/YYYY")
        if (strlen(dob) != 10 || dob[2] != '/' || dob[5] != '/')
        {
            printf(BRED "Invalid format! Please enter the date in DD/MM/YYYY format.\n" RESET);
            continue;
        }

        // Extract day, month, year as strings
        char day_str[3] = {dob[0], dob[1], '\0'};
        char month_str[3] = {dob[3], dob[4], '\0'};
        char year_str[5] = {dob[6], dob[7], dob[8], dob[9], '\0'};

        // Validate if day, month, and year are digits
        if (!is_valid_digit(day_str) || !is_valid_digit(month_str) || !is_valid_digit(year_str))
        {
            printf(BRED "Invalid date! Please enter numeric values for day, month, and year.\n" RESET);
            continue;
        }

        // Convert day, month, year strings to integers
        day = atoi(day_str);
        month = atoi(month_str);
        year = atoi(year_str);

        // Validate the date itself (correct day, month, year)
        if (!is_valid_date(day, month, year))
        {
            printf(BRED "Invalid date! Please enter a valid date.\n" RESET);
            continue;
        }

        // If all validations pass, break out of the loop
        //  printf("Date of birth is valid: %02d/%02d/%d\n", day, month, year);
        break;
    }
}

// Function to validate Bangladeshi phone number format
int is_valid_phone(const char *phone)
{
    int length = strlen(phone);

    // Check if it starts with +8801 and is 14 characters long
    if (strncmp(phone, "+8801", 5) == 0 && length == 14)
    {
        return is_valid_digit(phone + 5); // Check if remaining part contains only digits
    }
    // Check if it starts with 01 and is 11 characters long
    else if (strncmp(phone, "01", 2) == 0 && length == 11)
    {
        return is_valid_digit(phone + 2); // Check if remaining part contains only digits
    }

    return 0; // Invalid phone number
}

// Function to validate email format
int is_valid_email(const char *email)
{
    const char *at_sign = strchr(email, '@');
    if (at_sign == NULL)
    {
        return 0; // No '@' character
    }

    // Ensure there's at least one dot after the '@'
    const char *dot = strchr(at_sign, '.');
    if (dot == NULL || dot == at_sign + 1)
    {
        return 0; // No dot, or dot is right after the '@'
    }

    // Check for valid characters before and after '@'
    if (at_sign == email || at_sign == email + strlen(email) - 1)
    {
        return 0; // '@' is the first or last character
    }

    // Ensure the domain part isn't too short
    if (strlen(dot + 1) < 2)
    {
        return 0; // The domain is too short (e.g. '@domain.c')
    }

    return 1; // Email is valid
}

// Function to validate password based on certain criteria
int is_valid_password(const char *password)
{
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;

    if (strlen(password) < 8)
    {
        return 0; // Password is too short
    }

    for (int i = 0; password[i] != '\0'; i++)
    {
        if (isupper(password[i]))
            has_upper = 1;
        else if (islower(password[i]))
            has_lower = 1;
        else if (isdigit(password[i]))
            has_digit = 1;
        else if (ispunct(password[i]))
            has_special = 1;
    }

    return has_upper && has_lower && has_digit && has_special;
}

// Function to validate the PIN (4-digit numeric input)
int is_valid_pin(const char *pin)
{
    if (strlen(pin) != 4)
    {
        return 0; // PIN is not exactly 4 digits
    }
    return is_valid_digit(pin); // Check if all characters are digits
}

// Function to clear the input buffer
void clear_input_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

/**
 * Registers a new account by collecting user information and saving it to a file.
 * The account number is generated and displayed only after all other information is collected.
 */
void register_account()
{
    ensure_capacity(user_count + 1); // Ensure enough capacity for new user

    User new_user;
    struct stat st; // Declare the stat structure
                    // Check if the directory 'userdata' exists, and if not, create it
    if (stat("userdata", &st) == -1)
    {
        if (mkdir("userdata", 0700) != 0)
        {
            perror(BRED "Error creating userdata directory" RESET);
            return;
        }
    }
    char first_name[50], last_name[50];

    while (1)
    {
        printf(BYEL "Enter first name                : " RESET);
        fgets(first_name, sizeof(first_name), stdin); // Read input
        remove_newline(first_name);                   // Remove newline

        if (is_valid_name(first_name))
        {
            // If the name is valid (contains only alphabets)
            // printf("First name entered: %s\n", first_name);
            break;
        }
        else
        {
            // If invalid input (contains numbers or special characters)
            printf(BRED "Invalid input! Please enter only alphabets.\n" RESET);
        }
    }

    // Input for last name with validation
    while (1)
    {
        printf(BYEL "Enter last name                 : " RESET);
        fgets(last_name, sizeof(last_name), stdin); // Read input
        remove_newline(last_name);                  // Remove newline

        if (is_valid_name(last_name))
        {
            // If the name is valid (contains only alphabets)
            break;
        }
        else
        {
            // If invalid input (contains numbers or special characters)
            printf(BRED "Invalid input! Please enter only alphabets.\n" BYEL);
        }
    }

    snprintf(new_user.full_name, sizeof(new_user.full_name), "%s %s", first_name, last_name);

    char dob[100];
    input_and_validate_dob(dob);

    // Input for Phone Number (Bangladeshi format: +8801XXXXXXXXX or 01XXXXXXXXX)
    while (1)
    {
        printf("Enter phone number (+8801XXXXXXXXX or 01XXXXXXXXX): ");
        fgets(new_user.phone, sizeof(new_user.phone), stdin);
        remove_newline(new_user.phone);

        if (is_valid_phone(new_user.phone))
        {
            break;
        }
        else
        {
            printf(BRED "Invalid input! Please enter a valid Bangladeshi phone number (e.g., +8801XXXXXXXXX or 01XXXXXXXXX).\n" RESET);
        }
    }

    // Input for Email Address (email format)
    while (1)
    {
        printf(BMAG "Enter email address: " RESET);
        fgets(new_user.email, sizeof(new_user.email), stdin);
        remove_newline(new_user.email);

        if (is_valid_email(new_user.email))
        {
            break;
        }
        else
        {
            printf(BRED "Invalid input! Please enter a valid email address.\n" RESET);
        }
    }

    // Username is set to the email
    strcpy(new_user.username, new_user.email);

    // Input for NID or Birth Certificate number (must be 10 or 13 digits)
    while (1)
    {
        printf(BBLU "Enter NID or Birth Certificate number (10 or 13 Digits): " RESET);
        fgets(new_user.nid_or_birth_cert, 13, stdin); // Reading up to 13 characters (including newline)
        remove_newline(new_user.nid_or_birth_cert);

        // Check if the input contains only digits and has a valid length
        int length = strlen(new_user.nid_or_birth_cert);

        if (is_valid_digit(new_user.nid_or_birth_cert) && (length == 10 || length == 13))
        {
            break; // Valid input (either 10 or 13 digits)
        }
        else
        {
            printf(BRED "Invalid input! Please enter exactly 10 or 13 digits.\n" RESET);
        }
    }

    char confirm_password[MAX_PASSWORD_LENGTH];
    // Input for Password (must meet security criteria and match the confirmation password)
    while (1)
    {
        printf(BGRN "Enter password: " RESET);
        fgets(new_user.password, sizeof(new_user.password), stdin);
        remove_newline(new_user.password);

        if (is_valid_password(new_user.password))
        {
            printf(BGRN "Confirm password: " RESET);
            fgets(confirm_password, sizeof(confirm_password), stdin);
            remove_newline(confirm_password);

            // Check if both passwords match
            if (strcmp(new_user.password, confirm_password) == 0)
            {
                printf(BGRN "Password accepted!\n" RESET);
                break;
            }
            else
            {
                printf(BRED "Passwords do not match! Please try again.\n" RESET);
            }
        }
        else
        {
            printf(BRED "Password must be at least 8 characters long, contain an uppercase letter, a lowercase letter, a digit, and a special character.\n" RESET);
        }
    }

    // Account type selection
    printf("\tSelect account type:\n");
    printf("\t01. Mudaraba Term Deposit\n");
    printf("\t02. Al-Wadiah Current Account\n");
    printf("\t03. Mudaraba Scheme Deposits\n");
    printf("\t04. Super Savings Account\n");
    printf("\t05. Waqf Deposit Account\n");
    printf("\t06. Mudaraba Savings Account\n");
    printf("\t07. Bai-salam (Pc)\n");
    printf("\t08. Mudaraba Bashsthan Savings Scheme\n");
    printf("\t09. Mudaraba Hajj Saving Scheme\n");
    printf("\t10. Student Account\n");

    int account_type_choice;
    printf("Enter the number corresponding to your account type: ");
    while (scanf("%d", &account_type_choice) != 1 || account_type_choice < 1 || account_type_choice > 10)
    {
        printf("Invalid choice. Please enter a number between 1 and 10: ");
        // while (getchar() != '\n'); // Clear the input buffer
        clear_input_buffer();
    }
    // getchar(); // Consume the leftover newline character
    clear_input_buffer();

    // Assign the chosen account type
    switch (account_type_choice)
    {
    case 1:
        strcpy(new_user.account_type, "Mudaraba Term Deposit");
        break;
    case 2:
        strcpy(new_user.account_type, "Al-Wadiah Current Account");
        break;
    case 3:
        strcpy(new_user.account_type, "Mudaraba Scheme Deposits");
        break;
    case 4:
        strcpy(new_user.account_type, "Super Savings Account");
        break;
    case 5:
        strcpy(new_user.account_type, "Waqf Deposit Account");
        break;
    case 6:
        strcpy(new_user.account_type, "Mudaraba Savings Account");
        break;
    case 7:
        strcpy(new_user.account_type, "Bai-salam (Pc)");
        break;
    case 8:
        strcpy(new_user.account_type, "Mudaraba Bashsthan Savings Scheme");
        break;
    case 9:
        strcpy(new_user.account_type, "Mudaraba Hajj Saving Scheme");
        break;
    case 10:
        strcpy(new_user.account_type, "Student Account");
        break;
    }

    printf("Enter initial deposit                : ");
    while (scanf("%lf", &new_user.initial_deposit) != 1)
    {
        printf("Invalid input. Please enter a valid amount: ");
        // while (getchar() != '\n'); // Clear the input buffer
        clear_input_buffer();
    }
    // getchar(); // Consume the leftover newline character
    clear_input_buffer();

    
    // Input for PIN (must be 4 digits and entered twice)
    char confirm_pin[MAX_PIN_LENGTH];
    // Input for PIN
    while (1)
    {
        printf("Enter 4-digit PIN: ");
        if (!fgets(new_user.pin, sizeof(new_user.pin), stdin))
        {
            printf("Error reading input.\n");
            continue;
        }
        remove_newline(new_user.pin);

        if (is_valid_pin(new_user.pin))
        {
            printf("Confirm PIN: ");
            if (!fgets(confirm_pin, sizeof(confirm_pin), stdin))
            {
                printf("Error reading input.\n");
                continue;
            }
            remove_newline(confirm_pin);

            if (strcmp(new_user.pin, confirm_pin) == 0)
            {
                printf("PIN accepted!\n");
                break;
            }
            else
            {
                printf("PINs do not match! Please try again.\n");
            }
        }
        else
        {
            printf("Invalid PIN! Please enter a 4-digit number.\n");
        }
    }

    // Input for nominee name with validation
    while (1)
    {
        printf("Enter nominee name: ");
        fgets(new_user.nominee_name, sizeof(new_user.nominee_name), stdin);
        remove_newline(new_user.nominee_name);

        if (is_valid_name(new_user.nominee_name))
        {
            printf("Nominee name accepted: %s\n", new_user.nominee_name);
            break; // Break the loop if the name is valid
        }
        else
        {
            printf("Invalid name! Please enter only alphabetic characters and spaces.\n");
        }
    }
    fflush(stdin);

    // Input for nominee NID with validation
    while (1)
    {
        printf("Enter nominee NID or Birth Certificate number (10 or 13 Digits): ");
        fgets(new_user.nominee_nid, 13, stdin); // Reading up to 13 characters (including newline)
        remove_newline(new_user.nominee_nid);

        // Check if the input contains only digits and has a valid length
        int length = strlen(new_user.nominee_nid);

        if (is_valid_digit(new_user.nominee_nid) && (length == 10 || length == 13))
        {
            break; // Valid input (either 10 or 13 digits)
        }
        else
        {
            printf("Invalid input! Please enter exactly 10 or 13 digits.\n");
        }
    }
    fflush(stdin);

    // Input for nominee NID with validation

    printf("Enter address (city, state, postal zip code, country): ");
    fgets(new_user.address, 100, stdin);
    remove_newline(new_user.address);

    generate_account_number(new_user.account_number);
    printf("Account Number: %s\n", new_user.account_number);

    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", new_user.account_number);
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Account Number : %s\n", new_user.account_number);
    fprintf(file, "Full Name      : %s\n", new_user.full_name);
    fprintf(file, "Date of Birth  : %s\n", new_user.dob);
    fprintf(file, "Mobile Number  : %s\n", new_user.phone);
    fprintf(file, "Email          : %s\n", new_user.email);
    fprintf(file, "NID            : %s\n", new_user.nid_or_birth_cert);
    fprintf(file, "User Name      : %s\n", new_user.username);
    fprintf(file, "Password       : %s\n", new_user.password);
    fprintf(file, "Account type   : %s\n", new_user.account_type);
    fprintf(file, "Initial Deposit: %.2lf\n", new_user.initial_deposit);
    fprintf(file, "Account Pin    : %s\n", new_user.pin);
    fprintf(file, "Nominee Name   : %s\n", new_user.nominee_name);
    fprintf(file, "Noninee NID    : %s\n", new_user.nominee_nid);
    fprintf(file, "Address        : %s\n", new_user.address);
    fprintf(file, "----------------------------------------\n"); // Separator for clarity

    fclose(file);

    users[user_count++] = new_user; // Add new user to the array
    printf("Account registered successfully.\n");
}

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
        printf("No account found with the account number: %s\n", account_number);
        return;
    }

    User temp_user;

    // Read user details from the file
    fscanf(file, "Account Number : %s\n", temp_user.account_number);
    fgets(temp_user.full_name, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.full_name);
    fgets(temp_user.dob, MAX_STRING_LENGTH, file);
    remove_newline(temp_user.dob);
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
    printf("\n\n+-----------------------------------------+\n");
    printf("| %s\n", temp_user.full_name);
    printf("+-----------------------------------------+\n");
    printf("| Account Number: %s                     \n", temp_user.account_number);
    printf("| %s                     \n", temp_user.dob);
    printf("| %s                     \n", temp_user.phone);
    printf("| %s                     \n", temp_user.email);
    printf("| %s                     \n", temp_user.account_type);
    printf("| Initial Deposit: %.2lf \n", temp_user.initial_deposit);
    printf("| %s                     \n", temp_user.nominee_name);
    printf("| %s                     \n", temp_user.nominee_nid);
    printf("| %s                     \n", temp_user.address);
    printf("+-----------------------------------------+\n");
}

void print_border()
{
    printf(BYEL "------------------------------------------\n" RESET);
}

/**
 * Displays the home features of the banking system with a border around the text.
 */
void display_banking_system_home_features()
{
    print_border();                                                     // Print top border
    printf(BBLU "| 1. Admin Login                          |\n" RESET); // Option 1: Admin Login (Bold Blue)
    printf(BGRN "| 2. Customer Login                       |\n" RESET); // Option 2: Customer Login (Bold Green)
    printf(BYEL "| 3. View Banking Rules                   |\n" RESET); // Option 3: View Banking Rules (Bold Yellow)
    print_border();                                                     // Print bottom border
}

/**
 * Displays the banking system features with a border around the text.
 */
void display_banking_system_features()
{
    print_border();                                                     // Print top border
    printf(BBLU "| 1. Register Account                     |\n" RESET); // Option 1: Register Account (Blue)
    printf(BGRN "| 2. View Account Details                 |\n" RESET); // Option 2: View Account Details (Green)
    printf(BYEL "| 3. Search Account by Account Number     |\n" RESET); // Option 3: Search Account (Yellow)
    printf(BBLU "| 4. Balance Check by Account Number      |\n" RESET); // Option 4: Balance Check (Blue)
    printf(BMAG "| 5. Deposit Funds                        |\n" RESET); // Option 5: Deposit Funds (Magenta)
    printf(BRED "| 6. Withdraw Funds                       |\n" RESET); // Option 6: Withdraw Funds (Red)
    printf(BGRN "| 7. Transfer Funds                       |\n" RESET); // Option 7: Transfer Funds (Green)
    printf(BRED "| 8. Exit                                 |\n" RESET); // Option 8: Exit (Red)
    print_border();                                                     // Print bottom border
}

void display_customer_options()
{
    print_border();                                                     // Print top border
    printf(BBLU "| 1. View Balance                         |\n" RESET); // Option 1: View Balance
    printf(BBLU "| 2. Transfer Funds                       |\n" RESET); // Option 2: Transfer Funds
    printf(BBLU "| 3. View Transaction History             |\n" RESET); // Option 3: View Transaction History
    printf(BBLU "| 4. Logout                               |\n" RESET); // Option 4: Logout
    print_border();                                                     // Print bottom border
}

/**Load users from the file */
void load_users_from_file()
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    User temp_user;
    char buffer[MAX_STRING_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (strncmp(buffer, "Account Number:", 15) == 0)
        {
            sscanf(buffer + 15, "%8s", temp_user.account_number);
            fgets(temp_user.full_name, MAX_STRING_LENGTH, file);
            remove_newline(temp_user.full_name);
            fgets(temp_user.dob, MAX_STRING_LENGTH, file);
            remove_newline(temp_user.dob);
            fgets(temp_user.address, MAX_STRING_LENGTH, file);
            remove_newline(temp_user.address);
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
            fgets(buffer, sizeof(buffer), file); // Read separator line

            // Add debug print
            printf("Loaded User: %s\n", temp_user.username);

            ensure_capacity(user_count + 1);
            users[user_count++] = temp_user;
        }
    }
    fclose(file);
}

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

/**
 * Handles the customer login process by verifying the provided credentials.
 * Allows login using account number, email, or username.
 * @return The index of the customer in the users array if login is successful, -1 otherwise.
 */
int customer_login()
{
    char input[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    int login_option;

    // Ask the user which option they'd like to use for login
    printf("Login with:\n");
    printf("1. Account Number\n");
    printf("2. Email\n");
    printf("3. Username\n");
    printf("Enter your choice: ");
    scanf("%d", &login_option);
    getchar(); // To consume the leftover newline character from scanf

    // Get the input based on the choice
    switch (login_option)
    {
    case 1:
        printf("Enter account number: ");
        fgets(input, MAX_STRING_LENGTH, stdin);
        remove_newline(input); // Removes newline character
        break;
    case 2:
        printf("Enter email: ");
        fgets(input, MAX_STRING_LENGTH, stdin);
        remove_newline(input); // Removes newline character
        break;
    case 3:
        printf("Enter username: ");
        fgets(input, MAX_STRING_LENGTH, stdin);
        remove_newline(input); // Removes newline character
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        return -1; // Return -1 to indicate login failure
    }

    // Ask for password
    printf("Enter password: ");
    fgets(password, MAX_STRING_LENGTH, stdin);
    remove_newline(password);

    // Search for the user in the users array
    for (size_t i = 0; i < user_count; i++)
    {
        // Check based on the login option
        if (((login_option == 1 && strcmp(input, users[i].account_number) == 0) ||
             (login_option == 2 && strcmp(input, users[i].email) == 0) ||
             (login_option == 3 && strcmp(input, users[i].username) == 0)) &&
            strcmp(password, users[i].password) == 0) // Check if password matches
        {
            // Successful login
            printf("\n\n\n");
            printf("+-----------------------------------------+\n");
            printf("| Login successful!                       |\n");
            printf("+-----------------------------------------+\n");
            printf("| Welcome, %s                  \n", users[i].full_name);
            printf("| Account Number: %s                  \n", users[i].account_number);
            printf("| Mobile Number: %s                  \n", users[i].phone);
            printf("+-----------------------------------------+\n");
            printf("\n");

            return i; // Return index of the user
        }
    }

    // If no match is found
    printf("Invalid credentials. Please try again.\n");
    return -1; // Return -1 to indicate login failure
}
void view_balance(size_t customer_index)
{
    printf("Your current balance is: %.2f Taka\n", users[customer_index].initial_deposit);
}

/**
 * Searches for and displays the initial deposit (balance) of a user based on the account number provided.
 * Reads the corresponding file from the "userdata" directory and extracts the initial deposit amount.
 * If the account file or balance information is not found, an error message is displayed.
 *
 * @param account_number_for_balance The account number whose balance is to be viewed.
 */

void search_and_view_balance(const char *account_number_for_balance)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number_for_balance);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No account found with the account number: %s\n", account_number_for_balance);
        return;
    }

    char line[256];
    double initial_deposit = 0;
    int found_balance = 0;

    // Read through each line in the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Check if the line contains "Initial Deposit"
        if (sscanf(line, "Initial Deposit: %lf", &initial_deposit) == 1)
        {
            found_balance = 1;
            break;
        }
    }

    fclose(file);

    if (found_balance)
    {
        printf("Initial Deposit: %.2lf\n", initial_deposit);
    }
    else
    {
        printf("Error reading the account balance for account number: %s\n", account_number_for_balance);
    }
}
/**
 * Searches for a user account based on the provided account number and allows deposit of funds.
 * Loads the account details from the corresponding file, retrieves the current balance,
 * prompts the user to enter a deposit amount, and updates the balance in the file.
 *
 * @param account_number_for_deposit_funds The account number to search for and deposit funds into.
 */
void deposit_funds(const char *account_number_for_deposit_funds)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number_for_deposit_funds);

    FILE *file = fopen(filename, "r+"); // Open in read+write mode to update balance
    if (file == NULL)
    {
        printf("No account found with the account number: %s\n", account_number_for_deposit_funds);
        return;
    }

    char line[256];
    double initial_deposit = 0;
    int found_balance = 0;
    long balance_pos = 0;

    // Search for "Initial Deposit" line and record its position
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &initial_deposit) == 1)
        {
            found_balance = 1;
            balance_pos = ftell(file); // Save the current position
            break;
        }
    }

    if (found_balance)
    {
        double deposit_amount;
        printf("Current Balance: %.2lf\n", initial_deposit);
        printf("Enter amount to deposit: ");
        scanf("%lf", &deposit_amount);
        // getchar(); // Consume newline character

        if (deposit_amount > 0)
        {
            initial_deposit += deposit_amount;
            printf("Deposit successful. New balance: %.2lf\n", initial_deposit);

            // Update the balance in the file
            fseek(file, balance_pos - strlen(line), SEEK_SET); // Move to the balance line
            // fflush(stdin);
            fprintf(file, "nitial Deposit: %.2lf\n", initial_deposit); // Overwrite the line with the new balance
        }
        else
        {
            printf("Invalid deposit amount.\n");
        }
    }
    else
    {
        printf("Error reading the account balance for account number: %s\n", account_number_for_deposit_funds);
    }

    fclose(file);
}

/**
 * Searches for a user account based on the provided account number and allows withdrawal of funds.
 * Loads the account details from the corresponding file, retrieves the current balance,
 * prompts the user to enter a withdrawal amount, and updates the balance in the file.
 *
 * @param account_number_for_withdraw_funds The account number to search for and withdraw funds from.
 */
void withdraw_funds(const char *account_number_for_withdraw_funds)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number_for_withdraw_funds);

    FILE *file = fopen(filename, "r+"); // Open the file in read+write mode to update balance
    if (file == NULL)
    {
        printf(RED "No account found with the account number: %s\n" RESET, account_number_for_withdraw_funds);
        return;
    }

    char line[256];
    double current_balance = 0;
    int found_balance = 0;
    long balance_pos = 0;

    // Search for "Initial Deposit" line and record its position
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &current_balance) == 1)
        {
            found_balance = 1;
            balance_pos = ftell(file); // Save the current position to update the balance later
            break;
        }
    }

    if (found_balance)
    {
        double withdrawal_amount;
        printf(GRN "Current Balance: %.2lf\n" RESET, current_balance);
        printf("Enter amount to withdraw: ");
        scanf("%lf", &withdrawal_amount);

        if (withdrawal_amount > 0 && withdrawal_amount <= current_balance)
        {
            current_balance -= withdrawal_amount;
            printf(GRN "Withdrawal successful. New balance: %.2lf\n" RESET, current_balance);

            // Update the balance in the file
            fseek(file, balance_pos - strlen(line), SEEK_SET);          // Move to the balance line
            fprintf(file, "Initial Deposit: %.2lf\n", current_balance); // Overwrite with new balance
        }
        else if (withdrawal_amount > current_balance)
        {
            printf(RED "Insufficient balance! Your current balance is: %.2lf\n" RESET, current_balance);
        }
        else
        {
            printf(RED "Invalid withdrawal amount.\n" RESET);
        }
    }
    else
    {
        printf(RED "Error reading the account balance for account number: %s\n" RESET, account_number_for_withdraw_funds);
    }

    fclose(file); // Close the file
}

int transfer_funds(size_t customer_index, double amount, const char *recipient_account, const char *pin)
{
    if (strcmp(pin, users[customer_index].pin) != 0)
    {
        printf("Invalid PIN.\n");
        return 0; // Transfer failed
    }
    if (amount <= 0)
    {
        printf("Invalid amount.\n");
        return 0; // Transfer failed
    }
    if (amount > users[customer_index].initial_deposit)
    {
        printf("Insufficient funds.\n");
        return 0; // Transfer failed
    }

    // Simulate fund transfer
    users[customer_index].initial_deposit -= amount;
    printf("Transferred %.2f Taka to account %s.\n", amount, recipient_account);
    printf("New balance: %.2f Taka\n", users[customer_index].initial_deposit);
    return 1; // Transfer successful
}

/**
 * Displays the banking rules for customers.
 */
void banking_rules()
{
    // Title of the system in bold cyan
    printf(BCYN "Welcome to the Bank Management System!\n\n" RESET);

    // Introductory text in bold yellow
    printf(BYEL "Here are the rules and guidelines for using our system:\n\n" RESET);

    // Individual rules printed in different styles for emphasis
    printf(BMAG "1. Ensure the accuracy of your personal information during account registration.\n" RESET);
    printf(BGRN "2. Keep your account credentials and PIN secure and do not share them with anyone.\n" RESET);
    printf(BMAG "3. Maintain a minimum balance in your account as per the bank's policy.\n" RESET);
    printf(BRED "4. Report any suspicious activities or unauthorized transactions to the bank immediately.\n" RESET);
    printf(BGRN "5. Follow the bank's guidelines for transactions, including transfer limits and withdrawal limits.\n" RESET);
    printf(BGRN "6. Keep your contact information up to date to receive important notifications.\n" RESET);
    printf(BMAG "7. If you have any questions or need assistance, please contact our customer support.\n" RESET);
}

int main()
{
    // Print the face with different colors
    printf(BLUE "                  *****   \n" RESET);
    printf(BLUE "                 *     *  \n" RESET);
    printf(YELLOW "                *  " BLUE "O O" YELLOW "  * \n" RESET);
    printf(YELLOW "                *   " RED "^" YELLOW "   * \n" RESET);
    printf(YELLOW "                *  " GREEN "\\_/" YELLOW "  * \n" RESET);
    printf(BLUE "                 *     *  \n" RESET);
    printf(BLUE "                  *****   \n" RESET);

    // Set color to CYAN for the border and YELLOW for the text inside
    printf(CYAN "********************************************\n" RESET);
    printf(CYAN "*" RESET "                                          " CYAN "*\n" RESET);
    printf(CYAN "*" RESET "  " YELLOW "  Welcome to the Banking System!  " RESET CYAN "*\n" RESET);
    printf(CYAN "*" RESET "                                          " CYAN "*\n" RESET);
    printf(CYAN "********************************************\n\n\n" RESET);

    // load_users_from_file(); // Load existing users from the file at the start

    int choice, logged_in = 0, customer_index = -1;
    while (1)
    {
        display_banking_system_home_features();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the leftover newline character from scanf

        switch (choice)
        {
        case 1: // Admin Login
            logged_in = admin_login();
            if (logged_in)
            {
                while (logged_in)
                {
                    display_banking_system_features();
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    getchar(); // To consume the leftover newline character from scanf

                    switch (choice)
                    {
                    case 1:
                        register_account();
                        break;
                    case 2:
                        if (customer_index != -1)
                        {
                            view_balance(customer_index);
                        }
                        else
                        {
                            printf("Please login as a customer first.\n");
                        }
                        break;
                    case 3: // Search Account by Account Number
                    {
                        char account_number[ACCOUNT_NUMBER_LENGTH + 1];
                        printf("Enter the account number: ");
                        fgets(account_number, ACCOUNT_NUMBER_LENGTH + 1, stdin);
                        remove_newline(account_number);
                        search_and_view_account(account_number);
                        break;
                    }
                    case 4:
                    {
                        char account_number_for_balance[ACCOUNT_NUMBER_LENGTH + 1];
                        printf("Enter the account number: ");
                        fgets(account_number_for_balance, ACCOUNT_NUMBER_LENGTH + 1, stdin);
                        remove_newline(account_number_for_balance);
                        search_and_view_balance(account_number_for_balance);
                        break;
                    }
                    case 5:
                    {
                        char account_number_for_deposit_funds[ACCOUNT_NUMBER_LENGTH + 1];
                        printf("Enter the account number: ");
                        fgets(account_number_for_deposit_funds, ACCOUNT_NUMBER_LENGTH + 1, stdin);
                        remove_newline(account_number_for_deposit_funds);
                        deposit_funds(account_number_for_deposit_funds);
                        break;
                    }
                    case 6:
                    {
                        char account_number_for_withdraw_funds[ACCOUNT_NUMBER_LENGTH + 1];
                        printf("Enter the account number: ");
                        fgets(account_number_for_withdraw_funds, ACCOUNT_NUMBER_LENGTH + 1, stdin);
                        remove_newline(account_number_for_withdraw_funds);
                        withdraw_funds(account_number_for_withdraw_funds);
                        break;
                    }

                    case 8:
                        logged_in = 0; // Logout
                        break;
                    default:
                        printf("Invalid choice.\n");
                    }
                }
            }
            break;
        case 2: // Customer Login
            customer_index = customer_login();
            logged_in = customer_index != -1;
            if (logged_in)
            {
                while (logged_in)
                {
                    display_customer_options();
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    getchar(); // To consume the leftover newline character from scanf

                    switch (choice)
                    {
                    case 1:
                        view_balance(customer_index);
                        break;
                    case 2:
                    {
                        double amount;
                        char recipient_account[ACCOUNT_NUMBER_LENGTH + 1];
                        char pin[MAX_STRING_LENGTH];

                        printf("Enter amount to transfer: ");
                        scanf("%lf", &amount);
                        getchar(); // To consume the leftover newline character from scanf

                        printf("Enter recipient account number: ");
                        fgets(recipient_account, ACCOUNT_NUMBER_LENGTH + 1, stdin);
                        remove_newline(recipient_account);

                        printf("Enter your PIN: ");
                        fgets(pin, MAX_STRING_LENGTH, stdin);
                        remove_newline(pin);

                        transfer_funds(customer_index, amount, recipient_account, pin);
                        break;
                    }
                    case 4:
                        logged_in = 0; // Logout
                        break;
                    default:
                        printf("Invalid choice.\n");
                    }
                }
            }
            break;
        case 3: // View Banking Rules
            banking_rules();
            break;
        default:
            printf("Invalid choice.\n");
        }
    }

    free(users); // Free allocated memory before exiting
    return 0;
}
