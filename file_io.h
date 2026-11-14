#ifndef FILE_IO_H
#define FILE_IO_H       // These are include guards :)

#include "account.h"

Account* load_acc_from_file (const char* filename);
void save_acc_to_file(const char* filename, Account*);

#endif                  // This is ending include guard...