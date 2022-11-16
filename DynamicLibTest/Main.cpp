#include <iostream>
#include <Windows.h>

int main() {
	HINSTANCE load;
	load = LoadLibraryA("DynamicLib.dll");
	typedef int (*func) (char[], char[]);
	func Func;
	char str[] = "123pp";
	char str2[] = "321pp";
	char str3[] = "123pp";
	Func = (func)GetProcAddress(load, "changeMemo");
	Func(str, str2);
	FreeLibrary(load);
	printf_s("%s", str3);
}