//
// Created by Karl on 12/13/2015.
//

#ifndef SNOWDEVICE_LEVEL_H
#define SNOWDEVICE_LEVEL_H

#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <random>
#include <string>

#include "AABB.h"
#include "Node.h"

typedef AABB Room;
typedef std::vector<Vec2> Path;
typedef std::vector<unsigned int> GridLine;
typedef std::vector<std::vector<unsigned int> > Grid;


class Level {
public:
    Level(std::string seed, int width, int height);

    ~Level();

    enum TILE_TYPE {
        Empty = 0, Floor = 1, Corridor = 2, Entrance = 3, Exit = 4, Door = 5, Treasure = 6, Monster = 7, Trap = 8
    };
private:
    int mWidth;
    int mHeight;
    int mUnitSquare;
    std::mt19937 mRandGen;
    std::uniform_real_distribution<float> mUniDistr;
    std::seed_seq mSeedSeq;
    std::string mSeedString;
    std::vector<Room> mRooms;
    std::vector<Path> mCorridors;
    std::vector<Vec2> mTreasures;
    std::vector<Vec2> mMonsters;
    std::vector<Vec2> mTraps;
    Vec2 mEntrance;
    Vec2 mExit;
    Grid mGrid;
    Node<AABB> mRootNode;
public:
    void Generate(void);

    Grid GetGrid(void);

    Level *GetLevel(void);

    char Pick(int x, int y);

    char InterpretEnum(unsigned int enumVal);
private:
    void ClearGrid();

    void SplitSpace(Node<AABB> *node);

    void FindRoomsDigCorridors();

    void PlaceEntranceAndExit();

    void PlaceDoors();

    void BakeFloor();

    void BakeDetails();
};


#endif //SNOWDEVICE_LEVEL_H
