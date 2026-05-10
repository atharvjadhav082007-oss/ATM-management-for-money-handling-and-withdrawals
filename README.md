# ATM Management System

An ATM Management System in C is a simple project that performs banking operations like cash withdrawal, deposit, and balance checking. It uses basic C programming concepts such as functions, loops, conditions, and file handling to simulate ATM transactions securely.

## Features

- **User Authentication**: Login with account number and PIN
- **Balance Inquiry**: Check current account balance
- **Cash Withdrawal**: Withdraw money with validation
- **Deposit**: Add money to account
- **Transaction History**: View recent transactions
- **Account Management**: User profile and account details

## Project Structure

```
.
├── index.c           # Main ATM system implementation
├── Makefile          # Build configuration
├── README.md         # Project documentation
└── .gitignore        # Git ignore rules
```

## Compilation

Using GCC compiler:

```bash
gcc -o atm index.c
```

Or using Make:

```bash
make
```

## Usage

Run the compiled executable:

```bash
./atm
```

## Requirements

- C Compiler (GCC, Clang, or MSVC)
- Standard C Library
- Windows/Linux/macOS compatible

## Building

### Prerequisites

- GCC or any C compiler
- Make (optional, for Makefile usage)

### Build Commands

```bash
# Using GCC directly
gcc -o atm index.c -Wall -Wextra

# Using Make (if Makefile is present)
make
make clean     # Remove build files
```

## Technical Details

- **Language**: C
- **Standard**: C99 or later
- **File Handling**: For persistent data storage
- **Data Structures**: Structs for account management

## Author

Created by: Atharv Jadhav

## License

Open Source Project

## Contributing

Feel free to submit issues and enhancement requests!
