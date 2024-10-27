#include"../banking_system.h"

/**
 * Searches for a user account based on the provided account number and allows deposit of funds.
 * Loads the account details from the corresponding file, retrieves the current balance,
 * prompts the user to enter a deposit amount, and updates the balance in the file.
 *
 * @param account_number_for_deposit_funds The account number to search for and deposit funds into.
 */
void deposit_funds(const char *account_number)
{
    double branch_balance = get_branch_account_balance();
    if (branch_balance <= 0)
    {
        printf(BGRN"Insufficient funds in the branch account. Current balance: %.2lf\n"RESET, branch_balance);
        return; // Exit function if branch account balance is zero or negative
    }

    // Construct the filename for the user's account
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);// snprintf ফাংশনটি ব্যবহার করে একটি স্ট্রিং (string) তৈরি করা হচ্ছে যেখানে filename ভেরিয়েবলের মধ্যে একটি ফাইলের নাম সংরক্ষণ করা হবে।

    FILE *file = fopen(filename, "r+"); // Open in read+write mode to update balance
    if (file == NULL)
    {
        printf(BRED"No account found with the account number: %s\n"RESET, account_number);
        return;
    }

    char line[256];
    double initial_deposit = 0;
    long balance_pos = 0;

    // Search for "Initial Deposit" line and record its position
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &initial_deposit) == 1) // স্ট্রিং থেকে নির্দিষ্ট ফরম্যাট অনুযায়ী ডেটা পড়ার জন্য ব্যবহৃত হয়। sscanf একটি স্ট্রিংয়ের মধ্যে থেকে ভ্যারিয়েবলের ভ্যালু বের করে নেয়
        {
            balance_pos = ftell(file); // Save the current position for updating
            break;
        }
    }

    if (balance_pos != 0)
    { // If balance was found
        double deposit_amount;
        printf(BGRN"Current Balance: %.2lf\n"RESET, initial_deposit);
        printf(BBLU"Enter amount to deposit: "RESET);
        scanf("%lf", &deposit_amount);

        if (deposit_amount > 0)
        {
            // Check if there's enough balance in the branch account
            if (deposit_amount <= branch_balance)
            {
                initial_deposit += deposit_amount;
                printf(BGRN"Deposit successful. New balance: %.2lf\n"RESET, initial_deposit);

                // Update branch balance after subtracting deposit amount
                update_branch_account_balance(-deposit_amount);

                // Update the balance in the user's file
                fseek(file, balance_pos - strlen(line), SEEK_SET);         // Move to the balance line
                fprintf(file, "nitial Deposit: %.2lf", initial_deposit); // Overwrite the line with the new balance

                // Log the transaction
                log_transaction(account_number, "Deposit", deposit_amount);
            }
            else
            {
                printf(BRED"Insufficient funds in the branch account. Current balance: %.2lf\n"RESET, branch_balance);
            }
        }
        else
        {
            printf(BRED"Invalid deposit amount.\n"RESET);
        }
    }
    else
    {
        printf(BRED"Error reading the account balance for account number: %s\n"RESET, account_number);
    }

    fclose(file);
}