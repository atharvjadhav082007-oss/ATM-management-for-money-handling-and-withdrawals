#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ACCOUNTS 100
#define PIN_LENGTH 4
#define MAX_TRANSACTIONS 50

// Structure to store transaction details
typedef struct
{
    char type[20]; // "Deposit" or "Withdrawal"
    double amount;
    time_t timestamp;
} Transaction;

// Structure to store account details
typedef struct
{
    int accountNumber;
    char pin[PIN_LENGTH + 1];
    double balance;
    char accountHolder[50];
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
} Account;

// Global array to store accounts
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;
Account *currentUser = NULL;

// Function prototypes
void initializeAccounts();
void displayMainMenu();
void displayUserMenu();
int authenticate();
void displayBalance();
void withdrawCash();
void depositCash();
void viewTransactionHistory();
void addTransaction(const char *type, double amount);
void displayAccountDetails();

// Initialize sample accounts
void initializeAccounts()
{
    // Account 1
    accounts[0].accountNumber = 1001;
    strcpy(accounts[0].pin, "1234");
    strcpy(accounts[0].accountHolder, "John Doe");
    accounts[0].balance = 5000.00;
    accounts[0].transactionCount = 0;

    // Account 2
    accounts[1].accountNumber = 1002;
    strcpy(accounts[1].pin, "5678");
    strcpy(accounts[1].accountHolder, "Jane Smith");
    accounts[1].balance = 3000.00;
    accounts[1].transactionCount = 0;

    // Account 3
    accounts[2].accountNumber = 1003;
    strcpy(accounts[2].pin, "9999");
    strcpy(accounts[2].accountHolder, "Bob Wilson");
    accounts[2].balance = 7500.50;
    accounts[2].transactionCount = 0;

    accountCount = 3;
}

// Display main menu before authentication
void displayMainMenu()
{
    printf("\n");
    printf("========================================\n");
    printf("      ATM MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

// Display menu for authenticated user
void displayUserMenu()
{
    printf("\n");
    printf("========================================\n");
    printf("      WELCOME TO ATM\n");
    printf("========================================\n");
    printf("1. Check Balance\n");
    printf("2. Withdraw Cash\n");
    printf("3. Deposit Cash\n");
    printf("4. View Transaction History\n");
    printf("5. View Account Details\n");
    printf("6. Logout\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

// Authenticate user
int authenticate()
{
    int accountNum;
    char pin[PIN_LENGTH + 1];
    int attempts = 3;

    printf("\n========================================\n");
    printf("      LOGIN\n");
    printf("========================================\n");

    while (attempts > 0)
    {
        printf("Enter Account Number: ");
        scanf("%d", &accountNum);
        getchar(); // consume newline

        printf("Enter PIN: ");
        fgets(pin, sizeof(pin), stdin);
        pin[strcspn(pin, "\n")] = 0; // remove newline

        // Check credentials
        for (int i = 0; i < accountCount; i++)
        {
            if (accounts[i].accountNumber == accountNum &&
                strcmp(accounts[i].pin, pin) == 0)
            {
                currentUser = &accounts[i];
                printf("\nLogin successful! Welcome %s\n", currentUser->accountHolder);
                return 1;
            }
        }

        attempts--;
        printf("\nInvalid credentials. Attempts remaining: %d\n", attempts);
    }

    printf("\nToo many failed attempts. Access denied.\n");
    return 0;
}

// Display account balance
void displayBalance()
{
    printf("\n========================================\n");
    printf("      ACCOUNT BALANCE\n");
    printf("========================================\n");
    printf("Account Holder: %s\n", currentUser->accountHolder);
    printf("Account Number: %d\n", currentUser->accountNumber);
    printf("Current Balance: $%.2f\n", currentUser->balance);
    printf("========================================\n");
}

// Withdraw cash
void withdrawCash()
{
    double amount;

    printf("\n========================================\n");
    printf("      CASH WITHDRAWAL\n");
    printf("========================================\n");
    printf("Current Balance: $%.2f\n", currentUser->balance);
    printf("Enter amount to withdraw: $");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    if (amount > currentUser->balance)
    {
        printf("Insufficient funds. Cannot withdraw.\n");
        return;
    }

    currentUser->balance -= amount;
    addTransaction("Withdrawal", amount);
    printf("\nWithdrawal successful!\n");
    printf("New Balance: $%.2f\n", currentUser->balance);
}

// Deposit cash
void depositCash()
{
    double amount;

    printf("\n========================================\n");
    printf("      CASH DEPOSIT\n");
    printf("========================================\n");
    printf("Current Balance: $%.2f\n", currentUser->balance);
    printf("Enter amount to deposit: $");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    currentUser->balance += amount;
    addTransaction("Deposit", amount);
    printf("\nDeposit successful!\n");
    printf("New Balance: $%.2f\n", currentUser->balance);
}

// Add transaction record
void addTransaction(const char *type, double amount)
{
    if (currentUser->transactionCount < MAX_TRANSACTIONS)
    {
        strcpy(currentUser->transactions[currentUser->transactionCount].type, type);
        currentUser->transactions[currentUser->transactionCount].amount = amount;
        currentUser->transactions[currentUser->transactionCount].timestamp = time(NULL);
        currentUser->transactionCount++;
    }
}

// View transaction history
void viewTransactionHistory()
{
    printf("\n========================================\n");
    printf("      TRANSACTION HISTORY\n");
    printf("========================================\n");

    if (currentUser->transactionCount == 0)
    {
        printf("No transactions yet.\n");
        return;
    }

    printf("%-15s %-10s %-25s\n", "Type", "Amount", "Date & Time");
    printf("----------------------------------------\n");

    for (int i = 0; i < currentUser->transactionCount; i++)
    {
        char timeStr[50];
        struct tm *timeinfo = localtime(&currentUser->transactions[i].timestamp);
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

        printf("%-15s $%-9.2f %-25s\n",
               currentUser->transactions[i].type,
               currentUser->transactions[i].amount,
               timeStr);
    }
    printf("========================================\n");
}

// Display account details
void displayAccountDetails()
{
    printf("\n========================================\n");
    printf("      ACCOUNT DETAILS\n");
    printf("========================================\n");
    printf("Account Holder: %s\n", currentUser->accountHolder);
    printf("Account Number: %d\n", currentUser->accountNumber);
    printf("Current Balance: $%.2f\n", currentUser->balance);
    printf("Total Transactions: %d\n", currentUser->transactionCount);
    printf("========================================\n");
}

// Main function
int main()
{
    int choice;
    int isLoggedIn = 0;

    initializeAccounts();

    printf("\n========================================\n");
    printf("      ATM MANAGEMENT SYSTEM\n");
    printf("      Version 1.0\n");
    printf("========================================\n");

    while (1)
    {
        if (!isLoggedIn)
        {
            displayMainMenu();
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                if (authenticate())
                {
                    isLoggedIn = 1;
                }
                break;
            case 2:
                printf("\nThank you for using our ATM. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice. Please try again.\n");
            }
        }
        else
        {
            displayUserMenu();
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                displayBalance();
                break;
            case 2:
                withdrawCash();
                break;
            case 3:
                depositCash();
                break;
            case 4:
                viewTransactionHistory();
                break;
            case 5:
                displayAccountDetails();
                break;
            case 6:
                printf("\nLogging out...\n");
                isLoggedIn = 0;
                currentUser = NULL;
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}
