#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

void login(struct User *u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s\n", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u->name) == 0)
        {
            fclose(fp);
            u->id = userChecker.id;
            strcpy(u->name, userChecker.name);
            return;
        }
    }

    fclose(fp);
}

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s\n", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

void registerMenu(struct User *u)
{
    struct termios oflags, nflags;

    char name[50];

    char password[50];
    char checkPassword[50];

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\n\t\t\t\t\t Registration\n\n\n\t\t\t\tEnter your name:");
    scanf("%s", name);

    if (checkIfExists(name) == 1)
    {
        printf("Not unique name\n");
        return exit(1);
    }

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    printf("\n\t\t\t\tPassword:");
    scanf("%s", password);

    printf("\n\t\t\t\tCheck Password");
    scanf("%s", checkPassword);

    if (strcmp(password, checkPassword) != 0)
    {
        printf("Passwords did not match\n");
        
        if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
          perror("tcsetattr");
        }
      return exit(1);
    }

    strcpy(u->name, name);
    strcpy(u->password, password);

    saveUserToFile(u);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
    }
};

const int checkIfExists(char name[50])
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s\n", &userChecker.id, userChecker.name, userChecker.password) != EOF) {
       if (strcmp(name, userChecker.name) == 0)
       {
        return 1;
       }
    }

    fclose(fp);
    return 0;
};

void saveUserToFile(struct User *u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    int lastId;
    int notEmpty;
    while (fscanf(fp, "%d %s %s\n", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        notEmpty = 1;
        lastId = userChecker.id; 
    }
    if (notEmpty == 1)
    {
        u->id = lastId+1;
    } else {
        u->id = 0;
    }

    if ((fp = fopen("./data/users.txt", "a+")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    fseek(fp, -1, SEEK_END);
    char lastChar = fgetc(fp);

    if (lastChar != '\n')
    {
       fprintf(fp, "\n");
    }
    fprintf(fp, "%d %s %s\n", u->id, u->name, u->password);
    fclose(fp);
}
