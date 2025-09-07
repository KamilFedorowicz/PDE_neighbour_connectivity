#pragma once
#include "EquationBase.h"
#include "ScalarField.h"
#include "Operators.h"

class Equation01: public EquationBase
{
public:
    Equation01(ScalarField& _scalarField, double _D_temperature): scalarField(_scalarField), EquationBase(_scalarField.getMultiBlock()), D_temperature(_D_temperature)
    {
        scalarFields["temperature"] = &scalarField.getScalarValues();
    }
    
    void calculate_ddt()
    {
        size_t n_elements = (scalarField.getScalarValues()).size();
        std::vector<double> source(n_elements, 1.0); // add a source term with a unit value
        dTemperature_dt = D_temperature*Operators::Laplacian(scalarField) + source;
        dScalarFields_dt["temperature"] = &dTemperature_dt;
    }

    
private:
    double D_temperature;
    std::vector<double> temperature;
    std::vector<double> dTemperature_dt;
    ScalarField& scalarField;
    

    
};
