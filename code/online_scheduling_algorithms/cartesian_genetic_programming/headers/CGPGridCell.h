//
// Created by mihael on 5/26/24.
//

#ifndef CGPGRIDCELL_H
#define CGPGRIDCELL_H



class CGPGridCell {
public:
    int cell_index;
    int first_input_index;
    int second_input_index;
    int third_input_index;
    int function_index;
    CGPGridCell(int cell_index, int first_input_index, int second_input_index, int third_input_index, int function_index);
    CGPGridCell* copy();
};



#endif //CGPGRIDCELL_H
