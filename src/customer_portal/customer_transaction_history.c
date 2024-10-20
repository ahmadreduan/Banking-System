#include"../banking_system.h"

#define TRANSACTION_LENGTH 256 // Maximum length of a transaction line
#define MAX_TRANSACTIONS 100    // Maximum number of transactions to store
void customer_transaction_history(const char *account_number, int n) {
    char filename[100];
    snprintf(filename, sizeof(filename), "branch_transactions/%s_transactions.txt", account_number);

    // Check if the directory exists
    struct stat st = {0};
    if (stat("branch_transactions", &st) == -1) {
        printf("Directory 'userdata' not found. Please create the directory first.\n");
        return;
    }

    // Open the transaction history file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(BRED"Unable to open transaction history file for account number: %s\n"RESET, account_number);
        return;
    }

    char transactions[MAX_TRANSACTIONS][TRANSACTION_LENGTH];
    int count = 0;

    // Read transactions from the file
    while (fgets(transactions[count], TRANSACTION_LENGTH, file) != NULL && count < MAX_TRANSACTIONS) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No transactions found.\n");
        return;
    }

    // Determine how many transactions to display
    int display_count = (count < n) ? count : n;
    printf("Displaying last %d transactions:\n", display_count);

    // Display the last N transactions
    for (int i = count - display_count; i < count; i++) {
        printf("%s", transactions[i]);
    }
}