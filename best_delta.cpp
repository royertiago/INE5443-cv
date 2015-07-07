#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cmdline/args.hpp"
#include "positioning.h"

namespace command_line {
    std::string left, right;

    void parse( cmdline::args&& args ) {
        left = args.next();
        right = args.next();
    }
}

int main( int argc, char ** argv ) {
    command_line::parse( cmdline::args(argc, argv) );

    cv::Mat left = cv::imread( command_line::left, CV_LOAD_IMAGE_COLOR );
    cv::Mat right = cv::imread( command_line::right, CV_LOAD_IMAGE_COLOR );

    const char * window = "Best delta";
    cv::namedWindow( window, cv::WINDOW_NORMAL );
    cv::imshow( window, best_delta(left, right, 7) );
    cv::waitKey();

}
