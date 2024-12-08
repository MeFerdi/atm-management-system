#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r) {
   return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                 &r->id,
                 &r->userId,
                 name,
                 &r->accountNbr,
                 &r->deposit.month,
                 &r->deposit.day,
                 &r->deposit.year,
                 r->country,
                 &r->phone,
                 &r->amount,
                 r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r) {
   fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
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

void createNewAcc(struct User u) {
   struct Record r;
   char userName[50];
   FILE *pf = fopen(RECORDS, "a+");

   system("clear");
   printf("\t\t===== New record =====\n");

   printf("Enter today's date(mm/dd/yyyy): ");
   scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
   printf("Enter the account number: ");
   scanf("%d", &r.accountNbr);

   while (getAccountFromFile(pf, userName, &r)) { 
       if (strcmp(userName, u.name) == 0 && r.accountNbr == r.accountNbr) { 
           printf("✖ This Account already exists for this user.\n"); 
           return; 
       } 
   }

   printf("Enter the country: ");
   scanf("%s", r.country);
   printf("Enter the phone number: ");
   scanf("%d", &r.phone);
   printf("Enter amount to deposit: $");
   scanf("%lf", &r.amount);

   printf("Choose the type of account:\n-> saving\n-> current\n-> fixed01(for 1 year)\n-> fixed02(for 2 years)\n-> fixed03(for 3 years)\nEnter your choice: ");
   scanf("%s", r.accountType);

   saveAccountToFile(pf, u, r); 
   
   fclose(pf); 
}

void checkAllAccounts(struct User u) {
   char userName[100];
   struct Record r;

   FILE *pf = fopen(RECORDS, "r");

   system("clear");
   printf("\t====== All accounts from user: %s =====\n", u.name);

   while (getAccountFromFile(pf, userName, &r)) { 
       if (strcmp(userName, u.name) == 0) { 
           printf("_____________________\n"); 
           printf("Account number: %d\nDeposit Date: %d/%d/%d \nCountry: %s \nPhone number: %d \nAmount deposited: $%.2f \nType Of Account: %s\n",
                  r.accountNbr,
                  r.deposit.month,
                  r.deposit.day,
                  r.deposit.year,
                  r.country,
                  r.phone,
                  r.amount,
                  r.accountType); 
       } 
   }
   
   fclose(pf); 
}

void updateAccount(struct User u) {
   FILE *file = fopen(RECORDS, "r+");

   if (!file) { 
       printf("Unable to open records file.\n"); 
       return; 
   }

   int accountId; 
   char field[20], newValue[50];

   printf("Enter account ID to update: "); 
   scanf("%d", &accountId); 

   struct Record r; 

   while (getAccountFromFile(file, u.name, &r)) { 
       if (r.id == accountId) { 
           printf("Which field do you want to update? (country/phone): "); 
           scanf("%s", field); 

           if (strcmp(field, "country") == 0) { 
               printf("Enter new country: "); 
               scanf("%s", newValue); 
               strcpy(r.country,newValue); // Update country 
           } else if (strcmp(field,"phone") == 0){ 
               printf("Enter new phone number: "); 
               scanf("%d",&r.phone); // Update phone number 
           } else { 
               printf("Invalid field.\n"); fclose(file); return; 
           }

           fseek(file,-sizeof(r),SEEK_CUR); // Move back to overwrite record 
           saveAccountToFile(file,u,r); // Save updated record 

           break; 
       } 
   }

   fclose(file); 
}

void checkAccountDetails(struct User u) {
   FILE *file = fopen(RECORDS,"r");

   if (!file){ 
       printf("Unable to open records file.\n"); return; 
   }

   int accountId; 

   printf("Enter account ID to view details: "); 
   scanf("%d",&accountId); 

   struct Record r; 

   while(getAccountFromFile(file,u.name,&r)){ 
       if(r.id==accountId){ 
           printf("Account Details:\n"); 

           double interest = 0.0; 

           if(strcmp(r.accountType,"savings")==0){ 
               interest=r.amount*0.07; // 7% interest for savings  
               printf("You will get $%.2f as interest on day 10 of every month.\n",interest/12); // Monthly interest  
           } else if(strcmp(r.accountType,"fixed01")==0){  
               interest=r.amount*0.04; // 4% for fixed01  
               printf("You will get $%.2f as interest at maturity.\n",interest);  
           } else if(strcmp(r.accountType,"fixed02")==0){  
               interest=r.amount*0.05; // 5% for fixed02  
               printf("You will get $%.2f as interest at maturity.\n",interest);  
           } else if(strcmp(r.accountType,"fixed03")==0){  
               interest=r.amount*0.08; // 8% for fixed03  
               printf("You will get $%.2f as interest at maturity.\n",interest);  
           } else if(strcmp(r.accountType,"current")==0){  
               printf("You will not get interests because the account is of type current.\n");  
           }

          break;  
       }  
     }

     fclose(file);  
}

void makeTransaction(struct User u){
     FILE *file=fopen(RECORDS,"r+");

     if(!file){
         printf("Unable to open records file.\n");
         return;
     }

     int accountId;
     double amount;

     printf("Enter account ID for transaction: ");
     scanf("%d",&accountId);

     struct Record r;

     while(getAccountFromFile(file,u.name,&r)){
         if(r.id==accountId){
             char transactionType[10];
             printf("Enter transaction type (deposit/withdraw): ");
             scanf("%s",transactionType);

             if(strcmp(transactionType,"deposit")==0){
                 printf("Enter amount to deposit: ");
                 scanf("%lf",&amount);
                 r.amount+=amount; // Update balance for deposit
             }else if(strcmp(transactionType,"withdraw")==0){
                 printf("Enter amount to withdraw: ");
                 scanf("%lf",&amount);
                 if(amount>r.amount){ // Check for sufficient funds
                     printf("Insufficient funds!\n");
                     fclose(file);
                     return;
                 }
                 r.amount-=amount; // Update balance for withdrawal
             }else{
                 printf("Invalid transaction type.\n");
                 fclose(file);
                 return;
             }

             fseek(file,-sizeof(r),SEEK_CUR); // Move back to overwrite record
             saveAccountToFile(file,u,r); // Save updated record
             break;
         }
     }

     fclose(file);
}

void removeAccount(struct User u){
     FILE *file=fopen(RECORDS,"r");
     FILE *tempFile=fopen("./data/temp_records.txt","w");

     if(!file || !tempFile){
         printf("Unable to open records file.\n");
         return;
     }

     int accountId;
     struct Record r;

     printf("Enter account ID to remove: ");
     scanf("%d",&accountId);

     int found=0;

     while(getAccountFromFile(file,u.name,&r)){
         if(r.id!=accountId){ // Copy other records to temp file
             saveAccountToFile(tempFile,u,r);
         }else{
             found=1; // Mark as found for feedback later
         }
     }

     fclose(file);
     fclose(tempFile);

     remove(RECORDS); // Delete original records file
     rename("./data/temp_records.txt",RECORDS); // Rename temp file

     if(found)
         success(u); // Notify success on removal
     else
         stayOrReturn(0 ,removeAccount,u ); // Handle not found case
}

void transferOwnership(struct User u){
      FILE *file=fopen(RECORDS,"r+");

      if(!file){
          printf("Unable to open records file.\n");
          return;
      }

      int accountId;
      char newOwner[50];

      printf("Enter your account ID for transfer: ");
      scanf("%d",&accountId);

      struct Record r;

      while(getAccountFromFile(file,u.name,&r)){
          if(r.id==accountId){
              printf("Enter the username of the new owner: ");
              scanf("%s",newOwner);

              struct User newOwnerUser;
              strcpy(newOwnerUser.name,newOwner);

              const char* password=getPassword(newOwnerUser);

              if(password != NULL){ // Check that we found a valid user.
                  strcpy(r.name,newOwner);

                  fseek(file,-sizeof(r),SEEK_CUR);
                  saveAccountToFile(file,u,r);

                  success(u);
              }else{
                  stayOrReturn(0 ,transferOwnership,u );
              }
              
              break;
          }
      }

      fclose(file);
}

void mainMenu(struct User u) {
    int option;

    while (1) {
        printMainMenu(); // Function to print the menu options

        scanf("%d", &option);

        switch (option) {
            case 1:
                createNewAcc(u);
                break;
            case 2:
                updateAccount(u);
                break;
            case 3:
                checkAccountDetails(u);
                break;
            case 4:
                checkAllAccounts(u);
                break;
            case 5:
                makeTransaction(u);
                break;
            case 6:
                removeAccount(u);
                break;
            case 7:
                transferOwnership(u);
                break;
            case 8:
                exit(0); // Exit program
            default:
                printf("Invalid operation!\n");
        }
    }
}

void success(struct User u) {
    printf("\n✔ Success!\n");
    printf("Enter 1 to go to the main menu and 0 to exit: ");
    int option;
    scanf("%d", &option);
    if (option == 1) {
        mainMenu(u); // Go back to main menu
    } else {
        exit(0); // Exit program
    }
}

void stayOrReturn(int notGood, void (*f)(struct User), struct User u) {
    if (notGood == 0) {
        printf("\n✖ Record not found!!\n");
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit: ");
        int option;
        scanf("%d", &option);
        if (option == 0)
            f(u); // Retry function call
        else if (option == 1)
            mainMenu(u); // Return to main menu
        else
            exit(0); // Exit program
    }
}