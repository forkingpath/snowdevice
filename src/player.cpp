//
// Created by Karl on 12/12/2015.
//

#include "player.h"
#include "BearLibTerminal.h"

Player::Player(void) {
    playerLayer = 5;
    playerGlyph = (char *) "@";
    playerPosition = Position();
}

Player::Player(int x, int y) {
    playerPosition = Position(x, y, 0);
}

void Player::render() {
    int layer = terminal_state(TK_LAYER);
    int color = terminal_state(TK_BKCOLOR);
    terminal_layer(5);
    terminal_print(playerPosition.posX(), playerPosition.posY(), "[color=red][bkcolor=gray]@");
    terminal_layer(layer);
}

int Player::getPlayerLayer() {
    return playerLayer;
}