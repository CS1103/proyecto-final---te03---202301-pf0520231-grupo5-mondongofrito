#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "imageloading.h"
#include <random>
#include <cmath>


using namespace std;   

namespace mondongo {
    class NeuralNetwork {
        cv::Mat inputLayer; // Vector containing current image pixels
        cv::Mat hiddenLayer; // Vector containing the hidden layer values
        cv::Mat outputLayer; // Vector containing the output layer values
        cv::Mat hiddenWeights; // Weights for the connections between input and hidden layers
        cv::Mat outputWeights; // Weights for the connections between hidden and output layers
        cv::Mat hiddenBias; // Bias for the hidden layer
        cv::Mat outputBias; // Bias for the output layer
        double hiddenNeurons = 0; // Size of hidden layer
        int inputSize; // Size of input layer
        int outputSize; // Size of output layer
        
    private:
    // Sigmoid function
        double sigmoid(double x) {
            return 1 / (1 + exp(-x));
        }
        
        cv::Mat sigmoid(const cv::Mat& x) {
            cv::Mat result;
            cv::exp(-x, result);
            result = 1 / (1 + result);
            return result;
        }
        
        void initializeWeightsAndBiases() {
            cv::RNG rng; // se crea numeros aleatorios de la libreria opencv
            rng.fill(hiddenWeights, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1)); // se llena la matriz de pesos con numeros aleatorios
            rng.fill(outputWeights, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1)); // se llena la matriz de pesos con numeros aleatorios
            rng.fill(hiddenBias, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1));
            rng.fill(outputBias, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1));
        }
        
        cv::Mat forwardPropagation(const cv::Mat& input) {
            // Calculate values of the hidden layer
            cv::Mat hiddenInput = input * hiddenWeights + hiddenBias; // se multiplica la matriz de entrada por la matriz de pesos y se suma el bias
            hiddenLayer = sigmoid(hiddenInput); // se aplica la funcion de activacion a la matriz resultante
            
            // Calculate values of the output layer
            cv::Mat outputInput = hiddenLayer * outputWeights + outputBias; // se multiplica la matriz de entrada por la matriz de pesos y se suma el bias
            outputLayer = sigmoid(outputInput); // se aplica la funcion de activacion a la matriz resultante
            
            return outputLayer;
        }
        
        // Backward propagation of errors
        void backwardPropagation(const cv::Mat& input, const cv::Mat& target) // se le pasa la matriz de entrada, la matriz de salida y el learning rate
        {
            // Calculate errors in the output layer
            cv::Mat outputErrors = (target - outputLayer) * outputLayer.mul(1 - outputLayer); // se calcula el error de la capa de salida con la formula (target - outputLayer) * outputLayer * (1 - outputLayer)
            
            // Update weights and biases between hidden and output layers
            cv::Mat outputDelta = 0.1 * hiddenLayer.t() * outputErrors; // se calcula el delta de la capa de salida con la formula learningRate * hiddenLayer.t() * outputErrors
            outputWeights += outputDelta; // se actualizan los pesos de la capa de salida
            cv::reduce(outputDelta, outputBias, 0, cv::REDUCE_SUM);
            
            // Calculate errors in the hidden layer
            cv::Mat hiddenErrors = outputErrors * outputWeights.t() * hiddenLayer.mul(1 - hiddenLayer); // se calcula el error de la capa oculta con la formula outputErrors * outputWeights.t() * hiddenLayer * (1 - hiddenLayer)
            
            // Update weights and biases between input and hidden layers
            cv::Mat hiddenDelta = 0.1 * input.t() * hiddenErrors;  // se calcula el delta de la capa oculta con la formula learningRate * input.t() * hiddenErrors
            hiddenWeights += hiddenDelta; // se actualizan los pesos de la capa oculta
            cv::reduce(hiddenDelta, hiddenBias, 0, cv::REDUCE_SUM);
        }
    public:
    // NN
        NeuralNetwork() = default;
        NeuralNetwork(int inputSize, int hiddenNeurons, int outputSize) { // se le pasa el tamaño de la capa de entrada, el tamaño de la capa oculta y el tamaño de la capa de salida
            this->inputSize = inputSize;
            this->hiddenNeurons = hiddenNeurons;
            this->outputSize = outputSize;
            
            hiddenWeights = cv::Mat::zeros(inputSize, hiddenNeurons, CV_64F); // se inicializan los pesos de la capa oculta a cero
            outputWeights = cv::Mat::zeros(hiddenNeurons, outputSize, CV_64F); // se inicializan los pesos de la capa de salida a cero
            
            hiddenBias = cv::Mat::zeros(1, hiddenNeurons, CV_64F); // se inicializa el bias de la capa oculta a cero
            outputBias = cv::Mat::zeros(1, outputSize, CV_64F); // se inicializa el bias de la capa de salida a cero
            
            initializeWeightsAndBiases(); // se inicializan los pesos y biases con números aleatorios
        }

        void train(const cv::Mat& input, const cv::Mat& target) {
            cv::Mat output = forwardPropagation(input);
            backwardPropagation(input, target);
        }

        cv::Mat predict(const cv::Mat& input) {
            return forwardPropagation(input);
        }
    };
    
}
