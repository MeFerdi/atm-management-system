#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50]) {
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // Disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }
    
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // Restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        exit(1);
    }
}

const char *getPassword(struct User u) {
    FILE *fp;
    
    if ((fp = fopen(USERS, "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    struct User userChecker;

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF) {
        if (strcmp(userChecker.name, u.name) == 0) {
            fclose(fp);
            char *passwordCopy = malloc(strlen(userChecker.password) + 1); // Allocate memory
            strcpy(passwordCopy, userChecker.password); // Copy password
            return passwordCopy; // Return pointer to dynamically allocated memory
        }
    }

    fclose(fp);
    return NULL; // Return NULL if no user found
}

void registerMenu(char a[50], char pass[50]) {
    FILE *file = fopen(USERS, "a+");
    
    if (!file) {
        printf("Error opening users file.\n");
        return;
    }

    struct User newUser;
    
    printf("Enter username: ");
    scanf("%s", newUser.name);
    
    // Check for unique username
    char line[100];
    
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, newUser.name) != NULL) {
            printf("Username already exists.\n");
            fclose(file);
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", newUser.password);
    
    fprintf(file, "%d %s %s\n", newUser.id, newUser.name, newUser.password);
    
    fclose(file);
    
    printf("User registered successfully!\n");
}
