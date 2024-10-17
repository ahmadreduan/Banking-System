#include"../banking_system.h"


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