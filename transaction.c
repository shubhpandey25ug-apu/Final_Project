
#include <math.h>
#include <stddef.h>
#include "bank.h"

// Deposit money
int deposit(Account *bank_account, double amount)
{
    if (bank_account == NULL)
    {
        return 0;
    }
    else if (bank_account->status != ACCOUNT_ACTIVE)
    {
        return 0;
    }
    else if (amount <= 0 || !isfinite(amount))
    {
        return 0;
    }
    else if (bank_account->balance < 0 || !isfinite(bank_account->balance))
    {
        return 0;
    }
    else if (!isfinite(bank_account->balance + amount))
    {
        return 0;
    }
    else
    {
        bank_account->balance = bank_account->balance + amount;
        return 1;
    }
}

// Withdraw money
int withdraw(Account *bank_account, double withdrawal_amount)
{
    if (bank_account == NULL)
    {
        return 0;
    }
    else if (bank_account->status != ACCOUNT_ACTIVE)
    {
        return 0;
    }
    else if (withdrawal_amount <= 0 || !isfinite(withdrawal_amount))
    {
        return 0;
    }
    else if (bank_account->balance < 0 || !isfinite(bank_account->balance))
    {
        return 0;
    }
    else if (bank_account->balance < withdrawal_amount)
    {
        return 0;
    }
    else
    {
        bank_account->balance = bank_account->balance - withdrawal_amount;
        return 1;
    }
}

// Transfer money
int transfer(Account *source_account, Account *destination_account, double transfer_amount)
{
    if (source_account == NULL || destination_account == NULL)
    {
        return 0;
    }
    else if (source_account->status != ACCOUNT_ACTIVE || destination_account->status != ACCOUNT_ACTIVE)
    {
        return 0;
    }
    else if (source_account == destination_account || source_account->account_number == destination_account->account_number)
    {
        return 0;
    }
    else if (transfer_amount <= 0 || !isfinite(transfer_amount))
    {
        return 0;
    }
    else if (source_account->balance < 0 || !isfinite(source_account->balance))
    {
        return 0;
    }
    else if (source_account->balance < transfer_amount)
    {
        return 0;
    }
    else if (destination_account->balance < 0 || !isfinite(destination_account->balance))
    {
        return 0;
    }
    else if (!isfinite(destination_account->balance + transfer_amount))
    {
        return 0;
    }
    else
    {
        source_account->balance = source_account->balance - transfer_amount;
        destination_account->balance = destination_account->balance + transfer_amount;

        return 1;
    }
}