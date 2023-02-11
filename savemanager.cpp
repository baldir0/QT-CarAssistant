#include "savemanager.h"

bool SaveManager::save(QString filePath, QMap<int, QString> data) {
    QFile * file = openFile(filePath, QFile::OpenModeFlag::WriteOnly);

    if (file == nullptr) return false;

    QDataStream out(file);
    out << data;

    file->flush();
    file->close();
    delete file;
    return true;
}

QMap<int, QString> SaveManager::load(QString filePath) {
    QFile * file = openFile(filePath, QFile::OpenModeFlag::ReadOnly);
    QMap<int, QString> data;
    if (file == nullptr) return data;

    QDataStream in(file);
    in >> data;

    file->flush();
    file->close();
    delete file;
    return data;
}

QFile *SaveManager::openFile(QString filePath, QFile::OpenMode flag) {
    QFile *file = new QFile(filePath);
    if (!file->open(flag)) {
        qDebug() << "[SAVE_MANAGER] Failed To Open File at: " + filePath;
        return nullptr;
    }
    qDebug() << "[SAVE_MANAGER] File opened Sucessfull: " + filePath << "With Flag: " + QString::number(flag.toInt());
    return file;
}
