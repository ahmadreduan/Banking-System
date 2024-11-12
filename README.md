# 🏦 Banking System Project

![Banking System](https://vunetsystems.com/wp-content/uploads/2023/12/IMG-32-1.png)

## Table of Contents

- [Introduction](#introduction)
- [Technologies](#technologies)
- [Setup](#setup)
- [Features](#features)
- [Scope of Functionalities](#scope-of-functionalities)
- [Code Examples](#code-examples)
- [Project Status](#project-status)
- [Sources](#sources)
- [Other Information](#other-information)

---

## Introduction

This **Banking System Project** is a command-line application written in C that simulates the essential functionalities of a banking system. It allows administrators to manage customer accounts, and customers can log in to view their balance or transfer funds. The project is designed to demonstrate file handling, data management, and user input validation in C.

---

## Features

The project includes the following features:

- **Admin Login**: Admins can log in to manage customer accounts.
- **Customer Registration**: New customer accounts can be created.
- **Balance Inquiry**: View the balance of a customer’s account.
- **Deposit Funds**: Admins can deposit funds into a customer’s account.
- **Fund Transfer**: Customers can transfer money to other accounts with proper validation.
- **Account Search**: Admins can search for accounts using account numbers.
- **Logout Functionality**: Admins and customers can securely log out.

---

```c
void display_banking_system_home_features()
{
    print_border();                                                     
    printf(BGRN "| 1. Admin Login                          |\n" RESET); 
    printf(BGRN "| 2. Customer Login                       |\n" RESET); 
    printf(BGRN "| 3. View Banking Rules                   |\n" RESET); 
    print_border();                                                     
}

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
    printf(BGRN "| 9. Exit                                 |\n" RESET); 
    print_border();                                                     
}

void display_customer_options()
{
    print_border();                                                     
    printf(BGRN "| 1. View Balance                         |\n" RESET); 
    printf(BGRN "| 2. Transfer Funds                       |\n" RESET); 
    printf(BGRN "| 3. View Transaction History             |\n" RESET); 
    printf(BGRN "| 4. Logout                               |\n" RESET);
    print_border();                                                    
}
```

## Scope of Functionalities

The project offers basic banking operations:

### Admin Functions:
- Register new accounts.
- Search for accounts by account number.
- View and update customer balances.

### Customer Functions:
- Log in with account number and PIN.
- Transfer funds to other accounts.
- View current balance.

---

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

## Technologies

This project was built using:

- **C Language**: For core logic and functionality.
- **GCC Compiler**: To compile the code.
- **Standard Library Functions**: Used for input/output operations such as `fgets`, `printf`, `fopen`.

This setup ensures that the project is lightweight and portable.

---


## Technologies

This project was built using:

- **C Language**: For core logic and functionality.
- **GCC Compiler**: To compile the code.
- **Standard Library Functions**: Used for input/output operations such as `fgets`, `printf`, `fopen`.

This setup ensures that the project is lightweight and portable.

---

## Setup

To run the banking system project, follow these steps:

### Prerequisites

- A C compiler (GCC, Clang, or another).
- Command-line interface (Terminal, Command Prompt, etc.).

### Instructions

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/ahmadreduan/banking-system.git
   cd banking-system
