/**
 * Displays the home features of the banking system with a border around the text.
 */
void display_banking_system_home_features()
{
    print_border();
    printf(BGRN "| 1. Admin Login                          |\n" RESET);
    printf(BGRN "| 2. Customer Login                       |\n" RESET);
    printf(BGRN "| 3. View Banking Rules                   |\n" RESET);
    print_border();
}

/**
 * Displays the banking system features with a border around the text.
 */
void display_banking_system_features()
{
    print_border();
    printf(BGRN "| 1. Register Account                     |\n" RESET);
    printf(BGRN "| 2. View Account Transaction             |\n" RESET);
    printf(BGRN "| 3. View Account Details                 |\n" RESET);
    printf(BGRN "| 4. Balance Check by Account Number      |\n" RESET);
    printf(BGRN "| 5. Deposit Funds                        |\n" RESET);
    printf(BGRN "| 6. Withdraw Funds                       |\n" RESET);
    printf(BGRN "| 7. Transfer Funds                       |\n" RESET);
    printf(BGRN "| 8. Close Account                        |\n" RESET);
    printf(BGRN "| 9. Update Account                       |\n" RESET);
    printf(BGRN "| 10. Exit                                |\n" RESET);
    print_border();
}

void display_customer_options()
{
    print_border();
    printf(BGRN "| 1. View Balance                         |\n" RESET);
    printf(BGRN "| 2. Transfer Funds                       |\n" RESET);
    printf(BGRN "| 3. Withdraw Funds ATM                   |\n" RESET);
    printf(BGRN "| 4. View Transaction History             |\n" RESET);
    printf(BGRN "| 5. Logout                               |\n" RESET);
    print_border();
}
