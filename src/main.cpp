/* OpenCV includes */
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

/* potrace includes */
#include "potracelib.h"

/* C++ includes */
#include <iostream>

/* GSL includes */
#include <gsl/gsl>

/* Project includes */
#include "ColorQuantization.h"

/* replace these with useful interface (CLI or GUI) */
#define CQ_NO_CLUSTERS 8

namespace is = Inkstitchy;

static constexpr auto outpath{"./"};
static constexpr auto outext{".bmp"};

int main( int argc, const char* argv[] )
{
    /* Parse input parameters */
    cv::CommandLineParser parser( argc, argv, "{@input | ../data/HappyFish.jpg | input image}" );
    cv::Mat src = imread( parser.get<cv::String>( "@input" ) );
    auto args = gsl::multi_span<const char*>(argv, argc);
    if( src.empty() )
    {
      std::cout << "Could not open or find the image!\n" << std::endl;
      std::cout << "Usage: " << args[0] << " <Input image>" << std::endl;
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
    
    constexpr int stepwidth = 256/CQ_NO_CLUSTERS;
    cv::Mat colorPalette = 
            cv::Mat::zeros(
                32, 
                CQ_NO_CLUSTERS*stepwidth, 
                CV_8UC3                     // NOLINT
            );
    cv::Mat1f palette = colorQuantization.getPalette();   
    for( int i=0; i<CQ_NO_CLUSTERS; ++i )
    {
        const cv::Scalar myColor(palette(i,0), palette(i,1), palette(i,2));
        const cv::Rect myRect( i*stepwidth, 0, stepwidth, 32 );
        std::cout << "Color(" << i << "): " << myColor;
        std::cout << " in rect: " << myRect << std::endl;
        cv::rectangle(
            colorPalette,
            myRect,
            myColor,
            CV_FILLED           
        );
    }
    std::string palette_window = "Color palette";
    cv::namedWindow( palette_window );
    cv::imshow( palette_window, colorPalette );
    
    std::vector<cv::Mat> masks = colorQuantization.getPaletteMasks();
    for( int i=0; i<masks.size(); ++i )
    {
        std::stringstream ss;
        ss << "Masked_" << i; 
        cv::Mat img( colorReduced.size(), colorReduced.type(), cv::Scalar(0) );
        //std::cout << "Size " << src.size << " - " << masks.at(i).size << std::endl;
        colorReduced.copyTo( img, masks.at(i) );
        cv::namedWindow( ss.str() );
        cv::imshow( ss.str(), img );
        std::string filename = outpath + ss.str() + outext;
        std::cout << "Writing file " << filename << std::endl;
        cv::imwrite( filename, masks.at(i) );
    }
    /* Command line call for potrace: 
       ../../potrace/install/bin/potrace -i -t 5 -s -o Masked_0.svg --color=#FF0000 Masked_0.bmp
     */
    potrace_param_t * potrace_params = potrace_param_default();
    potrace_param_free( potrace_params );
    
    cv::waitKey();
    return 0;
}
