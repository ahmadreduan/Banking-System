/**
 * Searches for and displays the initial deposit (balance) of a user based on the account number provided.
 * Reads the corresponding file from the "userdata" directory and extracts the initial deposit amount.
 * If the account file or balance information is not found, an error message is displayed.
 *
 * @param account_number_for_balance The account number whose balance is to be viewed.
 */

void search_and_view_balance(const char *account_number_for_balance)
{
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number_for_balance);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf(BRED"No account found with the account number: %s\n"RESET, account_number_for_balance);
        return;
    }

    char line[256];
    double initial_deposit = 0;
    int found_balance = 0;

    // Read through each line in the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Check if the line contains "Initial Deposit"
        if (sscanf(line, "Initial Deposit: %lf", &initial_deposit) == 1)
        {
            found_balance = 1;
            break;
        }
    }

    fclose(file);

    if (found_balance)
    {
        printf(BGRN"Initial Deposit: %.2lf\n"RESET, initial_deposit);
    }
    else
    {
        printf(BRED"Error reading the account balance for account number: %s\n"RESET, account_number_for_balance);
    }
}