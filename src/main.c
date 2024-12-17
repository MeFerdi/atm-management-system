#include "header.h"

void mainMenu(struct User u)
{
    int option;

    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
     scanf("%d", &option);
     
    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAcc(u);
        break;
    case 3:
        checkAccount(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        transaction(u);
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        deleteAccount(u);
        break;
    case 7:
        transferAccount(u);
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    char input[256];
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        // Validate inputs
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%d", &option) != 1)
        {
            printf("Insert a valid operation!\n");
            continue;
        }


        // Match input
        switch (option)
        {
        case 1:
            // Login function
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                login(u);
                printf("\n\nPassword Match!");
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            // student TODO : add your **Registration** function
            registerMenu(u);
            
            r = 1;
            break;
        case 3:
            printf("See you soon!\n");
            exit(1);
            break;
        default:
            printf("Invalid input!\n\nKilling the session x_X\n");
            exit(1);
        }
    }
};

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
