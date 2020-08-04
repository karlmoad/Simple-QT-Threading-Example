//
// Created by Karl Moad on 8/3/20.
//

#ifndef THREADINGEXAMPLE_WORKTHREAD_H
#define THREADINGEXAMPLE_WORKTHREAD_H

#include <QThread>
#include <QString>

class WorkThread: public QObject
{
    Q_OBJECT
public:
    explicit WorkThread(const QString& value, QObject *parent = nullptr);

public slots:
    void process();

signals:
    void ProgressUpdate(int step, const QString& data);
    void finished();

private:
    QString _statement;
};


#endif //THREADINGEXAMPLE_WORKTHREAD_H
