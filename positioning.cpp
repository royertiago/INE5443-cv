#include "positioning.h"

namespace {

    int sqnorm( cv::Vec3b d ) {
        return d[0]*d[0] + d[1]*d[1] + d[2]*d[2];
    }

    long unsigned squared_delta( cv::Mat left, cv::Mat right ) {
        long unsigned sum = 0;
        for( auto it = left.begin<cv::Vec3b>(), jt = right.begin<cv::Vec3b>();
                it != left.end<cv::Vec3b>() && jt != right.end<cv::Vec3b>();
                ++it, ++jt
            )
        {
            sum += sqnorm( *it - *jt );
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
        auto diff = squared_delta( subleft, subright );
        if( diff < min ) {
            min = diff;
            best_subleft = subleft;
            best_subright = subright;
        }
    }
    return best_subleft - best_subright;
}
