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
    int result = 0;
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
	fflush(stdin);
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
    fflush(stdin);
    puts("**********************************");
    puts("*    Input the cryption key      *");
    if (blockFlag)
    {
        puts("*     Must be 16 bytes long      *");
    }
    else
    {
        puts("*  No more than 16 bytes long    *");
    }
    puts("**********************************");
    keyPtr = (char *)malloc(24);
    memset(keyPtr, 0, 24);
    readBuf(keyPtr, 16);
    fflush(stdin);
    if (blockFlag)
    {
        while(strlen(keyPtr) != 16)
        {
            puts("Length error!");
            readBuf(keyPtr, 16);
            fflush(stdin);
        }
    }
    if (iFileFlag)
    {
        puts("**********************************");
        puts("*   Opening the input file ...   *");
        iFile = fopen(iFilenamePtr, "r");
        if (iFile == NULL)
        {
            puts("* Failed to open the input file! *");
            puts("**********************************");
            return 0;
        }
        puts("**********************************");
    }
    if (oFileFlag)
    {
        puts("**********************************");
        puts("*  Preparing the output file ... *");
        oFile = fopen(oFilenamePtr, "wb+");
        if (oFile == NULL)
        {
            puts("*Failed to open the output file! *");
            puts("**********************************");
            return 0;
        }   
        puts("**********************************");
    }
    result = cryptoIO(operate - 1);
    if (iFile != stdin)
        fclose(iFile);
    if (oFile != stdout)
        fclose(oFile);
    iFile = NULL;
    oFile = NULL;
    free(keyPtr);
    keyPtr = NULL;
    return result;
}

int cryptoIO(int operate)
{
    int result = 0;
    int len = 0;
    int bufLength, writeLength;
    puts("**********************************");
    puts("*     Starting to do cipher      *");
    puts("**********************************");
    if (!iFileFlag)
    {
        puts("Input your text, within one line ...");
        iFile = stdin;
    }
    srcPtr = (char *)malloc(48);
    destPtr = (char *)malloc(48);
    memset(srcPtr, 0, sizeof(srcPtr));
    memset(destPtr, 0, sizeof(destPtr));
    if (blockFlag)
    {
        if (operate == doEncrypt)
        {
        	bufLength = 8;
        }
        else
        {
        	bufLength = 16;
        }
    }
    else
    {
        if (operate == doEncrypt)
        {
            bufLength = strlen(keyPtr);
        }
        else
        {
            bufLength = strlen(keyPtr) * 2;
        }
    }
    fflush(iFile);
    if (!oFileFlag)
    {
        oFile = stdout;
    }
    do
    {
    	if (iFileFlag)
        	len = fread(srcPtr, 1, bufLength, iFile);
        else
        	len = readBuf(srcPtr, bufLength);
        writeLength = doCipher(srcPtr, len, destPtr, operate, keyPtr, strlen(keyPtr), blockFlag);
        fwrite(destPtr, 1, writeLength, oFile);
        memset(srcPtr, 0, sizeof(srcPtr));
        memset(destPtr, 0, sizeof(destPtr));
    } while (len == bufLength);
    fflush(iFile);
    printf("\n");
    free(srcPtr);
    free(destPtr);
    srcPtr = NULL;
    destPtr = NULL;
    result = 1;
    return result;
}
