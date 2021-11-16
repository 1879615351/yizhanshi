#ifndef CLASSIMAGEDATA_H
#define CLASSIMAGEDATA_H

#include<QImage>
class classImageData
{
public:
    classImageData();
    QImage img;
    int type=-1; //区分类型
    int mode=-1; //区分是哪个模式下的图片
    int n=-1; //如果是图片，则是图片的索引，如果是视频则是视频的帧数，摄像头对应拍照顺序
};

#endif // CLASSIMAGEDATA_H
