//
// Created by Karl on 12/12/2015.
//

#include "position.h"

const int Position::posX() {
    return x;
}

const int Position::posY() {
    return y;
}

const int Position::posZ() {
    return z;
}

Position::Position() {
    x = y = z = 0;
}

Position::Position(int suppliedX, int suppliedY, int suppliedZ) {
    x = suppliedX;
    y = suppliedY;
    z = suppliedZ;
}

void Position::setX(int newX) {
    x = newX;
}

void Position::setY(int newY) {
    y = newY;
}

void Position::setZ(int newZ) {
    z = newZ;
}