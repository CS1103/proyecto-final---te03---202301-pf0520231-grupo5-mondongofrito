#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <random>
#include <cmath>
#include <fstream>
#include <sstream>

#include "imageloading.h"

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
        const int MNIST_RESOLUTION = 784; // Size of input layer
        const int OUTPUT_SIZE = 10; // Size of output layer
        const double LEARNING_RATE = 0.01;
        int epochs = 10;

        /// @brief Sigmoid activation function.
        /// @param x
        /// @return
        double sigmoid(double x) {
            return 1 / (1 + exp(-x));
        }

        /// @brief Sigmoid overload for matrices.
        /// @param x Matrix to apply sigmoid to.
        /// @return Matrix with sigmoid applied.
        cv::Mat sigmoid(const cv::Mat& x) {
            cv::Mat result;
            cv::exp(-x, result);
            result = 1 / (1 + result);
            return result;
        }

        /// @brief Initializes weights and biases with a random number from -1.0 to -1.0
        void initializeWeightsAndBiases() {
            cv::RNG rng; // se crea numeros aleatorios de la libreria opencv
            rng.fill(hiddenWeights, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1)); // se llena la matriz de pesos con numeros aleatorios
            rng.fill(outputWeights, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1)); // se llena la matriz de pesos con numeros aleatorios
            rng.fill(hiddenBias, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1));
            rng.fill(outputBias, cv::RNG::UNIFORM, cv::Scalar(-1), cv::Scalar(1));
        }

        /// @brief Executes the forward pass.
        /// @param input Input layer.
        /// @return Output layer.
        cv::Mat forwardPropagation(const cv::Mat& input) {
            input.reshape(1, 1);
            // Calculate values of the hidden layer
            cv::Mat hiddenInput = input * hiddenWeights + hiddenBias; // se multiplica la matriz de entrada por la matriz de pesos y se suma el bias
            hiddenLayer = sigmoid(hiddenInput); // se aplica la funcion de activacion a la matriz resultante
            // Calculate values of the output layer
            cv::Mat outputInput = hiddenLayer * outputWeights + outputBias; // se multiplica la matriz de entrada por la matriz de pesos y se suma el bias
            outputLayer = sigmoid(outputInput); // se aplica la funcion de activacion a la matriz resultante
            return outputLayer;
        }

        /// @brief Executes backpropagation.
        /// @param input Input layer.
        /// @param target Target layer.
        void backwardPropagation(const cv::Mat& input, const cv::Mat& target) {

            // Calculate errors in the output layer
            cv::Mat outputErrors = (target.t() - outputLayer).mul(outputLayer.mul(1 - outputLayer));

            // Update weights and biases between hidden and output layers
            cv::Mat outputDelta = LEARNING_RATE * outputErrors.t() * hiddenLayer;
            outputWeights += outputDelta.t();

            cv::Mat outputBiasDelta;
            cv::reduce(outputErrors, outputBiasDelta, 0, cv::REDUCE_SUM);
            outputBias += outputBiasDelta;

            // Calculate errors in the hidden layer
            cv::Mat hiddenErrors = outputWeights * outputErrors.t();
            hiddenErrors = hiddenErrors.t().mul(hiddenLayer.mul(1 - hiddenLayer));

            // Update weights and biases between input and hidden layers
            cv::Mat hiddenDelta = LEARNING_RATE * hiddenErrors.t() * input;
            hiddenWeights += hiddenDelta.t();

            cv::Mat hiddenBiasDelta;
            cv::reduce(hiddenErrors, hiddenBiasDelta, 0, cv::REDUCE_SUM);
            hiddenBias += hiddenBiasDelta;
        }

        /// @brief Saves the neural network parameters to a file.
        void save() const {
            ofstream file("data.txt");
            if (!file) {
                file.close();
                ofstream createFile("data.txt");
                if (!createFile) {
                    cout << "File creation failed." << endl;
                    return;
                }
                createFile.close();
                file.open("data.txt");
                if (!file) {
                    cout << "File couldn't be opened." << endl;
                    return;
                }
            }

            file << "/MondongoFrito/\n"; // For valid file check
            file << "hiddenWeights\n";
            file << cv::format(hiddenWeights, cv::Formatter::FMT_CSV) << "\n";
            file << "outputWeights\n";
            file << cv::format(outputWeights, cv::Formatter::FMT_CSV) << "\n";
            file << "hiddenBias\n";
            file << cv::format(hiddenBias, cv::Formatter::FMT_CSV) << "\n";
            file << "outputBias\n";
            file << cv::format(outputBias, cv::Formatter::FMT_CSV) << "\n";

            file.close();
            cout << "Parameters saved to data.txt." << endl;
        }



        /// @brief Loads the neural network parameters from a file.
        /// @param filePath Path to the parameter file.
        void load(const string& filePath) {
            ifstream file(filePath);
            if (file.is_open()) {
                string line;
                string parameterName;
                bool isFirstLine = true;
                while (getline(file, line)) {
                    if (isFirstLine) {
                        isFirstLine = false;
                        continue;
                    }
                    if (line.empty()) {
                        continue;
                    }
                    else if (line == "hiddenWeights") {
                        parameterName = "hiddenWeights";
                    }
                    else if (line == "outputWeights") {
                        parameterName = "outputWeights";
                    }
                    else if (line == "hiddenBias") {
                        parameterName = "hiddenBias";
                    }
                    else if (line == "outputBias") {
                        parameterName = "outputBias";
                    }
                    else {
                        cv::Mat parameter;
                        stringstream ss(line);
                        string data;
                        getline(ss, data);
                        vector<double> values;
                        string value;
                        stringstream data_ss(data);
                        while (getline(data_ss, value, ',')) {
                            values.push_back(stod(value));
                        }
                        parameter = cv::Mat(values).reshape(1, 1);
                        if (parameterName == "hiddenWeights") {
                            hiddenWeights = parameter;
                        }
                        else if (parameterName == "outputWeights") {
                            outputWeights = parameter;
                        }
                        else if (parameterName == "hiddenBias") {
                            hiddenBias = parameter;
                        }
                        else if (parameterName == "outputBias") {
                            outputBias = parameter;
                        }
                    }
                }

                file.close();
                cout << "Parameters loaded from " << filePath << "." << endl;
            }
            else {
                cout << "File couldn't be opened." << endl;
            }
        }

    public:
        NeuralNetwork() = default;

        /// @brief Parametrized constructor.
        /// @param hiddenNeurons Number of neurons in the hidden layer.
        NeuralNetwork(int hiddenNeurons) {
            this->hiddenNeurons = hiddenNeurons;

            hiddenWeights = cv::Mat::zeros(MNIST_RESOLUTION, hiddenNeurons, CV_64F);
            outputWeights = cv::Mat::zeros(hiddenNeurons, OUTPUT_SIZE, CV_64F);
            hiddenBias = cv::Mat::zeros(1, hiddenNeurons, CV_64F);
            outputBias = cv::Mat::zeros(1, OUTPUT_SIZE, CV_64F);

            initializeWeightsAndBiases();
        }

        /// @brief Parametrized constructor that loads the neural network parameters from a file.
        /// @param dataPath Path to the parameter file.
        NeuralNetwork(const string& dataPath) {
            load(dataPath);
        }

        /// @brief Trains the Neural Network with the given data.
        /// @param imagePath Path to the MNIST images.
        /// @param dataPath Path to the MNIST labels.
        void train(const string& imagePath, const string& dataPath) {
            vector<pair<cv::Mat, int>> data;
            loadMnist(imagePath, dataPath, ref(data));
            for (int epoch = 0; epoch < epochs; ++epoch) {
                cout << "Epoch " << (epoch + 1) << "/" << epochs << endl;
                for (int i = 0; i < data.size(); ++i) {
                    cout << "Image " << i << endl;
                    cv::Mat& inputMat = data[i].first;
                    auto label = data[i].second;
                    inputMat = inputMat.reshape(1, 1);
                    cv::Mat target = cv::Mat::zeros(OUTPUT_SIZE, 1, CV_64F);
                    target.at<double>(label, 0) = 1.0;
                    cv::Mat output = forwardPropagation(inputMat);
                    backwardPropagation(inputMat, target);
                }
            }
            save();
        }

        /// @brief Recognizes a number from a given image.
        /// @param input Source image.
        /// @return Digit as int.
        int predict(const cv::Mat& input) {
            cv::resize(input, input, cv::Size(28, 28));
            cv::Mat inputVector = input.reshape(1, 1);
            inputVector.convertTo(inputVector, CV_64F, 1.0 / 255.0);
            cv::Mat result = forwardPropagation(inputVector);
            cv::Point maxLocation;
            cv::minMaxLoc(result, nullptr, nullptr, nullptr, &maxLocation);
            return maxLocation.x;
        }
    };
}
