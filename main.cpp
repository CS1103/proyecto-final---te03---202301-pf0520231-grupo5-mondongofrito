#include <opencv2/opencv.hpp> // Solo funciona si se agrega el path correcto

using namespace std;
using namespace cv;

int main() {
    Mat image = imread("images.jpg", IMREAD_COLOR); // Puede usar otro directorio

    if (image.empty()) {
        cout << "Hubo un error al leer la imagen" << endl;
        return -1;
    }

    namedWindow("Image", WINDOW_NORMAL);
    imshow("Image", image);
    waitKey(0);
    destroyWindow("Image");

    return 0;
}

// Nunca mas opencv