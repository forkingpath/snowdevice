//
// Created by Karl on 12/12/2015.
//
#include "cereal.hpp"
#ifndef SNOWDEVICE_POSITION_H
#define SNOWDEVICE_POSITION_H


struct Position {
private:
    int x;
    int y;
    int z;
public:
    Position();

    Position(int, int, int);

    int posX();

    int posY();

    int posZ();

    void setX(int);

    void setY(int);

    void setZ(int);

    template<class Archive>
    void serialize(Archive &archive) {
        archive(x, y, z);
    }
};


#endif //SNOWDEVICE_POSITION_H
