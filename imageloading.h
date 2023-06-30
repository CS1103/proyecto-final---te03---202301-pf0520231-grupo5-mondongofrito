#include <iostream>
#include <fstream>
#include <vector>
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

void loadMnist(string imagePath, string labelPath, vector<pair<Mat, int>> &vec){

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

    char* currentImageValues = new char[rows * cols]; // Array temporal a usar para guardar la imagen actual dentro del bucle
    char label; // El numero que representa la imagen

    for (int imageIndex = 0; imageIndex < itemNumber; ++imageIndex) {
        images.read(currentImageValues, rows * cols);
        labels.read(&label, 1);
        Mat currentImage(rows, cols, CV_8UC1, currentImageValues); // Creamos una matriz a partir del array
        currentImage.convertTo(currentImage, CV_64F, 1.0 / 255.0); // Convertimos el valor de cada pixel al formato que usamos
        resize(currentImage, currentImage, Size(28, 28)); // Cambiamos las dimensiones de la imagen
        vec.push_back(make_pair(currentImage, int(label)));
    }
    delete[] currentImageValues;
} // Carga cada imagen del archivo a un vector de pairs<Mat, int>, donde Mat es la imagen y el int es el label

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


// ayuda aaaaaaaaaaa