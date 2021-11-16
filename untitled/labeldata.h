#ifndef LABELDATA_H
#define LABELDATA_H

#include <QImage>
class labeldata
{
public:
    labeldata();
    int type=-1;
    float  x_center;
    float  y_center;
    float  width;
    float  height;
    QImage img;
};

#endif // LABELDATA_H
