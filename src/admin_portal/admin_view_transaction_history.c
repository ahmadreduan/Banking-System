#include"../banking_system.h"

#define ADMIN_MAX_TRANSACTIONS 1000 // Maximum number of transactions expected
#define MAX_TRANSACTION_LENGTH 256 // Max length of each transaction line

void view_transaction_history() {
    char account_number[ACCOUNT_NUMBER_LENGTH + 1];
    int num_transactions;

    // Prompt the admin to enter the account number and number of recent transactions to view
    printf("Enter the account number: ");
    fgets(account_number, ACCOUNT_NUMBER_LENGTH + 1, stdin);
    remove_newline(account_number);

    printf("Enter the number of recent transactions to view: ");
    scanf("%d", &num_transactions);
    getchar(); // To consume the leftover newline character

    int mul_num_transactions = num_transactions*6;
    // Construct the filename from the account number
    char filename[150];
    snprintf(filename, sizeof(filename), "branch_transactions/%s_transactions.txt", account_number);

    // Open the transaction file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open transaction file for account %s.\n", account_number);
        return;
    }

    // Allocate memory for storing the last `num_transactions` lines
    char **transactions = (char **)malloc(mul_num_transactions * sizeof(char *));
    for (int i = 0; i < mul_num_transactions; i++) {
        transactions[i] = (char *)malloc(MAX_TRANSACTION_LENGTH * sizeof(char));
    }

    int transaction_count = 0;
    char line[MAX_TRANSACTION_LENGTH];
    
    // Read each line in a circular buffer style
    while (fgets(line, sizeof(line), file) != NULL) {
        // Free the memory for the current position and replace it with the new line
        free(transactions[transaction_count % mul_num_transactions]);
        transactions[transaction_count % mul_num_transactions] = strdup(line);
        transaction_count++;
    }
    fclose(file);

    // Display the most recent `num_transactions` in reverse order
    printf("\nRecent %d transaction(s) for account %s:\n", mul_num_transactions, account_number);
    int start_index = transaction_count > mul_num_transactions ? transaction_count % mul_num_transactions : 0;
    int count = transaction_count > mul_num_transactions ? mul_num_transactions : transaction_count;

    // Print in reverse order
    for (int i = count - 1; i >= 0; i--) {
        int index = (start_index + i) % mul_num_transactions;
        printf(BBLU"%s"RESET, transactions[index]);
    }

    // Free allocated memory for transactions
    for (int i = 0; i < mul_num_transactions; i++) {
        free(transactions[i]);
    }
    free(transactions);
}
