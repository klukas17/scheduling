//
// Created by mihael on 5/20/24.
//

#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"
#include "NeuralNetworkCombinationOperator.h"
#include "NeuralNetworkPerturbationOperator.h"
#include "NormalDistribution.h"
#include "RegressionFunction.h"
#include "SteadyStateGeneticAlgorithm.h"


int main() {

    int population_size = 20;
    int iterations_count = 1000000;

    auto evaluation_function = new RegressionFunction(true, {"x", "y"}, "../functions/function_01/data.txt");

    auto blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 0.1),{2, 20, 1});
    auto creation_operator = new NeuralNetworkCreationOperator(blueprint);
    auto combination_operator = new NeuralNetworkCombinationOperator();
    auto perturbation_operator = new NeuralNetworkPerturbationOperator(new NormalDistribution(0, 0.1));

    auto const ssga = new SteadyStateGeneticAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        population_size,
        iterations_count
    );

    auto const population = new Population(population_size);

    ssga->optimize(population);
}
