/* Program that reads an 10x10 image from stdin
 * and, based on the neural network in the file neural.net,
 * writes how close to a dog or an human this input is.
 */
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <fann.h>
#include <fann_cpp.h>
#include "pipeimg.h"

std::vector<float> mat_to_vector( cv::Mat img ) {
    std::vector<float> ret;
    for( int i = 0; i < img.rows; i++ )
        for( auto ptr = img.ptr<unsigned char>(i);
                ptr != img.ptr<unsigned char>(i) + img.cols;
                ++ptr
            )
        {
            ret.push_back( *ptr / 255.0 );
        }

    return ret;
}

int main() {
    cv::Mat img = util::in();
    auto vec = mat_to_vector( img );

    FANN::neural_net nn;
    nn.create_from_file( "neural.net" );
    auto result = nn.run( vec.data() );

    std::cout << "Dog index: " << result[0] << '\n';
    std::cout << "Human index: " << result[1] << '\n';
}
