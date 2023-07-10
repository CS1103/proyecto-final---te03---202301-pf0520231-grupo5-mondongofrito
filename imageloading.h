#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;

namespace mondongo {
    constexpr uint32_t swapEndian(uint32_t input);
    void loadMnist(string imagePath, string labelPath, vector<pair<cv::Mat, int>> &vec);
    void normalizeImage(cv::Mat &image);
    cv::Mat loadImage(const string &path, bool isGray = true);
    void showImage(const cv::Mat &image, const string &windowName = "Press any key to close");
    void displayImageValues(const cv::Mat &image, bool round = false);
    void displayImageChars(const cv::Mat &image);
}

// http://neuralnetworksanddeeplearning.com/chap1.html
// https://docs.opencv.org/4.7.0/d1/dfb/intro.html
// https://stackoverflow.com/questions/1041554/bitwise-operators-and-endianness
// https://stackoverflow.com/questions/8286668/how-to-read-mnist-data-in-c

// ayuda aaaaaaaaaaa