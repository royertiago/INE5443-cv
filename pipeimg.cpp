#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "pipeimg.h"

namespace util {
    void out( cv::Mat img ) {
        std::vector< unsigned char > buffer;
        cv::imencode( ".png", img, buffer );
        for( unsigned char c : buffer )
            std::cout.put( c );
    }

    cv::Mat in() {
        std::vector<unsigned char> buffer;
        int c;
        while( (c = std::cin.get()) != EOF )
            buffer.push_back( c );

        return cv::imdecode( buffer, CV_LOAD_IMAGE_GRAYSCALE );
    }
}
