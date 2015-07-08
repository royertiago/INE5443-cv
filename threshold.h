#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <opencv2/core/core.hpp>

/* Returns the maximum pixel value in this cv::Mat.
 */
int max( cv::Mat );

/* Replaces everything in the matrix lower than the threshold by zero
 * and everything higher than (or equal to) the threshold by 255. */
void threshold( cv::Mat, int threshold );

#endif // THRESHOLD_H
