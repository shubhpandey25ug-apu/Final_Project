
#ifndef ACCOUNT_H               //Include guards
#define ACCOUNT_H

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

#endif                         // Ending guard
