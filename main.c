
#include <stdio.h>
#include "bank.h"

int main(void)
{
    Account *head = NULL;
    Account *new_account;
    Account *selected;
    Account *current;

    int choice;
    int account_number;
    int next_account_number = 1;

    double balance;
    char name[50];

    printf("Welcome to the Banking Application!\n");

    // Load previously saved accounts
    head = load_acc_from_file("accounts.dat");

    // Find the next available account number
    current = head;
    while (current != NULL)
    {
        if (current->account_number >= next_account_number)
        {
            next_account_number = current->account_number + 1;
        }

        current = current->next;
    }

    while (1)
    {
        display_main_menu();
        choice = read_integer("Enter your choice: ");

        switch (choice)
        {
            case 1:
                display_accounts(head);
                break;

            case 2:
                read_string("Enter account holder name: ", name, sizeof(name));

                if (name[0] == '\0')
                {
                    printf("Name cannot be empty!\n");
                    break;
                }

                balance = read_double("Enter initial balance: ");

                new_account = make_account(
                    head,
                    name,
                    next_account_number,
                    balance
                );

                if (new_account != NULL)
                {
                    if (head == NULL)
                    {
                        head = new_account;
                    }

                    printf("Account created successfully!\n");
                    printf("Your account number is: %d\n", next_account_number);

                    next_account_number++;
                }
                else
                {
                    printf("Account creation failed!\n");
                }

                break;

            case 3:
                account_number = read_integer(
                    "Enter account number to select: "
                );

                selected = search_at_random_position(head, account_number);

                if (selected != NULL)
                {
                    if (selected->status == ACCOUNT_ACTIVE)
                    {
                        account_operations_menu(head, selected);
                    }
                    else
                    {
                        printf("This account is closed.\n");
                    }
                }

                break;

            case 4:
                save_acc_to_file("accounts.dat", head);

                printf("Exiting Banking Application...\n");

                free_memory(head);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
