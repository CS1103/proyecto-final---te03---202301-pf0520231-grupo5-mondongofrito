#pragma once

#include <iostream>
#include <cmath>

using namespace std;    

namespace mondongo {
    /// @brief Sigmoid function.
    /// @param x 
    /// @return 1.0 / (1.0 + exp(-x))
    inline double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    /// @brief Derivative of sigmoid function.
    /// @param x 
    /// @return sigmoid(x) * (1.0 - sigmoid(x))
    inline double sigmoid_prime(double x) {
        return sigmoid(x) * (1.0 - sigmoid(x));
    }
}