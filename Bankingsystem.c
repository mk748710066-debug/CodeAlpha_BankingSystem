#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

// Create Account
void createAccount() {
    FILE *fp = fopen("bank.dat", "ab");
    struct Account a;

    printf("Enter Account Number: ");
    scanf("%d", &a.accNo);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Account Created Successfully!\n");
}

// Deposit Money
void deposit() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct Account a;
    int acc;
    float amt;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amt);

    while(fread(&a, sizeof(a), 1, fp)) {
        if(a.accNo == acc) {
            a.balance += amt;
            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            printf("Deposit Successful!\n");
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

// Withdraw Money
void withdraw() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct Account a;
    int acc;
    float amt;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amt);

    while(fread(&a, sizeof(a), 1, fp)) {
        if(a.accNo == acc) {
            if(a.balance >= amt) {
                a.balance -= amt;
                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);
                printf("Withdrawal Successful!\n");
            } else {
                printf("Insufficient Balance!\n");
            }
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

// Balance Enquiry
void balanceEnquiry() {
    FILE *fp = fopen("bank.dat", "rb");
    struct Account a;
    int acc;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while(fread(&a, sizeof(a), 1, fp)) {
        if(a.accNo == acc) {
            printf("\nAccount Holder: %s", a.name);
            printf("\nBalance: %.2f\n", a.balance);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

// Main Menu
int main() {
    int choice;

    do {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5: printf("Thank You!\n"); break;
            default: printf("Invalid Choice!\n");
        }

    } while(choice != 5);

    return 0;
}