#include "imageloading.h"

using namespace std;
using namespace mondongo;

/// @brief Swaps a uint32_t value from bigEndian to littleEndian or viceversa.
/// @param input Of type uint32_t.
/// @return Endian-swapped input.
constexpr uint32_t mondongo::swapEndian(uint32_t input) {
    // Sabemos que un byte son 8 bits, asi que podemos ver el unsigned de 32 como 4 arrays de 8 elementos cada uno
    // Para invertir el orden y que nuestro procesador pueda leerlo, debemos intercambiar el orden de los bytes
    // Digamos que iniciamos con un array 1 2 3 4

    uint32_t output = 0;                       // 1 2 3 4
    output |= ((input & 0xFF) << 24);          // 4 2 3 4
    output |= ((input & 0xFF00) << 8);         // 4 3 3 4
    output |= ((input & 0xFF0000) >> 8);       // 4 3 2 4
    output |= ((input & 0xFF000000) >> 24);    // 4 3 2 1
    return output;
} // Invierte un unsigned int de 32 bytes de big endian a little endian (y viceversa)
// El mnist guardaba los archivos con un orden de bytes distinto al de procesadores intel, por eso que explotaba todo
// Con eso nos aseguramos de que podamos leerlo al invertir el orden de los bytes
// O al menos eso entendí :')

/// @brief Loads images and labels to a pair vector passed by reference.
/// @param imagePath Path to the .idx3-ubyte file.
/// @param labelPath Path to the .idx1-ubyte file.
/// @param vec A vector of pairs, each pair holds an image and its corresponding label.
void mondongo::loadMnist(string imagePath, string labelPath, vector<pair<cv::Mat, int>> &vec){

    ifstream images(imagePath, ios::in | ios::binary);
    ifstream labels(labelPath, ios::in | ios::binary);

    uint32_t magicNumber, itemNumber, num_labels, rows, cols;

    images.read(reinterpret_cast<char*>(&magicNumber), 4);
    magicNumber = swapEndian(magicNumber);

    labels.read(reinterpret_cast<char*>(&magicNumber), 4);
    magicNumber = swapEndian(magicNumber);

    images.read(reinterpret_cast<char*>(&itemNumber), 4);
    itemNumber = swapEndian(itemNumber);

    labels.read(reinterpret_cast<char*>(&num_labels), 4);
    num_labels = swapEndian(num_labels);

    images.read(reinterpret_cast<char*>(&rows), 4);
    rows = swapEndian(rows);

    images.read(reinterpret_cast<char*>(&cols), 4);
    cols = swapEndian(cols);

    // El reinterpret cast convierte la direccion de memoria de cada parametro en un puntero, por eso el char*
    // Luego se invierte el orden de los bytes para poder leerlo

    char* currentImageValues = new char[rows * cols]; // Array temporal a usar para guardar la imagen actual dentro del bucle
    char label; // El numero que representa la imagen

    for (uint32_t imageIndex = 0; imageIndex < itemNumber; ++imageIndex) {
        images.read(currentImageValues, rows * cols);
        labels.read(&label, 1);
        cv::Mat currentImage(rows, cols, CV_8UC1, currentImageValues); // Creamos una matriz a partir del array
        currentImage.convertTo(currentImage, CV_64F, 1.0 / 255.0); // Convertimos el valor de cada pixel al formato que usamos
        cv::resize(currentImage, currentImage, cv::Size(28, 28)); // Cambiamos las dimensiones de la imagen
        vec.push_back(make_pair(currentImage, int(label)));
    }
    delete[] currentImageValues;
} // Carga cada imagen del archivo a un vector de pairs<Mat, int>, donde Mat es la imagen y el int es el label

/// @brief Modifies the image to one with values between 0.0 and 1.0.
/// @param image Image to modify.
void mondongo::normalizeImage(cv::Mat &image) {
    image.convertTo(image, CV_64F, 1.0 / 255.0);
} // Convierte los pixeles de rango 0-255 a 0-1

/// @brief Loads an image file from a path and returns it as an OpenCV Mat.
/// @param path Path to an image file (.png, .jpg, etc).
/// @param isGray True if gray reading is desired, false for color. Gray by default.
/// @return cv::Mat holding the loaded image pixels.
cv::Mat mondongo::loadImage(const string &path, bool isGray) {
    cv::Mat image = isGray ? cv::imread(path, cv::IMREAD_GRAYSCALE) : cv::imread(path, cv::IMREAD_COLOR);
    return image;
} // Carga una imagen a color o grises, por default se carga a grises

/// @brief Opens a window for image display.
/// @param image a cv::Mat holding the image to display.
/// @param windowName the desired window name (optional).
void mondongo::showImage(const cv::Mat &image, const string &windowName) {
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::imshow(windowName, image);
    cv::waitKey(0);
    cv::destroyWindow(windowName);
} // Muestra una imagen con un nombre opcional de ventana

/// @brief Displays pixel values for each pixel in a cv::Mat of type CV_64F.
/// @param image Image to display values from.
/// @param round False by default, rounds values to the closest integer.
void mondongo::displayImageValues(const cv::Mat &image, bool round) {
    if (image.type() == CV_64F) {
        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                cout << (round ? std::round(image.at<double>(i, j)) : image.at<double>(i, j)) << " "; // Si se desea aproximar
            }
            cout << endl;
        }
    }
    else {
        cout << "Image is not CV_64F" << endl;
    }
    
} // Muestra el valor de cada pixel como int o double, el input debe ser CV_64F (grises)

/// @brief Displays a CV_64F image as ASCII art.
/// @param image Image to display.
void mondongo::displayImageChars(const cv::Mat &image) {
    if (image.type() == CV_64F) {
        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                auto val = image.at<double>(i, j);
                if (val == 0) {
                    cout << "  ";
                }
                else if (val > 0  && val < 0.2) {
                    cout << ". ";
                }
                else if (val >= 0.2 && val < 0.4) {
                    cout << ", ";
                }
                else if (val >= 0.4 && val < 0.6) {
                    cout << "+ ";
                }
                else if (val >= 0.6 && val < 0.8) {
                    cout << "* ";
                }
                else if (val > 0.8) {
                    cout << "# ";
                }
            }
            cout << endl;
        }
    }
    else {
        cout << "Image is not CV_64F" << endl;
    }
}

/// @brief cv::Mat::reshape wrapper, turns a matrix into an array.
/// @param img cv::Mat to be flattened.
void mondongo::flatten(const cv::Mat &img) {
    cv::Mat cop = img;
    cop = cop.reshape(1, 1);
    for (auto i = 0; i < cop.cols; ++i) {
        cout << cop.at<double>(i) << endl;
    }
}