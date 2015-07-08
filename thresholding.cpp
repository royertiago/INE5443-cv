/* Reads an image in stdin,
 * computes the highest pixel value in the image,
 * replaces everything above half with white
 * and everything below half with black,
 * and writes the result to stdout.
 */
#include "pipeimg.h"

/* Returns the maximum value of c.
 */
int max( cv::Mat c ) {
    int max = 0;
    for( int i = 0; i < c.rows; i++ )
        for( auto ptr = c.ptr<unsigned char>(i);
                ptr != c.ptr<unsigned char>(i) + c.cols;
                ++ptr
            )
        {
            max = std::max<int>( max, *ptr );
        }
    return max;
}

/* Replaces every byte in the figure with either 0 or 255,
 * according to the threshold.
 */
void threshold( cv::Mat img, int threshold ) {
    for( int i = 0; i < img.rows; i++ )
        for( auto ptr = img.ptr<unsigned char>(i);
                ptr != img.ptr<unsigned char>(i) + img.cols;
                ++ptr
            )
        {
            if( *ptr >= threshold )
                *ptr = 255;
            else
                *ptr = 0;
        }
}

int main() {
    cv::Mat img = util::in();
    int threshold = max(img) / 2;
    ::threshold( img, threshold );
    util::out( img );
    return 0;
}
