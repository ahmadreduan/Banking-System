
#include "../banking_system.h"
#include "customer_get_account_balance.c"
#include"customer_send_withdrawal_sms.c"


void withdraw_funds_ATM(const char *account_number)
{
    // Step 1: Display available ATMs
    print_border();
    printf(BGRN "| 1. Mirpur ATM\n" RESET);
    printf(BGRN "| 2. Savar ATM\n" RESET);
    printf(BGRN "| 3. Purbachol ATM\n" RESET);
    printf(BGRN "| 4. Brahmanbaria ATM\n" RESET);
    printf(BGRN "| 5. Natore ATM\n" RESET);
    printf(BGRN "| 6. Ashulia ATM\n" RESET);
    print_border();

    int atm_choice;
    printf(BGRN "Select ATM location (1-6): " RESET);
    scanf("%d", &atm_choice);

    // Validate the choice
    if (atm_choice < 1 || atm_choice > 6)
    {
        printf(BRED "Invalid ATM choice.\n" RESET);
        return;
    }

    // Step 2: Ask for withdrawal amount
    double withdrawal_amount;
    printf(BGRN "Enter amount to withdraw: " RESET);
    scanf("%lf", &withdrawal_amount);

    if (withdrawal_amount <= 0)
    {
        printf(BRED "Invalid withdrawal amount.\n" RESET);
        return;
    }

    // Step 3: Verify PIN
    char entered_pin[MAX_PIN_LENGTH];
    char stored_pin[MAX_PIN_LENGTH] = {0};

    printf(BGRN "Enter your PIN: " RESET);
    getchar(); // Clear leftover newline
    fgets(entered_pin, sizeof(entered_pin), stdin);
    remove_newline(entered_pin); // Remove trailing newline

    // Retrieve account details
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf(BRED "Account not found.\n" RESET);
        return;
    }

    char line[256];
    double current_balance = 0;
    int pin_found = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Parse balance
        if (sscanf(line, "Initial Deposit: %lf", &current_balance) == 1)
        {
            continue;
        }

        // Parse PIN
        if (sscanf(line, "Account Pin : %s", stored_pin) == 1)
        {
            pin_found = 1;
            continue;
        }
    }
    fclose(file);

    if (!pin_found)
    {
        printf(BRED "PIN not found in account file.\n" RESET);
        return;
    }

    // Compare entered PIN with stored PIN
    if (strcmp(entered_pin, stored_pin) != 0)
    {
        printf(BRED "Incorrect PIN.\n" RESET);
        return;
    }

    // Check if sufficient funds are available
    if (current_balance < withdrawal_amount)
    {
        printf(BRED "Insufficient funds. Your current balance is: %.2lf\n" RESET, current_balance);
        return;
    }

    // Step 4: Proceed with the withdrawal
    current_balance -= withdrawal_amount;

    // Update the user's balance
    update_account_balance(account_number, current_balance);

    // Log the transaction
    log_transaction_atm(account_number, "ATM Withdrawal", withdrawal_amount, atm_choice);

    // Step 5: Provide feedback to the user
    printf(BGRN "\nWithdrawal successful.\n" RESET);
    send_withdrawal_sms(account_number, withdrawal_amount, atm_choice, current_balance);
}
// Function to log transaction
void log_transaction_atm(const char *account_number, const char *transaction_type, double amount, int atm_choice)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "branch_transactions/%s_transactions.txt", account_number);

    FILE *file = fopen(filename, "a"); // Open file in append mode
    if (file == NULL)
    {
        printf(BRED "Error logging transaction.\n" RESET);
        return;
    }

    // Get current time for transaction logging
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[26];
    strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info); // Format the timestamp

    // Generate a random transaction ID
    char id[13]; // Length 12 for the ID + 1 for null terminator
    generate_transaction_id(id, 12);

    fprintf(file, "Transaction Type: %s\n", transaction_type);
    fprintf(file, "Amount: %.2lf\n", amount);
    fprintf(file, "ATM Location: ");
    switch (atm_choice)
    {
    case 1:
        fprintf(file, "Mirpur ATM\n");
        break;
    case 2:
        fprintf(file, "Savar ATM\n");
        break;
    case 3:
        fprintf(file, "Purbachol ATM\n");
        break;
    case 4:
        fprintf(file, "Brahmanbaria ATM\n");
        break;
    case 5:
        fprintf(file, "Natore ATM\n");
        break;
    case 6:
        fprintf(file, "Ashulia ATM\n");
        break;
    }
    fprintf(file, "Transaction ID: %s\n", id);
    fprintf(file, "Date and Time: %s\n", time_str);
    fprintf(file, "----------------------------------------\n");
    fclose(file);
}
