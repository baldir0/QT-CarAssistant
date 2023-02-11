#include "filemanager.h"
#include <QMessageBox>


FileManager::FileManager()
{
    this->checkSaveLocalization();

    this->loadVehicleList();
}

void FileManager::loadVehicleList() {
    qDebug() << "Loading vehicle list...";

    this->file = new QFile(QDir::homePath() + "/Documents/Ekonomizer/Saves/list.dat");
    // this->open(QDir::homePath() + "/Documents/Ekonomizer/Saves/list.dat");
    if (!this->file->open(QIODevice::ReadWrite)) {
        qDebug() << "Cannot open the file";
        return;
    }
    QByteArray data;
    do  {
        data = this->file->readLine().trimmed();
        qDebug() << data;
    } while ( data != "" );
    // qDebug() << data;
    this->file->close();
}

QString FileManager::getSaveLocation()
{
    return QDir::homePath() + "/Documents/" + FOLDER_NAME + "/Saves/";
}

QStringList FileManager::readSaveDir()
{
    dir.setPath(this->getSavesPath());
    return dir.entryList();
}

QString FileManager::loadVehicleData(QString vehicleName)
{
    dir.setPath(this->getSavesPath());
    QFile *file = new QFile(dir.path() + "/" + vehicleName);
    if (!file->open(QIODevice::ReadOnly)) {
        QMessageBox allertBox;
        allertBox.setText("Cannot load this File!");
        allertBox.exec();
        return 0;
    }
    return file->readAll();
}

void FileManager::checkSaveLocalization()
{
    // GO INTO DOCUMENTS
    // LOOK FOR EKONOMIZER FOLDER
    // INSIDE CHECK IF SAVES FOLDER EXISTS
    // CHECK IF USER SETTINGS FOLDER EXISTS ??
    // IF NOT EXISTS CREATE EMPTY FOLDER
    dir.setPath(dir.homePath() + "/Documents");
    bool isEkonomizerFolderExists = dir.entryList().contains(this->DATA_FOLDER_NAME);
    if (!isEkonomizerFolderExists) dir.mkdir(this->DATA_FOLDER_NAME);

    dir.setPath(dir.path() + "/" + this->DATA_FOLDER_NAME);
    bool isSaveFolderExists = dir.entryList().contains("Saves");
    if (!isSaveFolderExists) dir.mkdir("Saves");
}

QString FileManager::getSavesPath()
{
    return dir.homePath() + "/Documents/" + this->DATA_FOLDER_NAME + "/Saves";
}
