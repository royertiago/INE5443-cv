/* Reads an image in stdin and resize it do 10x10.
 */
#include <opencv2/opencv.hpp>
#include "pipeimg.h"

int main() {
    cv::Mat img = util::in();
    cv::Mat target;
    cv::resize( img, target, cv::Size(10, 10) );
    util::out( target );
    return 0;
}
