#include <BearLibTerminal.h>
#include <cstdio>
// Hide the console window

int main()
{
	terminal_open();
	terminal_print(1, 1, "Hello, world!");
	terminal_refresh();
	while (terminal_read() != TK_CLOSE);
	terminal_close();
	return 0;

}