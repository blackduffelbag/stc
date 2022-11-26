#include "worker.h"
#include <QDebug>
#include <QThread>
Worker::Worker(int id, int max) :
    id_(id),
    max_(max)
{

}

void Worker::func()
{
    //Цикл иметирующий сложные вычисления
    for(int i = 0; i <= max_; ++i)
    {
       QThread::sleep (1);
       qDebug() << i;
       emit(progress(i));

    }

}


int Worker::id() const
{
    return id_;
}

void Worker::setId(int id)
{
    id_ = id;
}
