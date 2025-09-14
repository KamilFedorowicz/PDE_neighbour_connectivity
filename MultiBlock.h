#pragma once
#include "Block.h"
#include <iomanip>

// multiblock is always initialised empty. then as blocks are added to it, we fill in the cell info
class MultiBlock
{
public:
    MultiBlock(); // always initialises an empty block
    void addBlock(Block block);
    void displayCells();
    size_t multiBlockSize();
    
    std::vector<Cell>& getMultiBlockCells();
    double get_dx() const;
    double get_dy() const;
    
    void checkConsistentGridSpacing(Block block);
    void resetAndUpdateWallCells();
    
private:
    std::vector<Cell> multiBlockCells{};
    std::vector<int> wallCellsIDs{};
    int cellID = 0;
    double dx = 0.0; // set up cell sizes as 0. these will be changed
    double dy = 0.0;
};
