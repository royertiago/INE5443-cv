/* This program searches for the
 * "most white subfigure" of the input.
 *
 * The program clusterizes the input into rectagles
 * (with dimensions about the square root of the input dimensions)
 * and computes the highest cluster value.
 * Then, it generates the smallest image than contains
 * all the clusters whose size is greater than half the highest cluster.
 */
#include <algorithm>
#include <iostream>
#include <cmath>
#include <list>
#include <utility>
#include "pipeimg.h"

int sum( cv::Mat subfig ) {
    int sum = 0;
    for( int i = 0; i < subfig.rows; i++ )
        for( auto ptr = subfig.ptr<unsigned char>(i);
                ptr != subfig.ptr<unsigned char>(i) + subfig.cols;
                ++ptr
            )
            sum += *ptr > 128;
    return sum;
}

cv::Mat img;
std::vector< std::vector<int> > clusters, map;
int group_number;
int v; // vertical cluster number
int h; // horizontal cluster number

void build_clusters() {
    v = std::sqrt( img.rows );
    h = std::sqrt( img.cols );

    clusters = std::vector< std::vector<int> >( h, std::vector<int>( v ) );

    for( int i = 0; i < h; i++ )
    for( int j = 0; j < v; j++ ) {
        cv::Mat subfig = img(
            cv::Range( j * img.rows / v, (j+1) * img.rows / v ),
            cv::Range( i * img.cols / h, (i+1) * img.cols / h )
        );
        clusters[i][j] = sum( subfig );
    }
}

void dijkstra() {
    group_number = 0;
    map = std::vector< std::vector< int > > ( h, std::vector<int>( v ) );
    int current_group = 1;
    int max_group_size = 0;

    for( int x = 0; x < map.size(); x++ )
    for( int y = 0; y < map[0].size(); y++ ) {
        if( map[x][y] != 0 )
            continue;

        int group_size = 0;
        std::list< std::pair<int, int> > queue;
        queue.push_back( std::make_pair(x, y) );
        while( !queue.empty() ) {
            auto pair = queue.front();
            queue.pop_front();

            int i = pair.first;
            int j = pair.second;

            if( clusters[i][j] == 0 )
                continue;
            if( map[i][j] != 0 )
                continue;

            group_size += clusters[i][j];
            map[i][j] = current_group;
            if( i > 0 )
                queue.emplace_back( i-1, j );
            if( j > 0 )
                queue.emplace_back( i, j-1 );
            if( i < map.size() - 1 )
                queue.emplace_back( i+1, j );
            if( j < map[0].size() - 1 )
                queue.emplace_back( i, j+1 );
        }

        if( group_size > max_group_size ) {
            max_group_size = group_size;
            group_number = current_group;
        }
        current_group++;
    }
}

cv::Mat best_array( cv::Mat img ) {
    int imin = h, imax = 0, jmin = v, jmax = 0;
    for( int i = 0; i < h; i++ )
    for( int j = 0; j < v; j++ ) {
        if( map[i][j] == group_number ) {
            imin = std::min( imin, i );
            imax = std::max( imax, i+1 );
            jmin = std::min( jmin, i );
            jmax = std::max( jmax, j+1 );
        }
    }
    return img(
        cv::Range( jmin * img.rows / v, jmax * img.rows / v ),
        cv::Range( imin * img.cols / h, imax * img.cols / h )
    );
}

int main() {
    img = util::in();
    build_clusters();
    dijkstra();
    util::out(best_array( img ));
    return 0;
}
