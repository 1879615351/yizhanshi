#include "usethread.h"

UseThread::UseThread(QObject *parent)
{

}
void UseThread::run()
{
    while(true)
    {
        if(isUsing==false)
        {
            msleep(1000);
        }
        else{

        }
    }
}
