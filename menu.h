#pragma once

#include <iostream>
#include <map>
#include <sstream>

using namespace std;

#pragma region Constants
const string VERSION = "0.1a";
const char* CLEARCONSOLE = "\x1b[2J\x1b[H";
const char* CLEARLINE = "\r";
#pragma endregion

/// @brief Clears the console.
void clearConsole() {
  cout << CLEARCONSOLE;
}

/// @brief Clears the last printed line.
void clearLine() {
    cout << CLEARLINE;
}

/// @brief Holds main menu options.
enum OPTION {
    START,
    QUIT = 0,
    TRAIN = 1,
    LOADTXT = 2,
    RECOGNIZE = 3,
    END
};

/// @brief Displays possible options.
void showOptions() {
    map<int, std::string> optionMap;
    optionMap[QUIT] = "Quit";
    optionMap[TRAIN] = "Train NN from MNIST data";
    optionMap[LOADTXT] = "Load NN from file";
    optionMap[RECOGNIZE] = "Recognize digit from an image";

    for (const auto& pair : optionMap) {
        cout << "[" << pair.first << "] " << pair.second << endl;
    }
    cout << endl;
}

/// @brief Asks and checks for valid input of type T.
/// @tparam T Type of desired input.
/// @param msg User prompt.
/// @return User input of type T.
template <typename T>
auto input(string msg = "") {
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

/// @brief Runs on startup.
void start() {
    while (true) {
        clearConsole();
        cout << "MondongoFrito - Digit Recognition\n" << "Ver " << VERSION << "\n" << endl;
        showOptions();

        auto opt = input<int>();

        switch (opt) {
            case QUIT: return;
            case TRAIN: break; // Pide directorio del mnist y hace n bucles por imagen, luego guarda el archivo
            case LOADTXT: break; // Carga un txt con la info de la red, y la tiene lista
            case RECOGNIZE: break; // usa la nn cargada para reconocer una imagen especificada por el usuario
        }
    }
}