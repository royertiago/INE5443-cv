#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cmdline/args.hpp"
#include "positioning.h"
#include "pipeimg.h"

namespace command_line {
    std::string left, right;

    void parse( cmdline::args&& args ) {
        left = args.next();
        right = args.next();
    }
}

int main( int argc, char ** argv ) {
    command_line::parse( cmdline::args(argc, argv) );

    cv::Mat left = cv::imread( command_line::left, CV_LOAD_IMAGE_GRAYSCALE );
    cv::Mat right = cv::imread( command_line::right, CV_LOAD_IMAGE_GRAYSCALE );

    util::out( best_delta( left, right, 10 ) );
}
