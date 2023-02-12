#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#define FOLDER_NAME "Ekonomizer"

#include <QDir>
#include <QStringList>


class FileManager
{
public:
    FileManager();
    void open(QString path);

    void close();
    QByteArray readData();

    QStringList readSaveDir();
    QString loadVehicleData(QString vehicleName);
    void checkSaveLocalization();
    void loadVehicleList();

    static QString getSaveLocation();
    static bool remove(QString path);
private:
    const QString DATA_FOLDER_NAME = "Ekonomizer";
    const QString FileExtension = "sav";
    QString getSavesPath();
    QDir dir;

    QFile *file;
    QByteArray data;
};

#endif // FILEMANAGER_H
