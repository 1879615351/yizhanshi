#ifndef IMGSENDER_H
#define IMGSENDER_H

#include <QObject>
#include "imgprovider.h"
class ImgSender : public QObject
{
    Q_OBJECT
public:
    explicit ImgSender(QObject *parent = nullptr);
    ~ImgSender();
    ImgProvider *provider;
public slots:
    void setImage(QImage image);//此函数接收CameraCapture的信号并发出刷新视频信号
signals:
    void callQmlRefeshImg();
};

#endif // IMGSENDER_H
