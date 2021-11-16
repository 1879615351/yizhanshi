#ifndef IMGPROVIDER_H
#define IMGPROVIDER_H
#include <QObject>
#include <QQuickImageProvider>
#include <QImage>
#include <QPixmap>
class ImgProvider : public QQuickImageProvider
{
   // Q_OBJECT
public:
    explicit ImgProvider(QObject *parent = nullptr);
    QImage img;
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
signals:

};

#endif // IMGPROVIDER_H
