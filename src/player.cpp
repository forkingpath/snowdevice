//
// Created by Karl on 12/12/2015.
//

#include "player.h"
#include "BearLibTerminal.h"

Player::Player(void) {
    playerGlyph = (char *) "@";
    playerPosition = Position();
}

Player::Player(int x, int y) {
    playerPosition = Position(x, y, 0);
}

void Player::render() {
    terminal_print(playerPosition.posX(), playerPosition.posY(), "@");
}