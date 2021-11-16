#include "detectthread.h"

detectThread::detectThread(QObject *parent)
{

}
void detectThread::setProjectFolder(QString path)
{
    this->path=path;
    qDebug()<<path;
    std::ifstream classNamesFile((this->path+"/data/obj.names").toStdString());
    if (classNamesFile.is_open())
    {
            std::string className = "";
            while (std::getline(classNamesFile, className))
                classNamesVec.push_back(className);
    }
    cfg_file=this->path+"/cfg/yolov4-tiny-trian.cfg";
    weight_file=this->path+"/backup/yolov4-tiny-trian_last.weights";
    testingPicList=this->getFileNames(this->path+"/data/obj");
    this->start();
}
QString detectThread::s2q(const std::string &s)
{
    return QString( QString::fromLocal8Bit(s.c_str()));
}
void detectThread::run()
{
    qDebug()<<"enter run";
    while(true)
    {
        if(QFile::exists(this->path+"/backup/yolov4-tiny-trian_last.weights")==false)
        {
            msleep(1000);
        }
        else{
            if(QFile::exists(this->path+"/backup/test.weights")==true)
            {
                  QFile::remove(this->path+"/backup/test.weights");
            }
            QFile file(this->path+"/backup/yolov4-tiny-trian_last.weights");
            bool ok = file.rename(this->path+"/backup/test.weights");
            qDebug()<<"change ok"<<ok;
            if(file.exists()==true)
            {
                weight_file=this->path+"/backup/test.weights";
                this->net = readNetFromDarknet(cfg_file.toStdString(), weight_file.toStdString());
                for(int i=0;i<testingPicList.length();i++)
                {
                   cv::Mat mat =cv::imread((this->path+"/data/obj/"+testingPicList[i]).toStdString());
                   QString testlabel=this->getDetect(mat);
                   this->sendTestLabel(i,testlabel);
                }
            }
        }
    }
}
QString  detectThread::getDetect(cv::Mat frame)
{
    objectVector.clear();
    Mat inputBlob = blobFromImage(frame, 1 / 255.F, Size(416, 416), Scalar(), true, false);
    net.setInput(inputBlob, "data");
    Mat detectionMat = net.forward("");
    std::vector<double> layersTimings;
    std::ostringstream ss;
    float confidenceThreshold = 0.2;
    for (int i = 0; i < detectionMat.rows; i++)
    {
        const int probability_index = 5;
        const int probability_size = detectionMat.cols - probability_index;
        float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
        size_t objectClass = std::max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
        float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);
        if (confidence > confidenceThreshold)
        {
                if (objectClass < classNamesVec.size())
                {
                    //String label = String(classNamesVec[objectClass]) + ": " + conf;
                    objData tempdata;
                    tempdata.objclass=objectClass;
                    tempdata.confidence=confidence;
                    objectVector.append(tempdata);
                }
        }
    }
    size_t maxindex=getMaxConfidence();
    return s2q(classNamesVec[maxindex]);
}
bool detectThread::compareOBJ(objData &a, objData &b)
{
    if(a.confidence>b.confidence){
        return true;
    }
    else {
        return false;
    }
}
size_t detectThread::getMaxConfidence()
{
    qSort(objectVector.begin(), objectVector.end(),compareOBJ);
    return objectVector[objectVector.length()-1].objclass;
}
QStringList detectThread::getFileNames(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png"<<"*.jpeg";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;
}
