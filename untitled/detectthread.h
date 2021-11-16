#ifndef DETECTTHREAD_H
#define DETECTTHREAD_H

#include <QObject>
#include "opencv2/imgproc/types_c.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <QThread>
#include <QDir>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <qdebug.h>
using namespace cv;
using namespace cv::dnn;
class objData{
     public :
        size_t objclass;
        float confidence;
};
class detectThread : public QThread
{
    Q_OBJECT
public:
    explicit detectThread(QObject *parent = nullptr);
    QString path="";
    QString weight_file = "";
    QString cfg_file = "";
    dnn::Net net;
    QStringList testingPicList;
    QStringList getFileNames(const QString &path);
    std::vector<std::string> classNamesVec;
    void run();
    QString getDetect(cv::Mat frame);
    QVector<objData> objectVector;
    size_t getMaxConfidence();
    static bool compareOBJ(objData &a, objData &b);
    QString s2q(const std::string &s);
public slots:
    void setProjectFolder(QString path);
signals:
    void sendTestLabel(int n,QString mark);
};

#endif // DETECTTHREAD_H
