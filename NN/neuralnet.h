#pragma once

#include <vector>
#include <random>
#include <assert.h>

#include "init.h"

using namespace std;

namespace mondongo {
    class NeuralNetwork{
        friend class Trainer; // Trainer class, has access to private stuff
        struct {
            vector<float> linear_vals, vals, grad;
            vector<float*> forward_weights;
            vector<pair<float*, float*>> forward_vals;
        } neurons; // Struct que encapsula a los valores
        vector<float> weights;
        vector<unsigned> layers; // Neuron quantity per layer
        unsigned nneuron, nweight, nlayer;

    public:
        NeuralNetwork() = default;
        NeuralNetwork(const vector<unsigned> &layers);
        NeuralNetwork(const char *filename);
        void save(const char *filename) const;
        void load(const char *filename);
        void initialize(const vector<unsigned> &layers);
        void randomWeights(float mn, float mx);
        void heRandomWeights();
        NeuralNetwork &operator=(const NeuralNetwork &other);
        inline void evaluar(const vector<float> &input);
        inline void backpropagation(const vector<float> &exp, vector<float> *suma_weight_grad);
        inline const float *result() const;
    };
}