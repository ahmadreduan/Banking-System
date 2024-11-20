#include "banking_system.h"
#include "banking_system_display.c"

#include "admin_portal/admin_login_portal.c"
#include "admin_portal/admin_deposit_funds.c"
#include "admin_portal/admin_registration_account.c"
#include "admin_portal/admin_transfer_funds.c"
#include "admin_portal/admin_search_and_view_account_details.c"
#include "admin_portal/admin_search_and_view_balance.c"
#include "admin_portal/admin_withdraw_funds.c"
#include "admin_portal/admin_view_transaction_history.c"
#include "admin_portal/admin_delete_Account.c"
#include "admin_portal/admin_account_update.c"

#include "generate_transaction_id.c"
#include "banking_rules.c"

#include "customer_portal/customer_menu_handle.c"
#include "customer_portal/customer_login_process.c"



int is_integer(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        /*isdigit একটি C স্ট্যান্ডার্ড লাইব্রেরির ফাংশন, যা নির্দিষ্ট কোনো ক্যারেক্টার ডিজিট (0-9)
         কিনা তা যাচাই করতে ব্যবহৃত হয়। এটি ctype.h হেডার ফাইলে থাকে।*/
        if (!isdigit(str[i]))
        {
            return 0; // False if any character is not a digit
        }
    }
    return 1; // True if all characters are digits
}

int main()
{

    // Initialize the branch account at the start
    initialize_branch_account(); // Ensure branch account is initialized
    printf(BRED "                  _________\n" RESET);
    printf(BBLU "                 /         \\\n" RESET);
    printf(BBLU "                /___________\\\n" RESET);
    printf(BBLU "                |           |\n" RESET);
    printf(BBLU "                |           |\n" RESET);
    printf(BGRN "               |||    $    |||\n" RESET);
    printf(BYEL "               |||         |||\n" RESET);
    printf(RED "               _|___________|_\n" RESET);

    // Set color to CYAN for the border and YELLOW for the text inside
    printf(CYAN "********************************************\n" RESET);
    printf(CYAN "*" RESET "                                          " CYAN "*\n" RESET);
    printf(CYAN "*" RESET " " CYAN "*"
                "    Welcome to the Banking System!  " RESET CYAN "  *"
                " *\n" RESET);
    printf(CYAN "*" RESET "                                          " CYAN "*\n" RESET);
    printf(CYAN "********************************************\n\n\n" RESET);

    int choice, logged_in = 0, customer_index = -1;
    User user;      // Declare the User struct for logged-in customer
    char input[10]; // Buffer to store user input as a string

    while (1)
    {
        display_banking_system_home_features();
        printf(BGRN "Enter your choice: " RESET);
        fgets(input, sizeof(input), stdin); // Read input as a string

        // Remove the newline character from input if it exists
        input[strcspn(input, "\n")] = 0;

        if (is_integer(input))
        {
            choice = atoi(input); // Convert valid input to integer | atoi একটি C স্ট্যান্ডার্ড লাইব্রেরির ফাংশন, যার পূর্ণরূপ "ASCII to Integer"
        }
        else
        {
            printf(BRED"Invalid choice. Please enter a number.\n"RESET);
            continue; // Skip to the next iteration if input is invalid
        }

        char account_number[ACCOUNT_NUMBER_LENGTH + 1]; // Buffer to store logged-in customer's account number

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
                        view_transaction_history();
                        break;
                    case 3: // Search Account by Account Number
                    {
                        char account_number[ACCOUNT_NUMBER_LENGTH + 1]; //+1 রাখা হয়েছে, কারণ স্ট্রিং-এর শেষে \0 (null terminator) রাখতে অতিরিক্ত এক বাইট প্রয়োজন হয়।
                        printf(BLUE "Enter the account number: " RESET);
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
                    {
                        char account_number_for_account_delete[ACCOUNT_NUMBER_LENGTH + 1];
                        printf("Enter the account number: ");
                        fgets(account_number_for_account_delete, ACCOUNT_NUMBER_LENGTH + 1, stdin);
                        remove_newline(account_number_for_account_delete);
                        deleteAccount(account_number_for_account_delete);
                    }
                    case 9:
                    {
                        char account_number_for_account_update[ACCOUNT_NUMBER_LENGTH + 1];
                        printf("Enter the account number: ");
                        fgets(account_number_for_account_update, ACCOUNT_NUMBER_LENGTH + 1, stdin);
                        remove_newline(account_number_for_account_update);
                        updateAccount(account_number_for_account_update);
                    }
                    case 10:
                        logged_in = 0; // Logout
                        break;
                    default:
                        printf("Invalid choice.\n");
                    }
                }
            }
            break;
        case 2: // Customer Login

            if (customer_login(account_number) == 1)
            {
                // Successfully logged in
                customer_menu_handle(account_number);
            }
            break;
        case 3:
            banking_rules(); // Display banking rules
            break;
        default:
            printf("Invalid choice.\n");
        }
    }

    free(users); // Free allocated memory before exiting
    return 0;
}

void print_border()
{
    printf(BYEL "------------------------------------------\n" RESET);
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
