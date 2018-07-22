/* OpenCV includes */
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

/* C++ includes */
#include <iostream>

/* Project includes */
#include "ColorQuantization.h"

/* replace these with useful interface (CLI or GUI) */
#define CQ_NO_CLUSTERS 6

namespace is = Inkstitchy;

int main( int argc, char** argv )
{
    /* Parse input parameters */
    cv::CommandLineParser parser( argc, argv, "{@input | ../data/HappyFish.jpg | input image}" );
    cv::Mat src = imread( parser.get<cv::String>( "@input" ) );
    if( src.empty() )
    {
      std::cout << "Could not open or find the image!\n" << std::endl;
      std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
      return -1;
    }
    
    /* Print out initial image */
    std::string source_window = "Source";
    cv::namedWindow( source_window );
    cv::imshow( source_window, src );
    
    /* Color quantization */
    is::ColorQuantization colorQuantization( src, CQ_NO_CLUSTERS );
    cv::Mat colorReduced = colorQuantization.getResult();
    std::string clustered_window = "Clustered";
    cv::namedWindow( clustered_window );
    cv::imshow( clustered_window, colorReduced );
    
    cv::Mat bgr[3];
    cv::split( colorReduced, bgr );
    
    cv::namedWindow( "Blue" );
    cv::imshow( "Blue", bgr[0] );
    cv::namedWindow( "Green" );
    cv::imshow( "Green", bgr[1] );
    cv::namedWindow( "Red" );
    cv::imshow( "Red", bgr[2] );
    
    cv::waitKey();
    return 0;
}
