#include "imgsender.h"
#include "QDebug"
ImgSender::ImgSender(QObject *parent) : QObject(parent)
{
    this->provider=new ImgProvider;
}
ImgSender::~ImgSender()
{
    delete provider;
    qDebug()<<"delete provider";
}
void ImgSender::setImage(QImage image)
{
    this->provider->img=image;
    emit this->callQmlRefeshImg();
}
