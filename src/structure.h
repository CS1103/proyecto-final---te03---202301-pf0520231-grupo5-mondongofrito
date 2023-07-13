#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
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
        
        void initializeWeights() {
            cv::RNG rng; // se crea numeros aleatorios de la libreria opencv
            rng.fill(hiddenWeights, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1)); // se llena la matriz de pesos con numeros aleatorios
            rng.fill(outputWeights, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1)); // se llena la matriz de pesos con numeros aleatorios
        }
        
        cv::Mat forwardPropagation(const cv::Mat& input) {
            // Calculate values of the hidden layer
            cv::Mat hiddenInput = input * hiddenWeights; // se multiplica la matriz de entrada por la matriz de pesos
            hiddenLayer = sigmoid(hiddenInput); // se aplica la funcion de activacion a la matriz resultante
            
            // Calculate values of the output layer
            cv::Mat outputInput = hiddenLayer * outputWeights; // se multiplica la matriz de entrada por la matriz de pesos
            outputLayer = sigmoid(outputInput); // se aplica la funcion de activacion a la matriz resultante
            
            return outputLayer;
        }
        
        // Backward propagation of errors
        void backwardPropagation(const cv::Mat& input, const cv::Mat& target, double learningRate) // se le pasa la matriz de entrada, la matriz de salida y el learning rate
        {
            // Calculate errors in the output layer
            cv::Mat outputErrors = (target - outputLayer) * outputLayer.mul(1 - outputLayer); // se calcula el error de la capa de salida con la formula (target - outputLayer) * outputLayer * (1 - outputLayer)
            
            // Update weights between hidden and output layers
            cv::Mat outputDelta = learningRate * hiddenLayer.t() * outputErrors; // se calcula el delta de la capa de salida con la formula learningRate * hiddenLayer.t() * outputErrors
            outputWeights += outputDelta; // se actualizan los pesos de la capa de salida
            
            // Calculate errors in the hidden layer
            cv::Mat hiddenErrors = outputErrors * outputWeights.t() * hiddenLayer.mul(1 - hiddenLayer); // se calcula el error de la capa oculta con la formula outputErrors * outputWeights.t() * hiddenLayer * (1 - hiddenLayer)
            
            // Update weights between input and hidden layers
            cv::Mat hiddenDelta = learningRate * input.t() * hiddenErrors;  // se calcula el delta de la capa oculta con la formula learningRate * input.t() * hiddenErrors
            hiddenWeights += hiddenDelta; // se actualizan los pesos de la capa oculta
        }
    public:
    // NN
        NeuralNetwork() = default;
        NeuralNetwork(int inputSize, int hiddenNeurons) { // se le pasa el tamaño de la capa de entrada, el tamaño de la capa oculta y el tamaño de la capa de salida
            const int outputSize = 10; // se asigna el tamaño de la capa de salida
            this->inputSize = inputSize; // se asigna el tamaño de la capa de entrada
            this->hiddenNeurons = hiddenNeurons; // se asigna el tamaño de la capa oculta
            
            inputLayer = cv::Mat::zeros(inputSize, 1, CV_64F); // se crea una matriz de ceros con el tamaño de la capa de entrada la cual es de 784
            hiddenLayer = cv::Mat::zeros(hiddenNeurons, 1, CV_64F); // se crea una matriz de ceros con el tamaño de la capa oculta la cual es de 15
            outputLayer = cv::Mat::zeros(1, CV_64F); // se crea una matriz de ceros con el tamaño de la capa de salida la cual es de 10
            
            hiddenWeights = cv::Mat::zeros(inputSize, hiddenNeurons, CV_64F); // se crea una matriz de ceros con el tamaño de la capa de entrada y la capa oculta
            outputWeights = cv::Mat::zeros(hiddenNeurons, CV_64F); // se crea una matriz de ceros con el tamaño de la capa oculta y la capa de salida
            
            initializeWeights(); // se inicializan los pesos
        }
        NeuralNetwork(string dataPath) {};
        ~NeuralNetwork(){};

        void train(string &imagePath, string &labelPath) {
            vector<pair<cv::Mat, int>> mnist;
            loadMnist(imagePath, labelPath, ref(mnist));
        }
    };
};
