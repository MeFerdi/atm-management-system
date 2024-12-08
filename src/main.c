#include "header.h"

void printMainMenu() {
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check account details\n");
    printf("\n\t\t[4]- Check list of owned accounts\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
}

void initMenu(struct User *u) {
   int r = 0;
   int option;

   system("clear");

   printf("\n\n\t\t======= ATM =======\n");

   while (!r) {
       printf("\n\t\t-->> Feel free to login / register :\n");
       printf("\n\t\t[1]- login\n");
       printf("\n\t\t[2]- register\n");
       printf("\n\t\t[3]- exit\n");

       scanf("%d", &option);

       switch (option) {
           case 1:
               loginMenu(u->name, u->password);
               if (strcmp(u->password, getPassword(*u)) == 0) {
                   printf("\n\nPassword Match!");
               } else {
                   printf("\nWrong password!! or Username\n");
                   exit(1);
               }
               r = 1; // Login successful
               break;
           case 2:
               registerMenu(u->name, u->password); // Call registration function
               r = 1; // Continue to main menu after registration
               break;
           case 3:
               exit(1); // Exit program
           default:
               printf("Insert a valid operation!\n");
       }
   }
}

int main() {
   struct User u;

   initMenu(&u); // Initialize menu for user login/register
   mainMenu(u); // Enter the main menu after successful login/register

   return 0;
}
