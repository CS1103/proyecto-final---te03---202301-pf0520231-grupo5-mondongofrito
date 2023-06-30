#include "imageloading.h"
#include <opencv2/core/utils/logger.hpp>

using namespace cv;
using namespace std;

int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
    string imagePath = "C:/Users/Danee/VSCodeProjects/MondongoFrito/mnist/t10k-images.idx3-ubyte";
    string labelPath = "C:/Users/Danee/VSCodeProjects/MondongoFrito/mnist/t10k-labels.idx1-ubyte";
    vector<pair<Mat, int>> images;
    loadMnist(imagePath, labelPath, ref(images));
    for (const auto &e : images) {
        cout << "Current image label: " << e.second << endl;
        showImage(e.first);
    }
    return 0;
}