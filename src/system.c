#include "header.h"
#include <unistd.h>
#include <stdio.h>

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
            r.id,
	        u.id,
	        u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{

   char optionStr[50];
    int option;
    do {
        printf("\nEnter 1 to go to the main menu and 0 to exit!\n");
        fgets(optionStr, sizeof(optionStr), stdin); // read the input as a string
        if(sscanf(optionStr, "%d", &option) != 1) {
            printf("Invalid input, please enter again.\n");
            continue;
        }
        if(option != 1 && option != 0) {
            printf("Invalid input, please enter again.\n");
        }
    } while(option != 1 && option != 0);

    system("clear");
    if (option == 1)
    {
    mainMenu(u);
    }
    else if (option == 0)
    {
    exit(1);
    }
}

void fail(struct User u)
{

    char optionStr[50];
    int option;
    do {
        printf("\nEnter 1 to go to the main menu and 0 to exit!\n");
        fgets(optionStr, sizeof(optionStr), stdin); // read the input as a string
        if(sscanf(optionStr, "%d", &option) != 1) {
            printf("Invalid input, please enter again.\n");
            continue;
        }
        if(option != 1 && option != 0) {
            printf("Invalid input, please enter again.\n");
        }
    } while(option != 1 && option != 0);

    system("clear");
    if (option == 1)
    {
    mainMenu(u);
    }
    else if (option == 0)
    {
    exit(1);
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");



    char date[50];
    do {

        printf("\nEnter today's date(mm/dd/yyyy):");
        fgets(date, sizeof(date), stdin);
        if (sscanf(date, "%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year) != 3 || r.deposit.month < 1 || r.deposit.month > 12 || r.deposit.day < 1 || r.deposit.day > 31 | r.deposit.year < 0){
            printf("Invalid date, please enter again.\n");
        }
    } while(sscanf(date, "%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year) != 3 || r.deposit.month < 1 || r.deposit.month > 12 || r.deposit.day < 1 || r.deposit.day > 31 | r.deposit.year < 0);

    char accountNumber[50];
    do {

        printf("\nEnter the account number:");
        fgets(accountNumber, sizeof(accountNumber), stdin);
        if (sscanf(accountNumber, "%d", &r.accountNbr) != 1 || r.accountNbr < 1 || r.accountNbr > 1000){
            printf("Invalid account number, please enter again.\n");
        }
    } while(sscanf(accountNumber, "%d", &r.accountNbr) != 1 || r.accountNbr < 1 || r.accountNbr > 1000);


    while (getAccountFromFile(pf, userName, &cr))
    {
        r.id = cr.id + 1;
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user");
            goto noAccount;
        }
    }

    printf("\nEnter the country:");
    scanf("%s", r.country);

    printf("\nEnter the phone number:");
    scanf("%s", r.phone);

    while ((c = getchar()) != '\n' && c != EOF) { }

    char amount[50];
    do {
        printf("\nEnter amount to deposit: $");
        fgets(amount, sizeof(amount), stdin);
        if (sscanf(amount, "%lf", &r.amount) != 1 || r.amount < 0){
            printf("Invalid amount, please enter again.\n");
        }
    } while(sscanf(amount, "%lf", &r.amount) != 1 || r.amount < 0);


    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);
    
    fclose(pf);
    while ((c = getchar()) != '\n' && c != EOF) { }
    success(u);
}

void checkAllAccounts(struct User u)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    printf("\nPress enter to continue\n");
    while ((c = getchar()) != '\n' && c != EOF) { }
    fclose(pf);
    success(u);
}

void checkAccount(struct User u)
{   
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    FILE *pf = fopen(RECORDS, "r");
    int accNum;
    int found = 0;
    struct Record cr;
   
    printf("\nEnter account number you want to check:");
    scanf("%d", &accNum);

    while (getAccountNumber(pf, &cr))
    {
        if (strcmp(u.name, cr.name) == 0)
        {
            if (cr.accountNbr == accNum)
            {
                found = 1;
                break;
            }
        }
    }
    
    fclose(pf);
    FILE *pf2 = fopen(RECORDS, "r");
    if (found == 0)
    {
       printf("✖ Account number is not found\n");
        while ((c = getchar()) != '\n' && c != EOF) { }
       fail(u);
    }    

    char userName[100];
    struct Record r;

    system("clear");
    printf("\t\t====== Account %d from user, %s =====\n\n", accNum, u.name);
    while (getAccountFromFile(pf2, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            if (r.accountNbr == accNum)
            {
                printf("_____________________\n");
                printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                    r.accountNbr,
                    r.deposit.day,
                    r.deposit.month,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);

                if (strcmp(r.accountType, "current") == 0)
                {
                    printf("\nYou will not get interests because the account is of type current\n");
                } else if (strcmp(r.accountType, "saving") == 0)
                {
                    float interest = (r.amount * 0.07) / 12.00;
                    printf("\n -> You will get %.2lf as interest on day %d of every month\n", interest, r.deposit.day);
                } else if (strcmp(r.accountType, "fixed01") == 0)
                {
                    float interest = (r.amount * 0.04) / 12.00;
                    printf("\n -> You will get %.2lf as interest on day %d of every month\n", interest, r.deposit.day);
                } else if (strcmp(r.accountType, "fixed02") == 0)
                {
                    float interest = (r.amount * 0.05) / 24.00;
                    printf("\n -> You will get %.2lf as interest on day %d of every month\n", interest, r.deposit.day);
                } else if (strcmp(r.accountType, "fixed03") == 0)
                {
                    float interest = (r.amount * 0.05) / 36.00;
                    printf("\n -> You will get %.2lf as interest on day %d of every month\n", interest, r.deposit.day);
                } else 
                {
                    printf("\nType of an account is not found\n");
                }
                break;
            }
        }
    }
    while ((c = getchar()) != '\n' && c != EOF) { }
    fclose(pf2);
    success(u);
}

void transaction(struct User u)
{   
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    FILE *pf = fopen(RECORDS, "r");
    int found = 0;
    struct Record cr;
   
    printf("\nEnter account number you want:");
    int accNum;

    if (scanf("%d", &accNum) != 1) {
        printf("Invalid input\n");
        fail(u);
    }

    while (getAccountNumber(pf, &cr))
    {
        if (strcmp(u.name, cr.name) == 0)
        {
            if (cr.accountNbr == accNum)
            {
                found = 1;

                if (strcmp(cr.accountType, "saving") != 0)
                {
                    if (strcmp(cr.accountType, "current") != 0)
                    {
                        found = -1;
                    }
                }
                break;
            }
        }
    }
    
    fclose(pf);
    FILE *pf2 = fopen(RECORDS, "r+");
    if (found == 0)
    {
       printf("✖ Account number is not found\n");
       while ((c = getchar()) != '\n' && c != EOF) { }
       fail(u);
    }    

    if (found == -1)
    {
       printf("✖ Accounts of type fixed are not allowed to make transactions \n");
       while ((c = getchar()) != '\n' && c != EOF) { }
       fail(u);
    } 

    char userName[50];
    system("clear");
    printf("\t\t====== Choose option =====\n\n");

    printf("\nDeposit or withdraw\nChoose 1 to deposit\nChoose 2 to withdraw\n");
    int trans; 
    if (scanf("%d", &trans) != 1) {
        printf("Invalid input\n");
        return;
    }

    while (getAccountFromFile(pf2, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0)
        {
            if (cr.accountNbr == accNum)
            {
                if (trans == 1)
                {
                    deposit(&cr);
                    printf("\nSuccess !\n");
                    break;
                }

                if (trans == 2)
                {
                    int isIf = withdraw(&cr);
                    if (isIf == -1)
                    {
                        printf("\nnot sufficient funds\n");
                        while ((c = getchar()) != '\n' && c != EOF) { }
                        break;
                    }

                    if (isIf == 1)
                    {
                        while ((c = getchar()) != '\n' && c != EOF) { }
                        break;
                    }
                    printf("\nSuccess !\n");
                    break;
                }

                break;
            }
        }
    }
    fclose(pf2);
    success(u);
}

void deposit(struct Record *cr)
{   

    FILE *pf = fopen(RECORDS, "r+");
    if (pf == NULL)
    {
        perror("Error opening file for deposit");
        exit(EXIT_FAILURE);
    }

    fseek(pf, 0, SEEK_SET); // Set the file position indicator to the beginning

    float amount;
    printf("\nEnter the amount you want to deposit: ");
    if (scanf("%f", &amount) != 1) {
        printf("Invalid input for amount\n");
        return;
    }

    cr->amount += amount;
    writeRecordNumber(pf, cr);
    fclose(pf);
}

int withdraw(struct Record *cr)
{   
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    FILE *pf = fopen(RECORDS, "r+");
    if (pf == NULL)
    {
        perror("Error opening file for withdrawal");
        exit(EXIT_FAILURE);
    }

    fseek(pf, 0, SEEK_SET); // Set the file position indicator to the beginning

    float amount;

    printf("\nEnter the amount you want to withdraw: ");
     if (scanf("%f", &amount) != 1) {
        printf("\ninvalid input for amount\n");
        return 1;
    }


    if (amount > cr->amount)
    {
        fclose(pf);
        return -1;
    }

    cr->amount -= amount;
    writeRecordNumber(pf, cr);

    fclose(pf);
    return 0;
}

void writeRecordNumber(FILE *pf, struct Record *cr)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    FILE *tempFile = fopen("./data/temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error opening temporary file");
        exit(EXIT_FAILURE);
    }

    struct Record temp;
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &temp.id,
                  &temp.userId,
                  temp.name,
                  &temp.accountNbr,
                  &temp.deposit.month,
                  &temp.deposit.day,
                  &temp.deposit.year,
                  temp.country,
                  temp.phone,
                  &temp.amount,
                  temp.accountType) != EOF)
    {

        if ((strcmp(temp.name, cr->name) == 0) && temp.accountNbr == cr->accountNbr)
        {
            // Update the existing record
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                    cr->id,
                    cr->userId,
                    cr->name,
                    cr->accountNbr,
                    cr->deposit.month,
                    cr->deposit.day,
                    cr->deposit.year,
                    cr->country,
                    cr->phone,
                    cr->amount,
                    cr->accountType);
        }
        else
        {
            // Copy the record as is
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                    temp.id,
                    temp.userId,
                    temp.name,
                    temp.accountNbr,
                    temp.deposit.month,
                    temp.deposit.day,
                    temp.deposit.year,
                    temp.country,
                    temp.phone,
                    temp.amount,
                    temp.accountType);
        }
    }

    fclose(tempFile);

    // Remove the original file
    if (remove(RECORDS) != 0)
    {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }

    // Rename the temporary file to the original file
    if (rename("./data/temp.txt", RECORDS) != 0)
    {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }
}

void updateAcc(struct User u)
{
   int c;
   while ((c = getchar()) != '\n' && c != EOF) { }
   system("clear");
   printf("\t\t\t===== Update record =====\n");
   FILE *pf = fopen(RECORDS, "a+");
   struct Record cr;
   int accNum;
   int found = 0;
   
   char accnum[50];
    do {

        printf("\nEnter account number you want to change:");
        fgets(accnum, sizeof(accnum), stdin);
        if(sscanf(accnum, "%d", &accNum) != 1 || accNum <= 0) {
            printf("Invalid account number, please enter again.\n");
        }
    } while(sscanf(accnum, "%d", &accNum) != 1 || accNum <= 0);

    while (getAccountNumber(pf, &cr))
    {
        if (strcmp(u.name, cr.name) == 0)
        {
            if (cr.accountNbr == accNum)
            {
                found = 1;
                break;
            }
        }
    }

   if (found == 0)
   {
       printf("✖ Account number is not found\n");
       fail(u);
   }
    
   char country[100];
   char phone[100];
   char date1[10];
   char date2[10];
   printf("\nYou can change only phone number and country");
   printf("\nDo you want to change country ? y/n:");
   char changeCountry;

   fgets(date1, sizeof(date1), stdin);

   if (sscanf(date1, "%c", &changeCountry) == 1 && changeCountry == 'y')
   {
       printf("\nEnter country:");
       scanf("%s",country);
       updateCountry(&cr, country);
   }

   printf("\nDo you want to change phone number ? y/n:");
   char changePhone;
   fgets(date2, sizeof(date2), stdin);

   if (sscanf(date2, "%c", &changePhone) == 1 && changePhone == 'y')
   {
       printf("\nEnter phone:");
       scanf("%s", phone);
       updatePhone(&cr, phone);
   }

   fclose(pf);
   success(u);
}

void updateCountry(struct Record *cr, char *country)
{
    FILE *pf = fopen(RECORDS, "r+");
    strcpy(cr->country, country);
    writeRecord(pf, cr);
}

void updatePhone(struct Record *cr, char *phone)
{
    FILE *pf = fopen(RECORDS, "r+");
    strcpy(cr->phone, phone);
    writeRecord(pf, cr);
}

void writeRecord(FILE *pf, struct Record *cr)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    FILE *tempFile = fopen("./data/temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error opening temporary file");
        exit(EXIT_FAILURE);
    }

    struct Record temp;
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &temp.id,
                  &temp.userId,
                  temp.name,
                  &temp.accountNbr,
                  &temp.deposit.month,
                  &temp.deposit.day,
                  &temp.deposit.year,
                  temp.country,
                  temp.phone,
                  &temp.amount,
                  temp.accountType) != EOF)
    {

        if ((strcmp(temp.name, cr->name) == 0) && temp.accountNbr == cr->accountNbr)
        {
            // Update the existing record
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                    cr->id,
                    cr->userId,
                    cr->name,
                    cr->accountNbr,
                    cr->deposit.month,
                    cr->deposit.day,
                    cr->deposit.year,
                    cr->country,
                    cr->phone,
                    cr->amount,
                    cr->accountType);
        }
        else
        {
            // Copy the record as is
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                    temp.id,
                    temp.userId,
                    temp.name,
                    temp.accountNbr,
                    temp.deposit.month,
                    temp.deposit.day,
                    temp.deposit.year,
                    temp.country,
                    temp.phone,
                    temp.amount,
                    temp.accountType);
        }
    }

    fclose(pf);
    fclose(tempFile);

    // Remove the original file
    if (remove(RECORDS) != 0)
    {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }

    // Rename the temporary file to the original file
    if (rename("./data/temp.txt", RECORDS) != 0)
    {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }
}


int getAccountNumber(FILE *ptr, struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r->id,
                  &r->userId,
                  r->name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}



void deleteAccount(struct User u)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    FILE *pf = fopen(RECORDS, "r");
    int accNum;
    int found = 0;
    struct Record cr;
   
    printf("\nEnter account number you want to delete:");
    scanf("%d", &accNum);

    while (getAccountNumber(pf, &cr))
    {
        if (strcmp(u.name, cr.name) == 0)
        {
            if (cr.accountNbr == accNum)
            {
                found = 1;
                break;
            }
        }
    }
    
    fclose(pf);
    FILE *pf2 = fopen(RECORDS, "r");
    if (found == 0)
    {
       printf("✖ Account number is not found\n");
       while ((c = getchar()) != '\n' && c != EOF) { }
       fail(u);
    }    

    deleteAccountRecord(pf2, &cr);

    printf("\nSuccess\n");
    
    fclose(pf2);
    success(u);
}

void deleteAccountRecord(FILE *pf, struct Record *cr)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    FILE *tempFile = fopen("./data/temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error opening temporary file");
        exit(EXIT_FAILURE);
    }

    struct Record temp;
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &temp.id,
                  &temp.userId,
                  temp.name,
                  &temp.accountNbr,
                  &temp.deposit.month,
                  &temp.deposit.day,
                  &temp.deposit.year,
                  temp.country,
                  temp.phone,
                  &temp.amount,
                  temp.accountType) != EOF)
    {

        if ((strcmp(temp.name, cr->name) == 0) && temp.accountNbr == cr->accountNbr)
        {
            continue;
        }
        else
        {
            // Copy the record as is
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                    temp.id,
                    temp.userId,
                    temp.name,
                    temp.accountNbr,
                    temp.deposit.month,
                    temp.deposit.day,
                    temp.deposit.year,
                    temp.country,
                    temp.phone,
                    temp.amount,
                    temp.accountType);
        }
    }

    fclose(tempFile);

    // Remove the original file
    if (remove(RECORDS) != 0)
    {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }

    // Rename the temporary file to the original file
    if (rename("./data/temp.txt", RECORDS) != 0)
    {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }
}

void transferAccount(struct User u)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    int accNum;
    int found = 0;
    FILE *pf = fopen(RECORDS, "r");
    struct Record cr;
   
    printf("\nEnter account number you want to transfer:");
    scanf("%d", &accNum);

    while (getAccountNumber(pf, &cr))
    {
        if (strcmp(u.name, cr.name) == 0)
        {
            if (cr.accountNbr == accNum)
            {
                found = 1;
                break;
            }
        }
    }
    
    fclose(pf);

    if (found == 0)
    {
       printf("\n✖ Account number is not found\n");
       while ((c = getchar()) != '\n' && c != EOF) { }
       fail(u);
    }    

    char userName[100];
    char user[100];
    printf("\nEnter user:");
    scanf("%s",userName);

    FILE *toF = fopen(RECORDS, "r");
    struct Record to;

    int found2 = 0;
    while (getAccountFromFile(toF, user, &to))
    {
        if (strcmp(user, userName) == 0)
        {
            found2 = 1;
            break;
        }
    }
    fclose(toF);

    FILE *pf2 = fopen(RECORDS, "r+");
    if (found2 == 0)
    {
        printf("\nuser not found\n");
        while ((c = getchar()) != '\n' && c != EOF) { }
        fail(u);
    }
    
    writeRecordTransfer(pf2, &cr, userName, to.userId);
    
    success(u);
}

void writeRecordTransfer(FILE *pf, struct Record *cr, char userName[100], int id)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    FILE *tempFile = fopen("./data/temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Error opening temporary file");
        exit(EXIT_FAILURE);
    }
    int newId;
    struct Record temp;
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &temp.id,
                  &temp.userId,
                  temp.name,
                  &temp.accountNbr,
                  &temp.deposit.month,
                  &temp.deposit.day,
                  &temp.deposit.year,
                  temp.country,
                  temp.phone,
                  &temp.amount,
                  temp.accountType) != EOF)
    {

        if ((strcmp(temp.name, cr->name) == 0) && temp.accountNbr == cr->accountNbr)
        {
            if (cr->accountNbr == temp.accountNbr)
            {
                newId = checkTransferId(cr);
            }
            // Update the existing record
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                    cr->id,
                    id,
                    userName,
                    newId,
                    cr->deposit.month,
                    cr->deposit.day,
                    cr->deposit.year,
                    cr->country,
                    cr->phone,
                    cr->amount,
                    cr->accountType);
        }
        else
        {
            // Copy the record as is
            fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                    temp.id,
                    temp.userId,
                    temp.name,
                    temp.accountNbr,
                    temp.deposit.month,
                    temp.deposit.day,
                    temp.deposit.year,
                    temp.country,
                    temp.phone,
                    temp.amount,
                    temp.accountType);
        }
    }

    fclose(pf);
    fclose(tempFile);

    // Remove the original file
    if (remove(RECORDS) != 0)
    {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }

    // Rename the temporary file to the original file
    if (rename("./data/temp.txt", RECORDS) != 0)
    {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }
}

int checkTransferId(struct Record *cr)
{
  char userName[100];
  struct Record r;
  FILE *pf = fopen(RECORDS, "r");
  int ids[100];
  int newID;
  int index = 0;
  
  while (getAccountFromFile(pf, userName, &r))
  {
      if (strcmp(userName, cr->name) == 0)
      {
          ids[index] = r.accountNbr;
          index++;
      }
  }
  
  fclose(pf); 
  newID = generateNewID(ids, index);
  return newID;
}

bool isIDInArray(int ids[], int numIds, int id)
{
   for (int i = 0; i < numIds; i++) {
       if (ids[i] == id) {
           return true;
       }
   }
   return false;
}

int generateNewID(int ids[], int numIds)
{
   int newID = 1;
   while (isIDInArray(ids, numIds, newID)) {
       newID++;
   }
   return newID;
}
