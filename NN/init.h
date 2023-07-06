#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <cmath>

using namespace std;    

// Implementar a sigmoid y su derivada

inline double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

inline double sigmoid_prime(double x) {
    return sigmoid(x) * (1.0 - sigmoid(x));
    }


#endif 


