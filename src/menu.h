#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <memory>
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <fstream>

#include "imageloading.h"
#include "structure.h"

using namespace std;

namespace mondongo {
    const string MNIST_TRAINIMAGES = "../../mnist/train-images.idx3-ubyte";
    const string MNIST_TRAINLABELS = "../../mnist/train-labels.idx1-ubyte";
    const string VERSION = "0.1a";
    const string USERCONFIRM = "YyNn";
    enum OPTION {
        QUIT   = 0,
        CREATE = 1,
        LOAD   = 2,
        TRAIN  = 3,
        GUESS  = 4
    };
    template <typename T>
    auto input(string msg = "");
    void clearConsole();
    void clearLine();
    void showOptions();
    void createNeuralNetwork(unique_ptr<NeuralNetwork> &nn);
    bool assertFileOpening(string &path);
    string openFileExplorer();
    void loadNeuralNetwork(unique_ptr<NeuralNetwork> &nn);
    void start();
}
