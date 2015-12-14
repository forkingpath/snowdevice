//
// Created by Karl on 12/12/2015.
//
#include <engine.h>
#include "BearLibTerminal.h"
#include "input.h"

void input::checkForInputAndBlock() {
    int key = terminal_read();
    parseInput(key);
    return;
}

void input::checkForInput() {
    if (terminal_has_input()) {
        int key = terminal_read();
        parseInput(key);
    }
    return;
}

const void input::parseInput(int suppliedKey) {
    bool didUpdate = false;
    const int x = Engine::getInstance().getCurrentPlayerPosition().posX();
    const int y = Engine::getInstance().getCurrentPlayerPosition().posY();
    switch (suppliedKey) {
        case TK_ESCAPE:
            terminal_close();
            didUpdate = true;
            break;
        case TK_LEFT:
            terminal_clear_area(x, y, 1, 1);
            Engine::getInstance().movePlayerBy(-1, 0);
            didUpdate = true;
            break;
        case TK_RIGHT:
            terminal_clear_area(x, y, 1, 1);
            Engine::getInstance().movePlayerBy(1, 0);
            didUpdate = true;
            break;
        case TK_DOWN:
            terminal_clear_area(x, y, 1, 1);
            Engine::getInstance().movePlayerBy(0, 1);
            didUpdate = true;
            break;
        case TK_UP:
            terminal_clear_area(x, y, 1, 1);
            Engine::getInstance().movePlayerBy(0, -1);
            didUpdate = true;
            break;
        default:
            break;
    }
    if (didUpdate) {
        didUpdate = false;
        terminal_refresh();
    }
}
