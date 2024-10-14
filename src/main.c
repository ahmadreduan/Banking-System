#include "banking_system.h" // Include the shared header file
// #include <direct.h> // For _mkdir
#define NUM_ADMIN_USERS 3
#include "usersite.c"
#include"banking_rules.c"
#include"deposit_funds.c"

// Dynamic array to store users
User *users = NULL;
size_t user_count;        // Current number of users
size_t user_capacity = 0; // Current allocated capacity of the users array

// Predefines admin usernames and passwords
const char *admin_usernames[NUM_ADMIN_USERS] = {"reduan", "asraful", "trisha"};
const char *admin_passwords[NUM_ADMIN_USERS] = {"23235016", "23235214", "23235292"};

int main()
{
    srand(time(NULL)); // Seed the random number generator with the current time
    // Initialize the branch account at the start
    initialize_branch_account(); // Ensure branch account is initialized
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
    printf(CYAN "*" RESET "  " YELLOW "*"
                "  Welcome to the Banking System!  " RESET CYAN "*\n" RESET);
    printf(CYAN "*" RESET "                                          " CYAN "*\n" RESET);
    printf(CYAN "********************************************\n\n\n" RESET);

    // load_users_from_file(); // Load existing users from the file at the start

    int choice, logged_in = 0, customer_index = -1;
    User user; // Declare the CUser struct for logged-in customer

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
                    // double balance = get_branch_account_balance();
                    // printf("Current branch account balance: %.2f\n", balance);
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
                    case 7:
                    {
                        admin_transfer_funds();
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

            if (customer_login() == 1)
            {
                // Successfully logged in, display customer options only
                return; // Exit the main menu
            }
            break;
        case 3:              // View Banking Rules
            banking_rules(); // Display banking rules
            break;
        default:
            printf("Invalid choice.\n");
        }
    }

    free(users); // Free allocated memory before exiting
    return 0;
}

/**
 * Displays the home features of the banking system with a border around the text.
 */
void display_banking_system_home_features()
{
    print_border();                                                     // Print top border
    printf(BGRN "| 1. Admin Login                          |\n" RESET); // Option 1: Admin Login (Bold Blue)
    printf(BGRN "| 2. Customer Login                       |\n" RESET); // Option 2: Customer Login (Bold Green)
    printf(BGRN "| 3. View Banking Rules                   |\n" RESET); // Option 3: View Banking Rules (Bold Yellow)
    print_border();                                                     // Print bottom border
}

/**
 * Displays the banking system features with a border around the text.
 */
void display_banking_system_features()
{
    print_border();                                                     // Print top border
    printf(BGRN "| 1. Register Account                     |\n" RESET); // Option 1: Register Account (Blue)
    printf(BGRN "| 2. View Account Details                 |\n" RESET); // Option 2: View Account Details (Green)
    printf(BGRN "| 3. Search Account by Account Number     |\n" RESET); // Option 3: Search Account (Yellow)
    printf(BGRN "| 4. Balance Check by Account Number      |\n" RESET); // Option 4: Balance Check (Blue)
    printf(BGRN "| 5. Deposit Funds                        |\n" RESET); // Option 5: Deposit Funds (Magenta)
    printf(BGRN "| 6. Withdraw Funds                       |\n" RESET); // Option 6: Withdraw Funds (Red)
    printf(BGRN "| 7. Transfer Funds                       |\n" RESET); // Option 7: Transfer Funds (Green)
    printf(BGRN "| 8. Exit                                 |\n" RESET); // Option 8: Exit (Red)
    print_border();                                                     // Print bottom border
}

void display_customer_options()
{
    print_border();                                                     // Print top border
    printf(BGRN "| 1. View Balance                         |\n" RESET); // Option 1: View Balance
    printf(BGRN "| 2. Transfer Funds                       |\n" RESET); // Option 2: Transfer Funds
    printf(BGRN "| 3. View Transaction History             |\n" RESET); // Option 3: View Transaction History
    printf(BGRN "| 4. Logout                               |\n" RESET); // Option 4: Logout
    print_border();                                                     // Print bottom border
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
void input_and_validate_dob(User *user)
{
    int day, month, year;
    char dob[11]; // Buffer for the date

    while (1)
    {
        printf(BGRN "Enter date of birth (DD/MM/YYYY): " RESET);
        fgets(dob, sizeof(dob), stdin); // Read input
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

        // Assign the validated date to the user struct
        snprintf(user->date_of_birth, sizeof(user->date_of_birth), "%s", dob);

        // If all validations pass, break out of the loop
        break;
    }
    fflush(stdin);
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

    // Input and validate date of birth
    input_and_validate_dob(&new_user);

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
        remove_newline(new_user.pin); // Remove newline from PIN input

        // Check if the PIN is valid (4 digits and numeric)
        if (is_valid_pin(new_user.pin))
        {
            printf("Confirm PIN: ");
            if (!fgets(confirm_pin, sizeof(confirm_pin), stdin))
            {
                printf("Error reading input.\n");
                continue;
            }
            remove_newline(confirm_pin); // Remove newline from confirmation PIN

            // Compare the two PINs
            if (strcmp(new_user.pin, confirm_pin) == 0)
            {
                printf("PIN accepted!\n");
                break; // Exit the loop if the PINs match
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
    fflush(stdin);

    // Input for nominee name with validation
    while (1)
    {
        printf("Enter nominee name: ");
        fgets(new_user.nominee_name, sizeof(new_user.nominee_name), stdin);
        remove_newline(new_user.nominee_name);

        if (is_valid_name(new_user.nominee_name))
        {
            // printf("Nominee name accepted: %s\n", new_user.nominee_name);
            break; // Break the loop if the name is valid
        }
        else
        {
            printf(BRED "Invalid name! Please enter only alphabetic characters and spaces.\n" RESET);
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
    fprintf(file, "Date of Birth  : %s\n", new_user.date_of_birth);
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
    printf("\n\n+-----------------------------------------+\n");
    printf("| %s\n", temp_user.full_name);
    printf("+-----------------------------------------+\n");
    printf("| Account Number: %s                     \n", temp_user.account_number);
    printf("| %s                     \n", temp_user.date_of_birth);
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

// Function to initialize the branch account
void initialize_branch_account()
{
    // Check if branch account file exists
    FILE *file = fopen(BRANCH_ACCOUNT_FILE, "r");
    if (file == NULL)
    {
        // Create a new branch account with an initial balance
        file = fopen(BRANCH_ACCOUNT_FILE, "w");
        if (file != NULL)
        {
            fprintf(file, "%.2f\n", 1000000000.00); // Set initial balance to 1 billion
            fclose(file);
            printf("Branch account initialized with balance: 1000000000.00\n");
        }
        else
        {
            printf("Error creating branch account file.\n");
        }
    }
    else
    {
        fclose(file);
        // printf("Branch account already exists.\n");
    }
}

// Function to read the current balance of the branch account
double read_branch_account_balance()
{
    FILE *file = fopen(BRANCH_ACCOUNT_FILE, "r");
    if (file == NULL)
    {
        printf("Error opening branch account file.\n");
        return 0.0; // Assuming 0 if the file can't be opened
    }
    double balance;
    if (fscanf(file, "%lf", &balance) != 1)
    {                  // Ensure successful read
        balance = 0.0; // Default to 0 if reading fails
    }
    fclose(file);
    return balance;
}

// Function to update the balance of the branch account
void update_branch_account_balance(double amount)
{
    double current_balance = read_branch_account_balance();
    double new_balance = current_balance + amount;

    FILE *file = fopen(BRANCH_ACCOUNT_FILE, "w");
    if (file != NULL)
    {
        fprintf(file, "%.2f\n", new_balance); // Write the new balance to the file
        fclose(file);
        printf("Branch account balance updated to: %.2f\n", new_balance);
    }
    else
    {
        printf("Error updating branch account balance.\n");
    }
}

// Function to get the branch account balance
double get_branch_account_balance()
{
    return read_branch_account_balance();
}



/**
 * Searches for a user account based on the provided account number and allows withdrawal of funds.
 * Loads the account details from the corresponding file, retrieves the current balance,
 * prompts the user to enter a withdrawal amount, and updates the balance in the file.
 * @param account_number_for_withdraw_funds The account number to search for and withdraw funds from.
 */
void withdraw_funds(const char *account_number)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r+"); // Open in read+write mode to update balance
    if (file == NULL)
    {
        printf("No account found with the account number: %s\n", account_number);
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
        printf("Current Balance: %.2lf\n", current_balance);
        printf("Enter amount to withdraw: ");
        scanf("%lf", &withdrawal_amount);

        if (withdrawal_amount > 0 && withdrawal_amount <= current_balance)
        {
            current_balance -= withdrawal_amount;
            printf("Withdrawal successful. New balance: %.2lf\n", current_balance);

            // Update the balance in the file
            fseek(file, balance_pos - strlen(line), SEEK_SET);         // Move to the balance line
            fprintf(file, "nitial Deposit: %.2lf\n", current_balance); // Overwrite with new balance

            // Update the branch account
            double branch_balance = get_branch_account_balance();
            branch_balance += withdrawal_amount; // Add to the branch account
            update_branch_account_balance(branch_balance);
            printf("Branch account updated. New balance: %.2lf\n", branch_balance);

            // Log the transaction
            log_transaction(account_number, "Withdrawal", withdrawal_amount);
        }
        else if (withdrawal_amount > current_balance)
        {
            printf("Insufficient balance! Your current balance is: %.2lf\n", current_balance);
        }
        else
        {
            printf("Invalid withdrawal amount.\n");
        }
    }
    else
    {
        printf("Error reading the account balance for account number: %s\n", account_number);
    }

    fclose(file); // Close the file
}
void admin_transfer_funds()
{
    char source_account[ACCOUNT_NUMBER_LENGTH + 1];
    char destination_account[ACCOUNT_NUMBER_LENGTH + 1];
    double amount;

    // Capture source account number
    printf("Enter the source account number: ");
    fgets(source_account, ACCOUNT_NUMBER_LENGTH + 1, stdin);
    fflush(stdin);

    // Capture destination account number
    printf("Enter the destination account number: ");
    fgets(destination_account, ACCOUNT_NUMBER_LENGTH + 1, stdin);
    fflush(stdin);

    // Capture transfer amount
    printf("Enter the amount to transfer: ");
    scanf("%lf", &amount);
    getchar(); // To consume the leftover newline character from scanf

    // Perform the transfer
    transfer_funds(source_account, destination_account, amount);
}

void transfer_funds(const char *source_account, const char *destination_account, double amount)
{
    char source_filename[150], destination_filename[150];
    FILE *source_file, *destination_file;
    double source_balance = 0, destination_balance = 0;
    char line[256];
    long source_balance_pos = 0, destination_balance_pos = 0;
    int source_balance_found = 0, destination_balance_found = 0;

    // Create file paths for source and destination accounts
    snprintf(source_filename, sizeof(source_filename), "userdata/%s.txt", source_account);
    snprintf(destination_filename, sizeof(destination_filename), "userdata/%s.txt", destination_account);

    // Open source account file
    source_file = fopen(source_filename, "r+");
    if (source_file == NULL)
    {
        printf("Error: Could not open source account file for account: %s\n", source_account);
        return;
    }

    // Open destination account file
    destination_file = fopen(destination_filename, "r+");
    if (destination_file == NULL)
    {
        printf("Error: Could not open destination account file for account: %s\n", destination_account);
        fclose(source_file); // Close source file since we're exiting
        return;
    }

    // Read the current balance from the source account file
    while (fgets(line, sizeof(line), source_file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &source_balance) == 1)
        {
            source_balance_pos = ftell(source_file); // Save the position of balance for updating later
            break;
        }
    }

    // Read the current balance from the destination account file
    while (fgets(line, sizeof(line), destination_file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &destination_balance) == 1)
        {
            destination_balance_pos = ftell(destination_file); // Save the position of balance for updating later
            break;
        }
    }

    // Check if there is enough balance in the source account for the transfer
    if (source_balance < amount)
    {
        printf("Error: Insufficient funds in source account. Current balance: %.2f\n", source_balance);
        fclose(source_file);
        fclose(destination_file);
        return;
    }

    // Update the balances
    source_balance -= amount;      // Deduct from source account
    destination_balance += amount; // Add to destination account

    // Update source account file with new balance
    fseek(source_file, source_balance_pos - strlen(line), SEEK_SET); // Go back to balance line
    fprintf(source_file, "Initial Deposit: %.2f\n", source_balance);

    // Update destination account file with new balance
    fseek(destination_file, destination_balance_pos - strlen(line), SEEK_SET); // Go back to balance line
    fprintf(destination_file, "Initial Deposit: %.2f\n", destination_balance);

    // Close the files
    fclose(source_file);
    fclose(destination_file);

    // Log the transaction for both accounts
    log_transaction(source_account, "Transfer Out", amount);
    log_transaction(destination_account, "Transfer In", amount);

    printf("Transfer successful! %.2f has been transferred from account %s to account %s.\n", amount, source_account, destination_account);
}

/**
 * Reads the current balance from the specified account file.
 * @param account_number The account number to read the balance from.
 * @return The current balance if found, -1 otherwise.
 */
double read_account_balance(const char *account_number)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return -1; // Return -1 if the file cannot be opened
    }

    char line[256];
    double current_balance = -1;

    // Search for "Initial Deposit" line and read the balance
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &current_balance) == 1)
        {
            break;
        }
    }

    fclose(file);
    return current_balance;
}

/**
 * Updates the account balance in the specified file.
 *
 * @param account_number The account number to update.
 * @param new_balance The new balance to be written.
 */
void update_account_balance(const char *account_number, double new_balance)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r+");
    if (file == NULL)
    {
        printf("Error opening account file: %s\n", filename);
        return;
    }

    char line[256];
    long balance_pos = 0;

    // Find the "Initial Deposit" line
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &new_balance) == 1)
        {
            balance_pos = ftell(file);
            break;
        }
    }

    // Update the balance
    if (balance_pos != 0)
    {
        fseek(file, balance_pos - strlen(line), SEEK_SET);
        fprintf(file, "Initial Deposit: %.2lf\n", new_balance);
    }

    fclose(file);
}

// Function to generate a random alphanumeric transaction ID
void generate_transaction_id(char *id, int length)
{
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++)
    {
        int key = rand() % (int)(sizeof(charset) - 1);
        id[i] = charset[key];
    }
    id[length] = '\0'; // Null-terminate the string
}

/**
 * Logs a transaction (withdrawal or deposit) to the specific branch transaction file.
 *
 * @param account_number The account number for which the transaction is being made.
 * @param transaction_type The type of transaction ("Deposit" or "Withdrawal").
 * @param amount The amount being transacted.
 */
void log_transaction(const char *account_number, const char *transaction_type, double amount)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "branch_transactions/%s_transactions.txt", account_number);

    // Open the transaction file in append mode
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening transaction file for account number: %s\n", account_number);
        return;
    }

    // Get the current date and time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Format the current date and time as a string
    char date_time[100];
    strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", t);

    // Generate a random transaction ID
    char id[13]; // Length 12 for the ID + 1 for null terminator
    generate_transaction_id(id, 12);

    // Write the transaction details to the file
    fprintf(file, "Account Number: %s\n", account_number);
    fprintf(file, "Transaction Type: %s\n", transaction_type);
    fprintf(file, "Amount: %.2lf\n", amount);
    fprintf(file, "Date: %s\n", date_time);
    fprintf(file, "Transaction ID: %s\n", id);
    fprintf(file, "----------------------------------------\n");

    fclose(file);
}

void log_transaction_to_branch(const char *account_number, double amount)
{
    // Directory for branch transactions
    char branch_dir[] = "branch_transactions/";

    // Create directory if it doesn't exist
    mkdir(branch_dir, 0777); // 0777 gives full permissions

    // Prepare the file name with the account number and timestamp
    char transaction_file[256];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    snprintf(transaction_file, sizeof(transaction_file), "%s%s_%04d-%02d-%02d_%02d-%02d-%02d.txt",
             branch_dir, account_number, tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec);

    // Open the file for writing
    FILE *file = fopen(transaction_file, "w");
    if (file == NULL)
    {
        printf("Error creating transaction log file.\n");
        return;
    }
}

