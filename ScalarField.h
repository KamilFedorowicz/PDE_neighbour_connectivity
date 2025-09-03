#pragma once
#include "MultiBlock.h"

class ScalarField
{
public:
    ScalarField(MultiBlock _multiBlock, double initialValue): multiBlock(_multiBlock)
    {
        // just initialise the scalar field on the whole multiBlock to initialValue
        scalarValues = std::vector<double>(multiBlock.multiBlockSize(), initialValue);
    }
    
    void displayScalarField()
    {
        for(double val: scalarValues)
        {
            std::cout << val << ", ";
        }
        std::cout << std::endl;
    }
    
    std::vector<double>& getScalarValues()
    {
        return scalarValues;
    }
    
    MultiBlock& getMultiBlock()
    {
        return multiBlock;
    }
    
    
private:
    std::vector<double> scalarValues; // n-th element of the scalar field corresponds to the n-th element of the MultiBlock
    MultiBlock multiBlock;
    
};
