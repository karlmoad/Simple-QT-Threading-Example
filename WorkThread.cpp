//
// Created by Karl Moad on 8/3/20.
//

#include "WorkThread.h"

WorkThread::WorkThread(const QString& value,QObject *parent) : QObject(parent), _statement(value)
{}

void WorkThread::process()
{
    for(int i=0; i<_statement.size(); i++)
    {
        QString msg = QString("%1%1%1").arg(_statement.at(i));
        emit ProgressUpdate(i+1,msg);
        QThread::sleep(5);
    }
    emit finished();
}
