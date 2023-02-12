#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QDebug>

class Logger
{
public:
    template <class T>
    static void log(QString msg) {
        qDebug() << "[" + QString(typeid(T).name()) + "] - " + msg;
    };
};

#endif // LOGGER_H
