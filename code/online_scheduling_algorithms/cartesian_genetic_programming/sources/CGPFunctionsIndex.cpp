//
// Created by mihael on 5/26/24.
//

#include "CGPFunctionsIndex.h"
#include <cmath>

double unary_minus(double a, double b, double c) {
    return -a;
}

double plus(double a, double b, double c) {
    return a + b;
}

double minus(double a, double b, double c) {
    return a - b;
}

double times(double a, double b, double c) {
    auto result = a * b;
    return std::isinf(result) ? 1 : result;
}

double divide(double a, double b, double c) {
    if (b >= -1e-6 && b <= 1e-6) {
        return 1;
    }
    auto res = a / b;
    return std::isinf(res) ? 1 : res;
}

double square(double a, double b, double c) {
    auto result = std::pow(a, 2);
    return std::isinf(result) ? 1 : result;
}

double root(double a, double b, double c) {
    return (a >= 0 ? 1 : -1) * std::sqrt(std::abs(a));
}

double branch(double a, double b, double c) {
    return a >= 0 ? b : c;
}

CGPFunctionsIndex::CGPFunctionsIndex() {
    functions[1] = unary_minus;
    functions[2] = plus;
    functions[3] = minus;
    functions[4] = times;
    functions[5] = divide;
    functions[6] = square;
    functions[7] = root;
    functions[8] = branch;
}

int CGPFunctionsIndex::getNumberOfFunctions() {
    return functions.size();
}

double CGPFunctionsIndex::executeFunction(int f_index, double a, double b, double c) {
    return functions[f_index](a, b, c);
}
