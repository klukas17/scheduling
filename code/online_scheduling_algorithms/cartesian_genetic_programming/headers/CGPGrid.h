//
// Created by mihael on 5/26/24.
//

#ifndef CGPGRID_H
#define CGPGRID_H
#include <map>
#include <string>
#include <vector>

#include "CGPFunctionsIndex.h"
#include "CGPGridCell.h"


class CGPGrid {
public:
    int rows;
    int cols;
    int output_index;
    CGPFunctionsIndex* functions_index;
    std::vector<CGPGridCell*> cells;
    std::map<long, double> constants;
    std::vector<std::string> inputs;
    CGPGrid(
        int rows,
        int cols,
        int output_index,
        CGPFunctionsIndex* functions_index,
        std::vector<CGPGridCell*> cells,
        std::map<long, double> constants,
        std::vector<std::string> inputs
    );
    ~CGPGrid();
    CGPGrid* copy();
    int getNumberOfFunctions();
    void addConstant(long cell_id, double constant);
    void removeConstant(long cell_id);
    double calculateOutput(std::map<std::string, double> params);
};



#endif //CGPGRID_H
