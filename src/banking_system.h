// banking_system.h

#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>  // for mkdir  Required for creating directories
#include <ctype.h> //পরীক্ষা করে  ডিজিট (0-9),বর্ণমালা (A-Z বা a-z), বড় হাতের (uppercase) অক্ষর  ছোট হাতের (lowercase) অক্ষর কিনা। 
#include <windows.h>  // For Windows Sleep()

#include <direct.h>



#define ACCOUNT_NUMBER_LENGTH 8
#define MAX_STRING_LENGTH 100

// Regular text and style definitions as per your list
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m" 
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
// Bold text definitions
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"
#define RESET "\x1B[0m" // Reset color
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

#define ACCOUNT_NUMBER_LENGTH 8
#define ACCOUNT_START 232
#define MAX_STRING_LENGTH 100

#define NUM_ADMIN_USERS 3

#define PHONE_PREFIX "+880"
#define PHONE_DIGITS 10
#define PHONE_LENGTH (strlen(PHONE_PREFIX) + PHONE_DIGITS + 1) // +1 for null terminator
#define MAX_PASSWORD_LENGTH 100
#define MAX_PIN_LENGTH 5 // 4 digits + null terminator
#define BRANCH_TRANSACTION_FILE "branch_transaction.txt"
#define BRANCH_ACCOUNT_FILE "branch_account.txt"


// User structure definition
typedef struct
{
    char account_number[ACCOUNT_NUMBER_LENGTH + 1];
    double balance;
    char full_name[100];
    char date_of_birth[11];
    char address[100];
    char phone[100];
    char email[100];
    char nid_or_birth_cert[14];
    char username[100];
    char password[100];
    char account_type[100];
    double initial_deposit;
    char pin[5]; // PIN is 4 digits + null terminator
    char nominee_name[100];
    char nominee_nid[100];
}User;


// Function prototypes for file operations
// Generates a random account number starting from 232 and having a length of 8 digits
void generate_account_number(char *account_number);

// Ensures that there is enough capacity in the users array to accommodate new users
void ensure_capacity(size_t new_capacity);

// Removes the newline character from the end of a string, if it exists
void remove_newline(char *str);

// Checks if the input contains only alphabets
int is_valid_name(const char *name);

// Checks if a string contains only digits
int is_valid_digit(const char *str);

// Checks if a given date is valid
int is_valid_date(int day, int month, int year);

// Inputs and validates the Date of Birth
void input_and_validate_dob(User *user);

// Validates Bangladeshi phone number format
int is_valid_phone(const char *phone);

// Validates email format
int is_valid_email(const char *email);

// Function prototype for logging transactions
void log_transaction(const char *account_number, const char *transaction_type, double amount);

// Function to validate password based on certain criteria
int is_valid_password(const char *password);

// Function to validate the PIN (4-digit numeric input)
int is_valid_pin(const char *pin);

// Function to clear the input buffer
void clear_input_buffer(void);

// Function to register a new account
void register_account(void);

// Function to search and view an account based on account number
void search_and_view_account(const char *account_number);

// Function to search and display balance based on account number
void search_and_view_balance(const char *account_number_for_balance);

// Function to deposit funds into a user account
void deposit_funds(const char *account_number);

// Function to withdraw funds from a user account
void withdraw_funds(const char *account_number);

// Function to log a transaction into the branch directory
void log_transaction_to_branch(const char *account_number, double amount);

// Function to transfer funds between accounts
// int transfer_funds(size_t customer_index, double amount, const char *recipient_account, const char *pin);
void transfer_funds(const char *source_account, const char *destination_account, double amount);

// Function to display banking rules for customers
void banking_rules(void);

// Function to print a border
void print_border(void);

// Function to display the home features of the banking system
void display_banking_system_home_features(void);

// Function to display the main features of the banking system
void display_banking_system_features(void);

// Function to display customer options after login
void display_customer_options(void);

// Function to handle the admin login process
int admin_login(void);

// Function to initialize the branch account with an initial balance
void initialize_branch_account(void);

// Function to get the balance of the Branch account
double get_branch_account_balance();

void log_transaction(const char *account_number, const char *transaction_type, double amount);
double read_branch_account_balance();

// Function to update the balance of the Branch account
void update_branch_account_balance(double amount);

void generate_transaction_id(char *id, int length);

void admin_transfer_funds(void);

void view_transaction_history(void);
void deleteAccount(const char *account_number);
void updateAccount(const char *account_number);


// Customer-related functions
int customer_login(char *account_number_out); // Handles customer login, stores logged-in account number
void customer_menu_handle(const char *account_number); // Handles customer menu after login
void view_customer_balance(const char *account_number); // Displays balance of the logged-in customer




void customer_fund_transfer(const char *sender_account_number);
void update_account_balance(const char *account_number, double new_balance);
void customer_transaction_history(const char *account_number,int n);

double get_account_balance(const char *account_number);
void log_transaction_atm(const char *account_number, const char *transaction_type, double amount, int atm_choice);
void withdraw_funds_ATM(const char *account_number);


void updateFullName(User *user);
void updateDateOfBirth(User *user);
void updatePhone(User *user);
void updateEmail(User *user);
void updateAddress(User *user);






#endif // BANKING_SYSTEM_H

