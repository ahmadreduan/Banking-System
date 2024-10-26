
#include "../banking_system.h"


void customer_fund_transfer(const char *sender_account_number) {
    char receiver_account_number[ACCOUNT_NUMBER_LENGTH + 1];
    double amount;
    char entered_pin[MAX_PIN_LENGTH];
    char stored_pin[MAX_PIN_LENGTH];
    int pin_found = 0;

    // Ask for receiver's account number
    printf(BBLU"Enter the receiver's account number: "RESET);
    fgets(receiver_account_number, sizeof(receiver_account_number), stdin);
    remove_newline(receiver_account_number);

    // Ask for the amount to transfer
    printf(BBLU"Enter the amount to transfer: "RESET);
    scanf("%lf", &amount);
    getchar(); // Consume the leftover newline character

    // Ask for the PIN
    printf(BGRN"Enter your PIN: ");
    fgets(entered_pin, sizeof(entered_pin), stdin);
    remove_newline(entered_pin);

    // Fetch sender's account details
    char sender_filename[150];
    snprintf(sender_filename, sizeof(sender_filename), "userdata/%s.txt", sender_account_number);
    FILE *sender_file = fopen(sender_filename, "r");
    if (sender_file == NULL) {
        printf(BRED"Sender account not found.\n"RESET);
        return;
    }

    char line[256];
    double sender_balance = 0;

    while (fgets(line, sizeof(line), sender_file) != NULL) {
        sscanf(line, "Initial Deposit: %lf", &sender_balance);
        sscanf(line, "Account Pin    : %s", stored_pin);
        
    }
    fclose(sender_file);

    // Validate the PIN
    if (strcmp(entered_pin, stored_pin) != 0) {
        printf(BRED"Incorrect PIN. Transfer failed.\n"RESET);
        return;
    }

    // Check if sender has enough balance
    if (sender_balance < amount) {
        printf(BGRN"Insufficient funds.\n"RESET);
        return;
    }

    // Fetch receiver's account details
    char receiver_filename[150];
    snprintf(receiver_filename, sizeof(receiver_filename), "userdata/%s.txt", receiver_account_number);
    FILE *receiver_file = fopen(receiver_filename, "r");
    if (receiver_file == NULL) {
        printf(BRED"Receiver account not found.\n"RESET);
        return;
    }

    double receiver_balance = 0;
    while (fgets(line, sizeof(line), receiver_file) != NULL) {
        sscanf(line, "Initial Deposit: %lf", &receiver_balance);
    }
    fclose(receiver_file);

    // Update balances
    sender_balance -= amount;
    receiver_balance += amount;

    // Update files with new balances
    update_account_balance(sender_account_number, sender_balance);
    update_account_balance(receiver_account_number, receiver_balance);

    // Log transactions
    log_transaction(sender_account_number, "Transfer Out", amount);
    log_transaction(receiver_account_number, "Transfer In", amount);

    printf(BGRN"Transfer successful! %.2lf has been transferred to %s.\n"RESET, amount, receiver_account_number);
}

void update_account_balance(const char *account_number, double new_balance) {
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf(BRED"Account file not found.\n"RESET);
        return;
    }

    char temp_filename[150];
    snprintf(temp_filename, sizeof(temp_filename), "userdata/temp_%s.txt", account_number);
    FILE *temp_file = fopen(temp_filename, "w");
    if (temp_file == NULL) {
        printf(BRED"Error creating temporary file.\n"RESET);
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Initial Deposit:") != NULL) {
            fprintf(temp_file, "Initial Deposit: %.2lf\n", new_balance);
        } else {
            fprintf(temp_file, "%s", line);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename(temp_filename, filename);
}

