/* Filter the remaining noise of an image,
 * after passing through the threshold.
 *
 * Input is read on stdin, output is written to stdout.
 */
#include <algorithm>
#include <iostream>
#include "cmdline/args.hpp"
#include "pipeimg.h"

namespace command_line {
    enum operation {
        erode,
        dilate,
        open,
        close,
        reconstruct
    };

    cv::Mat z4 = (cv::Mat_<unsigned char>(3,3) <<
            0, 1, 0,
            1, 1, 1,
            0, 1, 0);
    cv::Mat z8 = (cv::Mat_<unsigned char>(3,3) <<
            1, 1, 1,
            1, 1, 1,
            1, 1, 1);
    cv::Mat z24 = (cv::Mat_<unsigned char>(5,5) <<
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1);
    cv::Mat z48 = (cv::Mat_<unsigned char>(7,7) <<
            1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1);
    cv::Mat fat_plus = (cv::Mat_<unsigned char>(5,5) <<
            0, 1, 1, 1, 0,
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1,
            1, 1, 1, 1, 1,
            0, 1, 1, 1, 0);
    cv::Mat h = (cv::Mat_<unsigned char>(1,3) <<
            1, 1, 1);
    cv::Mat v = (cv::Mat_<unsigned char>(3,1) <<
            1, 1, 1);

    operation op;
    cv::Mat kernel = z8;
    cv::Mat reconstruction = z8;

    void parse( cmdline::args && args ) {
        while( args.size() > 0 ) {
            std::string arg = args.next();
            if( arg == "--dilate" ) {
                op = dilate;
                continue;
            }
            if( arg == "--erode" ) {
                op = erode;
                continue;
            }
            if( arg == "--open" ) {
                op = open;
                continue;
            }
            if( arg == "--close" ) {
                op = close;
                continue;
            }
            if( arg == "--reconstruct" || arg == "--kernel" ) {
                if( arg == "--reconstruct" )
                    op = reconstruct;
                cv::Mat & ref = arg == "--kernel" ? kernel : reconstruction;
                arg = args.next();
                if( arg == "Z8" || arg == "z8" )
                    ref = z8;
                else if( arg == "Z4" || arg == "z4" )
                    ref = z4;
                else if( arg == "Z24" || arg == "z24" )
                    ref = z24;
                else if( arg == "Z48" || arg == "z48" )
                    ref = z48;
                else if( arg == "fatplus" || arg == "fat-plus" )
                    ref = fat_plus;
                else if( arg == "h" )
                    ref = h;
                else if( arg == "v" )
                    ref = v;
                else {
                    std::cerr << "Unknown kernel " << arg << '\n';
                    std::exit(1);
                }
                continue;
            }

            std::cerr << "Unknown option " << arg << '\n';
            std::exit(1);
        }
    }
} // namespace command_line

/* Returns the pixel i,j of c,
 * unless i and j fall outside the screen;
 * in this case, returns k.
 */
unsigned char at( cv::Mat c, int i, int j, int k ) {
    if( i < 0 || j < 0 || i >= c.rows || j >= c.cols )
        return k;

    return c.at<unsigned char>(i, j);
}

/* Erode the image img with the given mask (structuring element) se,
 * with the origin placed at the middle.
 */
cv::Mat erode( cv::Mat img, cv::Mat se ) {
    cv::Mat out( img.size(), CV_8UC1 );
    int x = se.rows / 2;
    int y = se.cols / 2;

    for( int i = 0; i < img.rows; i++ )
    for( int j = 0; j < img.cols; j++ ) {
        int pixel = 255;

        for( int k = -x; k < se.rows - x; k++ )
        for( int l = -y; l < se.cols - y; l++ )
            if( se.at<unsigned char>(k+x, l+y) > 0 )
                pixel = std::min<int>( pixel, at( img, i + k, j + l, 255 ) );

        out.at<unsigned char>( i, j ) = pixel > 128 ? 255 : 0;
    }
    return out;
}

/* Dilates the image img with the given mask (structuring element) se,
 * with the origin placed at the middle.
 */
cv::Mat dilate( cv::Mat img, cv::Mat se ) {
    cv::Mat out( img.size(), CV_8UC1 );
    int x = se.rows / 2;
    int y = se.cols / 2;

    for( int i = 0; i < img.rows; i++ )
    for( int j = 0; j < img.cols; j++ ) {
        int pixel = 0;

        for( int k = -x; k < se.rows - x; k++ )
        for( int l = -y; l < se.cols - y; l++ )
            if( se.at<unsigned char>(k+x, l+y) > 0 )
                pixel = std::max<int>( pixel, at( img, i + k, j + l, 0 ) );

        out.at<unsigned char>( i, j ) = pixel > 128 ? 255 : 0;
    }
    return out;
}

// Returns true if both matrices are equal, false otherwise.
bool mateq( cv::Mat lhs, cv::Mat rhs ) {
    if( lhs.rows != rhs.rows || lhs.cols != rhs.cols )
        return false;

    return cv::Mat(lhs == rhs).at<unsigned char>(0, 0) == 255;
}

cv::Mat reconstruct( cv::Mat img, cv::Mat se, cv::Mat re ) {
    cv::Mat out = dilate( erode( img, se ), se );
    return out;
    cv::Mat tmp;
    while( !mateq( tmp, out ) ) {
        tmp = out;
        out = dilate( out, re );
        out = min( out, img );
    }
    return tmp;
}

int main( int argc, char ** argv ) {
    command_line::parse( cmdline::args(argc, argv) );
    cv::Mat img = util::in();

    using command_line::kernel;
    switch( command_line::op ) {
        case command_line::erode:
            util::out( erode( img, kernel ) );
            break;
        case command_line::dilate:
            util::out( dilate( img, kernel ) );
            break;
        case command_line::open:
            util::out( dilate( erode( img, kernel ), kernel ) );
            break;
        case command_line::close:
            util::out( erode( dilate( img, kernel ), kernel ) );
            break;
        case command_line::reconstruct:
            util::out( reconstruct( img, kernel, command_line::reconstruction ) );
    }
    return 0;
}
