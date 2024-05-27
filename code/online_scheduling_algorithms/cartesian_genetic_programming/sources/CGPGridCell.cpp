//
// Created by mihael on 5/26/24.
//

#include "CGPGridCell.h"

CGPGridCell::CGPGridCell(int cell_index, int first_input_index, int second_input_index, int third_input_index, int function_index) {
    this->cell_index = cell_index;
    this->first_input_index = first_input_index;
    this->second_input_index = second_input_index;
    this->third_input_index = third_input_index;
    this->function_index = function_index;
}

CGPGridCell* CGPGridCell::copy() {
    return new CGPGridCell(cell_index, first_input_index, second_input_index, third_input_index, function_index);
}
