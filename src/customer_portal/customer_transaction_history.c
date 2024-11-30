#include "../banking_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSACTION_LENGTH 256
#define TRANSACTION_BLOCK_SIZE 6 // Number of lines in a transaction block

void customer_transaction_history(const char *account_number, int num_transactions) {
    int mul_num_transactions = num_transactions * TRANSACTION_BLOCK_SIZE;

    // Construct the filename
    char filename[150];
    snprintf(filename, sizeof(filename), "branch_transactions/%s_transactions.txt", account_number);

    // Open the transaction file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open transaction file for account %s.\n", account_number);
        return;
    }

    // Allocate memory for storing the last `mul_num_transactions` lines
    char **transactions = (char **)malloc(mul_num_transactions * sizeof(char *));
    //**  2D dynamic array বা array of strings তৈরির জন্য ব্যবহৃত  double pointe

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
        //strdup() একটি স্ট্যান্ডার্ড লাইব্রেরি ফাংশন যা একটি স্ট্রিং-এর জন্য নতুন মেমোরি বরাদ্দ করে এবং সেই স্ট্রিংটি কপি করে।
        transaction_count++;
    }
    fclose(file);

    // Determine the number of lines to display
    int display_count = transaction_count > mul_num_transactions ? mul_num_transactions : transaction_count;
    int start_index = transaction_count > mul_num_transactions ? transaction_count % mul_num_transactions : 0;

    // Display the transactions in reverse order
    printf("\nRecent %d transaction(s) for account %s:\n", num_transactions, account_number);
    for (int i = display_count - 1; i >= 0; i--) {
        int index = (start_index + i) % mul_num_transactions;
        printf(BBLU"%s"RESET, transactions[index]);
    }

    // Free allocated memory
    for (int i = 0; i < mul_num_transactions; i++) {
        free(transactions[i]);
    }
    free(transactions);
}
