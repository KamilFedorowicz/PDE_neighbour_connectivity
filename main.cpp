#include <iostream>
#include "Block.h"
#include "MultiBlock.h"

int main(int argc, const char * argv[]) {
    
    // to do: get multiblock to work, then run all operations on it
    // multiblock should work when connecting
    
    int nx = 10;
    int ny = 10;
    double start_x=0;
    double start_y=0;
    double end_x=1;
    double end_y=1;
    
    Block block1(nx, ny, start_x, start_y, end_x, end_y);
    Block block2(nx, ny, start_x+1, start_y, end_x+1, end_y);
    // block1.displayCells();
    
    Multiblock multiblock;
    multiblock.addBlock(block1);
    multiblock.addBlock(block2);
    multiblock.displayCells();
    
    // insert code here...
    std::cout << "Code ended!\n";
    return 0;
}

