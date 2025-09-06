#pragma once
#include "Wall.h"
#include <map>
#include "ScalarField.h"
#include "MultiBlock.h"

enum class BCType {
    FixedValue,
    ZeroGradient
};

class FieldBC
{
public:
    FieldBC() = default;

    void addFixedValueWall(Wall& wall, double value)
    {
        fixedValueWalls[&wall] = value;
    }
    
    void addZeroGradientWall(Wall& wall)
    {
        zeroGradientWalls.push_back(&wall);
    }
    
    void apply(ScalarField& scalarField)
    {
        std::vector<double>& field = scalarField.getScalarValues();
        MultiBlock& multiblock = scalarField.getMultiBlock();
        
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
        
        // to do: iterate over zero gradient BCs
        
        
    }
    
private:
    std::map<Wall*, double> fixedValueWalls;   // correct
    std::vector<Wall*> zeroGradientWalls;
};
