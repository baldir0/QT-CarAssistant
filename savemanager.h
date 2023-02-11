#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QString>
#include <QFile>
#include <QMap>
#include <QDebug>

class SaveManager
{
public:
    static bool save(QString filePath, QMap<int, QString> data);
    static QMap<int, QString> load(QString filePath);
private:
    static QFile* openFile(QString filePath, QFile::OpenMode flag);
};

#endif // SAVEMANAGER_H
