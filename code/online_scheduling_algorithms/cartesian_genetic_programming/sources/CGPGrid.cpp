//
// Created by mihael on 5/26/24.
//

#include "CGPGrid.h"

#include <utility>

CGPGrid::CGPGrid(
    int rows,
    int cols,
    int output_index,
    CGPFunctionsIndex* functions_index,
    std::vector<CGPGridCell*> cells,
    std::map<long, double> constants,
    std::vector<std::string> inputs
) {
    this->rows = rows;
    this->cols = cols;
    this->output_index = output_index;
    this->functions_index = functions_index;
    this->cells = std::move(cells);
    this->constants = std::move(constants);
    this->inputs = std::move(inputs);
}

CGPGrid::~CGPGrid() {
    for (auto & cell : cells) {
        delete cell;
    }
}

CGPGrid* CGPGrid::copy() {
    std::vector<CGPGridCell*> cells_copy;
    cells_copy.reserve(cells.size());
    for (auto & cell : cells) {
        cells_copy.push_back(cell->copy());
    }
    return new CGPGrid(
        rows,
        cols,
        output_index,
        functions_index,
        cells_copy,
        constants,
        inputs
    );
}

int CGPGrid::getNumberOfFunctions() {
    return functions_index->getNumberOfFunctions();
}

void CGPGrid::addConstant(long cell_id, double constant) {
    constants[cell_id] = constant;
}

void CGPGrid::removeConstant(long cell_id) {
    constants.erase(cell_id);
}

double CGPGrid::calculateOutput(std::map<std::string, double> params) {
    std::map<int, double> cell_outputs;
    for (int i = 0; i < inputs.size(); i++) {
        cell_outputs[i + 1] = params[inputs[i]];
    }
    for (auto cell : cells) {
        auto cell_index = cell->cell_index;
        auto f_index = cell->function_index;
        // constant
        if (f_index == functions_index->getNumberOfFunctions() + 1) {
            cell_outputs[cell_index] = constants[cell_index];
        } else {
            cell_outputs[cell_index] = functions_index->executeFunction(
                f_index,
                cell_outputs[cell->first_input_index],
                cell_outputs[cell->second_input_index],
                cell_outputs[cell->third_input_index]
            );
        }
    }

    return cell_outputs[output_index];
}

