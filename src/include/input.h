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
};


#endif //SNOWDEVICE_INPUT_H
