//
// Created by Karl on 12/12/2015.
//

#ifndef SNOWDEVICE_SD_ENGINE_H
#define SNOWDEVICE_SD_ENGINE_H


#include "player.h"

class Engine {
public:
    static Engine &getInstance() {
        static Engine instance_;
        return instance_;
    }

    int run();

    bool movePlayerTo(int, int);

    bool canMovePlayerTo(int, int);

    void movePlayerBy(int, int);

    Player getCurrentPlayer();

    Position getCurrentPlayerPosition();
private:
    Player mainCharacter;
};

#endif //SNOWDEVICE_SD_ENGINE_H
