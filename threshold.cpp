#include <algorithm>
#include "threshold.h"

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
