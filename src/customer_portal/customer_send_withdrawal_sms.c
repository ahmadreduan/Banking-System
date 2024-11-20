#include "../banking_system.h"
// Function to send withdrawal SMS
void send_withdrawal_sms(const char *account_number, double withdrawal_amount, int atm_choice, double available_balance) {
    const char *atm_locations[] = {
        "Invalid Location",
        "Mirpur ATM",
        "Savar ATM",
        "Purbachol ATM",
        "Brahmanbaria ATM",
        "Natore ATM",
        "Ashulia ATM"
    };

    const char *atm_location = (atm_choice >= 1 && atm_choice <= 6) ? atm_locations[atm_choice] : "Unknown ATM";

    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%d.%m.%y %H:%M", local_time);

    char masked_account[20] = "****";
    strncat(masked_account, &account_number[strlen(account_number) - 4], 4);

    printf(BBLU"Dear User,\n");
    printf("Withdrawn %.2lf BDT\n", withdrawal_amount);
    printf("ATM/CRM: %s\n", atm_location);
    printf("at %s\n", time_str);
    printf("Account: %s\n", masked_account);
    printf("Avl Bal: %.2lf BDT\n", available_balance);
    printf("Help: 01538-363737\n"RESET);
    printf(BRED"Never Share Card no/OTP/PIN with anyone.\n"RESET);
}