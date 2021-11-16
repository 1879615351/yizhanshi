#ifndef LABELING_H
#define LABELING_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QDir>
#include <QFileInfo>
#include <QPen>
#include <QPainter>
#include <QMap>
#include "labeldata.h"
#include "opencv2/imgproc/types_c.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <QDateTime>
#include <QFileDialog>
#include <classimagedata.h>
#include <QMutex>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace cv;
using namespace cv::dnn;
#define YOLO_CLASS_LINE1 219
#define YOLO_CLASS_LINE2 268
#define YOLO_FILTERS1 213
#define YOLO_FILTERS2 262
class objData2{
     public :
        size_t objclass;
        float confidence;
};
class labeling : public QThread
{
    Q_OBJECT
public:
    explicit labeling(QObject *parent = nullptr);
    ~labeling();
    void run() override;
    QStringList getFileNames(const QString &path);
    void drawFromMap(int n); //依据图片名vector序号
    void drawVideoFromMap(int n);//依据视频帧数
    void drawCameraFromMap(int n);//依据照相顺序
    QString getCurrentTime();
    QImage Mat2QImage(const cv::Mat &mat);
    bool isTraining=false;
    void writeLabelNames();
    void writeLabelData();
    void writeLabelTrainAndTestTxt();
    void writeLabelObjDir();
    void writeTrainLabelCfg(int classnum);
    void copyConvFile();
    void updateAllLabel();
    void showALL(int dir);
    void showClass(int dir);
    void sendLabeledPicLabel(QStringList picnamelist);
    QMap<QString,classImageData>::Iterator classItB;
    QMap<QString,classImageData>::Iterator classItE;
    QMap<QString,classImageData>::Iterator classItTemp;//操作变量
    QVector<QMap<QString,classImageData>> classImageDataVector;//每个索引代表一种类型的数据vector
    QVector<QImage>cameraImage;
    QString exportFolderPath="";
    QDir *exportBackUpFolder=Q_NULLPTR;
    QDir *exportFolder=Q_NULLPTR;
    QDir *exportDataFolder=Q_NULLPTR;
    QDir *exportDataObjFolder=Q_NULLPTR;
    QDir *exportCppFolder=Q_NULLPTR;
    QDir *exportPythonFolder=Q_NULLPTR;
    QDir *exportCfgFolder=Q_NULLPTR;
    qint8 currentMode=0;
    int usingmode=0;
    qint32 currentPictureNum=0;
    QString pictureFloderUrl="";
    QStringList pictureNameList;
    QStringList generateImgNameList;//视频及摄像头标注的图片名字
    QStringList trainingPicList;//正在训练的图片名字
    QString videoFileUrl="";
    QVector<QString> classNameVector;
    QVector<int>  classNum; //索引代表对应的类的索引号，值对应当前类的个数
    int classAllCount=0;  //总标记数
    bool isplayCamera=false;
    bool isUsing=false;
    bool isLabeling=false;
    bool isRunning=false;
    QImage img;
    cv::VideoCapture cap;
    cv::VideoCapture videocap;//处理打开的视频数据
    int showMode=-1;  //显示已经标注的类别的图片
    int currentVideoWidth=1;
    int currentVideoHeight=1;
    int currentVideoFrameCount=0;
    int currentVideoAllFrameCount=0;
    QStringList detectPicNameList;

    int currentDetectPictureNum=0;
    QString detectPictureFloderUrl="";
    int currentDetectVideoFrameCount=0;
    int currentDetectVideoAllFrameCount=0;
    QString detectVideoFloderUrl="";
    QMap<int,labeldata> videolabelMap;//视频帧数对应的数据
    QMap<QString,labeldata> labelMap;   //记录当前图片名字对应的数据
    QMap<int,labeldata> cameraMap;//记录摄像头标注数据
    QString weight_file = "";
    QString cfg_file = "";
    dnn::Net net;
    std::vector<std::string> classNamesVec;
    void getDetect(cv::Mat frame);
    QVector<objData2> objectVector;
    size_t getMaxConfidence();
    static bool compareOBJ(objData2 &a, objData2 &b);
    QString s2q(const std::string &s);
    cv::Mat matTOimge(QImage & mage);
    Q_INVOKABLE void getPictureFloder(qint8 mode,QString pictureFloderUrl);
    Q_INVOKABLE void getVideoFile(qint8 mode,QString vidoeFileUrl);
    Q_INVOKABLE void getCamera();
    Q_INVOKABLE void changePicture(qint8 dir);
    Q_INVOKABLE bool findSameName(QString name);
    Q_INVOKABLE void addClassName(QString name);
    Q_INVOKABLE void addLabelData(int type,float bx,float by,float ex,float ey);
    Q_INVOKABLE void tryReleaseVideo();
    Q_INVOKABLE void tryReleaseCamera();
    Q_INVOKABLE void exportLabelData();
    Q_INVOKABLE void getshowMode(int n);
    Q_INVOKABLE void beginTrain();
    Q_INVOKABLE void stopTrain();
    Q_INVOKABLE void beginUse();
    Q_INVOKABLE void setLabeling();
    Q_INVOKABLE void setDetect(int m,QString dir);
    Q_INVOKABLE void detectChange(int dir);
signals:
    void pictureChangeSignal(QImage img);
    void openModeTypeSignal(int type);
    void setPictureSignal(int pw,int ph);
    void setPicLabel(int type,float bx,float by,float ex,float ey);
    void setPicLabel_None();
    void setLabelPercent(int index,int count,float percent);//根据索引设置当前数目和百分比
    void resetCanvs();
    void setListView(int n);//设置第n个框被选中
    void resetCameraBtn();
    void startProcess(QString dir);
    void sendTrainLabel(QString filepath,QString filename,QString trainText);
    void stopTrainSignal();
    void exportTrainData();
    void setDetectDir(QString dir);
    void sendDetectImage(QImage img);
};

#endif // LABELING_H
