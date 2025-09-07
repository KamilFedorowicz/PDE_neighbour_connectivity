#pragma once
#include "Wall.h"
#include <map>
#include "ScalarField.h"
#include "MultiBlock.h"
#include <algorithm>

enum class BCType {
    FixedValue,
    ZeroGradient
};

class FieldBC
{
public:
    FieldBC(MultiBlock& multiblock)
    {
        std::vector<Cell>& multiblockCells = multiblock.getMultiBlockCells();
        for(Cell& cell: multiblockCells)
        {
            if(cell.south==-1 || cell.north==-1 || cell.east==-1 || cell.west==-1)
            {
                cellsWithoutBC.push_back(&cell);
            }
        }
        
        
    };

    void addFixedValueWall(Wall& wall, double value)
    {
        auto it = std::find(zeroGradientWalls.begin(), zeroGradientWalls.end(), &wall); // check if the wall is already in the zero gradient walls
        if(it!=zeroGradientWalls.end())
        {
            throw std::runtime_error("Wall already assigned a zero gradient BC!");
        }
        fixedValueWalls[&wall] = value; // assign a value to the map
        updateCellsWithoutBC(wall);
        
    }
    
    void addZeroGradientWall(Wall& wall)
    {
        auto it = fixedValueWalls.find(&wall);
        if(it!=fixedValueWalls.end())
        {
            throw std::runtime_error("Wall already assigned a fixed value BC!");
        }
        zeroGradientWalls.push_back(&wall);
        updateCellsWithoutBC(wall);

    }
    
    void apply(ScalarField& scalarField)
    {
        applyFixedValueBC(scalarField);
        applyZeroGradientBC(scalarField);
        // to do: iterate over zero gradient BCs
    }
    
    // when adding a wall BC, look at the list of cells without BC and erase those for which the BC was added
    void updateCellsWithoutBC(Wall& wall)
    {
        for(Cell* cellPtr: wall.wallCells)
        {
            auto it = std::find(cellsWithoutBC.begin(), cellsWithoutBC.end(), cellPtr);
            if(it!=cellsWithoutBC.end())
            {
                cellsWithoutBC.erase(it);
            }
        }
        std::cout << "Cells without BC: " << cellsWithoutBC.size() << std::endl;
    }
    
    size_t uninitialisedBC_cells()
    {
        return cellsWithoutBC.size();
    }
    
    void applyFixedValueBC(ScalarField& scalarField)
    {
        std::vector<double>& field = scalarField.getScalarValues();
        // iterating over fixed value BCs
        for(auto it = fixedValueWalls.begin(); it!=fixedValueWalls.end(); ++it)
        {
            Wall* wall = it->first;
            double value = it->second;
            
            for(Cell* cellPtr: wall->wallCells)
            {
                Cell& cell = *cellPtr;
                int ID = cell.ID;
                field[ID] = value;
            }
        }
    }
    
    void applyZeroGradientBC(ScalarField& scalarField)
    {
        std::vector<double>& field = scalarField.getScalarValues();
        for(auto wallIt = zeroGradientWalls.begin(); wallIt!=zeroGradientWalls.end(); wallIt++)
        {
            Wall* wall = *wallIt;
            for(Cell* cellPtr: wall->wallCells)
            {
                Cell& cell = *cellPtr;
                int ID = cell.ID;
                
                if(cell.north==-1)
                {
                    field[ID] = field[cell.south];
                }
                if(cell.south==-1)
                {
                    field[ID] = field[cell.north];
                }
                if(cell.west==-1)
                {
                    field[ID] = field[cell.east];
                }
                if(cell.east==-1)
                {
                    field[ID] = field[cell.west];
                }
            }
        }
    }
    
private:
    std::map<Wall*, double> fixedValueWalls;   // correct
    std::vector<Wall*> zeroGradientWalls;
    std::vector<Cell*> cellsWithoutBC{};
};
