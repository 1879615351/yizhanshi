#ifndef TRAINTHREADPROCESS_H
#define TRAINTHREADPROCESS_H

#include <QObject>
#include <QThread>
#include <QProcess>
class trainthreadProcess : public QThread
{
    Q_OBJECT
public:
    explicit trainthreadProcess(QObject *parent = nullptr);
    ~trainthreadProcess();
    void run() override;
    QString dirPath="";
    QProcess process;
    Q_INVOKABLE void closeTrain();
signals:
    void trainDone();
public slots:
    void startTrain(QString dirPath);
    void stopTrain();
};

#endif // TRAINTHREADPROCESS_H
