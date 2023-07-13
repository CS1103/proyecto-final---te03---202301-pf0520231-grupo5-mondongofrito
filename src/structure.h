#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <random>

using namespace std;

namespace mondongo {
    class NeuralNetwork {
        cv::Mat inputLayer; // Vector containing current image pixels
        cv::Mat hiddenLayer; // Vector containing the hidden layer values
        double hiddenNeurons = 0; // Size of hidden layer
        int resolution; // Size of input layer
    public:
        double hiddenLayerSize() { return hiddenNeurons; }
        NeuralNetwork() {
            hiddenNeurons = 0;
        }
        NeuralNetwork(int hiddenNeurons) {
            hiddenNeurons = hiddenNeurons;
            hiddenLayer.reshape(hiddenNeurons);
        }
        NeuralNetwork(string dataPath) {
            
        }
        void train(vector<pair<cv::Mat, int>> &dataset, int timesPerImage) {
        }
    };
};