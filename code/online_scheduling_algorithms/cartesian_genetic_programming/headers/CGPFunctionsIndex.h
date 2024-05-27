//
// Created by mihael on 5/26/24.
//

#ifndef CGPFUNCTIONSINDEX_H
#define CGPFUNCTIONSINDEX_H

#include <map>

class CGPFunctionsIndex {
    std::map<long, double (*)(double, double, double)> functions{};
public:
    CGPFunctionsIndex();
    int getNumberOfFunctions();
    double executeFunction(int f_index, double a, double b, double c);
};



#endif //CGPFUNCTIONSINDEX_H
