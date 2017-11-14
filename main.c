#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypt.h"

unsigned char flags[4] = {0};
#define blockFlag flags[0]
#define fileFlag flags[1]
#define successFlag flags[2]

int mainMenu();
int processSettings();
int settingsMenu();
int doSettings();
int prepareToDoCipher(int operate);

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
            case 2:
                prepareToDoCipher(choice);
                break;
            case 3:
                successFlag = doSettings();
                if (successFlag)
                {
                    puts("Settings changed successfully!");
                }
                else
                {
                    puts("Invalid settings choice!");
                }
                successFlag = 0;
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
    puts("* 3. Cipher algorithm settings   *");
    puts("* 4. Exit                        *");
    puts("**********************************");
    puts("Input your choice:");
    scanf("%d", &choice);
    return choice;
}

int settingsMenu()
{
    int choice = 0;
    puts("**********************************");
    puts("*       ALGORITHM SETTINGS       *");
    puts("**********************************");
    puts("* 1. Simple stream cipher        *");
    puts("* (Vigenere-style XOR cipher)    *");
    puts("* 2. Simple block cipher         *");
    puts("* (TEA-style block cipher)       *");
    puts("**********************************");
    printf("* Current algorithm: %d           *\n", blockFlag + 1);
    puts("**********************************");
    puts("Input your choice:");
    scanf("%d", &choice);
    return choice;
}

int doSettings()
{
    int choice;
    choice = settingsMenu();
    switch (choice)
    {
        case 1:
        case 2:
            blockFlag = choice - 1;
            return 1;
        default:
            return 0;
    }
    return 0;
}

int prepareToDoCipher(int operate)
{

}