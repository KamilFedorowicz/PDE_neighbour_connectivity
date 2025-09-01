#pragma once
#include "Block.h"

// multiblock is always initialised empty. then as blocks are added to it, we fill in the cell info
class Multiblock
{
public:
    Multiblock(){}; // always initialises an empty block
    
    void addBlock(Block block)
    {
        for(Cell cell: block.blockCells)
        {
            cell.ID = cellID;
            multiBlockCells.push_back(cell);
            cellID++;
        }
    }
    
    void displayCells()
    {
        for(int i=0; i<multiBlockCells.size(); i++)
        {
            Cell cell = multiBlockCells[i];
            std::cout << "ID: " << cell.ID << ", x: " << cell.x << ", y: " << cell.y << std::endl;
        }
    }

    
private:
    std::vector<Cell> multiBlockCells{};
    int cellID = 0;
};
