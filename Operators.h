#pragma once
#include "ScalarField.h"

namespace Operators
{

std::vector<double> compute(ScalarField scalarField)
    {
    
    const std::vector<double>& scalarValues = scalarField.getScalarValues();
    MultiBlock& multiBlock = scalarField.getMultiBlock();
    
    std::vector<double> result(scalarValues.size(),0);
    
    std::vector<Cell>& gridCells = multiBlock.getMultiBlockCells();
    const double dx = multiBlock.get_dx();
    const double dy = multiBlock.get_dy();
    
    for(const Cell& cell: gridCells)
    {
        double d2x = 0;
        double d2y = 0;
        
        // look at the cell only if it is not on the bountady
        if(cell.north!=-1 && cell.south!=-1 && cell.east!=-1 && cell.west!=-1)
        {
            d2x = (scalarValues[cell.east] - 2*scalarValues[cell.ID] + scalarValues[cell.west])/(dx*dx);
            d2y = (scalarValues[cell.north] - 2*scalarValues[cell.ID] + scalarValues[cell.south])/(dy*dy);
        }
        
        result[cell.ID] = d2x + d2y;
        
    }
    
     
    return result;
    }
    
}

inline std::vector<double> operator+(const std::vector<double>& a,
                                     const std::vector<double>& b)
{
    if (a.size() != b.size())
    {
        throw std::invalid_argument("Vector sizes must match for operator+");
    }

    std::vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        result[i] = a[i] + b[i];
    }
    return result;
}

inline std::vector<double> operator*(double scalar, const std::vector<double>& v)
{
    std::vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i)
    {
        result[i] = scalar * v[i];
    }
    return result;
}

// vector * scalar
inline std::vector<double> operator*(const std::vector<double>& v, double scalar)
{
    std::vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i)
    {
        result[i] = v[i] * scalar;
    }
    return result;
}

void print(std::vector<double> vect)
{
    for(double a: vect)
    {
        std::cout << a << " ";
    }
}
