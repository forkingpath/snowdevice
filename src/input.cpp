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
    const int x = Engine::getInstance().getCurrentPlayerPosition().posX();
    const int y = Engine::getInstance().getCurrentPlayerPosition().posY();
    bool didUpdate = false;
    int termLayer = terminal_state(TK_LAYER);
    int baseLayer = 0;
    int playerLayer = Engine::getInstance().getCurrentPlayer().getPlayerLayer();
    switch (suppliedKey) {
        case TK_CLOSE:
            terminal_close();
            break;
        case TK_ESCAPE:
            terminal_close();
            break;
        case TK_LEFT:
            terminal_layer(baseLayer);
            didUpdate = Engine::getInstance().movePlayerBy(-1, 0);
            break;
        case TK_RIGHT:
            terminal_layer(baseLayer);
            didUpdate = Engine::getInstance().movePlayerBy(1, 0);
            break;
        case TK_DOWN:
            terminal_layer(baseLayer);
            didUpdate = Engine::getInstance().movePlayerBy(0, 1);
            break;
        case TK_UP:
            terminal_layer(baseLayer);
            didUpdate = Engine::getInstance().movePlayerBy(0, -1);
            break;
        default:
            break;
    }
    if (didUpdate) {
        restoreMap(x, y, baseLayer, playerLayer);
    }
    terminal_refresh();
}

void input::restoreMap(const int x, const int y, int baseLayer, int playerLayer) {
    terminal_layer(baseLayer);
    terminal_put(x, y, Engine::getInstance().getCurrentLevel()->Pick(x, y));
    terminal_layer(playerLayer);
    terminal_clear_area(x, y, 1, 1);
}
