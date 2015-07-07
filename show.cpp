/* Program that reads an image format from stdin
 * and shows to the screen.
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "pipeimg.h"

int main() {
    cv::Mat img = util::in();
    cv::namedWindow( "Image", cv::WINDOW_NORMAL );
    cv::imshow( "Image", img );
    cv::waitKey();
    return 0;
}
