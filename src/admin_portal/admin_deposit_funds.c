#include "../banking_system.h"

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
        printf(BGRN "Insufficient funds in the branch account. Current balance: %.2lf\n" RESET, branch_balance);
        return; // শাখা অ্যাকাউন্টের ব্যালেন্স কম হলে ফাংশন 
    }

    // ব্যবহারকারীর অ্যাকাউন্টের ফাইলের নাম তৈরি
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf(BRED "No account found with the account number: %s\n" RESET, account_number);
        return;
    }

    // ফাইলের সমস্ত ডেটা মেমোরিতে লোড 
    char file_content[5000]; // ফাইলের আকার বড় হলে ডায়নামিক মেমোরি বরাদ্দ 
    char line[256];
    char updated_content[5000] = ""; // আপডেট হওয়া কনটেন্ট রাখার জন্য
    double initial_deposit = 0;
    int balance_updated = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // যদি "Initial Deposit" লাইন পাওয়া যায়
        if (sscanf(line, "Initial Deposit: %lf", &initial_deposit) == 1)
        {
            if (!balance_updated)
            {
                double deposit_amount;
                printf(BGRN "Current Balance: %.2lf\n" RESET, initial_deposit);
                printf(BBLU "Enter amount to deposit: " RESET);
                scanf("%lf", &deposit_amount);
                fflush(stdin);

                if (deposit_amount > 0)
                {
                    if (deposit_amount <= branch_balance)
                    {
                        initial_deposit += deposit_amount;
                        printf(BGRN "Deposit successful. New balance: %.2lf\n" RESET, initial_deposit);

                        // শাখার অ্যাকাউন্ট ব্যালেন্স আপডেট করুন
                        update_branch_account_balance(-deposit_amount);

                        // আপডেট করা ব্যালেন্স লাইন সংযুক্ত করুন
                        snprintf(line, sizeof(line), "Initial Deposit: %.2lf\n", initial_deposit);
                        balance_updated = 1;

                        // লেনদেন লগ করুন
                        log_transaction(account_number, "Deposit", deposit_amount);
                    }
                    else
                    {
                        printf(BRED "Insufficient funds in the branch account. Current balance: %.2lf\n" RESET, branch_balance);
                        fclose(file);
                        return;
                    }
                }
                else
                {
                    printf(BRED "Invalid deposit amount.\n" RESET);
                    fclose(file);
                    return;
                }
            }
        }
        // লাইনটি আপডেট করা হলে বা না হলে এটিকে কনটেন্টে যোগ করুন
        strcat(updated_content, line);
    }

    fclose(file);

    // ফাইলটি আবার লিখুন
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf(BRED "Error opening file for writing: %s\n" RESET, filename);
        return;
    }

    fputs(updated_content, file);
    fclose(file);
}
