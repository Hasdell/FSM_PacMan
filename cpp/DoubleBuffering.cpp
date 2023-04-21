#include "DoubleBuffering.h"

void ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(screen[0], &cci);
	SetConsoleCursorInfo(screen[1], &cci);
}
void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(screen[screenIndex]);
	screenIndex = !screenIndex;
}
void ScreenClear()
{
	COORD coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(screen[screenIndex], ' ', 80 * 40, coor, &dw);
}
void ScreenPrint(int x, int y, const char* string)
{
	DWORD dw;
	COORD cursorPosition = { x, y };
	SetConsoleCursorPosition(screen[screenIndex], cursorPosition);
	WriteFile(screen[screenIndex], string, strlen(string), &dw, NULL);
}