#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* iFilenamePtr = NULL;
char* oFilenamePtr = NULL;
char* srcPtr = NULL;
char* keyPtr = NULL;
char* destPtr = NULL;

FILE* iFile = NULL;
FILE* oFile = NULL;

unsigned char flags[4] = {0};
#define blockFlag flags[0]
#define iFileFlag flags[1]
#define oFileFlag flags[2]
#define successFlag flags[3]
#define doEncrypt 0
#define doDecrypt 1

#include "crypt.h"
#include "acdio.h"

int mainMenu();
int processSettings();
int settingsMenu();
int doSettings();
int prepareToDoCipher(int operate);
int cipherIO(int operate);


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
                successFlag = prepareToDoCipher(choice);
                if (successFlag)
                {
                    puts("Doing cipher successfully!");
                }
                else
                {
                    puts("Error!");
                }
                successFlag = 0;
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
    choice = readNum();
    return choice;
}

int settingsMenu()
{
    int choice = 0;
    puts("**********************************");
    puts("*       ALGORITHM SETTINGS       *");
    puts("**********************************");
    puts("* 1. Simple stream cipher        *");
    puts("* (Subkeys-generated XOR cipher) *");
    puts("* 2. Simple block cipher         *");
    puts("* (TEA-style block cipher)       *");
    puts("**********************************");
    printf("* Current algorithm: %d           *\n", blockFlag + 1);
    puts("**********************************");
    puts("Input your choice:");
    choice = readNum();
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
    puts("**********************************");
    puts("*   Input the source filename    *");
    puts("*  No more than 250 characters   *");
    puts("* Leave blank for keyboard input *");
    puts("**********************************");
    iFilenamePtr = (char *)malloc(0x100);
    memset(iFilenamePtr, 0, 0x100);
    if(readBuf(iFilenamePtr, 252) == 0)
    {
    	iFileFlag = 0;
	}
	else
	{
		iFileFlag = 1;
	}
	puts("**********************************");
    puts("*   Input the target filename    *");
    puts("*  No more than 250 characters   *");
    puts("* Leave blank for screen output  *");
    puts("**********************************");
    oFilenamePtr = (char *)malloc(0x100);
    memset(oFilenamePtr, 0, 0x100);
    if(readBuf(oFilenamePtr, 252) == 0)
    {
    	oFileFlag = 0;
	}
	else
	{
		oFileFlag = 1;
    }
    puts("**********************************");
    puts("*    Input the cryption key      *");
    if (blockFlag)
    {
        puts("*     Must be 8 bytes long      *");
    }
    else
    {
        puts("*   No more than 8 bytes long    *");
    }
    puts("**********************************");
    keyPtr = (char *)malloc(16);
    memset(keyPtr, 0, 16);
    do
    {
        continue;
    } while(readBuf(keyPtr, 8));

    puts("**********************************");
    if (!iFileFlag)
    {
        puts("*     Input the source text      *");
        puts("*     Do not change the line     *");
    }
    else
    {
        puts("* Reading the text from file ... *");
        iFile = fopen(iFilenamePtr, "r");
        if (iFile == NULL)
        {
            puts("* Failed to open the input file! *");
            puts("**********************************");
            return 0;
        }
    }
    puts("**********************************");
}
