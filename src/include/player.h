//
// Created by Karl on 12/12/2015.
//
#include "Inventory.h"
#include "position.h"

#ifndef SNOWDEVICE_PLAYER_H
#define SNOWDEVICE_PLAYER_H


struct Player {
    char *playerGlyph;
public:
    Player();

    Player(int, int);

    void render();

    Position playerPosition;
    Inventory playerInventory;
};


#endif //SNOWDEVICE_PLAYER_H
