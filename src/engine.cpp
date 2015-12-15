//
// Created by Karl on 12/12/2015.
//
#include <Level.h>
#include "BearLibTerminal.h"
#include "engine.h"
#include "input.h"

int Engine::run() {
    int playerStartX = 10;
    int playerStartY = 10;
    mainCharacter = Player(10, 10);
    Level mainLevel("longer_seed", terminal_state(TK_WIDTH), terminal_state(TK_HEIGHT));
    mainLevel.Generate();
    currentLevel = mainLevel.GetLevel();
    terminal_layer(0);
    levelGrid = mainLevel.GetGrid();
    for (Grid::iterator it = levelGrid.begin(); it != levelGrid.end(); ++it) {
        for (GridLine::iterator itL = it->begin(); itL != it->end(); ++itL) {
            switch (*itL) {
                case Level::TILE_TYPE::Floor:
                    terminal_put((int) std::distance(it->begin(), itL), (int) std::distance(levelGrid.begin(), it),
                                 '#');
                    break;
                case Level::TILE_TYPE::Corridor:
                    terminal_put((int) std::distance(it->begin(), itL), (int) std::distance(levelGrid.begin(), it),
                                 '=');
                    break;
                case Level::TILE_TYPE::Entrance:
                    terminal_put((int) std::distance(it->begin(), itL), (int) std::distance(levelGrid.begin(), it),
                                 '<');
                    break;
                case Level::TILE_TYPE::Empty:
                    terminal_put((int) std::distance(it->begin(), itL), (int) std::distance(levelGrid.begin(), it),
                                 ' ');
                    break;
                case Level::TILE_TYPE::Door:
                    terminal_put((int) std::distance(it->begin(), itL), (int) std::distance(levelGrid.begin(), it),
                                 '+');
                    break;
                case Level::TILE_TYPE::Exit:
                    terminal_put((int) std::distance(it->begin(), itL), (int) std::distance(levelGrid.begin(), it),
                                 '>');
                    break;
                default:
                    break;
            }
        }
        terminal_refresh();
    }
    terminal_layer(0);
    terminal_clear_area(playerStartX, playerStartY, 1, 1);
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
    int tile = levelGrid.at((size_t) y).at((size_t) x);
    return (tile == Level::TILE_TYPE::Corridor ||
            tile == Level::TILE_TYPE::Floor ||
            tile == Level::TILE_TYPE::Door ||
            tile == Level::TILE_TYPE::Entrance ||
            tile == Level::TILE_TYPE::Exit);
}

bool Engine::movePlayerTo(int newX, int newY) {
    int term_layer = terminal_state(TK_LAYER);
    if (!canMovePlayerTo(newX, newY)) {
        return false;
    } else {
        mainCharacter.playerPosition.setX(newX);
        mainCharacter.playerPosition.setY(newY);
        terminal_layer(0);
        terminal_clear_area(newX, newY, 1, 1);
        terminal_layer(term_layer);
        return true;
    }
}

bool Engine::movePlayerBy(int x, int y) {
    int newX = mainCharacter.playerPosition.posX() + x;
    int newY = mainCharacter.playerPosition.posY() + y;
    if (!canMovePlayerTo(newX, newY)) {
        // feedback for pathing
        return false;
    }
    int termLayer = terminal_state(TK_LAYER);
    mainCharacter.playerPosition.setX(mainCharacter.playerPosition.posX() + x);
    mainCharacter.playerPosition.setY(mainCharacter.playerPosition.posY() + y);
    terminal_layer(0);
    terminal_clear_area(mainCharacter.playerPosition.posX(), mainCharacter.playerPosition.posY(), 1, 1);
    terminal_layer(mainCharacter.playerLayer);
    mainCharacter.render();
    return true;
}

Player Engine::getCurrentPlayer() {
    return this->mainCharacter;
}

Position Engine::getCurrentPlayerPosition() {
    return this->mainCharacter.playerPosition;
}

Level *Engine::getCurrentLevel() {
    return currentLevel;
}
