
#ifndef BANK_H               //Include guards
#define BANK_H
#include <stdio.h>
#include <stdlib.h>

typedef enum {                  // Enum = conditions as 0,1,2...,n 
    ACCOUNT_ACTIVE,
    ACCOUNT_CLOSED
} AccountStatus;

typedef struct Account {         // The main structure (Modified)
    int account_number;
    char holder_name[50];
    double balance;
    AccountStatus status;
    struct Account *next;
} Account;

//Sameer's .h file
Account *make_account(Account *head , char *name , int number , double balance);

Account  *search_at_random_position( Account *head ,int number );

Account  *change_account_status(Account *head ,int number  );

void free_memory( Account *head);

//Shubh's .h file
Account* load_acc_from_file (const char* filename);

void save_acc_to_file(const char* filename, Account*);

//Radhika's .h file
int deposit(Account *bank_account, double amount);

int withdraw(Account *bank_account, double withdrawal_amount);

int transfer(Account *source_account, Account *destination_account, double transfer_amount);

//Prakash's .h file
int read_integer(const char *prompt);

double read_double(const char *prompt);

void read_string(const char *prompt, char *buffer, int size);

void display_main_menu(void);

void display_accounts(Account *head);

void display_account_details(Account *account);

void account_operations_menu(Account *head, Account *selected);

#endif                  // This is ending include guard...