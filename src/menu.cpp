#include "menu.h"

using namespace std;
using namespace mondongo;

/// @brief Asks and checks for valid input of type T.
/// @tparam T Type of desired input.
/// @param msg User prompt.
/// @return User input of type T.
template <typename T>
auto mondongo::input(string msg) {
    if (!msg.empty()) {
        cout << msg << endl;
    }
    T value;
    string line;
    while (getline(cin, line))
    {
        stringstream ss(line);
        if (ss >> value)
        {
            if (ss.eof()) { break; }
        }
        cout << "\nInput should be of type " << typeid(T).name() << endl;
    }
    return value;
}

/// @brief Clears the console.
void mondongo::clearConsole() {
    system("cls");
}

/// @brief Clears the last printed line.
void mondongo::clearLine() {
    cout << "\r";
}

/// @brief Displays possible options.
void mondongo::showOptions() {
    map<int, std::string> optionMap;
    optionMap[QUIT]   = "Quit";
    optionMap[CREATE] = "Create a Neural Network";
    optionMap[LOAD]   = "Load a Neural Network from a .txt file";
    optionMap[TRAIN]  = "Train the loaded network";
    optionMap[GUESS]  = "Run a prediction test";

    for (const auto& pair : optionMap) {
        cout << "[" << pair.first << "] " << pair.second << endl;
    }
    cout << endl;
}

/// @brief Creates a neural network
/// @param nn Neural network pointer to host the network on
void mondongo::createNeuralNetwork(unique_ptr<NeuralNetwork> &nn) {
    clearConsole();
    while (nn) { // If the NN already exists
        auto opt = input<string>("A neural network was found. Would you like to override it? [Y/N]:");
        while (USERCONFIRM.find(opt) == string::npos) {
            opt = input<string>("\nNot a valid option. [Y/N]:");
        }
        if (opt == "Y" || opt == "y") { cout << endl; break; }
        else if (opt == "N" || opt == "n") { return; }
    }
    int hiddenNeurons = input<int>("Enter number of hidden neurons [10+]:");
    while (hiddenNeurons < 10) {
        hiddenNeurons = input<int>("\nThe network must have more than 10 neurons:");
    }
    // delete old object in ptr and assign it a new one
    nn.reset(new NeuralNetwork(28*28, hiddenNeurons, 10));
}

/// @brief Verifies the correct opening and reading of data files.
/// @param path The path of the selected file.
/// @return True if file was read and loaded correctly, false otherwise.
bool mondongo::assertNeuralNetworkDataOpening(string &path) {
    auto file = ifstream(path);
    if(!file.is_open()) { return false;}
    string check; getline(file, check);
    if (check.substr(0, 15) != "/MondongoFrito/") { return false; }
    return true;
}

/// @brief Verifies the selected file is of the desired extension.
/// @param path File path.
/// @param extension Extension to be checked for.
/// @return True if extension matches, false otherwise.
bool mondongo::assertFileExtension(string path, string extension) {
    filesystem::path filePath = path;
    return filePath.extension() == extension;
}

/// @brief Opens the file explorer to look for a file.
/// @return The selected file absolute path.
string mondongo::openFileExplorer() {
    char filename[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = NULL;
    ofn.lpstrFilter = _T("Text Files\0*.txt\0Any File\0*.*\0");
    ofn.lpstrFile   = filename;
    ofn.nMaxFile    = MAX_PATH;
    ofn.lpstrTitle  = _T("Please select the .txt data file");
    ofn.Flags       = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        cout << "\nFile \"" << filename << "\" selected.\n";
        return ofn.lpstrFile;
    }
    else {
        cout << "\nOperation cancelled.\n" << endl;
        system("pause");
        return "cancel";
    }
}

/// @brief Loads a neural network from a file.
/// @param nn Neural network pointer to load the network to.
void mondongo::loadNeuralNetwork(unique_ptr<NeuralNetwork> &nn) {
    clearConsole();
    while (nn) {
        auto opt = input<string>("A neural network was found. Would you like to override it? [Y/N]:");
        while (USERCONFIRM.find(opt) == string::npos) {
            opt = input<string>("\nNot a valid option. [Y/N]:");
        }
        if (opt == "Y" || opt == "y") { cout << endl; break; }
        else if (opt == "N" || opt == "n") { return; }
    }
    cout << "Please choose the .txt data file:\n";
    string dataPath = openFileExplorer();
    if (!assertNeuralNetworkDataOpening(dataPath)) {
        cout << "\nSelection is not a valid MondongoFrito file.\n" << endl;
        system("pause");
    }
    else {
        nn.reset(new NeuralNetwork(dataPath)); // TODO
    }
}

/// @brief Calls the NN trainer.
/// @param nn Pointer to the NN.
void mondongo::trainNeuralNetwork(unique_ptr<NeuralNetwork> &nn) {
    clearConsole();
    while (!nn) { // If there's no nn yet
        auto opt = input<string>("No neural network found. Would you like to create one? [Y/N]:");
        while (USERCONFIRM.find(opt) == string::npos) {
            opt = input<string>("\nNot a valid option. [Y/N]:");
        }
        if (opt == "Y" || opt == "y") { cout << endl; createNeuralNetwork(nn); break; }
        else if (opt == "N" || opt == "n") { return; }
    }
    cout << "\nPlease select the MNIST image file:\n";
    string imagePath = openFileExplorer();
    cout << "\nPlease select the MNIST label file:\n";
    string labelPath = openFileExplorer();

    if (assertFileExtension(imagePath, MNIST_TRAINIMAGES_EXTENSION) && assertFileExtension(labelPath, MNIST_TRAINLABELS_EXTENSION)) {
        nn->train(imagePath, labelPath);
    }
}

/// @brief Main program loop.
void mondongo::start() {
    unique_ptr<NeuralNetwork> nn(nullptr);
    while (true) {
        clearConsole();
        cout << "MondongoFrito - Digit Recognition\n" << "Ver " << VERSION << "\n" << endl;
        if (nn) {
            cout << "* Neural Network is loaded!\n" << endl;
        }
        showOptions();
        auto opt = input<int>();
        switch (opt) {
            case QUIT: return;
            case CREATE: 
                createNeuralNetwork(nn);
                break;
            case LOAD:
                loadNeuralNetwork(nn); // Carga un txt con la info de la red, y la tiene lista
                break;
            case TRAIN:
                trainNeuralNetwork(nn);
                break;
        }
    }
}
