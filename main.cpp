#include <iostream>
#include "Block.h"
#include "MultiBlock.h"
#include "ScalarField.h"

int main(int argc, const char * argv[]) {
    
    // to do: impose BC (just fixed value for now)
    // then introduce some diffrential operators and solve
    
    int nx1 = 4;
    int ny1 = 4;
    double start_x1=0;
    double start_y1=0;
    double end_x1=1;
    double end_y1=1;
    
    Block block1(nx1, ny1, start_x1, start_y1, end_x1, end_y1);
    
    int nx2 = 4;
    int ny2 = 4;
    double start_x2=1;
    double start_y2=0;
    double end_x2=2;
    double end_y2=1;
    Block block2(nx2, ny2, start_x2, start_y2, end_x2, end_y2);
    
    int nx3 = 4;
    int ny3 = 4;
    double start_x3=0;
    double start_y3=1;
    double end_x3=1;
    double end_y3=2;
    Block block3(nx3, ny3, start_x3, start_y3, end_x3, end_y3);
    
    MultiBlock multiblock;
    multiblock.addBlock(block1);
    std::cout << "Before" << std::endl;
    multiblock.displayCells();
    std::cout << "After" << std::endl;
    multiblock.addBlock(block2);
    multiblock.addBlock(block3);
    multiblock.displayCells();
    
    ScalarField scalarField(multiblock, 3.0);
    scalarField.displayScalarField();
    
    // insert code here...
    std::cout << "Code ended!\n";
    return 0;
}

