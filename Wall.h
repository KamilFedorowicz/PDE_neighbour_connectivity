#pragma once
#include "Block.h"
#include "MultiBlock.h"
#include <stdexcept>

struct Wall
{
    void addVerticalCells(MultiBlock& multiBlock, double x, double y_min, double y_max)
    {
        std::vector<Cell>& multiblockCells = multiBlock.getMultiBlockCells();
        bool someCellWasAdded = false; // a bool to see if at least one cell was added
        for(Cell& cell: multiblockCells)
        {
            bool isWallCell = (cell.south==-1 || cell.north==-1 || cell.west==-1 || cell.east==-1); // checks if the cell is at the wall
            constexpr double eps = 1e-12; // allow for some tolerance for floating point coordinates
            if (std::abs(cell.x - x) < eps && cell.y >= y_min && cell.y <= y_max && isWallCell)
            {
                wallCells.push_back(&cell);
                someCellWasAdded = true;
            }
        }
        // check if the add cells function actually added some cells to the wall
        if(someCellWasAdded==false)
        {
            throw("No cells were added! \n");
        }
    }
    
    void addHorizontalCells(MultiBlock& multiBlock, double x_min, double x_max, double y)
    {
        std::vector<Cell>& multiblockCells = multiBlock.getMultiBlockCells();
        bool someCellWasAdded = false; // a bool to see if at least one cell was added
        for(Cell& cell: multiblockCells)
        {
            bool isWallCell = (cell.south==-1 || cell.north==-1 || cell.west==-1 || cell.east==-1); // checks if the cell is at the wall
            constexpr double eps = 1e-12;
            if(cell.x >= x_min && cell.x <= x_max && std::abs(cell.y - y) < eps && isWallCell)
            {
                wallCells.push_back(&cell);
                someCellWasAdded = true;
            }
        }
        // check if the add cells function actually added some cells to the wall
        if(someCellWasAdded==false)
        {
            throw("No cells were added! \n");
        }
    }
    
    void displayCellIDs()
    {
        std::cout << "Wall cells: " << std::endl;
        for(Cell* pcell: wallCells)
        {
            std::cout << "ID: " << pcell->ID << ", ";
        }
        std::cout << std::endl;
    }
    
    std::vector<Cell*> wallCells{};

};
