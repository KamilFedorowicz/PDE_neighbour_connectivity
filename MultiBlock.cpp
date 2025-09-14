#include "MultiBlock.h"


// multiblock is always initialised empty. then as blocks are added to it, we fill in the cell info

MultiBlock::MultiBlock(){}; // always initialises an empty block
    
void MultiBlock::addBlock(Block block)
{
    // check correct cell spacing
    checkConsistentGridSpacing(block);
    
    std::cout << "difference 1: " << abs(block.dx - dx) << std::endl;
    std::cout << "difference 2: " << abs(block.dy - dy) << std::endl;
    
    if (dx == 0.0 && dy == 0.0) { dx = block.dx; dy = block.dy; }


    // Map from block-local ID -> multiblock global ID
    std::unordered_map<int, int> localToGlobal;

    // 1) First pass: add new cells (DO NOT mutate IDs in the block)
    for (const Cell& cell : block.blockCells)
    {
        bool exists = false;

        // Find by coordinates (O(N)); OK for now. (If needed, add a coord->ID map.)
        for (const Cell& existing : multiBlockCells)
        {
            if (cell.x == existing.x && cell.y == existing.y)
            {
                exists = true;
                // Local (block) cell maps to existing global ID
                localToGlobal[cell.ID] = existing.ID;
                break;
            }
        }

        if (!exists)
        {
            // Create a copy with a new global ID; DON'T change the block's cell
            Cell copy = cell;
            copy.ID = cellID++;                   // new global ID
            multiBlockCells.push_back(copy);
            localToGlobal[cell.ID] = copy.ID;     // map local->global
        }
    }

    // 2) Second pass: wire neighbors using the map; set reverse links too
    for (const Cell& cell : block.blockCells)
    {
        const int gID = localToGlobal[cell.ID];
        Cell& gCell = multiBlockCells[gID]; // gCell is a multiblock representation of the cell

        // North
        if (cell.north != -1) // if the block cell had a north neighbour
        {
            auto it = localToGlobal.find(cell.north); // take the north index of a cell and find this index in the map
            if (it != localToGlobal.end())
            {
                const int nID = it->second; // take the index of the north cell after mapping
                gCell.north = nID; // assign the north id to the global cell
                
                if (multiBlockCells[nID].south != gID) multiBlockCells[nID].south = gID; // set up backward connectivity
            }
        }

        // South
        if (cell.south != -1) {
            auto it = localToGlobal.find(cell.south);
            if (it != localToGlobal.end()) {
                const int sID = it->second;
                gCell.south = sID;
                if (multiBlockCells[sID].north != gID) multiBlockCells[sID].north = gID;
            }
        }

        // East
        if (cell.east != -1) {
            auto it = localToGlobal.find(cell.east);
            if (it != localToGlobal.end()) {
                const int eID = it->second;
                gCell.east = eID;
                if (multiBlockCells[eID].west != gID) multiBlockCells[eID].west = gID;
            }
        }

        // West
        if (cell.west != -1) {
            auto it = localToGlobal.find(cell.west);
            if (it != localToGlobal.end()) {
                const int wID = it->second;
                gCell.west = wID;
                if (multiBlockCells[wID].east != gID) multiBlockCells[wID].east = gID;
            }
        }
    }
    
    resetAndUpdateWallCells();
}

void MultiBlock::resetAndUpdateWallCells()
{
    wallCellsIDs = {};
    for(Cell cell: multiBlockCells)
    {
        if(cell.north==-1 || cell.south==-1 || cell.east==-1 || cell.west==-1)
        {
            wallCellsIDs.push_back(cell.ID);
        }
    }
}

void MultiBlock::checkConsistentGridSpacing(Block block)
{
    //std::cout << "entering the function \n";
    double epsilon = 1e-5;
    std::vector<Cell> newBlockWallCells = block.wallCells;
    std::vector<Cell> newBlockCells = block.blockCells;
    for(Cell newBlockWallCell: newBlockWallCells)
    {
        for(int wallCellsID: wallCellsIDs)
        {
            Cell multiBlockCell = multiBlockCells[wallCellsID];
            // if two cells have the same locations
            if(multiBlockCell.x == newBlockWallCell.x && multiBlockCell.y == newBlockWallCell.y)
            {
                // if two cells have a vertical boundary, multiblock on the left side, new block on the right side
                // we are not checking corners (hence checking if north and south boundaries are not -1)
                if(multiBlockCell.east == -1 && newBlockWallCell.west==-1 && multiBlockCell.north!=-1 && multiBlockCell.south!=-1 && newBlockWallCell.north!=-1 && newBlockWallCell.south!=-1)
                {
                    // we just need to check if y values are the same
                    // grids are uniform in x and y direction so we can just check either north or south value
                    double multiBlockCellNorthY = multiBlockCells[multiBlockCell.north].y;
                    Cell newBlockNorthCell = newBlockCells[newBlockWallCell.north];
                    int newBlockNorthCellID = newBlockNorthCell.ID;
                    double newBlockWallCellY = newBlockCells[newBlockNorthCellID].y;
                    if(abs(multiBlockCellNorthY-newBlockWallCellY)<epsilon)
                    {
                        // correct cell spacing. the message is commented out
                        // std::cout << "Correct cell spacing on stitched walls of the vertical boundary \n";
                    }
                    else
                    {
                        throw("Incorrect cell spacing! \n");
                    }
                }
                
                // if two cells have a vertical boundary, multiblock on the right side, new block on the left side
                if(multiBlockCell.west == -1 && newBlockWallCell.east==-1 && multiBlockCell.north!=-1 && multiBlockCell.south!=-1 && newBlockWallCell.north!=-1 && newBlockWallCell.south!=-1)
                {
                    // we just need to check if y values are the same
                    // grids are uniform in x and y direction so we can just check either north or south value
                    double multiBlockCellNorthY = multiBlockCells[multiBlockCell.north].y;
                    Cell newBlockNorthCell = newBlockCells[newBlockWallCell.north];
                    int newBlockNorthCellID = newBlockNorthCell.ID;
                    double newBlockWallCellY = newBlockCells[newBlockNorthCellID].y;
                    if(abs(multiBlockCellNorthY-newBlockWallCellY)<epsilon)
                    {
                        // correct cell spacing. the message is commented out
                        // std::cout << "Correct cell spacing on stitched walls of the vertical boundary \n";
                    }
                    else
                    {
                        throw("Incorrect cell spacing! \n");
                    }
                }
                
                // if two cells have a horizontal boundary, multiblock on the bottom side, new block on the top side
                if(multiBlockCell.north == -1 && newBlockWallCell.south==-1 && multiBlockCell.east!=-1 && multiBlockCell.west!=-1 && newBlockWallCell.east!=-1 && newBlockWallCell.west!=-1)
                {
                    // we just need to check if y values are the same
                    // grids are uniform in x and y direction so we can just check either west or east value
                    double multiBlockCellEastX = multiBlockCells[multiBlockCell.east].x;
                    Cell newBlockEastCell = newBlockCells[newBlockWallCell.east];
                    int newBlockEastCellID = newBlockEastCell.ID;
                    double newBlockWallCellX = newBlockCells[newBlockEastCellID].x;
                    if(abs(multiBlockCellEastX-newBlockWallCellX)<epsilon)
                    {
                        // correct cell spacing. the message is commented out
                        // std::cout << "Correct cell spacing on stitched walls of the horizontal boundary \n";
                    }
                    else
                    {
                        throw("Incorrect cell spacing! \n");
                    }
                }
                
                // if two cells have a horizontal boundary, multiblock on the top side, new block on the bottom side
                if(multiBlockCell.south == -1 && newBlockWallCell.north==-1 && multiBlockCell.east!=-1 && multiBlockCell.west!=-1 && newBlockWallCell.east!=-1 && newBlockWallCell.west!=-1)
                {
                    // we just need to check if y values are the same
                    // grids are uniform in x and y direction so we can just check either west or east value
                    double multiBlockCellEastX = multiBlockCells[multiBlockCell.east].x;
                    Cell newBlockEastCell = newBlockCells[newBlockWallCell.east];
                    int newBlockEastCellID = newBlockEastCell.ID;
                    double newBlockWallCellX = newBlockCells[newBlockEastCellID].x;
                    if(abs(multiBlockCellEastX-newBlockWallCellX)<epsilon)
                    {
                        // correct cell spacing. the message is commented out
                        // std::cout << "Correct cell spacing on stitched walls of the horizontal boundary \n";
                    }
                    else
                    {
                        throw("Incorrect cell spacing! \n");
                    }
                }


                
            }
        }
        
    }
    
}

void MultiBlock::displayCells()
{
    for (const Cell& cell : multiBlockCells)
    {
        std::cout << std::left
                  << std::setw(3) << ("ID:")    << std::setw(8) << cell.ID
                  << std::setw(3) << ("x:")     << std::setw(8) << std::fixed << std::setprecision(2) << cell.x
                  << std::setw(3) << ("y:")     << std::setw(8) << std::fixed << std::setprecision(2) << cell.y
                  << std::setw(8) << ("north:") << std::setw(8) << cell.north
                  << std::setw(8) << ("south:") << std::setw(8) << cell.south
                  << std::setw(8) << ("east:")  << std::setw(8) << cell.east
                  << std::setw(8) << ("west:")  << std::setw(8) << cell.west;

        if(cell.north==-1) {std::cout << "North cell! ";}
        if(cell.south==-1) {std::cout << "South cell! ";}
        if(cell.east==-1) {std::cout << "East cell! ";}
        if(cell.west==-1) {std::cout << "West cell! ";}

        std::cout << "\n";
    }
}

size_t MultiBlock::multiBlockSize()
{
    return multiBlockCells.size();
}

std::vector<Cell>& MultiBlock::getMultiBlockCells()
{
    return multiBlockCells;
}

double MultiBlock::get_dx() const
{
    return dx;
}

double MultiBlock::get_dy() const
{
    return dy;
}
