// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"
extern "C" __declspec(dllexport) void changeString(char str[], char str2[]) {

	HANDLE handle = GetCurrentProcess();

	MEMORY_BASIC_INFORMATION mbi;

	SYSTEM_INFO msi;

	ZeroMemory(&mbi, sizeof(mbi));

	GetSystemInfo(&msi);

	for (LPBYTE lpAddress = (LPBYTE)msi.lpMinimumApplicationAddress; lpAddress <= (LPBYTE)msi.lpMaximumApplicationAddress; lpAddress += mbi.RegionSize) {

		if (VirtualQueryEx(handle, lpAddress, &mbi, sizeof(mbi))) {

			if (mbi.Protect == PAGE_READWRITE) {

				UINT64 addr = (UINT64)mbi.BaseAddress;
				for (; addr < (UINT64)mbi.BaseAddress + mbi.RegionSize - strlen(str) - 1; addr++) {

					if (memcmp(str, (LPVOID)addr, strlen(str) + 1) == 0) {
						WriteProcessMemory(handle, (void*)addr, (LPCVOID)str2, strlen(str2) + 1, 0);
						return;
					}

				}
			}

		}

	}
}

