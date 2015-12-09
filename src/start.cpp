#include <cstdio>
#include "libtcod.hpp"

// Hide the console window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
	TCODConsole::initRoot(80, 50, "C++ libtcod tutorial");
	TCODConsole::root->printEx(40, 25, TCOD_BKGND_NONE, TCOD_CENTER, "Hello world");
	TCODConsole::flush();
	TCODConsole::waitForKeypress(true);

	return 0;

}