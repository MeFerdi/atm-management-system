#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    char phone[100];
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void login(struct User *u);
const char *getPassword(struct User u);

// register
void registerMenu(struct User *u);
const int checkIfExists(char name[50]);
void saveUserToFile(struct User *u);
int getNewId();

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);

// updating function
void updateAcc(struct User u);
void updateCountry(struct Record *cr, char *country);
void updatePhone(struct Record *cr, char *phone);
void writeRecord(FILE *pf, struct Record *cr);
int getAccountNumber(FILE *ptr, struct Record *r);
void checkAccount(struct User u);
void transaction(struct User u);

void writeRecordNumber(FILE *pf, struct Record *cr);
int withdraw(struct Record *cr);
void deposit(struct Record *cr);

void deleteAccount(struct User u);
void deleteAccountRecord(FILE *pf, struct Record *cr);

void transferAccount(struct User u);
void writeRecordTransfer(FILE *pf, struct Record *cr, char userName[100], int id);

int checkTransferId(struct Record *cr);
bool isIDInArray(int ids[], int numIds, int id);
int generateNewID(int ids[], int numIds);
void fail(struct User u);