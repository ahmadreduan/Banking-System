#include "../banking_system.h"

void deleteAccount(const char *account_number)
{
    // Construct the paths for the account file and transaction file
    char accountFile[150];
    snprintf(accountFile, sizeof(accountFile), "userdata/%s.txt", account_number);

    char transactionFile[150];
    snprintf(transactionFile, sizeof(transactionFile), "branch_transactions/%s_transactions.txt", account_number);

    if (access(accountFile, F_OK) == -1)
    {
        printf("No account found with the account number: %s\n", account_number);
        return;
    }

    // Try to delete both files
    int accountFileDeleted = remove(accountFile);
    int transactionFileDeleted = remove(transactionFile);

    if (accountFileDeleted == 0 && transactionFileDeleted == 0)
    {
        printf("Account with account number %s and its transaction file have been successfully deleted.\n", account_number);
    }
    else
    {
        // Handle errors for each file individually
        if (accountFileDeleted != 0)
        {
            perror("Error deleting the account file");
        }
        if (transactionFileDeleted != 0)
        {
            perror("Error deleting the transaction file");
        }
        printf("Deletion process completed for account number: %s.\n", account_number);
    }
}
