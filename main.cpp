#include "menu.h"

using namespace std;

int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
    mondongo::start();/*
    string imagePath = "./mnist/train-images.idx3-ubyte";
    string labelPath = "./mnist/train-labels.idx1-ubyte";
    vector<pair<cv::Mat, int>> images;
    mondongo::loadMnist(imagePath, labelPath, ref(images));*/
    return 0;
}