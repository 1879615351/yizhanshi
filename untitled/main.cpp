#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <imgsender.h>
#include <imgprovider.h>
#include <QQmlContext>
#include <labeling.h>
#include <trainthreadprocess.h>
#include <QDebug>
#include <detectthread.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    ImgSender *OBJ_imgSender =new ImgSender();  //将接收camera的数据发送视频数据到QML中的对象
    ImgSender *OBJ_imgDetectSender =new ImgSender();  //将接收camera的数据发送视频数据到QML中的对象
    labeling  *OBJ_label= new labeling();
    trainthreadProcess *OBJ_trainprocess=new trainthreadProcess();
    detectThread *detect =new detectThread();
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.addImageProvider(QLatin1String("imgProvider"), OBJ_imgSender->provider);
    engine.addImageProvider(QLatin1String("imgProvider2"), OBJ_imgDetectSender->provider);
    engine.rootContext()->setContextProperty("imgSender",OBJ_imgSender);
    engine.rootContext()->setContextProperty("detectSender",OBJ_imgDetectSender);
    engine.rootContext()->setContextProperty("labeling",OBJ_label);
    engine.rootContext()->setContextProperty("trainprocess",OBJ_trainprocess);
    engine.rootContext()->setContextProperty("detect",detect);
    QObject::connect(OBJ_label,&labeling::pictureChangeSignal,OBJ_imgSender,&ImgSender::setImage);
    QObject::connect(OBJ_label,&labeling::sendDetectImage,OBJ_imgDetectSender,&ImgSender::setImage);
    QObject::connect(OBJ_label,&labeling::startProcess,OBJ_trainprocess,&trainthreadProcess::startTrain);
    QObject::connect(OBJ_label,&labeling::stopTrainSignal,OBJ_trainprocess,&trainthreadProcess::stopTrain);
    QObject::connect(OBJ_label,&labeling::setDetectDir,detect,&detectThread::setProjectFolder);
    engine.load(url);
    return app.exec();
}
