#include "Block.h"


Block::Block(int _nx, int _ny, double _start_x, double _start_y, double _end_x, double _end_y): nx(_nx), ny(_ny), start_x(_start_x), start_y(_start_y), end_x(_end_x), end_y(_end_y)
{
    dx = (end_x-start_x)/(nx-1);
    dy = (end_y-start_y)/(ny-1);
    
    for(int i=0; i<ny; i++)
    {
        for(int j=0; j<nx; j++)
        {
            Cell cell;
            
            cell.ID = i*nx + j;
            cell.x = start_x + j*dx;
            cell.y = start_y + i*dy;
            
            // east neighbour cell
            if(j==nx-1)
            {
                cell.east = -1;
            } else
            {
                cell.east = cell.ID+1;
            }
            
            // west neighbour cell
            if(j==0)
            {
                cell.west = -1;
            }else
            {
                cell.west = cell.ID-1;
            }
            
            // south neighbour cell
            if(i==0)
            {
                cell.south = -1;
            } else
            {
                cell.south = cell.ID - nx;
            }
            
            // north neighbour cell
            if(i==ny-1)
            {
                cell.north = -1;
            }else
            {
                cell.north = cell.ID + nx;
            }
            
            if(cell.east==-1 || cell.west==-1 || cell.north==-1 || cell.south==-1)
            {
                wallCells.push_back(cell);
            }
            
            blockCells.push_back(cell);
        }
    }
}

void Block::displayCells()
{
    for(int i=0; i<blockCells.size(); i++)
    {
        Cell cell = blockCells[i];
        std::cout << "ID: " << cell.ID << ", x: " << cell.x << ", y: " << cell.y << std::endl;
    }
}

