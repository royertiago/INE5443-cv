#ifndef POSITIONING_H
#define POSITIONING_H

#include <opencv2/core/core.hpp>

/* Computes the difference between the two images;
 * however, this function is allowed to reposition both images
 * in order to minimize this difference.
 *
 * 'tolerance' is how much pixels are we allowed to move the images.
 *
 * The idea is that if the two images are from the same place,
 * an added or removed element will have great impact in the 
 * resulting difference, wether we move the image or not;
 * but moving the image will minimize the difference
 * that is due to camera movimentation.
 *
 * Note that the resulting image may be smaller than the inputs.
 */
cv::Mat best_delta( cv::Mat, cv::Mat, int tolerance );

#endif // POSITIONING_H
