#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypt.h"

unsigned char flags[10] = {0};
#define fileFlag flag[0]
#define blockFlag flag[1]


int mainMenu();
int settingsMenu();

int main(int argc, char** argv)
{
    int choice = 0;
    puts("Simple text encrypt & decrypt system");
    puts("Program by acdxvfsvd");
    puts("");
    do 
    {
        choice = mainMenu();
        switch (choice)
        {
            case 1:
                
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                puts("Bye");
                break;
            default:
                puts("Invalid choice!");
                break;
        }
    } while (choice != 4);
    return 0;
}

int mainMenu()
{
    int choice = 0;
    puts("**********************************");
    puts("*              MENU              *");
    puts("**********************************");
    puts("* 1. Encrypt text                *");
    puts("* 2. Decrypt text                *");
    puts("* 3. Encrypt & decrypt settings  *");
    puts("* 4. Exit                        *");
    puts("**********************************");
    puts("Input your choice:");
    scanf("%d", &choice);
    return choice;
}

int settingsMenu()
{

}