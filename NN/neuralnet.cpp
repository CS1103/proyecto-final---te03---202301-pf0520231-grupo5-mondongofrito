#include <iomanip>
#include <fstream>
#include <numeric>
#include <cstdio>

#include "neuralnet.h"
#include "init.h"

using namespace std;
using namespace mondongo;

// NeuralNetwork start it UPPPPP
NeuralNetwork::NeuralNetwork(const vector<unsigned> &layers)
{
    initialize(layers);
} // Constructor con un vector de numeros

/// @brief Creates a NeuralNetwork object from a .txt file
/// @param filename Path to specified .txt.
NeuralNetwork::NeuralNetwork(const char *filename)
{
    load(filename);
}

// Start nn 2 w layers
void NeuralNetwork::initialize(const vector<unsigned> &layers){
    this->layers = layers;
    nneuron = accumulate(layers.begin(), layers.end(), 0u);

    neurons.vals.resize(nneuron);
    neurons.linear_vals.resize(nneuron);
    neurons.grad.resize(nneuron);
    neurons.forward_vals.resize(nneuron);
    neurons.forward_weights.resize(nneuron);
    nlayer = layers.size();

    vector<pair<float*, float*>> ranges(nlayer);
    for(unsigned s = 0, i = 0; i < nlayer; ++i){
        ranges[i] = {neurons.vals.data() + s, neurons.vals.data() + s + layers[i]};
        s += layers[i];
    }
    for(unsigned s = layers.front(), i = 1; i < nlayer; ++i)
        for(unsigned j = 0; j < layers[i]; ++j, ++s)
            neurons.forward_vals[s] = ranges[i-1];

    nweight = 0;
    for(unsigned i = layers[0]; i < nneuron; ++i)
        nweight += neurons.forward_vals[i].second - neurons.forward_vals[i].first + 1;
    weights.resize(nweight);
    
    nweight = 0;
    for(unsigned i = layers[0]; i < nneuron; ++i){
        neurons.forward_weights[i] = weights.data() + nweight;
        nweight += neurons.forward_vals[i].second - neurons.forward_vals[i].first + 1;
    }
}

// Función que carga el loudout y los weights de la NeuralNetwork desde un archivo
void NeuralNetwork::load(const char *filename){
    ifstream in{filename};
    in >> nlayer;
    layers.resize(nlayer);
    for(unsigned i = 0; i < nlayer; ++i)
        in >> layers[i];
    initialize(layers);
    for(unsigned i = 0; i < nweight; ++i)
        in >> weights[i];
}

// Guarda el loudout y los weights de la NeuralNetwork en un archivo
void NeuralNetwork::save(const char *filename) const{
    ofstream out{filename};
    out << nlayer << endl;
    for(unsigned i = 0; i < nlayer; ++i) {
        out << layers[i] << " ";
    }
    out << endl;
    for(unsigned i = 0; i < nweight; ++i) {
        out << weights[i] << " ";
    }
    out << endl;
}
// randomizers de pesos par la NeuralNetwork uno con un rango y otro con la formula de He

void NeuralNetwork::randomWeights(float mn, float mx){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(mn, mx);
    for(unsigned i = 0; i < nweight; ++i) {
        weights[i] = dis(gen);
    }
}

void NeuralNetwork::heRandomWeights(){
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<float> dis(0, sqrt(2.0f / layers[0]));
    for(unsigned i = 0; i < nweight; ++i) {
        weights[i] = dis(gen);
    }
}

NeuralNetwork &NeuralNetwork::operator=(const NeuralNetwork &other){
    nlayer = other.nlayer;
    nneuron = other.nneuron;
    nweight = other.nweight;
    neurons = other.neurons;
    weights = other.weights;
    layers = other.layers;
    for(auto &i : neurons.forward_weights) {
        i = i - other.weights.data() + weights.data();
    }
        
    for(auto &i : neurons.forward_vals) {
        i.first = i.first - other.neurons.vals.data() + neurons.vals.data();
        i.second = i.second - other.neurons.vals.data() + neurons.vals.data();
    }
    return *this;
} // Constructor Copy entre NNs

inline void NeuralNetwork::evaluar(const vector<float> &input){
    // Copiar los valores de entrada al vector de valores de las neuronas
    assert(input.size() == layers.front());
    copy(input.data(), input.data() + layers.front(), neurons.vals.data());
    for (unsigned i = layers.front(); i< nneuron; ++i){
        float &linear_val = neurons.linear_vals[i], *w = neurons.forward_weights[i];
        linear_val = 0;
        // Suma de los valores de las neuronas hacia adelante
        for (float *v = neurons.forward_vals[i].first, *end = neurons.forward_vals[i].second; v != end; ++v, ++w)
            linear_val += *v * *w;
        // Sumar sesgo
        linear_val += *w;
        // Llamar a sigmoid el grande
        neurons.vals[i] = sigmoid(linear_val);
    }
};

inline void NeuralNetwork::backpropagation(const vector<float> &exp, vector<float> *suma_weight_grad) {
    assert(exp.size() == layers.back());
    assert(suma_weight_grad -> size() == nweight);

    // Reiniciar los gradientes de las neuronas menos de la ultima
    fill(neurons.grad.begin(), neurons.grad.begin()+ nneuron - layers.back(), 0.0f);

    // Cuantos gradientes tiene la ultima capa
    for(unsigned i = nneuron - layers.back(), j = 0; i < nneuron; ++i, ++j){
        neurons.grad[i] = 2.0*(neurons.vals[i] - exp[j]);
    // Retropropagacion del error para las capas anteriores
    for(unsigned i = nneuron-1; i>= layers.front(); --i){
        // Calcular 
        float delta = neurons.grad[i] * sigmoid_prime(neurons.linear_vals[i]);
        float *w = neurons.forward_weights[i];
        float *e = neurons.forward_vals[i].first;
        int wi = w - weights.data();
        int ei= e - neurons.vals.data();
        // Actualizar los gradientes de las neuronas y sumar los gradientes de los pesos
        for(float *end = neurons.forward_vals[i].second; e != end; ++e, ++ei, ++w, ++wi) {
            (*suma_weight_grad)[wi] += *e * delta;
            neurons.grad[ei] += *w * delta;
        }
        (*suma_weight_grad)[wi] += delta;
        }
    }
}

inline const float *NeuralNetwork::result() const {
    // Devolver un puntero al vector de valores de las neuronas correspondientes a la salida de la red neuronal
    return neurons.vals.data() + nneuron - layers.back();
}   