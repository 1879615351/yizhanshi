#include "labeling.h"
#include "QDebug"
#define pic_dir_up 1
#define pic_dir_down 0
QMutex m_mtx;
labeling::labeling(QObject *parent)
{
     exportFolder=new QDir();
     exportDataFolder=new QDir();
     exportDataObjFolder=new QDir();
     exportCppFolder=new QDir();
     exportPythonFolder=new QDir();
     exportBackUpFolder=new QDir();
     exportCfgFolder=new QDir();
}
labeling::~labeling()
{
    if(exportFolder!=nullptr)
    {
        delete exportFolder;
    }
    if(exportDataFolder!=nullptr)
    {
        delete exportDataFolder;
    }
    if(exportCppFolder!=nullptr)
    {
        delete exportCppFolder;
    }
    if(exportPythonFolder!=nullptr)
    {
        delete exportPythonFolder;
    }
    if(exportDataObjFolder!=nullptr)
    {
        delete exportDataObjFolder;
    }
    if(exportBackUpFolder!=nullptr)
    {
        delete exportBackUpFolder;
    }
    if(exportCfgFolder!=nullptr)
    {
        delete exportCfgFolder;
    }
}
void labeling::updateAllLabel()
{
    emit this->setLabelPercent(-1,classAllCount,1);  //设置总数
    for(int i=0;i<this->classNum.length();i++)
    {
        emit this->setLabelPercent(i,this->classNum[i],this->classNum[i]*1.0/classAllCount);
    }
}
void labeling::getshowMode(int n)
{
    //qDebug()<<"in>>"<<n;
    this->showMode=n;
    if(n==-1)
    {
       if(currentMode==1)
       {
            if(this->pictureFloderUrl!="")
            {
                this->img=QImage(this->pictureFloderUrl+"/"+this->pictureNameList[this->currentPictureNum]);
                emit this->pictureChangeSignal(this->img);
                emit this->openModeTypeSignal(1);
                emit this->resetCanvs();
                this->drawFromMap(this->currentPictureNum);
            }
       }
       else if(currentMode==2)
       {
           if(this->videocap.isOpened())
               this->videocap.release();
           if(this->videoFileUrl!="")
           {
                this->videocap.open(this->videoFileUrl.toStdString());
                this->videocap.set(cv::CAP_PROP_POS_FRAMES, this->currentVideoFrameCount);//从此时的帧数开始获取帧
                cv::Mat mat;
                this->videocap>>mat;
                this->img=this->Mat2QImage(mat);
                emit this->pictureChangeSignal(this->img);
           }
       }
       else if(currentMode==3)
       {
           this->tryReleaseCamera();
           if(this->cap.isOpened()==false)
               this->cap.open(0);
       }
    }
    else
    {
        if(this->classImageDataVector.length()<(n+1))
        {
            this->classImageDataVector.resize(n+1);
            //qDebug()<<this->classImageDataVector[n].count();
        }
        //qDebug()<<this->classImageDataVector[n].count();
        //qDebug()<<"n  "<<n;
        if(this->classImageDataVector[n].count()!=0)
        {
            //qDebug()<<"count "<<this->classImageDataVector[n].count();
            classItB=(this->classImageDataVector[n]).begin();
            //qDebug()<<"begin";
            classItE=(this->classImageDataVector[n]).end();
            //qDebug()<<"end";
            classItTemp=(this->classImageDataVector[n]).begin();
            //qDebug()<<"begin 2";
            this->img=classItB.value().img;
            //qDebug()<<"img";
            emit this->pictureChangeSignal(this->img);
            //qDebug()<<"emit";
            if(classItB.value().mode==1)
            {
                this->drawFromMap(classItB.value().n);
            }
            else if(classItB.value().mode==2)
            {
                this->drawVideoFromMap(classItB.value().n);
            }
            else if(classItB.value().mode==3)
            {
                this->drawCameraFromMap(classItB.value().n);
            }
        }
        else {
            this->showMode=-1;
        }
    }
}
void labeling::addLabelData(int type,float bx,float by,float ex,float ey)
{
 if(this->showMode==-1)
 {
    if(type==-1||bx==ex||by==ey)
    {
        return;    //没有标记
    }
    bx=bx*(this->img.width()*1.0/1200);
    by=by*(this->img.height()*1.0/800);
    ex=ex*(this->img.width()*1.0/1200);
    ey=ey*(this->img.height()*1.0/800);
    float mid_x=qAbs((bx+ex)/2);
    float mid_y=qAbs((by+ey)/2);
    float width=qAbs(ex-bx);
    float height=qAbs(ey-by);
    labeldata tempdata;
    tempdata.type=type;
    tempdata.x_center=mid_x;
    tempdata.y_center=mid_y;
    tempdata.width=width;
    tempdata.height=height;
    tempdata.img=this->img;
    classImageData tempclass;
    tempclass.img=this->img;
    tempclass.mode=this->currentMode;
    tempclass.type=type;
    if(this->currentMode==1)
    {
        labeldata testdata=this->labelMap.value(this->pictureNameList[currentPictureNum]);
        if(testdata.type==-1)  //之前没插入过
        {
            classAllCount++;

            if(type>(this->classNum.length()-1))
            {
                this->classNum.resize(type+1);
                classImageDataVector.resize(type+1);
                tempclass.n=currentPictureNum;
                classImageDataVector[type].insert("P"+QString::number(currentPictureNum),tempclass);
                this->classNum[type]++;
            }
            else{
                tempclass.n=currentPictureNum;
                classImageDataVector[type].insert("P"+QString::number(currentPictureNum),tempclass);
                this->classNum[type]++;
            }
            this->updateAllLabel();
             //emit this->setLabelPercent(type,this->classNum[type],this->classNum[type]*1.0/classAllCount);
        }
        else{
            int old_type=testdata.type;
            if(old_type!=type)
            {
                tempclass.n=currentPictureNum;
                classImageDataVector[old_type].remove("P"+QString::number(currentPictureNum));
                this->classNum[old_type]--;
                this->classNum[type]++;
                classImageDataVector[type].insert("P"+QString::number(currentPictureNum),tempclass);
                this->updateAllLabel();
            }
            else{
                 tempclass.n=currentPictureNum;
                 classImageDataVector[type].insert("P"+QString::number(currentPictureNum),tempclass);
            }
            //qDebug()<<"remove "<<classImageDataVector[old_type].remove("P"+QString::number(currentPictureNum));
            //this->classNum[old_type]--;
            //emit this->setLabelPercent(old_type,this->classNum[old_type],this->classNum[old_type]*1.0/classAllCount);
            //this->classNum[type]++;
            //classImageDataVector[type].insert("P"+QString::number(currentPictureNum),tempclass);
            //emit this->setLabelPercent(type,this->classNum[type],this->classNum[type]*1.0/classAllCount);
            this->updateAllLabel();
        }
            this->labelMap.insert(this->pictureNameList[currentPictureNum],tempdata);
            //for(int i=0;i<classImageDataVector.length();i++)
            //{
            //    for(int j=0;j<classImageDataVector[i].count();j++)
            //    {
             //       qDebug()<<classImageDataVector[i].value("P"+QString::number(currentPictureNum)).n;
             //   }
           // }
    }
    else if(this->currentMode==2)
    {
        labeldata testdata=this->videolabelMap.value(this->currentVideoFrameCount);
        if(testdata.type==-1)  //之前没插入过
        {
            classAllCount++;
            //emit this->setLabelPercent(-1,classAllCount,1);  //设置总数
            if(type>(this->classNum.length()-1))
            {
                classImageDataVector.resize(type+1);
                tempclass.n=currentVideoFrameCount;
                classImageDataVector[type].insert("V"+QString::number(currentVideoFrameCount),tempclass);
                this->classNum.resize(type+1);
                qDebug()<<this->classNum.length();
                this->classNum[type]++;
            }
            else{
                tempclass.n=currentVideoFrameCount;
                classImageDataVector[type].insert("V"+QString::number(currentVideoFrameCount),tempclass);
                this->classNum[type]++;
            }
            this->updateAllLabel();
            //emit this->setLabelPercent(type,this->classNum[type],this->classNum[type]*1.0/classAllCount);
        }
        else{
            int old_type=testdata.type;
            if(old_type!=type)
            {
                tempclass.n=currentVideoFrameCount;
                classImageDataVector[old_type].remove("V"+QString::number(currentVideoFrameCount));
                classImageDataVector[type].insert("V"+QString::number(currentVideoFrameCount),tempclass);
                this->updateAllLabel();
                this->classNum[old_type]--;
                this->classNum[type]++;
            }
            else
            {
                tempclass.n=currentVideoFrameCount;
                classImageDataVector[type].insert("V"+QString::number(currentVideoFrameCount),tempclass);
            }
            this->updateAllLabel();
            //emit this->setLabelPercent(old_type,this->classNum[old_type],this->classNum[old_type]*1.0/classAllCount);
            //emit this->setLabelPercent(type,this->classNum[type],this->classNum[type]*1.0/classAllCount);
        }
        this->videolabelMap.insert(this->currentVideoFrameCount,tempdata);
    }
    else if(this->currentMode==3)  //视频每次插入都加
    {
        //tempdata.img=this->img;
        this->cameraImage.append(this->img);
        //QString time=this->getCurrentTime();
        //QString name="camera_"+time;
        this->cameraMap.insert(this->cameraImage.length(),tempdata);
        classAllCount++;
        //emit this->setLabelPercent(-1,classAllCount,1);  //设置总数
        if(type>(this->classNum.length()-1))
        {
            this->classNum.resize(type+1);
            classImageDataVector.resize(type+1);
            this->classNum[type]++;
        }
        else{
            this->classNum[type]++;
        }
        tempclass.n=this->cameraImage.length();
        classImageDataVector[type].insert("C"+QString::number(this->cameraImage.length()),tempclass);
        this->updateAllLabel();
        //emit this->setLabelPercent(type,this->classNum[type],this->classNum[type]*1.0/classAllCount);
    }
 }
}
bool labeling::findSameName(QString name)
{
    if(this->classNameVector.contains(name))
    {
        return true;
    }
    else
    {
        return  false;
    }
}
void labeling::addClassName(QString name)
{
    this->classNameVector.append(name);
    //qDebug()<<classNameVector;
}
QStringList labeling::getFileNames(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png"<<"*.jpeg";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;
}
void labeling::run()
{
    isRunning=true;
    while(true)
    {
        if(this->isplayCamera)
        {
            if(this->cap.isOpened())
            {
                cv::Mat mat;
                cap>>mat;
                if(isUsing==true&&usingmode==3)
                {
                    this->getDetect(mat);
                    emit this->sendDetectImage(this->img);
                }
                else if(isUsing==false)
                {
                    this->img=this->Mat2QImage(mat);
                    emit this->pictureChangeSignal(this->img);
                }
                cv::waitKey(1);
            }
        }
        else{
            msleep(1000);
        }
    }
    this->img=QImage();
    emit this->pictureChangeSignal(this->img);
}
void labeling::drawFromMap(int n)
{
    labeldata tempdata=this->labelMap.value(this->pictureNameList[n]);
    if(tempdata.type!=-1)  //标签存在
    {
        int type=tempdata.type;
        float mid_x=tempdata.x_center;
        float mid_y=tempdata.y_center;
        float width=tempdata.width;
        float height=tempdata.height;
        float begin_x=mid_x-width/2;
        float begin_y=mid_y-height/2;
        float end_x=mid_x+width/2;
        float end_y=mid_y+height/2;
        emit this->setPicLabel(type,begin_x/(this->img.width()*1.0/1200),begin_y/(this->img.height()*1.0/800),end_x/(this->img.width()*1.0/1200),end_y/((this->img.height()*1.0/800)));
       // qDebug()<<type;
    }
    else {
        //qDebug()<<"None";
        emit setPicLabel_None();
    }
}
void labeling::drawVideoFromMap(int n)
{
    labeldata tempdata=this->videolabelMap.value(n);//从帧数
    if(tempdata.type!=-1)  //标签存在
    {
        int type=tempdata.type;
        float mid_x=tempdata.x_center;
        float mid_y=tempdata.y_center;
        float width=tempdata.width;
        float height=tempdata.height;
        float begin_x=mid_x-width/2;
        float begin_y=mid_y-height/2;
        float end_x=mid_x+width/2;
        float end_y=mid_y+height/2;
        emit this->setPicLabel(type,begin_x/(this->img.width()*1.0/1200),begin_y/(this->img.height()*1.0/800),end_x/(this->img.width()*1.0/1200),end_y/((this->img.height()*1.0/800)));
        qDebug()<<type;
    }
    else {
        qDebug()<<"None";
        emit setPicLabel_None();
    }
}
void labeling::drawCameraFromMap(int n)
{
    labeldata tempdata=this->cameraMap.value(n);//从帧数
    if(tempdata.type!=-1)  //标签存在
    {
        int type=tempdata.type;
        float mid_x=tempdata.x_center;
        float mid_y=tempdata.y_center;
        float width=tempdata.width;
        float height=tempdata.height;
        float begin_x=mid_x-width/2;
        float begin_y=mid_y-height/2;
        float end_x=mid_x+width/2;
        float end_y=mid_y+height/2;
        emit this->setPicLabel(type,begin_x/(this->img.width()*1.0/1200),begin_y/(this->img.height()*1.0/800),end_x/(this->img.width()*1.0/1200),end_y/((this->img.height()*1.0/800)));
        qDebug()<<type;
    }
    else {
        qDebug()<<"None";
        emit setPicLabel_None();
    }
}
void labeling::showALL(int dir)
{
    if(this->currentMode==1)   //照片
    {
         if(dir ==pic_dir_down){
            if((this->currentPictureNum-1)>=0)
            {
                this->currentPictureNum--;
            }
         }
         else if(dir==pic_dir_up) {
         if((this->currentPictureNum+1)<this->pictureNameList.length())
         {
                this->currentPictureNum++;
         }
    }
    this->img=QImage(this->pictureFloderUrl+"/"+this->pictureNameList[this->currentPictureNum]);
    this->drawFromMap(this->currentPictureNum);
    emit this->setPictureSignal(this->img.width(),this->img.height());
    emit this->pictureChangeSignal(this->img);
    }
    else if(this->currentMode==2)  //视频
    {
        if(this->cap.isOpened())
        {
            if(dir ==pic_dir_down){
                if(this->currentVideoFrameCount-1>=1)
                {
                    this->currentVideoFrameCount--;
                    this->cap.set(cv::CAP_PROP_POS_FRAMES, this->currentVideoFrameCount);//从此时的帧数开始获取帧
                    cv::Mat mat;
                    this->cap>>mat;
                    this->img=this->Mat2QImage(mat);
                    emit this->pictureChangeSignal(this->img);
                }
            }
            else if(dir==pic_dir_up)
            {
                 if(this->currentVideoFrameCount+1<=this->currentVideoAllFrameCount)
                 {
                     this->currentVideoFrameCount++;
                     this->cap.set(cv::CAP_PROP_POS_FRAMES, this->currentVideoFrameCount);//从此时的帧数开始获取帧
                     cv::Mat mat;
                     this->cap>>mat;
                     this->img=this->Mat2QImage(mat);
                     emit this->pictureChangeSignal(this->img);
                 }
            }
            this->drawVideoFromMap(this->currentVideoFrameCount);
        }
    }
}
void labeling::showClass(int dir)
{
    if(dir==0&&classItTemp!=classItB)
    {
        classItTemp--;
    }
    else if(dir==1&&classItTemp!=classItE-1)
    {
        classItTemp++;
    }
    classImageData tempcalssdata=classItTemp.value();
    this->img=tempcalssdata.img;
    if(tempcalssdata.mode==1)  //当前图片为图片
    {
        //this->resetCanvs();
        //this->drawFromMap(tempcalssdata.n);
        qDebug()<<"n  " <<tempcalssdata.n;
        //this->resetCanvs();
        this->drawFromMap(tempcalssdata.n);
    }
    else if(tempcalssdata.mode==2)//当前图片为视频图片
    {
        this->drawVideoFromMap(tempcalssdata.n);
    }
    else if(tempcalssdata.mode==3)//当前图片为视频camera照片
    {
        this->drawCameraFromMap(tempcalssdata.n);
    }
    this->img=tempcalssdata.img;
    emit this->pictureChangeSignal(this->img);
}
void labeling::changePicture(qint8 dir)
{
    if(this->showMode==-1)
    {
        if(this->currentMode!=3)
        {
            showALL(dir);
        }
    }
    else
    {
        showClass(dir);
    }
}
void labeling::getPictureFloder(qint8 mode,QString pictureFloderUrl)
{
      this->currentPictureNum=0;
      this->showMode=-1;
      emit this->setListView(0); //选中显示全部图片
      this->tryReleaseCamera();
      this->currentMode = mode;
      this->pictureFloderUrl = pictureFloderUrl.split("file:///")[1];
      this->pictureNameList = this->getFileNames(this->pictureFloderUrl);
      if(this->pictureNameList.length()!=0)
      {
          this->img=QImage(this->pictureFloderUrl+"/"+this->pictureNameList[this->currentPictureNum]);
          emit this->setPictureSignal(this->img.width(),this->img.height());
          emit this->pictureChangeSignal(this->img);
          emit this->openModeTypeSignal(1);
          emit this->resetCanvs();
          this->drawFromMap(this->currentPictureNum);
      }
      else {
          this->currentPictureNum=0;
      }
      qDebug()<<this->pictureFloderUrl;
}
void labeling::getVideoFile(qint8 mode,QString vidoeFileUrl)
{
    this->currentVideoFrameCount=0;
    this->showMode=-1;
    emit this->setListView(0); //选中显示全部图片
    this->tryReleaseCamera();
    this->currentMode=mode;
    this->videoFileUrl=vidoeFileUrl.split("file:///")[1];
    this->cap.open(this->videoFileUrl.toStdString());
    if(this->cap.isOpened())
    {
        this->currentVideoWidth=this->cap.get(cv::CAP_PROP_FRAME_WIDTH);
        this->currentVideoHeight=this->cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        this->currentVideoAllFrameCount=this->cap.get(cv::CAP_PROP_FRAME_COUNT);
        cv::Mat mat;
        this->cap>>mat;
        this->img=this->Mat2QImage(mat);
        emit this->pictureChangeSignal(this->img);
        emit this->openModeTypeSignal(2);
        emit this->resetCanvs();
        this->currentVideoFrameCount++;
        this->drawVideoFromMap(this->currentVideoFrameCount);
    }
}
void labeling::getCamera()
{
    this->tryReleaseCamera();
    this->showMode=-1;
    emit this->setListView(0); //选中显示全部图片
    if(this->cap.isOpened()==false)
    {
        this->cap.open(0);//打开摄像头
        this->isplayCamera=true;
        this->start();
        this->currentMode=3;
        emit this->openModeTypeSignal(3);
    }
}
QImage labeling::Mat2QImage(const cv::Mat &mat)
{
    if (mat.type() == CV_8UC1) {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        image.setColorCount(256);
        for (int i = 0; i < 256; i++) {
            image.setColor(i, qRgb(i, i, i));
        }
        uchar *pSrc = mat.data;
        for (int row = 0; row < mat.rows; row++) {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, static_cast<quint32>(mat.cols) );
            pSrc += static_cast<quint32>(mat.step);
        }
        return image;
    } else if (mat.type() == CV_8UC3) {
        const uchar *pSrc = const_cast<const uchar *>(mat.data);
        QImage image(pSrc, mat.cols, mat.rows,
                     static_cast<qint32>(mat.step), QImage::Format_RGB888);
        return image.rgbSwapped();
    } else if (mat.type() == CV_8UC4) {
        const uchar *pSrc = const_cast<const uchar *>(mat.data);
        QImage image(pSrc, mat.cols, mat.rows,
                     static_cast<qint32>(mat.step), QImage::Format_ARGB32);
        return image.copy();
    } else if (mat.type() == 22) {
        cv::Mat src;
        mat.convertTo(src, CV_8UC3);
        const uchar *pSrc = const_cast<const uchar *>(src.data);
        QImage image(pSrc, src.cols, src.rows,
                     static_cast<qint32>(src.step), QImage::Format_RGB888);
        return image.rgbSwapped();
    } else {
        return QImage();
    }
}
void labeling::tryReleaseVideo()
{
    if(this->videocap.isOpened())
    {
        this->videocap.release();
    }
}
void labeling::tryReleaseCamera()
{
    if(this->cap.isOpened())
    {
        this->cap.release();
        this->isplayCamera=false;
        this->img=QImage();
        emit this->pictureChangeSignal(this->img);
        emit resetCameraBtn();
    }
}
QString labeling::getCurrentTime()
{
    QDateTime timeCurrent = QDateTime::currentDateTime();
    QString time = timeCurrent.toString("yyyy-MM-dd hh-mm-ss");
    QTime time1;
    time1= QTime::currentTime();
    qsrand(time1.msec()+time1.second()*1000);
    return time+QString::number(qrand()%1000);
}
void labeling::exportLabelData()
{
    this->exportFolderPath=QFileDialog::getSaveFileName();//得到新建文件夹路径
    if(this->exportFolderPath!="")
    {
       this->exportFolder->mkdir(this->exportFolderPath);  //在选择路径下创建工程文件夹
       this->exportDataFolder->mkdir(this->exportFolderPath+"/data");
       this->exportBackUpFolder->mkdir(this->exportFolderPath+"/backup");
       this->exportDataObjFolder->mkdir(this->exportFolderPath+"/data/obj");
       this->exportCfgFolder->mkdir(this->exportFolderPath+"/cfg");
       qDebug()<<"export mkdir";
       this->writeLabelNames();
       qDebug()<<"export names";
       this->writeLabelData();
       qDebug()<<"export data";
       this->writeLabelObjDir();
       qDebug()<<"export obj";
       this->writeLabelTrainAndTestTxt();
       qDebug()<<"export train test";
       this->writeTrainLabelCfg(this->classNameVector.length());
       this->copyConvFile();
       qDebug()<<"export conv";
       emit this->exportTrainData();
    }
}
void labeling::writeLabelNames()
{
    QFile File(this->exportFolderPath+"/data/obj.names");
    File.open(QIODevice::ReadWrite);
    File.close();
    File.open(QIODevice::ReadWrite | QIODevice::Append);
    foreach(QString namestr,this->classNameVector)
    {
            File. write((namestr+"\n").toUtf8());
    }
    File.close();
}
void labeling::writeLabelData()
{
    QFile File(this->exportFolderPath+"/data/obj.data");
    File.open(QIODevice::ReadWrite);
    File.close();
    File.open(QIODevice::ReadWrite | QIODevice::Append);
    //写总类别数
    File.write(("classes = "+QString::number(this->classNameVector.length())+"\n").toUtf8());
    File.write(("train  = "+this->exportFolderPath+"/data/train.txt"+"\n").toUtf8());
    File.write(("valid  = "+this->exportFolderPath+"/data/test.txt"+"\n").toUtf8());
    File.write(("names  = "+this->exportFolderPath+"/data/obj.names"+"\n").toUtf8());
    File.write(("backup = "+this->exportFolderPath+"/backup/").toUtf8());
    File.close();
}
void labeling::writeLabelTrainAndTestTxt()
{
    QMap<QString,labeldata>::Iterator it = this->labelMap.begin();
    QStringList templist1;
    while(it!=this->labelMap.end())
    {
            templist1.append(it.key());
            it++;
    }
    QStringList templist2=this->generateImgNameList;
    std::random_shuffle(templist1.begin(), templist1.end());//随机打散
    std::random_shuffle(templist2.begin(), templist2.end());//随机打散
    QFile file(this->exportFolderPath+"/data/train.txt");
    file.open(QIODevice::ReadWrite);
    file.close();
    QFile file1(this->exportFolderPath+"/data/test.txt");
    file1.open(QIODevice::ReadWrite);
    file1.close();
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    file1.open(QIODevice::ReadWrite | QIODevice::Append);
    for(int i=0;i<templist1.length();i++)
    {
        if((i<templist1.length()/4+1))
        {
            file1.write((this->exportFolderPath+"/data/obj/"+templist1[i]+"\n").toUtf8());  //写测试
        }
        else{
            file.write((this->exportFolderPath+"/data/obj/"+templist1[i]+"\n").toUtf8());   //写训练
        }
    }
    for(int i=0;i<templist2.length();i++)
    {
        if((i<templist2.length()/4+1))
        {
            file1.write((templist2[i]+"\n").toUtf8());  //写测试
        }
        else{
            file.write((templist2[i]+"\n").toUtf8());   //写训练
        }
    }
    file1.close();
    file.close();
}
void labeling::writeLabelObjDir()
{
    //遍历图片标注，将标注的图片插入到obj目录中
    QMap<QString,labeldata>::Iterator it = this->labelMap.begin();
    while(it!=this->labelMap.end())
    {
          QString allPicPath=this->pictureFloderUrl+"/"+it.key();
          labeldata tempdata=it.value();
          QString classNum=QString::number(tempdata.type);
          QString x_center=QString::number(tempdata.x_center*1.0/tempdata.img.width());
          QString y_center=QString::number(tempdata.y_center*1.0/tempdata.img.height());
          QString width=QString::number(tempdata.width*1.0/tempdata.img.width());
          QString height=QString::number(tempdata.height*1.0/tempdata.img.height());
          QFile::copy(allPicPath,this->exportFolderPath+"/data/obj/"+it.key());
          QFile file(this->exportFolderPath+"/data/obj/"+it.key().split(".")[0]+".txt");
          file.open(QIODevice::ReadWrite);
          file.close();
          file.open(QIODevice::ReadWrite | QIODevice::Append);
          file.write((classNum+" "+x_center+" "+y_center+" "+width+" "+height).toUtf8());
          file.close();
          it++;
    }
    if(this->videoFileUrl!="")
    {
        QMap<int,labeldata>::Iterator it1 = this->videolabelMap.begin();
        this->videocap.open(this->videoFileUrl.toStdString());
        QFileInfo info = QFileInfo(this->videoFileUrl);
        QString videoFileName = info.fileName().split(".")[0];
        if(this->videocap.isOpened())
        {
            while(it1!=this->videolabelMap.end())
            {
                labeldata tempdata=it1.value();
                QString classNum=QString::number(tempdata.type);
                QString x_center=QString::number(tempdata.x_center*1.0/tempdata.img.width());
                QString y_center=QString::number(tempdata.y_center*1.0/tempdata.img.height());
                QString width=QString::number(tempdata.width*1.0/tempdata.img.width());
                QString height=QString::number(tempdata.height*1.0/tempdata.img.height());
                QString imgname=this->exportFolderPath+"/data/obj/"+"video"+videoFileName+this->getCurrentTime()+".png";
                this->generateImgNameList.append(imgname);
                tempdata.img.save(imgname);
                QFile file(imgname.split(".")[0]+".txt");
                file.open(QIODevice::ReadWrite);
                file.close();
                file.open(QIODevice::ReadWrite | QIODevice::Append);
                file.write((classNum+" "+x_center+" "+y_center+" "+width+" "+height).toUtf8());
                file.close();
                it1++;
            }
            this->videocap.release();
        }
    }
    QMap<int,labeldata>::Iterator it2 = this->cameraMap.begin();
    while(it2!=this->cameraMap.end())
    {
        QString time=this->getCurrentTime();
        QString name="camera_"+time;
        QString imgname=this->exportFolderPath+"/data/obj/"+name+".png";
        this->generateImgNameList.append(imgname);
        labeldata tempdata=it2.value();
        QString classNum=QString::number(tempdata.type);
        QString x_center=QString::number(tempdata.x_center*1.0/tempdata.img.width());
        QString y_center=QString::number(tempdata.y_center*1.0/tempdata.img.height());
        QString width=QString::number(tempdata.width*1.0/tempdata.img.width());
        QString height=QString::number(tempdata.height*1.0/tempdata.img.height());
        tempdata.img.save(imgname);
        QFile file(this->exportFolderPath+"/data/obj/"+name+".txt");
        file.open(QIODevice::ReadWrite);
        file.close();
        file.open(QIODevice::ReadWrite | QIODevice::Append);
        file.write((classNum+" "+x_center+" "+y_center+" "+width+" "+height).toUtf8());
        file.close();
        it2++;
    }
}
void labeling::writeTrainLabelCfg(int classnum)
{
    QFile cfgback("./yolov4-tiny-trian.cfg");
    //QFile cfgtrain("./test.cfg");
    QFile cfgtrain(this->exportFolderPath+"/cfg/yolov4-tiny-trian.cfg");
    cfgtrain.open(QIODevice::ReadWrite);
    cfgtrain.close();
    cfgtrain.open(QIODevice::ReadWrite);
    cfgtrain.write("");
    cfgtrain.close();
    cfgtrain.open(QIODevice::ReadWrite | QIODevice::Append);
    QString text="";
    cfgback.open(QIODevice::ReadOnly | QIODevice::Text);
    QString line;
    QTextStream in(&cfgback);  //用文件构造流
    line = in.readLine();//读取一行放到字符串里
    int currentLine=0;
    qDebug() << line;
    QString classtext="classes="+QString::number(classnum)+"\n";
    //QString classtext="classes="+QString::number(this->classNameVector.length())+"\n";
    //QString filterstext="filters="+QString::number((this->classNameVector.length()+5)*3)+"\n";
    QString filterstext="filters="+QString::number((classnum+5)*3)+"\n";
    while(!line.isNull())//字符串有内容
    {
            currentLine++;
            if((currentLine==YOLO_FILTERS1)||(currentLine==YOLO_FILTERS2))
            {
                cfgtrain.write(filterstext.toUtf8());
            }
            else if((currentLine==YOLO_CLASS_LINE1)||(currentLine==YOLO_CLASS_LINE2))
            {
                cfgtrain.write(classtext.toUtf8());
            }
            else{
                cfgtrain.write((line+"\n").toUtf8());
            }
            line=in.readLine();//循环读取下行
            //qDebug() << line;
    }
    cfgback.close();
    cfgtrain.close();
    qDebug()<<currentLine;
}
void labeling::copyConvFile()
{
    QFile::copy("./yolov4-tiny.conv.29",this->exportFolderPath+"/cfg/"+"yolov4-tiny.conv.29");
}
void labeling::sendLabeledPicLabel(QStringList picnamelist)
{
   for(int i=0;i<picnamelist.length();i++)
   {
        QFile file(this->exportFolderPath+"/data/obj/"+picnamelist[i].split(".")[0]+".txt");
        file.open(QIODevice::ReadOnly);
        int labelnum=file.readAll()[0]-'0';
        file.close();
        emit this->sendTrainLabel(this->exportFolderPath+"/data/obj/"+picnamelist[i],picnamelist[i],this->classNameVector[labelnum]);
   }
}
void labeling::beginTrain()
{
    if(this->exportFolderPath!=""&&isTraining==false)
    {
        emit this->startProcess(this->exportFolderPath);
        isTraining=true;
        trainingPicList=this->getFileNames(this->exportFolderPath+"/data/obj");
        sendLabeledPicLabel(trainingPicList);
        emit setDetectDir(this->exportFolderPath);
    }
}
void labeling::stopTrain()
{
    if(isTraining==true)
    {
        emit this->stopTrainSignal();
    }
}
void labeling::getDetect(cv::Mat frame)
{
    if(QFile::exists(weight_file)==false)
    {
        this->img=this->Mat2QImage(frame);
        return ;
    }
    else{
        this->net = readNetFromDarknet(cfg_file.toStdString(), weight_file.toStdString());
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
            float x = detectionMat.at<float>(i, 0);
            float y = detectionMat.at<float>(i, 1);
            float width = detectionMat.at<float>(i, 2);
            float height = detectionMat.at<float>(i, 3);
            int xLeftBottom = static_cast<int>((x - width / 2) * frame.cols);
            int yLeftBottom = static_cast<int>((y - height / 2) * frame.rows);
            int xRightTop = static_cast<int>((x + width / 2) * frame.cols);
            int yRightTop = static_cast<int>((y + height / 2) * frame.rows);
            Rect object(xLeftBottom, yLeftBottom,
                xRightTop - xLeftBottom,
                yRightTop - yLeftBottom);
            rectangle(frame, object, Scalar(0, 0, 255), 2, 8);
            if (objectClass < classNamesVec.size())
            {
                ss.str("");
                ss << confidence;
                String conf(ss.str());
                String label = String(classNamesVec[objectClass]) + ": " + conf;
                int baseLine = 0;
                Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                rectangle(frame, Rect(Point(xLeftBottom, yLeftBottom),
                    Size(labelSize.width, labelSize.height + baseLine)),
                    Scalar(255, 255, 255), cv::FILLED);
                putText(frame, label, Point(xLeftBottom, yLeftBottom + labelSize.height),
                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
            }
        }
    }
        this->img=this->Mat2QImage(frame);
    }
}
bool labeling::compareOBJ(objData2 &a, objData2 &b)
{
    if(a.confidence>b.confidence){
        return true;
    }
    else {
        return false;
    }
}
size_t labeling::getMaxConfidence()
{
    qSort(objectVector.begin(), objectVector.end(),compareOBJ);
    return objectVector[objectVector.length()-1].objclass;
}
void labeling::beginUse(){
    this->isUsing=true;
    std::ifstream classNamesFile((this->exportFolderPath+"/data/obj.names").toStdString());
    if (classNamesFile.is_open())
    {
            std::string className = "";
            while (std::getline(classNamesFile, className))
                classNamesVec.push_back(className);
    }
    cfg_file=this->exportFolderPath+"/cfg/yolov4-tiny-trian.cfg";
    weight_file=this->exportFolderPath+"/backup/yolov4-tiny-trian_best.weights";
}
QString labeling::s2q(const std::string &s)
{
    return QString( QString::fromLocal8Bit(s.c_str()));
}
void labeling::setLabeling()
{
    this->isLabeling=true;
    this->isUsing=false;
}
void labeling::detectChange(int dir)
{

}
void labeling::setDetect(int m,QString dir)
{
     this->usingmode=m;
     if(this->usingmode==1)
     {
         this->detectPictureFloderUrl = dir.split("file:///")[1];
         this->detectPicNameList = this->getFileNames(this->detectPictureFloderUrl);
         if(this->detectPicNameList.length()!=0)
         {
             this->img=QImage(this->detectPictureFloderUrl+"/"+this->detectPicNameList[this->currentDetectPictureNum]);
             //emit this->setPictureSignal(this->img.width(),this->img.height());
             getDetect(matTOimge(this->img));
             emit this->sendDetectImage(this->img);
             emit this->resetCanvs();
         }
         else {
             this->currentDetectPictureNum=0;
         }
     }
     else if(this->usingmode==2){
         tryReleaseVideo();
         this->currentDetectVideoAllFrameCount=0;
         this->detectVideoFloderUrl=dir.split("file:///")[1];
         this->videocap.open(this->detectVideoFloderUrl.toStdString());
         if(this->videocap.isOpened())
         {
             this->currentVideoWidth=this->videocap.get(cv::CAP_PROP_FRAME_WIDTH);
             this->currentVideoHeight=this->videocap.get(cv::CAP_PROP_FRAME_HEIGHT);
             this->currentVideoAllFrameCount=this->videocap.get(cv::CAP_PROP_FRAME_COUNT);
             cv::Mat mat;
             this->videocap>>mat;
             getDetect(mat);
             emit this->sendDetectImage(this->img);
             emit this->resetCanvs();
             this->currentVideoFrameCount++;
         }
     }
      else if(this->usingmode==3){
         this->tryReleaseCamera();
         this->cap.open(0);
         this->isplayCamera=true;
         if(isRunning==false)
         {
             this->start();
         }
     }
}
cv::Mat labeling::matTOimge(QImage & mage)
{

    QImage::Format format = mage.format();
    if (format != QImage::Format_RGB888)
    {
        return Mat();
    }
    mage.convertToFormat(QImage::Format_RGB888);
    Mat mat = Mat (mage.height(),
                   mage.width(),
                   CV_8UC3,
                   mage.bits(),
                   mage.bytesPerLine());//创建3通道8位图片并分配内存
    return cv::Mat(mat);
}
