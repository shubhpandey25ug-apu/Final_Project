#include <stdio.h>

#include "file_io.h"
#include "list.h"


Account* load_acc_from_file(const char* filename){   //First Function, does as its name
    FILE* fp = fopen(filename, "rb");        //fopen open the file and "rb" for Read & Binary modes

    if(fp==NULL){
        return NULL;
    }

    Account* head = NULL;
    Account* tail = NULL;
    Account temp;      //Defining a temporary struct var

    while(fread(&temp, sizeof(Account), 1, fp)== 1){       //The syntax is: fread(address, size, count, file_pointer);
        Account* new_account = make_account(           //first contact with Sameer's function
            tail,
            temp.holder_name,
            temp.account_number,
            temp.balance
        );

        if(new_account==NULL){      //If allocation/account creation fails
            break;
        }
        if(head==NULL){            //Setting up first account
            head = new_account;
        }
        tail = new_account;        //making it the last node/account in Linked List
        tail->status = temp.status;
    }  
    
    if(ferror(fp)){        //checks for the error
        perror("Error reading account file");   //prints the error statement
    }
    fclose(fp);           //closes the file that we opened using fopen
    return head;          //giving the starting address of LL to Head pointer
}

void save_acc_to_file(const char* filename, Account* head){      //Second function
    FILE* fp = fopen(filename, "wb");
    
    if(fp==NULL){        //if file does not opens
        perror("Error opening accounts file");    //gives error statement with reason
        return;
    }

    Account* current = head;    //Defining current var to navigate in LL
    while(current != NULL){
        Account temp = *current;    // "*" cauz we want to access the content inside the address that current ptr holds
        temp.next = NULL;         //we set it to NULL as we don't want to save older memory address

        if(fwrite(&temp, sizeof(Account), 1, fp) != 1){
            perror("Error writing accounts file");
            break;
        }
        current = current->next; 
    }

    if(fclose(fp)== EOF){
            perror("Error closing accounts file");
        }
}