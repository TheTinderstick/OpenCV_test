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
#include <vector>
#include "opencv2/imgproc.hpp"

/* debug includes */
//#include "opencv2/highgui.hpp"
//#include <iostream>

#define BLUR_SIZE 3

namespace Inkstitchy {
ColorQuantization::ColorQuantization(const cv::Mat& src, uint32_t clusters) {
    const int n = src.cols*src.rows;
    cv::blur(src, result, cv::Size(BLUR_SIZE,BLUR_SIZE));
    cv::Mat data = result.reshape( 1, n );
    data.convertTo( data, CV_32F );
    std::vector<int> labels;
    cv::Mat1f colors;
    
    const int K = static_cast<int>(clusters);
    cv::kmeans(data, K, labels, 
            cv::TermCriteria( cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 10, 1.0), 
            5, cv::KMEANS_PP_CENTERS, colors);
            
    for (int i = 0; i < n; ++i)
    {
        data.at<float>(i, 0) = colors(labels[i], 0);
        data.at<float>(i, 1) = colors(labels[i], 1);
        data.at<float>(i, 2) = colors(labels[i], 2);
    }

    result = data.reshape(3, src.rows);
    result.convertTo(result, CV_8U);
    //cv::imshow("Reduced", result);
}

ColorQuantization::ColorQuantization(const ColorQuantization& orig) {
}

ColorQuantization::~ColorQuantization() {
}

const cv::Mat& ColorQuantization::getResult() const {
    return result;
}

} // namespace