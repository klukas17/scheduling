//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGTYPES_H
#define HYPERPARAMETERTUNINGTYPES_H

#include <variant>
#include <vector>
#include <string>
#include "sstream"

using hyperparameter_value = std::variant<int, double, std::string, std::vector<int>>;

struct hyperparameter_value_printer {
    std::ostream& os;

    void operator()(int val) const { os << val; }
    void operator()(double val) const { os << val; }
    void operator()(const std::string& val) const { os << val; }
    void operator()(const std::vector<int>& vec) const {
        os << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) os << ", ";
            os << vec[i];
        }
        os << "]";
    }
};

inline std::ostream& operator<<(std::ostream& os, const hyperparameter_value& value) {
    std::visit(hyperparameter_value_printer{os}, value);
    return os;
}

#endif //HYPERPARAMETERTUNINGTYPES_H
