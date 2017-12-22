#ifndef IMGPROCESS_H
#define IMGPROCESS_H

#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImgProcess
{
public:
    ImgProcess();
    QImage Mat2QImage(cv::Mat cvImg);   //用于将cv::Mat 转换为QImage
    void adjustImage(cv::Mat srcImg, cv::Mat dstImg, double alpha, int beta);   //调整图像亮度
    //区域标记的两种算法
    int icvprCcaByTwoPass(const cv::Mat& _binImg, cv::Mat& _lableImg); //two pass
    int icvprCcaBySeedFill(const cv::Mat& _binImg, cv::Mat& _lableImg);    //seed fill
};

#endif // IMGPROCESS_H
