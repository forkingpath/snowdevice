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

void input::parseInput(int suppliedKey) {
    switch (suppliedKey) {
        case TK_ESCAPE:
            terminal_close();
            break;
        case TK_LEFT:
            Engine::getInstance().movePlayerBy(-1, 0);
            break;
        case TK_RIGHT:
            Engine::getInstance().movePlayerBy(1, 0);
            break;
        case TK_DOWN:
            Engine::getInstance().movePlayerBy(0, 1);
            break;
        case TK_UP:
            Engine::getInstance().movePlayerBy(0, -1);
            break;
        default:
            break;
    }
}
