//
// Created by Karl on 12/13/2015.
//
#include <iostream>
#include <cmath>
#include <AABB.h>
#include "Corridor.h"
#include "Node.h"
#include "Level.h"


#define RAND_GEN_PERCENTAGE (float)mUniDistr(mRandGen)


// Constructors
Level::Level(std::string seed, int width, int height) : mWidth(width), mHeight(height),
                                                        mRootNode(nullptr, AABB(0, 0, width, height)) {
    // init grid
    mGrid = std::vector<std::vector<unsigned int> >(mHeight, std::vector<unsigned int>(mWidth, TILE_TYPE::Empty));

    mSeedString = seed;
    mSeedSeq = std::seed_seq(mSeedString.begin(), mSeedString.end());
    mRandGen = std::mt19937(mSeedSeq);
    mUniDistr = std::uniform_real_distribution<float>(0.0f, 1.0f);
}


Level::~Level() { }

// Public Methods
void Level::Generate() {
    // Clean-up if already generated
    mRootNode = Node<AABB>(nullptr, AABB(0, 0, mWidth, mHeight));
    mRooms.clear();
    mCorridors.clear();
    mTreasures.clear();
    mMonsters.clear();
    mTraps.clear();
    ClearGrid();

    // Generate dungeon parts
    SplitSpace(&mRootNode);
    FindRoomsDigCorridors();
    BakeFloor();
    PlaceEntranceAndExit();
    PlaceDoors();
    BakeDetails();
    std::cout << "Dungeon Generation complete!" << std::endl;

#ifdef DEBUG
    for (int i = 0; i < mGrid.size(); i++) {
        for (int j = 0; j < mGrid[i].size(); j++) {
            std::cout << mGrid[i][j];
        }
        std::cout << std::endl;
    }
#endif
}


Grid Level::GetGrid(void) {
    return mGrid;
}


// Private Methods
void Level::ClearGrid() {
    mGrid.clear();
    mGrid = std::vector<std::vector<unsigned int> >(mHeight, std::vector<unsigned int>(mWidth, TILE_TYPE::Empty));
}

void Level::SplitSpace(Node<AABB> *node) {

    // Choose how and where to split
    float ratio = (float) node->GetData().getWidth() / node->GetData().getHeight();
    bool splitVertical = true;
    if (ratio < 1.0f)
        splitVertical = false;


    float split = RAND_GEN_PERCENTAGE;
    do {
        split = RAND_GEN_PERCENTAGE;
    } while (split < 0.4f || split > 0.6f);


    // Create and calculate the 2 subspaces
    // of the splitted one.
    AABB subspaceA, subspaceB;

    if (splitVertical) {
        int splitX = node->GetData().X() + (int) (split * node->GetData().getWidth());
        subspaceA = AABB(node->GetData().X(), node->GetData().Y(),
                         (int) (split * node->GetData().getWidth()), node->GetData().getHeight());
        subspaceB = AABB(splitX, node->GetData().Y(),
                         (int) ((1 - split) * node->GetData().getWidth()), node->GetData().getHeight());
    } else {
        int splitY = node->GetData().Y() + (int) (split * node->GetData().getHeight());
        subspaceA = AABB(node->GetData().X(), node->GetData().Y(),
                         node->GetData().getWidth(), (int) (split * node->GetData().getHeight()));
        subspaceB = AABB(node->GetData().X(), splitY,
                         node->GetData().getWidth(), (int) ((1 - split) * node->GetData().getHeight()));
    }

#ifdef DEBUG
    std::cout << "Splitting [" << node->GetData().X() << ", " << node->GetData().Y() << ", " <<
    node->GetData().getWidth() << ", " << node->GetData().getHeight() << "] into:" << std::endl;
    std::cout << "Space A: [" << subspaceA.X() << ", " << subspaceA.Y() << ", " << subspaceA.getWidth() << ", " <<
    subspaceA.getHeight() << "]" << std::endl;
    std::cout << "Space B: [" << subspaceB.X() << ", " << subspaceB.Y() << ", " << subspaceB.getWidth() << ", " <<
    subspaceB.getHeight() << "]" << std::endl;
    std::cout << std::endl;
#endif

    // Add subspaces to the current node
    node->MakeLeftChild(subspaceA);
    node->MakeRightChild(subspaceB);

    // Decide if we need to split more
    // and continue recursion.
    if (subspaceA.getWidth() > 7 && subspaceA.getHeight() > 6)
        SplitSpace(node->GetLeftChild());
    if (subspaceB.getWidth() > 7 && subspaceB.getHeight() > 6)
        SplitSpace(node->GetRightChild());

} // method ends here

void Level::FindRoomsDigCorridors() {
    Node<AABB>::NodeIterator it(&mRootNode);

    // Iterate over bsp-tree and add Rooms that
    // adhere to the minimum size required
    while (it.Next() != false) {
        if (it.IsLeaf() == true && it.GetData().getWidth() > 3 && it.GetData().getHeight() > 3) {
            mRooms.push_back(AABB(it.GetData().X() + 1, it.GetData().Y() + 1, it.GetData().getWidth() - 2,
                                  it.GetData().getHeight() - 2));
#ifdef DEBUG
            std::cout << "Added [" << it.GetData().X() << ", " << it.GetData().Y() << ", " << it.GetData().getWidth() <<
            ", " << it.GetData().getHeight() << "]" << std::endl;
#endif
        }
    }

    it.Reset();

    // Re-iterate over bsp-tree and create
    // corridors using pathfind function (grid-based)
    while (it.Next() != false) {
        if (!it.IsLeaf()) {
            Path corridor = FindPath(it.GetNode()->GetLeftChild()->GetData().getCenter(),
                                     it.GetNode()->GetRightChild()->GetData().getCenter());
            mCorridors.push_back(corridor);

#ifdef DEBUG
            std::cout << "Corridor points from [" << it.GetNode()->GetLeftChild()->GetData().getCenter().x << ", " <<
            it.GetNode()->GetLeftChild()->GetData().getCenter().y << "]" << std::endl;
            std::cout << " to [" << it.GetNode()->GetRightChild()->GetData().getCenter().x << ", " <<
            it.GetNode()->GetRightChild()->GetData().getCenter().y << "]" << std::endl;
            for (Path::iterator itP = corridor.begin(); itP != corridor.end(); itP++) {
                std::cout << itP->x << ", " << itP->y << std::endl;
            }
            std::cout << std::endl;
#endif
        }
    }

} // method ends here


void Level::PlaceDoors() {
    // Detects corridor-room crossings and
    // places doors (door=5)
    // *fix* weird door placement sometimes
    for (int i = 1; i < mGrid.size() - 1; i++) {
        for (int j = 1; j < mGrid[i].size() - 1; j++) {
            if (mGrid[i][j] == 2 &&
                (mGrid[i + 1][j] == 1 || mGrid[i - 1][j] == 1 || mGrid[i][j + 1] == 1 || mGrid[i][j - 1] == 1) &&
                (mGrid[i + 1][j] != 5 && mGrid[i - 1][j] != 5 && mGrid[i][j + 1] != 5 && mGrid[i][j - 1] != 5) &&
                ((mGrid[i + 1][j] == 0 && mGrid[i - 1][j] == 0) || (mGrid[i][j + 1] == 0 && mGrid[i][j - 1] == 0))) {
                mGrid[i][j] = TILE_TYPE::Door;
            }
        }
    }
}

void Level::BakeFloor() {
    std::cout << std::endl << "Baking data on mGrid..." << std::endl;

    // Fill rooms on the grid with the proper id (floor=1)
    for (std::vector<Room>::iterator it = mRooms.begin(); it != mRooms.end(); ++it) {
        for (int i = it->Y(); i < it->Y() + it->getHeight(); i++) {
            for (int j = it->X(); j < it->X() + it->getWidth(); j++) {
                mGrid[i][j] = TILE_TYPE::Floor;
            }
        }
    }

    // Fill corridors on the grid with the proper id (corridor=2)
    for (std::vector<Path>::iterator it = mCorridors.begin(); it != mCorridors.end(); ++it) {
        for (Path::iterator pathIt = it->begin(); pathIt != it->end(); ++pathIt) {
            if (mGrid[pathIt->y][pathIt->x] != 1)
                mGrid[pathIt->y][pathIt->x] = TILE_TYPE::Corridor;
        }
    }

} // method ends here

void Level::BakeDetails() {
    // Write the details of the dungeon to its grid.
    // Details = Entrance/Exit, Monsters, Treasure and Traps

    // Entrance and exit...
    mGrid[mEntrance.y][mEntrance.x] = TILE_TYPE::Entrance;
    mGrid[mExit.y][mExit.x] = TILE_TYPE::Exit;
    // Monsters...
    for (std::vector<Vec2>::iterator it = mMonsters.begin(); it != mMonsters.end(); ++it)
        mGrid[it->y][it->x] = TILE_TYPE::Monster;
    // Treasure...
    for (std::vector<Vec2>::iterator it = mTreasures.begin(); it != mTreasures.end(); ++it)
        mGrid[it->y][it->x] = TILE_TYPE::Treasure;
    // Traps...
    for (std::vector<Vec2>::iterator it = mTraps.begin(); it != mTraps.end(); ++it)
        mGrid[it->y][it->x] = TILE_TYPE::Trap;
}


void Level::PlaceEntranceAndExit() {

    int i, j; // i is the index of the room with the entrance
    // j is the index of the room with the exit
    i = j = 0;

    // There are N rooms, choose if entrance will be in one
    // of the rooms of the first half (0 to N/2) or on the
    // second (N/2 to N). Exit will be on the other.
    if (RAND_GEN_PERCENTAGE > 0.5f) {
        i = floorf(RAND_GEN_PERCENTAGE * (mRooms.size() / 2.0f));
        j = floorf((mRooms.size() / 2.0f) + RAND_GEN_PERCENTAGE * (mRooms.size() / 2.0f));
    } else {
        j = floorf(RAND_GEN_PERCENTAGE * (mRooms.size() / 2.0f));
        i = floorf((mRooms.size() / 2.0f) + RAND_GEN_PERCENTAGE * (mRooms.size() / 2.0f));
    }

    // Set the center of the rooms as entrance and exit
    mEntrance = mRooms[i].getCenter();
    mExit = mRooms[j].getCenter();

#ifdef DEBUG
    std::cout << "Entrance: [" << mEntrance.x << ", " << mEntrance.y << "]" << std::endl;
    std::cout << "Exit: [" << mExit.x << ", " << mExit.y << "]" << std::endl;
#endif

} // method ends here
