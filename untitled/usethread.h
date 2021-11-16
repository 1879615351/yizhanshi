#ifndef USETHREAD_H
#define USETHREAD_H

#include <QObject>
#include <QThread>
class UseThread : public QThread
{
    Q_OBJECT
public:
    explicit UseThread(QObject *parent = nullptr);
    void run();
    bool isUsing=false;
    Q_INVOKABLE void beginUse();
public slots:

signals:

};

#endif // USETHREAD_H
