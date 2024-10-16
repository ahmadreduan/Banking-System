#include "banking_system.h"
#include "banking_system_display.c"
#include "admin_login_portal.c"
#include "admin_registration_account.c"
#include "usersite.c"
#include "admin_search_and_view_account_details.c"
#include "admin_search_and_view_balance.c"
#include "admin_deposit_funds.c"
#include "admin_withdraw_funds.c"
#include "admin_transfer_funds.c"
#include "generate_transaction_id.c"
#include "banking_rules.c"

int main()
{

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
                        srand(time(NULL)); // Seed the random number generator with the current time
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
                        printf(BLUE"Enter the account number: "RESET);
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

void view_balance(size_t customer_index)
{
    printf("Your current balance is: %.2f Taka\n", users[customer_index].initial_deposit);
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
