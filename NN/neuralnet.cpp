#include "neuralnet.h"
#include "init.h"
#include <iomanip>
#include <fstream>
#include <numeric>
#include <cstdio>

using namespace std;

NN::NN(const vector<unsigned> &layers)
{
	Initialize(layers);
}

NN::NN(const char *filename)
{
	Load(filename);
}

// starters
void NN::Initialize(const vector<unsigned> &layers){
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

void NN::Load(const char *filename){
    ifstream in{filename};
    in >> nlayer;
    layers.resize(nlayer);
    for(unsigned i = 0; i < nlayer; ++i)
        in >> layers[i];
    Initialize(layers);
    for(unsigned i = 0; i < nweight; ++i)
        in >> weights[i];
}

void NN::Save(const char *filename) const{
    ofstream out{filename};
    out << nlayer << endl;
    for(unsigned i = 0; i < nlayer; ++i)
        out << layers[i] << " ";
    out << endl;
    for(unsigned i = 0; i < nweight; ++i)
        out << weights[i] << " ";
    out << endl;
}

// randomizers

void NN::RandomWeights(float mn, float mx){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(mn, mx);
    for(unsigned i = 0; i < nweight; ++i)
        weights[i] = dis(gen);
}

void NN::HeRandomWeights(){
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<float> dis(0, sqrt(2.0f / layers[0]));
    for(unsigned i = 0; i < nweight; ++i)
        weights[i] = dis(gen);
}

