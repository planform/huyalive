#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "imgprocess.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public ImgProcess
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    cv::Mat frame;
    cv::VideoCapture capture;
    QImage image;
    QTimer *timer;
    double rate;    //fps
    cv::VideoWriter writer;
    double alpha;   //控制对比
    int beta;   //控制亮度
    int label;  //药丸数量

private slots:
    void nextFrame();
    void on_pushButton_open_clicked();
    void on_pushButton_camera_clicked();
    void on_pushButton_process_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_end_clicked();
};

#endif // MAINWINDOW_H
