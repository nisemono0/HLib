#pragma once

#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QList>

class Utils {
public:
    static QJsonObject getJsonFromZip(const QString zip_path, const QString json_name);
    static QMap<QString, QString> getMapFromJson(QJsonObject json_obj);
    static bool createDB(const QString db_path, const QString con_name);
    static bool isDirEmpty(const QString dir_path);
    static QStringList getZipFilesList(const QString dir_path);
    static bool isNullOrEmpty(const QString str);
    static bool isNullOrEmpty(const QByteArray bytearray);
    static QString getSHA1Hash(const QString file_path);
    static QByteArray getFirstImageFromZip(const QString zip_path);
    static void naturalOrder(QStringList *str_list);
    static QByteArrayList getImagesFromZip(const QString zip_path, QWidget *parent);
};
