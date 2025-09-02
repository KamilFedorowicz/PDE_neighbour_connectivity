#pragma once
#include "MultiBlock.h"


// multiblock is always initialised empty. then as blocks are added to it, we fill in the cell info

MultiBlock::MultiBlock(){}; // always initialises an empty block
    
void MultiBlock::addBlock(Block block)
{
    // check if cell sizes are the same. this is just done for simplicity now
    if(dx==0.0 && dy==0.0)
    {
        dx = block.dx;
        dy = block.dy;
    }
    else if(block.dx!=dx || block.dy!=dy)
    {
        throw std::runtime_error("Incorrect cell sizes!");
    }
    
    for(Cell& cell: block.blockCells)
    {

        
        bool exists = false;
        for(Cell& cellInMultiblock: multiBlockCells)
        {
            // if cells have the same location, then they must be on the interface
            if(cell.x == cellInMultiblock.x && cell.y == cellInMultiblock.y)
            {
                exists = true;
                
                if (cellInMultiblock.north == -1){cellInMultiblock.north = cell.north;}
                if (cellInMultiblock.south == -1){cellInMultiblock.south = cell.south;}
                if (cellInMultiblock.east == -1){cellInMultiblock.east = cell.east;}
                if (cellInMultiblock.west == -1){cellInMultiblock.west = cell.west;}

                break;
            }
            
        }
        
        if(!exists)
        {
            cell.ID = cellID++; // overwrite cell ID only if this is a new cell
            multiBlockCells.push_back(cell);
        }
    }
}



void MultiBlock::displayCells()
{
    for (const Cell& cell : multiBlockCells)
    {
        std::cout << std::left
                  << std::setw(3) << ("ID:")    << std::setw(8) << cell.ID
                  << std::setw(3) << ("x:")     << std::setw(8) << std::fixed << std::setprecision(2) << cell.x
                  << std::setw(3) << ("y:")     << std::setw(8) << std::fixed << std::setprecision(2) << cell.y
                  << std::setw(8) << ("north:") << std::setw(8) << cell.north
                  << std::setw(8) << ("south:") << std::setw(8) << cell.south
                  << std::setw(8) << ("east:")  << std::setw(8) << cell.east
                  << std::setw(8) << ("west:")  << std::setw(8) << cell.west;

        if(cell.north==-1) {std::cout << "North cell! ";}
        if(cell.south==-1) {std::cout << "South cell! ";}
        if(cell.east==-1) {std::cout << "East cell! ";}
        if(cell.west==-1) {std::cout << "West cell! ";}

        std::cout << "\n";
    }
}

size_t MultiBlock::multiBlockSize()
{
    return multiBlockCells.size();
}

const std::vector<Cell> MultiBlock::cellsInMultiblock()
{
    return multiBlockCells;
}
