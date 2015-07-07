#ifndef PIPEIMG_H
#define PIPEIMG_H

/* Utilities to pass images to stdout and read images to stdin.
 *
 * All of these functions use PNG format to exchange data.
 *
 * Note that the use of util::in will read all the data from stdin.
 */

#include <opencv2/core/core.hpp>

namespace util {
    // Writes the image to stdout.
    void out( cv::Mat );

    // Reads the image from stdin.
    cv::Mat in();
}

#endif // PIPEIMG_H
