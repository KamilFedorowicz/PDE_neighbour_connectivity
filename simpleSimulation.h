#pragma once
#include "Block.h"
#include "MultiBlock.h"
#include "ScalarField.h"
#include "Operators.h"
#include "savingOutput.h"
#include "Wall.h"
#include "FieldBC.h"

void runSimulation()
{
    int nx1 = 3;
    int ny1 = 3;
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
    int ny3 = ny1;
    double start_x3=0;
    double start_y3=1;
    double end_x3=1;
    double end_y3=2;
    Block block3(nx3, ny3, start_x3, start_y3, end_x3, end_y3);
    
     
    
    MultiBlock multiblock;
    multiblock.addBlock(block1);
    std::cout << "Adding second block: " << std::endl;
    multiblock.displayCells();
    
    multiblock.addBlock(block2);
    std::cout << "Adding second block: " << std::endl;
    multiblock.addBlock(block3);
    multiblock.displayCells();
    
    ScalarField scalarField(multiblock, 0.0);
    
    std::vector<double>& temperature = scalarField.getScalarValues(); // we can modify values through this
    std::vector<double> source(temperature.size(), 1);
    
    std::vector<Cell> multiBlockCells = multiblock.getMultiBlockCells();
    std::vector<double> isBoundary{};
    for(Cell cell: multiBlockCells)
    {
        if(cell.north==-1 || cell.south==-1 || cell.east==-1 || cell.west==-1)
        {
            source[cell.ID] = 0;
            isBoundary.push_back(1);
        }
        else
        {
            isBoundary.push_back(0);
        }
        
    }
    

    Wall wallWest1;
    wallWest1.addVerticalCells(multiblock, 0, 0, 2);
    //wallWest1.displayCellIDs();
    
    Wall wallEast1;
    wallEast1.addVerticalCells(multiblock, 1, 1, 2);
    Wall wallEast2;
    wallEast2.addVerticalCells(multiblock, 2, 0, 1);
    Wall wallNorth1;
    wallNorth1.addHorizontalCells(multiblock, 0, 1, 2);
    Wall wallNorth2;
    wallNorth2.addHorizontalCells(multiblock, 1, 2, 1);
    Wall wallSouth1;
    wallSouth1.addHorizontalCells(multiblock, 0, 2, 0);
    
    
    
    
    
    
    
    
    /*
    double dt = 1e-2;
    double D = 1e-2;
    for(int i=0; i<10000; i++)
    {
        std::vector<double> d_temperature_dt = D*Operators::compute(scalarField) + source;
        temperature = temperature + dt*d_temperature_dt;
    }
    
    std::string result1 = "/Users/Kamil/Desktop/cpp/work_udemy/PDE_solver_connectivity/PDE_solver_connectivity/result1.vtk";
    saveToVTK(result1, scalarField);
     */
    
}


