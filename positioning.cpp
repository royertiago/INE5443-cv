#include <algorithm>
#include "positioning.h"

namespace {

    long unsigned delta( cv::Mat left, cv::Mat right ) {
        long unsigned sum = 0;
        for( int i = 0; i < left.rows; i++ )
            for( auto ptr = left.ptr<unsigned char>(i),
                    pts = right.ptr<unsigned char>(i);
                    ptr != left.ptr<unsigned char>(i) + left.cols;
                    ++ptr, ++pts
                )
            {
                sum += std::abs( *ptr - *pts );
            }

        return sum;
    }

} // anonymous namespace

cv::Mat best_delta( cv::Mat lhs, cv::Mat rhs, int lim ) {
    int width = lhs.size().width;
    int height = lhs.size().height;

    long unsigned min = -1u; 
    cv::Mat best_subleft, best_subright;

    for( int i = 0; i < lim; i++ )
    for( int j = 0; j < lim; j++ ) {
        cv::Mat subleft = lhs( cv::Range(0, height - i), cv::Range(0, width - j) );
        cv::Mat subright = rhs( cv::Range(i, height), cv::Range(j, width) );
        auto diff = delta( subleft, subright );
        if( diff < min ) {
            min = diff;
            best_subleft = subleft;
            best_subright = subright;
        }
    }
    return cv::abs(best_subleft - best_subright);
}
