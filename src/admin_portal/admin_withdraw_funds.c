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

    FILE *file = fopen(filename, "r+");
    if (file == NULL)
    {
        printf(BRED"No account found with the account number: %s\n"RESET, account_number);
        return;
    }

    char line[256];
    double current_balance = 0;
    int found_balance = 0;
    long balance_pos = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &current_balance) == 1)
        {
            found_balance = 1;
            balance_pos = ftell(file);
            break;
        }
    }

    if (found_balance)
    {
        double withdrawal_amount;
        printf(BBLU"Current Balance: %.2lf\n"RESET, current_balance);
        printf(BBLU"Enter amount to withdraw: "RESET);
        scanf("%lf", &withdrawal_amount);

        if (withdrawal_amount > 0 && withdrawal_amount <= current_balance)
        {
            current_balance -= withdrawal_amount;
            printf(BGRN"Withdrawal successful. New balance: %.2lf\n"RESET, current_balance);

            // Update user balance in the file
            fseek(file, balance_pos - strlen(line), SEEK_SET);
            fprintf(file, "nitial Deposit: %.2lf", current_balance);

            // Update branch account balance by adding withdrawal amount
            update_branch_account_balance(withdrawal_amount);
            printf(BMAG"Branch account updated. New balance: %.2lf\n"RESET, get_branch_account_balance());

            log_transaction(account_number, "Withdrawal", withdrawal_amount);
        }
        else if (withdrawal_amount > current_balance)
        {
            printf(BYEL"Insufficient balance! Your current balance is: %.2lf\n", current_balance);
        }
        else
        {
            printf(BRED"Invalid withdrawal amount.\n"RESET);
        }
    }
    else
    {
        printf(BRED"Error reading the account balance for account number: %s\n"RESET, account_number);
    }

    fclose(file);
}
