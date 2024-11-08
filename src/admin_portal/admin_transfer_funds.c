#include"../banking_system.h"

void admin_transfer_funds()
{
    char source_account[ACCOUNT_NUMBER_LENGTH + 1];
    char destination_account[ACCOUNT_NUMBER_LENGTH + 1];
    double amount;

    // Capture source account number
    printf(BGRN"Enter the source account number: "RESET);
    fgets(source_account, ACCOUNT_NUMBER_LENGTH + 1, stdin);
    fflush(stdin);

    // Capture destination account number
    printf(BGRN"Enter the destination account number: "RESET);
    fgets(destination_account, ACCOUNT_NUMBER_LENGTH + 1, stdin);
    fflush(stdin);

    // Capture transfer amount
    printf(BGRN"Enter the amount to transfer: "RESET);
    scanf("%lf", &amount);
    getchar(); // To consume the leftover newline character from scanf

    // Perform the transfer
    transfer_funds(source_account, destination_account, amount);
}

void transfer_funds(const char *source_account, const char *destination_account, double amount)
{
    char source_filename[150], destination_filename[150];
    FILE *source_file, *destination_file;
    double source_balance = 0, destination_balance = 0;
    char line[256];
    long source_balance_pos = 0, destination_balance_pos = 0;
    int source_balance_found = 0, destination_balance_found = 0;

    // Create file paths for source and destination accounts
    snprintf(source_filename, sizeof(source_filename), "userdata/%s.txt", source_account);
    snprintf(destination_filename, sizeof(destination_filename), "userdata/%s.txt", destination_account);

    // Open source account file
    source_file = fopen(source_filename, "r+");
    if (source_file == NULL)
    {
        printf(BRED"Error: Could not open source account file for account: %s\n"RESET, source_account);
        return;
    }

    // Open destination account file
    destination_file = fopen(destination_filename, "r+");
    if (destination_file == NULL)
    {
        printf(BRED"Error: Could not open destination account file for account: %s\n"RESET, destination_account);
        fclose(source_file); // Close source file since we're exiting
        return;
    }

    // Read the current balance from the source account file
    while (fgets(line, sizeof(line), source_file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &source_balance) == 1)
        {
            source_balance_pos = ftell(source_file); // Save the position of balance for updating later
            break;
        }
    }

    // Read the current balance from the destination account file
    while (fgets(line, sizeof(line), destination_file) != NULL)
    {
        if (sscanf(line, "Initial Deposit: %lf", &destination_balance) == 1)
        {
            destination_balance_pos = ftell(destination_file); // Save the position of balance for updating later
            break;
        }
    }

    // Check if there is enough balance in the source account for the transfer
    if (source_balance < amount)
    {
        printf(BRED"Error: Insufficient funds in source account. Current balance: %.2f\n"RESET, source_balance);
        fclose(source_file);
        fclose(destination_file);
        return;
    }

    // Update the balances
    source_balance -= amount;      // Deduct from source account
    destination_balance += amount; // Add to destination account

    // Update source account file with new balance
    fseek(source_file, source_balance_pos - strlen(line), SEEK_SET); // Go back to balance line fseek এর কাজ হলো ফাইলের পজিশন কার্সরকে নির্দিষ্ট অবস্থানে সরানো, যাতে ফাইলের সেই অংশে নতুন ডেটা লেখা যায়।
    fprintf(source_file, "Initial Deposit: %.2f", source_balance);

    // Update destination account file with new balance
    fseek(destination_file, destination_balance_pos - strlen(line), SEEK_SET); // Go back to balance line
    fprintf(destination_file, "nitial Deposit: %.2f", destination_balance);

    // Close the files
    fclose(source_file);
    fclose(destination_file);

    // Log the transaction for both accounts
    log_transaction(source_account, "Transfer Out", amount);
    log_transaction(destination_account, "Transfer In", amount);

    printf(BGRN"Transfer successful! %.2f has been transferred from account %s to account %s.\n"RESET, amount, source_account, destination_account);
}
