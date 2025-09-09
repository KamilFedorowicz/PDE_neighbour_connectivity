#pragma once
#include "Block.h"
#include "MultiBlock.h"
#include "ScalarField.h"
#include "Operators.h"
#include "savingOutput.h"
#include "Wall.h"
#include "FieldBC.h"
#include "Equation01.h"
#include "Solver.h"

void runSimulation()
{
    int nx1 = 20;
    int ny1 = 20;
    double start_x1=0;
    double start_y1=0;
    double end_x1=1;
    double end_y1=1;
    
    Block block1(nx1, ny1, start_x1, start_y1, end_x1, end_y1);
    
    int nx2 = nx1;
    int ny2 = ny1;
    double start_x2=1;
    double start_y2=0;
    double end_x2=2;
    double end_y2=1;
    Block block2(nx2, ny2, start_x2, start_y2, end_x2, end_y2);
    
    
    int nx3 = nx1;
    int ny3 = 2*(ny1-1)+1; // need to use this to make sure that dy=(end_y-stary_x)/(ny-1) is the same
    double start_x3=0;
    double start_y3=1;
    double end_x3=1;
    double end_y3=3;
    Block block3(nx3, ny3, start_x3, start_y3, end_x3, end_y3);
    
    MultiBlock multiblock;
    multiblock.addBlock(block1);

    multiblock.addBlock(block2);
    multiblock.addBlock(block3);
    multiblock.displayCells();

    // DEFINE TEMPERATURE FIELD
    ScalarField temperatureField(multiblock, 0.0);

    // DEFINE PRESSURE FIELD
    ScalarField pressureField(multiblock, 0.0);

    std::vector<Cell> multiBlockCells = multiblock.getMultiBlockCells();
    
    // DEFINE WALLS
    Wall wallWest1;
    wallWest1.addVerticalCells(multiblock, 0, 0, 3); // x, y_min, y_max
    Wall wallEast1;
    wallEast1.addVerticalCells(multiblock, 1, 1, 3);
    Wall wallEast2;
    wallEast2.addVerticalCells(multiblock, 2, 0, 1);
    Wall wallNorth1;
    wallNorth1.addHorizontalCells(multiblock, 0, 1, 3); // x_min, x_max, y
    Wall wallNorth2;
    wallNorth2.addHorizontalCells(multiblock, 1, 2, 1);
    Wall wallSouth1;
    wallSouth1.addHorizontalCells(multiblock, 0, 2, 0);
    
    // TEMPERATURE BC
    FieldBC tempBC(multiblock);
    tempBC.addFixedValueWall(wallWest1, 0);
    tempBC.addFixedValueWall(wallEast1, 0);
    tempBC.addFixedValueWall(wallNorth2, 0);
    tempBC.addFixedValueWall(wallSouth1, 0);
    tempBC.addZeroGradientWall(wallNorth1);
    tempBC.addZeroGradientWall(wallEast2);
    
    // PRESSURE BC
    FieldBC pressBC(multiblock);
    pressBC.addFixedValueWall(wallWest1, 1);
    pressBC.addFixedValueWall(wallEast1, 0);
    pressBC.addFixedValueWall(wallNorth2, 0);
    pressBC.addFixedValueWall(wallSouth1, 1);
    pressBC.addFixedValueWall(wallNorth1, 0);
    pressBC.addFixedValueWall(wallEast2, 0);
    
    // DEFINE EQUATION CONSTANTS
    double dt = 1e-2;
    double D_temp = 1e-2;
    double D_press = 1e-2;
    std::map<std::string, double> constantsMap;
    constantsMap["temperature"] = D_temp;
    constantsMap["pressure"] = D_press;
    
    size_t iterations = 1000;
    
    std::map<std::string, ScalarField*> scalarFieldMap;
    scalarFieldMap["temperature"] = &temperatureField;
    scalarFieldMap["pressure"] = &pressureField;
    
    Equation01 eq(scalarFieldMap, D_temp, constantsMap);

    Solver solver(eq);
    
    std::map<std::string, FieldBC*> BC_map;
    BC_map["temperature"] = &tempBC;
    BC_map["pressure"] = &pressBC;
    
    solver.solve(iterations, dt, BC_map);
    
    std::string resultTemp = "/Users/Kamil/Desktop/cpp/work_udemy/PDE_solver_connectivity/PDE_solver_connectivity/resultTemp.vtk";
    saveToVTK(resultTemp, temperatureField, "temperature");
    
    std::string resultPress = "/Users/Kamil/Desktop/cpp/work_udemy/PDE_solver_connectivity/PDE_solver_connectivity/resultPress.vtk";
    saveToVTK(resultPress, pressureField, "pressure");
     
    
}


