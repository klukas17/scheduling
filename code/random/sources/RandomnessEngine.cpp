//
// Created by mihael on 4/3/24.
//

#include "RandomnessEngine.h"

std::default_random_engine& RandomnessEngine::getEngine() {
    if (engine == nullptr) {
        engine = new DefaultRandomEngine();
    }
    return engine->engine;
}

DefaultRandomEngine* RandomnessEngine::engine = nullptr;
