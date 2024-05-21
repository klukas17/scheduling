//
// Created by mihael on 5/19/24.
//

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <Eigen/Dense>

#include "OnlineSchedulingAlgorithm.h"

class NeuralNetwork final : public OnlineSchedulingAlgorithm {
    std::vector<Eigen::MatrixXd> matrices;
public:
    NeuralNetwork(std::vector<Eigen::MatrixXd> matrices);
    ~NeuralNetwork();
    std::vector<Eigen::MatrixXd> getMatrices();
    void setMatrices(std::vector<Eigen::MatrixXd> matrices);
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //NEURALNETWORK_H
