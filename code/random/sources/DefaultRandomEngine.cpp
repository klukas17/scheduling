//
// Created by mihael on 4/3/24.
//

#include "DefaultRandomEngine.h"
#include "chrono"
#include "iostream"

DefaultRandomEngine::DefaultRandomEngine() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::cout << "Random seed = " << seed << std::endl;
    engine.seed(seed);
}
