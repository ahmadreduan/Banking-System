#include "../banking_system.h"

#include "customer_fund_transfer.c"
#include "customer_transaction_history.c"
#include "customer_withdraw_fund_ATM.c"

/**
 * Handles the customer menu after successful login.
 */
void customer_menu_handle(const char *account_number)
{
    int choice;

    do
    {
        display_customer_options(); // Show the customer options
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the input buffer by scanf

        switch (choice)
        {
        case 1:
            // Call the function to view balance
            view_customer_balance(account_number);
            break;
        case 2:
            customer_fund_transfer(account_number); // Call the fund transfer function with the logged-in user's account number
            break;
        case 3:
        {
            withdraw_funds_ATM(account_number);
            break;
        }
        case 4:
        {
            int n;
            printf(BMAG "How many recent transactions would you like to see? " RESET);
            scanf("%d", &n);
            // int mul_n = n*6;
            //  Call the function to view transaction history
            customer_transaction_history(account_number, n);
            break;
        }
        case 5:
            printf(GREEN "Logging out...\n" RESET);
            break;
        default:
            printf(RED "Invalid choice. Please try again.\n" RESET);
        }
    } while (choice != 4); // Keep looping until the user chooses to logout
}

/**
 * Displays the balance of the  currently logged-in customer.
 * Uses the account number from the login process to read the balance from the respective file.
 * If the account file or balance information is not found, an error message is displayed.
 *
 * @param account_number The account number of the logged-in customer.
 */
void view_customer_balance(const char *account_number)
{

    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf(RED "No account found with the account number: %s\n" RESET, account_number);
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
        printf(GREEN "Current Balance: %.2lf\n" RESET, initial_deposit);
    }
    else
    {
        printf(RED "Error reading the account balance for account number: %s\n" RESET, account_number);
    }
}
