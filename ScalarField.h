#pragma once
#include "MultiBlock.h"

class ScalarField
{
public:
    ScalarField(MultiBlock multiBlock, double initialValue)
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
    
private:
    std::vector<double> scalarValues; // n-th element of the scalar field corresponds to the n-th element of the MultiBlock
    
};
