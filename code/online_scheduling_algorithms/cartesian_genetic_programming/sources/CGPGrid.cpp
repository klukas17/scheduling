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

    return calculateOutputForCell(output_index, cell_outputs, params);
}

double CGPGrid::calculateOutputForCell(int cell_index, std::map<int, double>& values, std::map<std::string, double> params) {
    if (values.contains(cell_index)) {
        return values[cell_index];
    }

    double value;

    auto cell = cells[cell_index - inputs.size() - 1];

    if (cell->cell_index != cell_index)
    {
        throw;
    }

    auto f_index = cell->function_index;

    // constant
    if (f_index == functions_index->getNumberOfFunctions() + 1) {
        value = constants[cell_index];
    } else {
        value = functions_index->executeFunction(
            f_index,
            calculateOutputForCell(cell->first_input_index, values, params),
            calculateOutputForCell(cell->second_input_index, values, params),
            calculateOutputForCell(cell->third_input_index, values, params)
        );
    }

    values[cell_index] = value;
    return value;
}
