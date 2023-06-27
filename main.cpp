#include <iostream>
#include <opencv2/opencv.hpp>
#include "imageloading.h"

using namespace cv;
using namespace std;

int main() {
    Mat image = loadImage("images.jpg");
    normalizeImage(image);
    cout << "Rounded values:" << endl; 
    displayImageValues(image, true);
    showImage(image);
    return 0;
}