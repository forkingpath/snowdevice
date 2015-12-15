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
    int baseLayer = 0;
    int termLayer = terminal_state(TK_LAYER);
    int playerLayer = Engine::getInstance().getCurrentPlayer().getPlayerLayer();
    terminal_layer(playerLayer);
    switch (suppliedKey) {
        case TK_CLOSE:
            terminal_close();
            break;
        case TK_ESCAPE:
            terminal_close();
            break;
        case TK_LEFT:
            terminal_layer(baseLayer);
            Engine::getInstance().movePlayerBy(-1, 0);
            terminal_layer(playerLayer);
            terminal_clear_area(x, y, 1, 1);
            break;
        case TK_RIGHT:
            terminal_layer(baseLayer);
            Engine::getInstance().movePlayerBy(1, 0);
            terminal_layer(playerLayer);
            terminal_clear_area(x, y, 1, 1);
            break;
        case TK_DOWN:
            terminal_layer(baseLayer);
            Engine::getInstance().movePlayerBy(0, 1);
            terminal_layer(playerLayer);
            terminal_clear_area(x, y, 1, 1);
            break;
        case TK_UP:
            terminal_layer(baseLayer);
            Engine::getInstance().movePlayerBy(0, -1);
            terminal_layer(playerLayer);
            terminal_clear_area(x, y, 1, 1);
            break;
        default:
            break;
    }
    terminal_layer(baseLayer);
    terminal_put(x, y, Engine::getInstance().getCurrentLevel()->Pick(x, y));
    terminal_layer(termLayer);
    terminal_refresh();
}
