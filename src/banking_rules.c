#include "banking_system.h"

/**
 * Displays the banking rules for customers.
 */
void banking_rules()
{
    // Title of the system in bold cyan
    printf(BCYN "Welcome to the Bank Management System!\n\n" RESET);

    // Introductory text in bold yellow
    printf(BYEL "Here are the rules and guidelines for using our system:\n\n" RESET);

    // Individual rules printed in different styles for emphasis
    printf(BMAG "1. Ensure the accuracy of your personal information during account registration.\n" RESET);
    printf(BGRN "2. Keep your account credentials and PIN secure and do not share them with anyone.\n" RESET);
    printf(BMAG "3. Maintain a minimum balance in your account as per the bank's policy.\n" RESET);
    printf(BRED "4. Report any suspicious activities or unauthorized transactions to the bank immediately.\n" RESET);
    printf(BGRN "5. Follow the bank's guidelines for transactions, including transfer limits and withdrawal limits.\n" RESET);
    printf(BGRN "6. Keep your contact information up to date to receive important notifications.\n" RESET);
    printf(BMAG "7. If you have any questions or need assistance, please contact our customer support.\n" RESET);
}
