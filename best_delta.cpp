#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cmdline/args.hpp"
#include "pipeimg.h"

namespace command_line {
    std::string left, right;

    void parse( cmdline::args&& args ) {
        left = args.next();
        right = args.next();
    }
} // namespace command_line

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

int main( int argc, char ** argv ) {
    command_line::parse( cmdline::args(argc, argv) );

    cv::Mat left = cv::imread( command_line::left, CV_LOAD_IMAGE_GRAYSCALE );
    cv::Mat right = cv::imread( command_line::right, CV_LOAD_IMAGE_GRAYSCALE );

    util::out( best_delta( left, right, 10 ) );
}
