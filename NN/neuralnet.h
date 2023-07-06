
#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include <random>
#include <cassert>
#include "init.h"

using namespace std;

class NN{
    friend class Trainer;
private:
    struct{
        vector<float> linear_vals, vals, grad;
        vector<float*> forward_weights;
        vector<pair<float*, float*>> forward_vals;
    } neurons;
    vector<float> weights;
    vector<unsigned> layers;
    unsigned nneuron, nweight, nlayer;
public:
    NN() = default;
    NN(const vector<unsigned> &layers);
    NN(const char *filename);
    void Save(const char *filename) const;
    void Load(const char *filename);
    
    NN &operator = (const NN &x){
        nlayer = x.nlayer;
        nneuron = x.nneuron;
        nweight = x.nweight;
        neurons = x.neurons;
        weights = x.weights;
        layers = x.layers;
        for(auto &i : neurons.forward_weights)
            i = i - x.weights.data() + weights.data();
        for(auto &i : neurons.forward_vals){
            i.first = i.first - x.neurons.vals.data() + neurons.vals.data();
            i.second = i.second - x.neurons.vals.data() + neurons.vals.data();
        }
        return *this;
    }
    void Initialize(const vector<unsigned> &layers);
    void RandomWeights(float mn, float mx);
    void HeRandomWeights();

    inline void Evaluar(const vector<float> &input){
        assert(input.size() == layers.front());
        copy(input.data(), input.data() + layers.front(), neurons.vals.data());
        for (unsigned i = layers.front(); i< nneuron; ++i){
            float &linear_val = neurons.linear_vals[i], *w = neurons.forward_weights[i];
            linear_val = 0;
            for (float *v = neurons.forward_vals[i].first, *end = neurons.forward_vals[i].second; v != end; ++v, ++w)
                linear_val += *v * *w;
            linear_val += *w;
            neurons.vals[i] = sigmoid(linear_val);
        }
    };
    
    // uwU QUIERO MORIR
    inline void Backpropagation(const vector<float> &exp, vector<float> *suma_weight_grad){
        assert(exp.size() == layers.back());
        assert(suma_weight_grad -> size() == nweight);

        fill(neurons.grad.begin(), neurons.grad.begin()+ nneuron - layers.back(), 0.0f);

        for(unsigned i = nneuron - layers.back(), j = 0; i < nneuron; ++i, ++j){
            neurons.grad[i] = 2.0*(neurons.vals[i] - exp[j]);
        
        for(unsigned i = nneuron-1; i>= layers.front(); --i){
            float delta = neurons.grad[i] * sigmoid_prime(neurons.linear_vals[i]);
            float *w = neurons.forward_weights[i];
            float *e = neurons.forward_vals[i].first;
            int wi = w - weights.data();
            int ei= e - neurons.vals.data();
            for(float *end = neurons.forward_vals[i].second; e != end; 
					++e, ++ei, ++w, ++wi)
			{
				(*suma_weight_grad)[wi] += *e * delta;
				neurons.grad[ei] += *w * delta;
			}
			(*suma_weight_grad)[wi] += delta;
		    }
        }
    }
    inline const float *result() const{
        return neurons.vals.data() + nneuron - layers.back();
    }     

};

#endif // !NEURALNET_H