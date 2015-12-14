//
// Created by Karl on 12/12/2015.
//
#include <Level.h>
#include "BearLibTerminal.h"
#include "engine.h"
#include "input.h"

int Engine::run() {
    mainCharacter = Player(10, 10);
    Level mainLevel("longer_seed", terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
    mainLevel.Generate();
    terminal_layer(0);
    Grid levelGrid = mainLevel.GetGrid();

    terminal_layer(1);
    mainCharacter.render();
    terminal_refresh();
    while (terminal_peek() != TK_CLOSE) {
        input::checkForInput();
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

Player Engine::getCurrentPlayer() {
    return this->mainCharacter;
}

Position Engine::getCurrentPlayerPosition() {
    return this->mainCharacter.playerPosition;
}