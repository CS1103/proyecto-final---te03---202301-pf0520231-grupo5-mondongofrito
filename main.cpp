#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    bool isGray = true; // True si se quiere convertir a grises, false para color
    Mat img = imread("images.jpg", IMREAD_COLOR);

    if (img.empty()) {
        cout << "No se pudo cargar la imagen" << endl;
        return -1;
    }
    if (!isGray) {
        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                Vec3b& color = img.at<Vec3b>(i, j);
                cout << "Pixel en (" << i << ", " << j << ") BGR: ["
                << (int)color[0] << ", " << (int)color[1] << ", " << (int)color[2] << "]\n";
            }
        }
        namedWindow("Image", WINDOW_NORMAL);
        imshow("Image", img);
        waitKey(0);
        destroyWindow("Image");
    }
    else {
        Mat imgGray;
        cvtColor(img, imgGray, COLOR_BGR2GRAY);

        for (int i = 0; i < imgGray.rows; i++) {
            for (int j = 0; j < imgGray.cols; j++) {
                uchar intensity = imgGray.at<uchar>(i, j);
                cout << "Pixel en (" << i << ", " << j << ") GRISES: "
                << (int)intensity << endl;
            }
        }
        namedWindow("Image", WINDOW_NORMAL);
        imshow("Image", imgGray);
        waitKey(0);
        destroyWindow("Image");
    }
    return 0;
}