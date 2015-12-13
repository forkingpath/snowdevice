//
// Created by Karl on 12/12/2015.
//
#include "BearLibTerminal.h"
#include "engine.h"
#include "input.h"

int Engine::run() {
    mainCharacter = Player(10, 10);
    mainCharacter.render();
    terminal_refresh();
    while (terminal_read() != TK_CLOSE) {
        input::checkForInputAndBlock();
        terminal_clear();
    }
    terminal_close();
    return 0;
}

bool Engine::canMovePlayerTo(int x, int y) {
    return true;
}

bool Engine::movePlayerTo(int newX, int newY) {
    if (!canMovePlayerTo(newX, newY)) {
        return false;
    } else {
        mainCharacter.playerPosition.setX(newX);
        mainCharacter.playerPosition.setY(newY);
        return true;
    }
}

void Engine::movePlayerBy(int x, int y) {
    mainCharacter.playerPosition.setX(mainCharacter.playerPosition.posX() + x);
    mainCharacter.playerPosition.setY(mainCharacter.playerPosition.posY() + y);
    mainCharacter.render();
    terminal_refresh();
}

const Player Engine::getCurrentPlayer() {
    return this->mainCharacter;
}