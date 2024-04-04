//
// Created by mihael on 4/3/24.
//

#include "DefaultRandomEngine.h"
#include "chrono"

DefaultRandomEngine::DefaultRandomEngine() {
    engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
}
