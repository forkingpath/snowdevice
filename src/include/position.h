//
// Created by Karl on 12/12/2015.
//

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

    const int posX();

    const int posY();

    const int posZ();

    void setX(int);

    void setY(int);

    void setZ(int);
};


#endif //SNOWDEVICE_POSITION_H
