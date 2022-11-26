#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
     Q_OBJECT
public:
     Worker(int id, int max);
     ~Worker(){}

    int id() const;
    void setId(int id);

public slots:
    void func();

signals:
    void progress(int);

private:
    int id_;
    int max_;
};

#endif // WORKER_H



