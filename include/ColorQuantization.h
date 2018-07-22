/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ColorQuantization.h
 * Author: raspi
 *
 * Created on July 21, 2018, 8:32 PM
 */

#ifndef COLORQUANTIZATION_H
#define COLORQUANTIZATION_H
#include <cstdint>
#include "opencv2/core.hpp"

namespace Inkstitchy {
class ColorQuantization {
public:
    ColorQuantization(const cv::Mat& src, uint32_t clusters);
    ColorQuantization(const ColorQuantization& orig);  
    virtual ~ColorQuantization();
    const cv::Mat& getResult() const;
private:
    cv::Mat result;
};
}
#endif /* COLORQUANTIZATION_H */

