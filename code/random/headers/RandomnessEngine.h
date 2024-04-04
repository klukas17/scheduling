//
// Created by mihael on 4/3/24.
//

#ifndef RANDOMNESSENGINE_H
#define RANDOMNESSENGINE_H
#include "DefaultRandomEngine.h"


class RandomnessEngine {
private:
    static DefaultRandomEngine* engine;
public:
    static std::default_random_engine& getEngine();
};


#endif //RANDOMNESSENGINE_H
