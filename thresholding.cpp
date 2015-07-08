namespace command_line {
    const char help_message[] =
" <threshold> [options]\n"
"Reads an image from stdin,\n"
"replaces every byte above the threshold with 255 and every byte below by 0\n"
"and writes it to stdout.\n"
"\n"
"If no options nor the threshold is given, assumes '--ratio 0.5'.\n"
"\n"
"Options:\n"
"--ratio <F>\n"
"    Instead of using an absolute value, pick the greatest value on the image,\n"
"    multiplies by the given floating point, and use this value as threshold.\n"
"\n"
"--help\n"
"    Display this message and exit.\n"
;
} // namespace command_line

#include "cmdline/args.hpp"
#include "pipeimg.h"

namespace command_line {
    int threshold = -1;
    double ratio = 0.5;

    void parse( cmdline::args && args ) {
        while( args.size() > 0 ) {
            std::string arg = args.peek();
            if( arg == "--ratio" ) {
                args.shift();
                args.range(0, 1) >> ratio;
                continue;
            }
            if( arg == "--help" ) {
                std::cout << args.program_name() << help_message;
                std::exit(0);
            }
            args.range(0, 255) >> threshold;
        }
    }
} // namespace command_line

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

int main( int argc, char ** argv ) {
    command_line::parse( cmdline::args(argc, argv) );
    cv::Mat img = util::in();

    int threshold;
    if( command_line::threshold == -1 )
        threshold = max(img) * command_line::ratio;
    else
        threshold = command_line::threshold;

    ::threshold( img, threshold );
    util::out( img );
    return 0;
}
