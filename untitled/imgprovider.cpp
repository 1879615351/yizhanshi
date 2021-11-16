#include "imgprovider.h"

ImgProvider::ImgProvider(QObject *parent) : QQuickImageProvider(QQuickImageProvider::Image)
{

}
QImage ImgProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

    return this->img;
}
