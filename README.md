# 🏦 Banking System

![Banking System](https://vunetsystems.com/wp-content/uploads/2023/12/IMG-32-1.png)

## Table of Contents
- [Introduction](#introduction)
- [Technologies](#technologies)
- [Setup](#setup)
- [Features](#features)
- [Scope of Functionalities](#scope-of-functionalities)
- [Code Examples](#code-examples)
- [Sources](#sources)
- [Other Information](#other-information)

---

## Introduction
This **Banking System Project** is a command-line application written in C, simulating the essential functionalities of a modern banking system. It supports account management, transaction processing, and secure authentication for both administrators and customers. The project demonstrates efficient file handling, data validation, and modular programming techniques.

---

## Features

### Core Features:
- **Admin Login**: Enables administrators to manage all customer accounts and transactions.
- **Customer Registration**: Allows new customers to register securely.
- **Balance Inquiry**: Customers can view their account balance.
- **Deposit Funds**: Admins can add funds to accounts.
- **Fund Transfer**: Customers can transfer money to other accounts with validation.
- **Account Search**: Admins can search for accounts by account number.
- **Transaction History**: View detailed transaction history for customer accounts.
- **Logout Functionality**: Ensures secure session management for both admins and customers.

### Admin-Specific Features:
1. Register new accounts.
2. View account transactions and details.
3. Manage customer account balances, deposits, and withdrawals.
4. Transfer funds between accounts.
5. Close accounts securely.
6. Update customer details.

### Customer-Specific Features:
1. Log in with account credentials.
2. View current balance.
3. Transfer funds.
4. View transaction history.
5. Logout securely.

---

## Technologies

This project was built using:
- **C Programming Language**: For implementing the core functionality.
- **GCC Compiler**: To compile and run the program.
- **Standard Library Functions**: Includes `fgets`, `printf`, `fopen`, and others for input/output and file handling.

This lightweight setup ensures portability and compatibility across various platforms.

---

## Setup

To set up and run the Banking System Project, follow these steps:

### Prerequisites:
- A C compiler like GCC or Clang.
- Command-line interface (Terminal, Command Prompt, etc.).

### Installation:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/ahmadreduan/banking-system.git
   cd banking-system
   ```
2. **Compile the Program**:
   ```bash
   gcc -o banking_system main.c
   ```
3. **Run the Program**:
   ```bash
   ./banking_system
   ```

---

## Scope of Functionalities

### Admin Functions:
- **Manage Accounts**: Create, update, and close customer accounts.
- **Transaction Oversight**: Deposit, withdraw, and transfer funds between accounts.
- **Search Accounts**: Locate accounts using unique account numbers.
- **Generate Reports**: Access transaction logs and account activity summaries.

### Customer Functions:
- **View Balance**: Check current account balance.
- **Transfer Funds**: Transfer money to other accounts securely.
- **ATM Withdrawals**: Handle secure cash withdrawals.
- **Transaction History**: Access past account activities and logs.

---

## Code Examples

### Display Home Features:
```c
void display_banking_system_home_features() {
    print_border();
    printf(BGRN "| 1. Admin Login                          |\n" RESET);
    printf(BGRN "| 2. Customer Login                       |\n" RESET);
    printf(BGRN "| 3. View Banking Rules                   |\n" RESET);
    print_border();
}
```

### Account Balance Inquiry:
```c
void search_and_view_balance(const char *account_number) {
    char filename[150];
    snprintf(filename, sizeof(filename), "userdata/%s.txt", account_number);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No account found with the account number: %s\n", account_number);
        return;
    }

    char line[256];
    double initial_deposit = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "Initial Deposit: %lf", &initial_deposit) == 1) {
            printf("Current Balance: %.2lf\n", initial_deposit);
            break;
        }
    }
    fclose(file);
}
```
---

## Sources
1. [Banking System Basics](https://en.wikipedia.org/wiki/Banking_system)
2. [C Programming File Handling](https://www.programiz.com/c-programming/c-file-handling)

---

## Other Information
This project is open-source and welcomes contributions. For more information or support, visit the [GitHub Repository](https://github.com/ahmadreduan/banking-system).

--- 
### Contributors:
- **Reduan Ahmad**
- **Asraful Alam**
- **Rukaiya Akther Trisha**
