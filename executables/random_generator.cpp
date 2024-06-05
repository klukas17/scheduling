//
// Created by mihael on 5/19/24.
//

#include "NormalDistribution.h"
#include "iostream"
#include "UniformIntDistributionGenerator.h"

int main() {
    // auto generator = new NormalDistribution(0, 0.01);
    auto generator = new UniformIntDistributionGenerator(0, 1);

    for (int i = 0; i < 10; i++) {
        std::cout << generator->generate() << std::endl;
    }
}
