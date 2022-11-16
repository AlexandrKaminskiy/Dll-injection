#include <Windows.h>
#include <stdio.h>

void changeMemo(char str[] ,char str2[]) {

	HANDLE handle = GetCurrentProcess();
	
	MEMORY_BASIC_INFORMATION mbi;

	SYSTEM_INFO msi;

	ZeroMemory(&mbi, sizeof(mbi));
	
	GetSystemInfo(&msi);

	for (LPBYTE lpAddress = (LPBYTE)msi.lpMinimumApplicationAddress; lpAddress <= (LPBYTE)msi.lpMaximumApplicationAddress; lpAddress += mbi.RegionSize) {

		if (VirtualQueryEx(handle, lpAddress, &mbi, sizeof(mbi))) {
		
			if (mbi.Protect == PAGE_READWRITE) {
				
				UINT64 addr = (UINT64)mbi.BaseAddress;
				for (; addr < (UINT64)mbi.BaseAddress + mbi.RegionSize - 5; addr++) {
				
					if (memcmp(str, (LPVOID)addr, 5) == 0 && str != (LPVOID)addr) {
						WriteProcessMemory(handle, (void*)addr, (LPCVOID)str2, 3, 0);
					}
					
				}
			}

		}

	}

}
int a() {
	return 0;
}