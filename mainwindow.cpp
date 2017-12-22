#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QLCDNumber>

#define CAM_NUM     1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ImgProcess(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rate = 30;
    ui->label->setScaledContents(true); //设置label自适应图片大小
    ui->label_2->setScaledContents(true);
    alpha = 0;
    beta = 0;
    label = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nextFrame()
{
    capture >> frame;
    if (!frame.empty())
    {
        image = ImgProcess::Mat2QImage(frame);
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
}

void MainWindow::on_pushButton_open_clicked()
{
    if (capture.isOpened())
        capture.release(); //if capture is opened , close it
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("open Video file"), ".",
                                                    tr("Video files(*.avi *.mp4 *.flv *.mkv)"));
    capture.open(filename.toLocal8Bit().data());
    if (capture.isOpened())
    {
        rate = capture.get(CV_CAP_PROP_FPS);
        capture >> frame;
        if (!frame.empty())
        {
            image = ImgProcess::Mat2QImage(frame);
            ui->label->setPixmap(QPixmap::fromImage(image));
            timer = new QTimer(this);
            timer->setInterval(1000/rate);
            connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
            timer->start();
        }
    }
}

void MainWindow::on_pushButton_camera_clicked()
{
    if (capture.isOpened())
        capture.release();
    capture.open(CAM_NUM);
    if (capture.isOpened())
    {
        rate = capture.get(CV_CAP_PROP_FPS);
        capture >> frame;
        if (!frame.empty())
        {
            image = ImgProcess::Mat2QImage(frame);
            ui->label->setPixmap(QPixmap::fromImage(image));
            timer = new QTimer(this);
            timer->setInterval(1000/rate);
            connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
            timer->start();
        }
    }
}

void MainWindow::on_pushButton_process_clicked()
{
    cv::Mat tmpImg;
    cv::Mat result;
    cv::Mat labelImg;
    double area;
    int discount = 0;

    alpha = 2.2;
    beta = 50;

    capture >> frame;
    if(!frame.data) return ;
    cv::GaussianBlur(frame, tmpImg, cv::Size(21, 21), 0, 0);
    //ImgProcess::adjustImage(frame, tmpImg, alpha, beta);
    //cv::namedWindow("adjustLight");
    //cv::imshow("adjustLight", tmpImg);
    cv::cvtColor(tmpImg, tmpImg, CV_BGRA2GRAY);
    //创建同原始图像等大小的图像空间
    result.create(tmpImg.rows, tmpImg.cols, CV_8U);
    //tmpImg = ImgProcess::adjustImage(tmpImg, 2.2, 50);

    //二值化
    //CV_THRESH_OTSU参数自动生成阈值，跟第三个参数也就没有关系了。
    //全局固定阈值
    cv::threshold(tmpImg, result, 0, 255,  CV_THRESH_BINARY | CV_THRESH_OTSU);
    //局部自适应阈值
    //cv::adaptiveThreshold(tmpImg, result, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 3, 5);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10));

    //开运算，平滑轮廓，去掉细节，断开缺口
    cv::morphologyEx(result, result, cv::MORPH_OPEN, element);
    //闭运算，平滑轮廓，连接缺口
    cv::morphologyEx(result, result, cv::MORPH_CLOSE, element);
    ui->label_2->setPixmap(QPixmap::fromImage(ImgProcess::Mat2QImage(result)));

    //显示数量
    //label = ImgProcess::icvprCcaByTwoPass(result, labelImg);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(result, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    QString tmp;
    for (int i=0; i<contours.size(); i++)
    {
        area = cv::contourArea(contours[i]);
        if (area > 15000.00 || area < 2)
            discount++;
        //tmp.sprintf("%f", area);
        //ui->textBrowser->setText(tmp);
    }

    label = contours.size() - discount;
    ui->lcdNumber->display(label);



    /**/
    cv::Mat cannyImg;    
    cv::Canny(result, cannyImg, 0, 30, 3);
    cv::namedWindow("Canny");
    cv::imshow("Canny", cannyImg);

}

void MainWindow::on_pushButton_start_clicked()
{
    writer.open("./myrec.avi", cv::VideoWriter::fourcc('P', 'I', 'M', '1'), 30,
                cv::Size(frame.cols, frame.rows), true);
    int t = 100;
    while(t--)
        writer.write(frame);
    ui->pushButton_start->setDisabled(true);
}

void MainWindow::on_pushButton_end_clicked()
{
    writer.release();
}
