#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            
            wchar_t* txt = entry.szExeFile;
            wstring ws(txt);
            string str(ws.begin(), ws.end());

            if (str == string("TestRemoteDll.exe"))
            {
                DWORD pid = entry.th32ProcessID;
                HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
                LPVOID lpvoid = VirtualAllocEx(handle, NULL, 100, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                char dllName[] = "InjectedDll.dll";
                SIZE_T result;
                WriteProcessMemory(handle, lpvoid, dllName, strlen(dllName) * sizeof(char), &result);
                PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
                    GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA");
                HANDLE hThread = CreateRemoteThread(handle, NULL, 0, (PTHREAD_START_ROUTINE)pfnThreadRtn, (LPVOID)lpvoid, 0, NULL);
                //WaitForSingleObject(hThread, INFINITE);
                break;
            }
        }
    }

    CloseHandle(snapshot);

   
}