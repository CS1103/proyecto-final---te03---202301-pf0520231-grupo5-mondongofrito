#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

/*
void loadMnist(const string &path) {
    ifstream idxFile (path,ios::binary);
}*/ // Deberia convertir los archivos idx de imagenes y labels a matrices y un numeros dependiendo del label

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
/*
void train(int loopsPerImage, std::vector<double> biases) {
    for (int i = 0; i < loopsPerImage; ++i) {

    }
}*/ // Idealmente deberia loopear por cada imagen loopsPerImage veces, ajustando los weights y biases del modelo

// http://neuralnetworksanddeeplearning.com/chap1.html
// https://docs.opencv.org/4.7.0/d1/dfb/intro.html
