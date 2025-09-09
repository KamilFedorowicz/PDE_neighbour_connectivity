#pragma once
#include "EquationBase.h"
#include "ScalarField.h"
#include "Operators.h"

class Equation01: public EquationBase
{
public:
    Equation01(std::map<std::string, ScalarField*> _scalarFieldMap, double _D_temperature, std::map<std::string, double> constantsMap): scalarFieldMap(_scalarFieldMap), EquationBase(_scalarFieldMap.at("temperature")->getMultiBlock()) // EquationBase needs multiblock to initialise
    {
        scalarFields["temperature"] = &scalarFieldMap.at("temperature")->getScalarValues();
        scalarFields["pressure"] = &scalarFieldMap.at("pressure")->getScalarValues() ;
        D_temperature = constantsMap.at("temperature");
        D_pressure = constantsMap.at("pressure");

    }
    
    void calculate_ddt()
    {
        ScalarField* temperatureFieldPtr = scalarFieldMap.at("temperature");
        
        size_t n_elements = temperatureFieldPtr->getScalarValues().size();
        std::vector<double> sourceTemp(n_elements, 1.0); // add a source term with a unit value
        dTemperature_dt = D_temperature*Operators::Laplacian(*temperatureFieldPtr) + sourceTemp;
        dScalarFields_dt["temperature"] = &dTemperature_dt;
        
        ScalarField* pressureFieldPtr = scalarFieldMap.at("pressure");

        std::vector<double> sourcePress(n_elements, 0.0); // add a source term with a unit value
        dPressure_dt = D_pressure*Operators::Laplacian(*pressureFieldPtr) + sourcePress; // change D_pressure later
        dScalarFields_dt["pressure"] = &dPressure_dt;
    }

    
    std::map<std::string, ScalarField*> getScalarFieldMap()
    {
        return scalarFieldMap;
    }
     
    
private:
    
    // temperature info
    double D_temperature;
    //std::vector<double> temperature;
    std::vector<double> dTemperature_dt;
    
    // pressure info
    double D_pressure;
    //std::vector<double> pressure;
    std::vector<double> dPressure_dt;
    
    
    std::map<std::string, ScalarField*> scalarFieldMap;
    

    
};
