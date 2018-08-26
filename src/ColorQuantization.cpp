/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ColorQuantization.cpp
 * Author: raspi
 * 
 * Created on July 21, 2018, 8:32 PM
 */

#include "ColorQuantization.h"
#include "opencv2/imgproc.hpp"

/* debug includes */
//#include "opencv2/highgui.hpp"
//#include <iostream>

#define BLUR_SIZE 4

namespace Inkstitchy {
ColorQuantization::ColorQuantization(const cv::Mat& src, uint32_t clusters) {
    const int n = src.cols*src.rows;
    cv::blur(src, result, cv::Size(BLUR_SIZE,BLUR_SIZE));
    cv::Mat data = result.reshape( 1, n );
    data.convertTo( data, CV_32F );
    std::vector<int> labels;
    cv::Mat1f colors;
    
    const auto K = static_cast<int>(clusters);
    cv::kmeans(
        data, 
        K, 
        labels, 
        cv::TermCriteria( 
            cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 
            10, 
            1.0), 
        10, 
        cv::KMEANS_PP_CENTERS, 
        colors
    );
    
    /* create masks for palette colors */
    //std::vector<cv::Mat> masks;
    paletteMasks.clear();
    for( int col = 0; col < K; ++col )
    {
        paletteMasks.push_back( cv::Mat::zeros( src.rows, src.cols, CV_8U ) );
    }
    
    for (int i = 0; i < n; ++i)
    {
        data.at<float>(i, 0) = colors(labels[i], 0);
        data.at<float>(i, 1) = colors(labels[i], 1);
        data.at<float>(i, 2) = colors(labels[i], 2);
        
        paletteMasks.at(labels[i]).at<uchar>(i/src.rows,i%src.rows) = 0xFF;
        //std::cout << "(" << (i/src.rows) << "," << (i%src.rows) << ")" << std::endl;
    }

    result = data.reshape(3, src.rows);
    result.convertTo(result, CV_8U);
    colors.copyTo(palette);
}

const cv::Mat& ColorQuantization::getResult() const {
    return result;
}

const cv::Mat1f& ColorQuantization::getPalette() const {
    return palette;
}

const std::vector<cv::Mat>& ColorQuantization::getPaletteMasks() const {
    return paletteMasks;
}
} // end namespace Inkstitchy