#pragma once
#include "EquationBase.h"
#include "FieldBC.h"
#include "ScalarField.h"

class Solver
{
public:
    Solver(EquationBase& eq): equation(eq), scalarFieldMap(eq.getScalarFieldMap()) {}
    
    void solve(size_t steps, double _dt, std::map<std::string, FieldBC*> fieldBCs)
    {
        
        for(auto kv: fieldBCs)
        {
            auto fieldBC = kv.second;
            
            if(fieldBC->uninitialisedBC_cells()>0)
            {
                throw("Some cells are uninitialised! \n");
            }
        
        }
        
        
        dt = _dt;
        for(size_t i=0; i<steps; i++)
        {
            std::cout << "Step: " << i << std::endl;
            equation.calculate_ddt();
            updateFields(fieldBCs);
            
            
        }
    }
    
    void updateFields(std::map<std::string, FieldBC*> fieldBCs)
    {
        for (auto it = equation.dScalarFields_dt.begin(); it != equation.dScalarFields_dt.end(); it++)
        {
            auto fieldName = it->first;
            auto dField = it->second; // pointer to derivative
            
            std::vector<double> oldField = *(equation.scalarFields[fieldName]);
            auto test1 = *(equation.scalarFields[fieldName]);
            *(equation.scalarFields[fieldName]) = *(equation.scalarFields[fieldName]) + dt*(*dField) ;
            std::vector<double> newField = *(equation.scalarFields[fieldName]);
            
            fieldBCs.at(fieldName)->apply(*scalarFieldMap.at(fieldName));
            // double error = ... ; // this is to be done later
        }
        
    }
    
    
private:
    std::map<std::string, ScalarField*> scalarFieldMap;
    EquationBase& equation;
    double dt;
    
};
