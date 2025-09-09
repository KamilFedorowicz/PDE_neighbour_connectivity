#pragma once
#include "FieldBC.h"
#include "MultiBlock.h"

class EquationBase
{
public:
    EquationBase(MultiBlock& _multiblock): multiblock(_multiblock){};
    virtual ~EquationBase() = default;
    virtual void calculate_ddt() = 0;
    virtual std::map<std::string, ScalarField*> getScalarFieldMap() = 0;
    virtual void solve(size_t steps, double dt, FieldBC fieldBC){};
    
    MultiBlock& multiblock;
    std::map<std::string, std::vector<double>*> scalarFields;
    std::map<std::string, std::vector<double>*> dScalarFields_dt;
    
    
};
