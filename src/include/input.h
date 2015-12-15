//
// Created by Karl on 12/12/2015.
//

#ifndef SNOWDEVICE_INPUT_H
#define SNOWDEVICE_INPUT_H


class input {
public:
    static void checkForInputAndBlock();

    const static void parseInput(int suppliedKey);

    static void checkForInput();

    static void restoreMap(const int x, const int y, int baseLayer, int playerLayer);
};


#endif //SNOWDEVICE_INPUT_H
