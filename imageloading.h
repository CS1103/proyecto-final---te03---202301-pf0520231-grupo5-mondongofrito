#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

uint32_t swapEndian(uint32_t input) {
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

void loadMnist(const string &imagePath, const string &labelPath) {
    ifstream images(imagePath, std::ios::in | std::ios::binary);
    ifstream labels(labelPath, std::ios::in | std::ios::binary);

    uint32_t magicNum, itemNum, labelNum, rows, cols;
} // aaaaaaaaaaaaaa
  // Probablemente debería devolver un vector con las imágenes

void normalizeImage(Mat &image) {
    image.convertTo(image, CV_64F, 1.0 / 255.0);
} // Convierte los pixeles de rango 0-255 a 0-1

Mat loadImage(const string &path, bool isGray = true) {
    Mat image = isGray ? imread(path, IMREAD_GRAYSCALE) : imread(path, IMREAD_COLOR);
    return image;
} // Carga una imagen a color o grises, por default se carga a grises

void showImage(const Mat &image, const string &windowName = "Press any key to close") {
    namedWindow(windowName, WINDOW_NORMAL);
    imshow(windowName, image);
    waitKey(0);
    destroyWindow(windowName);
} // Muestra una imagen con un nombre opcional de ventana

void displayImageValues(const Mat &image, bool round = false) {
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

// http://neuralnetworksanddeeplearning.com/chap1.html
// https://docs.opencv.org/4.7.0/d1/dfb/intro.html
// https://stackoverflow.com/questions/1041554/bitwise-operators-and-endianness
// https://stackoverflow.com/questions/8286668/how-to-read-mnist-data-in-c



// No estoy mentalmente preparado para los finales