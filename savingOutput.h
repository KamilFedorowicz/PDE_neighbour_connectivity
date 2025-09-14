#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

void saveToVTK(const std::string& filename, ScalarField field, std::string fieldName)
{
    MultiBlock& multiblock = field.getMultiBlock();
    const std::vector<Cell>& cells = multiblock.getMultiBlockCells();
    std::vector<double>& values = field.getScalarValues();

    // double dx = multiblock.get_dx();
    // double dy = multiblock.get_dy();

    std::ofstream vtkFile(filename);
    if (!vtkFile.is_open())
    {
        std::cerr << "Error: could not open file " << filename << " for writing.\n";
        return;
    }

    vtkFile << "# vtk DataFile Version 3.0\n";
    vtkFile << "Scalar field output\n";
    vtkFile << "ASCII\n";
    vtkFile << "DATASET UNSTRUCTURED_GRID\n";

    // Generate points: 4 corners per cell
    vtkFile << "POINTS " << cells.size() * 4 << " double\n";
    for (const Cell& c : cells)
    {
        double left_dx = 0.0, right_dx = 0.0;
        double down_dy = 0.0, up_dy = 0.0;

        if (c.west != -1) {
            left_dx = (c.x - cells[c.west].x) / 2.0;
        }
        if (c.east != -1) {
            right_dx = (cells[c.east].x - c.x) / 2.0;
        }
        if (c.south != -1) {
            down_dy = (c.y - cells[c.south].y) / 2.0;
        }
        if (c.north != -1) {
            up_dy = (cells[c.north].y - c.y) / 2.0;
        }
        
        double x = c.x;
        double y = c.y;

        // corners in CCW order: SW, SE, NE, NW
        vtkFile << x - left_dx  << " " << y - down_dy << " 0.0\n"; // SW
        vtkFile << x + right_dx << " " << y - down_dy << " 0.0\n"; // SE
        vtkFile << x + right_dx << " " << y + up_dy   << " 0.0\n"; // NE
        vtkFile << x - left_dx  << " " << y + up_dy   << " 0.0\n"; // NW
    }

    // Write cells
    vtkFile << "CELLS " << cells.size() << " " << cells.size() * 5 << "\n";
    for (size_t i = 0; i < cells.size(); ++i)
    {
        size_t base = i * 4;
        vtkFile << "4 " << base << " " << base+1 << " " << base+2 << " " << base+3 << "\n";
    }

    // Cell types: VTK_QUAD = 9
    vtkFile << "CELL_TYPES " << cells.size() << "\n";
    for (size_t i = 0; i < cells.size(); ++i)
        vtkFile << "9\n";

    // Write scalar data per cell
    vtkFile << "CELL_DATA " << cells.size() << "\n";
    vtkFile << "SCALARS " << fieldName << " double 1\n";
    vtkFile << "LOOKUP_TABLE default\n";
    for (double val : values)
        vtkFile << val << "\n";

    vtkFile.close();
    std::cout << "VTK file saved to " << filename << std::endl;
}
