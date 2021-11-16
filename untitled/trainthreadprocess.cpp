#include "trainthreadprocess.h"
#include "QDebug"
trainthreadProcess::trainthreadProcess(QObject *parent)
{

}
trainthreadProcess::~trainthreadProcess()
{
    //qDebug()<<"kill process";
    //process.kill();
}
void trainthreadProcess::closeTrain()
{
    qDebug()<<"kill process1";
    process.kill();
}
void trainthreadProcess::run()
{
        QString command = ".\\darknet.exe detector train "+this->dirPath+"/data/obj.data "+this->dirPath+"/cfg/yolov4-tiny-trian.cfg "+this->dirPath+"/cfg/yolov4-tiny.conv.29 -map";
        process.start(command);
        emit this->trainDone();
}
void trainthreadProcess::startTrain(QString dirPath)
{
        process.moveToThread(this);
        this->dirPath=dirPath;
        this->start();
}
void trainthreadProcess::stopTrain()
{
        process.kill();
}
