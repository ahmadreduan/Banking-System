#include "banking_system.h" // Include the shared header file

// Function to generate a random alphanumeric transaction ID
void generate_transaction_id(char *id, int length)
{
    const char charset[] = "KLFBCDG56789HIJU4TAEXYZ01VWMNOPQRS23";
    for (size_t i = 0; i < length; i++)
    {
        int key = rand() % (int)(sizeof(charset) - 1);
        id[i] = charset[key];
    }
    id[length] = '\0'; // Null-terminate the string
}


/**
 * Logs a transaction (withdrawal or deposit) to the specific branch transaction file.
 *
 * @param account_number The account number for which the transaction is being made.
 * @param transaction_type The type of transaction ("Deposit" or "Withdrawal").
 * @param amount The amount being transacted.
 */
void log_transaction(const char *account_number, const char *transaction_type, double amount)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "branch_transactions/%s_transactions.txt", account_number);

    // Open the transaction file in append mode
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf(BRED"Error opening transaction file for account number: %s\n"RESET, account_number);
        return;
    }

    // Get the current date and time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Format the current date and time as a string
    char date_time[100];
    strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", t);

    // Generate a random transaction ID
    char id[13]; // Length 12 for the ID + 1 for null terminator
    generate_transaction_id(id, 12);

    // Write the transaction details to the file
    fprintf(file, "Account Number: %s\n", account_number);
    fprintf(file, "Transaction Type: %s\n", transaction_type);
    fprintf(file, "Amount: %.2lf\n", amount);
    fprintf(file, "Date: %s\n", date_time);
    fprintf(file, "Transaction ID: %s\n", id);
    fprintf(file, "----------------------------------------\n");

    fclose(file);
}

void log_transaction_to_branch(const char *account_number, double amount)
{
    // Directory for branch transactions
    char branch_dir[] = "branch_transactions/";

    // Create directory if it doesn't exist
    _mkdir(branch_dir); // gives full permissions

    // Prepare the file name with the account number and timestamp
    char transaction_file[256];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    snprintf(transaction_file, sizeof(transaction_file), "%s%s_%04d-%02d-%02d_%02d-%02d-%02d.txt",
             branch_dir, account_number, tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec);

    // Open the file for writing
    FILE *file = fopen(transaction_file, "w");
    if (file == NULL)
    {
        printf(BRED"Error creating transaction log file.\n"RESET);
        return;
    }
}

