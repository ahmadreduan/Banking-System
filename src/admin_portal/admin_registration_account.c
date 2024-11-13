#include "../banking_system.h"

// Dynamic array to store users
User *users = NULL;
size_t user_count;        // Current number of users
size_t user_capacity = 0; // Current allocated capacity of the users array
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
    size_t len = strlen(str);//size_t ডেটাটাইপটি একটি unsigned integer, যা সাধারণত স্ট্রিংয়ের দৈর্ঘ্য সংরক্ষণের জন্য ব্যবহৃত হয়।
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

        // Convert day, month, year strings to integers   স্ট্রিং থেকে ইনটিজারে রূপান্তর using atoi -> ASCII TO INTEGER
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
        if (_mkdir("userdata") != 0) // gives full permissions
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
        printf(BGRN "Enter phone number (+8801XXXXXXXXX or 01XXXXXXXXX): " RESET);
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
    printf(BBLU "\tSelect account type:\n" RESET);
    printf(BYEL "\t01. Mudaraba Term Deposit\n" RESET);
    printf(BYEL "\t02. Al-Wadiah Current Account\n" RESET);
    printf(BYEL "\t03. Mudaraba Scheme Deposits\n" RESET);
    printf(BYEL "\t04. Super Savings Account\n" RESET);
    printf(BYEL "\t05. Waqf Deposit Account\n" RESET);
    printf(BYEL "\t06. Mudaraba Savings Account\n" RESET);
    printf(BYEL "\t07. Bai-salam (Pc)\n" RESET);
    printf(BYEL "\t08. Mudaraba Bashsthan Savings Scheme\n" RESET);
    printf(BYEL "\t09. Mudaraba Hajj Saving Scheme\n" RESET);
    printf(BYEL "\t10. Student Account\n" RESET);

    int account_type_choice;
    printf(BBLU "Enter the number corresponding to your account type: " RESET);
    while (scanf("%d", &account_type_choice) != 1 || account_type_choice < 1 || account_type_choice > 10)
    {
        printf(BRED "Invalid choice. Please enter a number between 1 and 10: " RESET);
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

    printf(BCYN "Enter initial deposit                : " RESET);
    while (scanf("%lf", &new_user.initial_deposit) != 1)
    {
        printf(BRED "Invalid input. Please enter a valid amount: " RESET);
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
        printf(BMAG "Enter 4-digit PIN: " RESET);
        if (!fgets(new_user.pin, sizeof(new_user.pin), stdin))
        {
            printf(BRED "Error reading input.\n" RESET);
            continue;
        }
        fflush(stdin);
        // remove_newline(new_user.pin); // Remove newline from PIN input

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
                printf(BRED "PINs do not match! Please try again.\n" RESET);
            }
        }
        else
        {
            printf(BRED "Invalid PIN! Please enter a 4-digit number.\n" RESET);
        }
    }
    fflush(stdin);

    // Input for nominee name with validation
    while (1)
    {
        printf(BYEL "Enter nominee name: " RESET);
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
        printf(BYEL "Enter nominee NID or Birth Certificate number (10 or 13 Digits): " RESET);
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
            printf(BRED "Invalid input! Please enter exactly 10 or 13 digits.\n" RESET);
        }
    }
    fflush(stdin);

    // Input for nominee NID with validation

    printf(BGRN "Enter address (city, state, postal zip code, country): " RESET);
    fgets(new_user.address, 100, stdin);
    remove_newline(new_user.address);

    generate_account_number(new_user.account_number);
    printf(BMAG "Account Number: %s\n" RESET, new_user.account_number);

    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", new_user.account_number);
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        perror(BRED "Error opening file" RESET);
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
    printf(BGRN "Account registered successfully.\n" RESET);
}
