#include <iostream>
#include <Windows.h>
#include "..\lab3\MemExpl.h"
using namespace std;

int main() {
	char str[] = "123pp";
	char str2[] = "321pp";
	char str3[] = "123pp";
	changeMemo(str, str2);
	//a();
	cout << str3;
}