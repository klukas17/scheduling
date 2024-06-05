//
// Created by mihael on 5/23/24.
//

#include "CartesianGeneticProgrammingSerializationOperator.h"

#include "CartesianGeneticProgramming.h"
#include "sstream"

CartesianGeneticProgrammingSerializationOperator::CartesianGeneticProgrammingSerializationOperator(CartesianGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

CartesianGeneticProgrammingSerializationOperator::~CartesianGeneticProgrammingSerializationOperator() = default;

std::vector<std::string> CartesianGeneticProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto cgp = dynamic_cast<CartesianGeneticProgramming*>(genotype);
    auto grid = cgp->getGrid();
    std::ostringstream oss;
    for (auto input : cgp->getInputs()) {
        oss << input << " ";
    }
    std::vector<std::string> result = {oss.str()};

    oss.str("");
    oss << grid->output_index;
    result.push_back(oss.str());

    auto constants = grid->constants;
    oss.str("");
    oss << constants.size();
    result.push_back(oss.str());
    for (auto [key, value] : constants) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    for (auto cell : grid->cells) {
        oss.str("");
        oss << cell->cell_index << " " << cell->first_input_index << " " << cell->second_input_index << " " << cell->third_input_index << " " << cell->function_index;
        result.push_back(oss.str());
    }
    return result;
}

Genotype* CartesianGeneticProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {

    std::istringstream iss(representation[0]);
    std::vector<std::string> inputs;
    std::string input;
    while (iss >> input) {
        inputs.push_back(input);
    }

    int output_index = std::stoi(representation[1]);

    int constants_number = std::stoi(representation[2]);
    std::map<long, double> constants;
    int index = 3;
    for (int i = 0; i < constants_number; i++) {
        long cell_index;
        double constant;
        std::istringstream iss(representation[index]);
        iss >> cell_index;
        iss >> constant;
        constants[cell_index] = constant;
        index++;
    }

    std::vector<CGPGridCell*> cells;

    for (int i = 0; i < blueprint->rows * blueprint->cols; i++) {
        std::istringstream iss(representation[index]);
        int cell_index, first_input_index, second_input_index, third_input_index, function_index;
        iss >> cell_index;
        iss >> first_input_index;
        iss >> second_input_index;
        iss >> third_input_index;
        iss >> function_index;
        cells.push_back(new CGPGridCell(cell_index, first_input_index, second_input_index, third_input_index, function_index));
        index++;
    }

    auto grid = new CGPGrid(
        blueprint->rows,
        blueprint->cols,
        output_index,
        blueprint->functions_index,
        cells,
        constants,
        inputs
    );

    auto cgp = new CartesianGeneticProgramming(grid);
    cgp->setInputs(inputs);

    return cgp;
}

