#include "src/menu.h"

using namespace std;

int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
    mondongo::start();
    /*vector<pair<cv::Mat, int>> images;
    mondongo::loadMnist(mondongo::MNIST_TRAINIMAGES, mondongo::MNIST_TRAINLABELS, ref(images));
    for (auto e : images) {
        mondongo::showImage(e.first);
    }*/
    return 0;
}