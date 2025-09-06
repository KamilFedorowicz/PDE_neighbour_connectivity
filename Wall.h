#pragma once
#include "Block.h"
#include "MultiBlock.h"

struct Wall
{
    void addVerticalCells(MultiBlock& multiBlock, double x, double y_min, double y_max)
    {
        std::vector<Cell>& multiblockCells = multiBlock.getMultiBlockCells();
        for(Cell& cell: multiblockCells)
        {
            constexpr double eps = 1e-12; // allow for some tolerance for floating point coordinates
            if (std::abs(cell.x - x) < eps && cell.y >= y_min && cell.y <= y_max)
            {
                wallCells.push_back(&cell);
            }
        }
    }
    
    void addHorizontalCells(MultiBlock& multiBlock, double x_min, double x_max, double y)
    {
        std::vector<Cell>& multiblockCells = multiBlock.getMultiBlockCells();
        for(Cell& cell: multiblockCells)
        {
            constexpr double eps = 1e-12;
            if(cell.x >= x_min && cell.x <= x_max && std::abs(cell.y - y) < eps)
            {
                wallCells.push_back(&cell);
            }
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
