#pragma once
#include <vector>
#include <iostream>

struct Cell
{
public:
    int ID;
    int north;
    int south;
    int east;
    int west;
    double x, y;
};

class Block
{
public:
    Block(int _nx, int _ny, double _start_x, double _start_y, double _end_x, double _end_y);
    
    std::vector<Cell> blockCells{};
    std::vector<Cell> wallCells{}; // these are wall cells when a single block is created, but need not be wall cells in a multiblock
    
    void displayCells();
    
    double dx, dy;
private:
    
    int nx, ny;
    double start_x, start_y, end_x, end_y;
};
