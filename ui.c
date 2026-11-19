
#include "bank.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int read_integer(const char *prompt)
{
    char input[100];
    char *endptr;
    long number;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Input error. Try again.\n");
            continue;
        }

        errno = 0;
        number = strtol(input, &endptr, 10);

        while (isspace((unsigned char)*endptr))
        {
            endptr++;
        }

        if (endptr == input || *endptr != '\0' ||
            errno == ERANGE || number < INT_MIN || number > INT_MAX)
        {
            printf("Invalid input! Please enter a valid integer.\n");
            continue;
        }

        return (int)number;
    }
}

double read_double(const char *prompt)
{
    char input[100];
    char *endptr;
    double number;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Input error. Try again.\n");
            continue;
        }

        errno = 0;
        number = strtod(input, &endptr);

        while (isspace((unsigned char)*endptr))
        {
            endptr++;
        }

        if (endptr == input || *endptr != '\0' || errno == ERANGE)
        {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }

        return number;
    }
}

//Reads and validates account holder's name
void read_string(const char *prompt, char *buffer, int size)
{
    int i;
    int valid;
    int has_letter;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(buffer, size, stdin) == NULL)
        {
            printf("Input error.\n");
            buffer[0] = '\0';
            return;
        }

        // Remove newline
        buffer[strcspn(buffer, "\n")] = '\0';

        // VALIDATION
        valid = 1;
        has_letter = 0;

        for (i = 0; buffer[i] != '\0'; i++)
        {
            if ((buffer[i] >= 'A' && buffer[i] <= 'Z') ||
                (buffer[i] >= 'a' && buffer[i] <= 'z'))
            {
                has_letter = 1;
            }
            else if (buffer[i] != ' ')
            {
                valid = 0;
                break;
            }
        }

        if (valid && has_letter)
            return;

        printf("Invalid name! Use only English letters and spaces.\n");
    }
}

void display_main_menu(void)
{
    printf("\n");
    printf("       BANKING APPLICATION\n");
    printf("1. List All Active Accounts\n");
    printf("2. Create New Account\n");
    printf("3. Select Account\n");
    printf("4. Save & Exit\n");
}

void display_accounts(Account *head)
{
    Account *current = head;
    int found = 0;

    printf("\n========== ACTIVE ACCOUNTS ==========\n");
    printf("%-15s %-25s %-15s\n",
           "Account Number", "Account Holder", "Balance");
    printf("-----------------------------------------------\n");

    while (current != NULL)
    {
        if (current->status == ACCOUNT_ACTIVE)
        {
            printf("%-15d %-25s %-15.2f\n",
                   current->account_number,
                   current->holder_name,
                   current->balance);
            found = 1;
        }

        current = current->next;
    }

    if (found == 0)
    {
        printf("No active accounts found.\n");
    }

    printf("===============================================\n");
}

void display_account_details(Account *account)
{
    if (account == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    printf("\n========== ACCOUNT DETAILS ==========\n");
    printf("Account Number : %d\n", account->account_number);
    printf("Account Holder : %s\n", account->holder_name);
    printf("Balance        : %.2f\n", account->balance);

    if (account->status == ACCOUNT_ACTIVE)
        printf("Status         : ACTIVE\n");
    else
        printf("Status         : CLOSED\n");

    printf("======================================\n");
}

void account_operations_menu(Account *head, Account *selected)
{
    int choice;
    double amount;
    int destination_number;
    int result;
    Account *destination;

    if (selected == NULL)
    {
        printf("No account selected!\n");
        return;
    }

    if (selected->status != ACCOUNT_ACTIVE)
    {
        printf("This account is closed. Operations are not allowed.\n");
        return;
    }

    while (1)
    {
        printf("\n========== ACCOUNT OPERATIONS ==========\n");
        printf("1. View Account Details\n");
        printf("2. Deposit Funds\n");
        printf("3. Withdraw Funds\n");
        printf("4. Transfer Funds\n");
        printf("5. Close Account\n");
        printf("6. Back to Main Menu\n");
        printf("========================================\n");

        choice = read_integer("Enter your choice: ");

        switch (choice)
        {
            case 1:
                display_account_details(selected);
                break;

            case 2:
                amount = read_double("Enter deposit amount: ");
                result = deposit(selected, amount);

                if (result == 1)
                    printf("Deposit successful!\n");
                else
                    printf("Deposit failed!\n");

                break;

            case 3:
                amount = read_double("Enter withdrawal amount: ");
                result = withdraw(selected, amount);

                if (result == 1)
                    printf("Withdrawal successful!\n");
                else
                    printf("Withdrawal failed!\n");

                break;

            case 4:
                destination_number = read_integer(
                    "Enter destination account number: "
                );

                destination = head;

                while (destination != NULL)
                {
                    if (destination->account_number == destination_number)
                        break;

                    destination = destination->next;
                }

                if (destination == NULL)
                {
                    printf("Destination account not found!\n");
                    break;
                }

                amount = read_double("Enter transfer amount: ");
                result = transfer(selected, destination, amount);

                if (result == 1)
                    printf("Transfer successful!\n");
                else
                    printf("Transfer failed!\n");

                break;

            case 5:
                destination = change_account_status(
                    head,
                    selected->account_number
                );

                if (destination != NULL)
                    printf("Account closed successfully!\n");
                else
                    printf("Failed to close account!\n");

                return;

            case 6:
                printf("Returning to main menu...\n");
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
