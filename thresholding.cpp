/* Reads an image in stdin,
 * computes the highest pixel value in the image,
 * replaces everything above half with white
 * and everything below half with black,
 * and writes the result to stdout.
 */
#include <iostream>
#include "pipeimg.h"
#include "threshold.h"

int main() {
    cv::Mat img = util::in();

    int threshold = max(img) / 2;
    std::clog << "Threshold: " << threshold << '\n';

    ::threshold( img, threshold );
    util::out( img );
    return 0;
}
