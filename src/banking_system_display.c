/**
 * Displays the home features of the banking system with a border around the text.
 */
void display_banking_system_home_features()
{
    print_border();                                                     // Print top border
    printf(BGRN "| 1. Admin Login                          |\n" RESET); // Option 1: Admin Login (Bold Blue)
    printf(BGRN "| 2. Customer Login                       |\n" RESET); // Option 2: Customer Login (Bold Green)
    printf(BGRN "| 3. View Banking Rules                   |\n" RESET); // Option 3: View Banking Rules (Bold Yellow)
    print_border();                                                     // Print bottom border
}

/**
 * Displays the banking system features with a border around the text.
 */
void display_banking_system_features()
{
    print_border();                                                     // Print top border
    printf(BGRN "| 1. Register Account                     |\n" RESET); // Option 1: Register Account (Blue)
    printf(BGRN "| 2. View Account Details                 |\n" RESET); // Option 2: View Account Details (Green)
    printf(BGRN "| 3. Search Account by Account Number     |\n" RESET); // Option 3: Search Account (Yellow)
    printf(BGRN "| 4. Balance Check by Account Number      |\n" RESET); // Option 4: Balance Check (Blue)
    printf(BGRN "| 5. Deposit Funds                        |\n" RESET); // Option 5: Deposit Funds (Magenta)
    printf(BGRN "| 6. Withdraw Funds                       |\n" RESET); // Option 6: Withdraw Funds (Red)
    printf(BGRN "| 7. Transfer Funds                       |\n" RESET); // Option 7: Transfer Funds (Green)
    printf(BGRN "| 8. Exit                                 |\n" RESET); // Option 8: Exit (Red)
    print_border();                                                     // Print bottom border
}

void display_customer_options()
{
    print_border();                                                     // Print top border
    printf(BGRN "| 1. View Balance                         |\n" RESET); // Option 1: View Balance
    printf(BGRN "| 2. Transfer Funds                       |\n" RESET); // Option 2: Transfer Funds
    printf(BGRN "| 3. View Transaction History             |\n" RESET); // Option 3: View Transaction History
    printf(BGRN "| 4. Logout                               |\n" RESET); // Option 4: Logout
    print_border();                                                     // Print bottom border
}
