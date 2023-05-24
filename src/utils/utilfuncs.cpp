#include "utils/utilfuncs.h"

#include <QString>
#include <QTextCodec>
#include <quazip/quazip.h>
#include <quazip/quazipfile.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QDir>
#include <QDirIterator>
#include <QCryptographicHash>
#include <QMimeDatabase>
#include <QCollator>
#include <QByteArrayList>
#include <QVariantList>
#include <QProgressDialog>
#include <QEventLoop>
#include <QApplication>

QJsonObject Utils::getJsonFromZip(const QString zip_path, const QString json_name) {
    QJsonObject json_obj;
    QuaZip zip(zip_path);

    if (zip.open(QuaZip::mdUnzip)) {
        QStringList info_json = zip.getFileNameList().filter(json_name, Qt::CaseInsensitive);
        
        if (info_json.isEmpty()) {
            Utils::log_window->appendMessage(QString("[No json.info]: %1").arg(zip_path));
        } else {
            if (zip.setCurrentFile(info_json[0], QuaZip::csInsensitive)) {
                QuaZipFile zip_file(&zip);
                if (zip_file.open(QIODevice::ReadOnly)) {
                    QByteArray json_bytes = zip_file.readAll();
                    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

                    if (json_doc.isNull() || !json_doc.isObject()) {
                        Utils::log_window->appendMessage(QString("[Failed to load info.json]: %1").arg(zip_path));
                        zip_file.close();
                        zip.close();
                        return json_obj;
                    }

                    json_obj = json_doc.object();
                    
                    QFileInfo zip_info(zip_path);
                    // Some archives have dont have [Artist] ... (Published in) in the [gallery_info][title] field
                    // so I add a [title_basename] key containing the basename of the file
                    json_obj.insert("title_basename", zip_info.completeBaseName());
                    json_obj.insert("file_path", zip_info.filePath());
                    json_obj.insert("file_hash", Utils::getSHA1Hash(zip_info.filePath()));

                    zip_file.close();
                }
            }
        }
        zip.close();
    }
    return json_obj;
}

QMap<QString, QString> Utils::getMapFromJson(QJsonObject json_obj) {
    QMap<QString, QString> mapped_data;

    if (json_obj.isEmpty()) {
        return mapped_data;
    }

    QVariantMap tags = json_obj.toVariantMap()["gallery_info"].toMap()["tags"].toMap();

    QString title = json_obj.toVariantMap()["title_basename"].toString();
    QString file_path = json_obj.toVariantMap()["file_path"].toString();
    QString file_hash = json_obj.toVariantMap()["file_hash"].toString();
    QStringList artist = tags["artist"].toStringList();
    QStringList parody = tags["parody"].toStringList();
    QStringList publisher = tags["publisher"].toStringList();
    QStringList circle = tags["circle"].toStringList();
    QStringList event = tags["event"].toStringList();
    QStringList other = tags["other"].toStringList();
    QStringList magazine = tags["magazine"].toStringList();

    QString str_tags = "title:" + title + ", ";
    for (auto it : artist) {
        str_tags += "artist:" + it + ", ";
    }
    for (auto it : parody) {
        str_tags += "parody:" + it + ", ";
    }
    for (auto it : magazine) {
        str_tags += "magazine:" + it + ", ";
    }
    for (auto it : publisher) {
        str_tags += "publisher:" + it + ", ";
    }
    for (auto it : circle) {
        str_tags += "circle:" + it + ", ";
    }
    for (auto it : event) {
        str_tags += "event:" + it + ", ";
    }
    for (auto it : other) {
        str_tags += "other:" + it + ", ";
    }

    if (str_tags.endsWith(", ")) {
        str_tags.chop(2);
    }
    
    mapped_data["file_hash"] = file_hash;
    mapped_data["title"] = title;
    mapped_data["file_path"] = file_path;
    mapped_data["tags"] = str_tags;

    return mapped_data;
}

bool Utils::createDB(const QString db_path, const QString con_name) {
    bool success = false;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", con_name);
        db.setDatabaseName(db_path);
        if (db.open()) {
            QSqlQuery query(db);
            query.prepare(
                "CREATE VIRTUAL TABLE IF NOT EXISTS HLib using fts4"
                "(file_hash,"
                "title,"
                "file_path,"
                "tags)"
            );

            if (query.exec()) {
                success = true;
            } else {
                Utils::log_window->appendMessage(QString("[createDB error]: %1").arg(query.lastError().text()));
            }
            query.clear();
            db.close();
        } else {
            Utils::log_window->appendMessage(QString("[createDB couldn't open]: %1").arg(db_path));
            success = false;
        }
    }
    QSqlDatabase::removeDatabase(con_name);
    return success;
}

bool Utils::isDirEmpty(const QString dir_path) {
    QDir dir(dir_path);
    if(dir.isEmpty()){
        return true;
    }
    return false;
}

QStringList Utils::getZipFilesList(const QString dir_path) {
    QStringList zips_list;

    QDir dir(dir_path);
    if(dir.isEmpty()){
        return zips_list;
    }

    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    dir.setNameFilters({ "*.zip" });

    QDirIterator zip_files_it(dir, QDirIterator::Subdirectories);
    while(zip_files_it.hasNext()){
        zips_list.append(zip_files_it.next());
    }

    return zips_list;
}


bool Utils::isNullOrEmpty(const QString str) {
    if (str.isNull() || str.isEmpty()) {
        return true;
    }
    return false;
}

bool Utils::isNullOrEmpty(const QByteArray bytearray) {
    if (bytearray.isNull() || bytearray.isEmpty()) {
        return true;
    }
    return false;
}

QString Utils::getSHA1Hash(const QString file_path) {
    QString hash_string;
    QFile file(file_path);
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            // Hash the frst 512Kb of the file
            QByteArray hash = QCryptographicHash::hash(file.read(512000), QCryptographicHash::Sha1);
            hash_string = QLatin1String(hash.toHex());
            file.close();
        }
    }
    return hash_string;
}

void Utils::naturalOrder(QStringList *str_list) {
    QCollator collator;
    collator.setNumericMode(true);
    std::sort(str_list->begin(), str_list->end(), collator);
}


QByteArray Utils::getFirstImageFromZip(const QString zip_path) {
    QByteArray image_bytes;

    QuaZip zip(zip_path);
    if (zip.open(QuaZip::mdUnzip)) {
        QStringList filenames = zip.getFileNameList();

        Utils::naturalOrder(&filenames);

        QMimeDatabase mimedb;
        QString zip_imgname;

        bool found = false;
        for (auto name : filenames) {
            auto mimetype = mimedb.mimeTypeForFile(name, QMimeDatabase::MatchExtension);
            if (mimetype.isValid() && mimetype.name().startsWith("image", Qt::CaseInsensitive)) {
                found = true;
                zip_imgname = name;
                break;
            }
        }

        if (found) {
            if (zip.setCurrentFile(zip_imgname, QuaZip::csInsensitive)) {
                QuaZipFile zip_file(&zip);
                if (zip_file.open(QIODevice::ReadOnly)) {
                    image_bytes = zip_file.readAll();
                    zip_file.close();
                }
            }
        }
        
        zip.close();
    }
    
    return image_bytes;
}

QByteArrayList Utils::getImagesFromZip(const QString zip_path, QWidget *parent) {
    QByteArrayList images_bytelist;

    QuaZip zip(zip_path);
    if (zip.open(QuaZip::mdUnzip)) {
        QStringList filenames = zip.getFileNameList();
        QStringList imagenames;
        
        QMimeDatabase mimdedb;
        for (auto name : filenames) {
            auto mimetype = mimdedb.mimeTypeForFile(name, QMimeDatabase::MatchExtension);
            if (mimetype.isValid() && mimetype.name().startsWith("image", Qt::CaseInsensitive)) {
                imagenames.append(name);
            }
        }

        Utils::naturalOrder(&imagenames);

        QProgressDialog progress("Extracting images", nullptr, 0, imagenames.count(), parent);
        progress.setWindowModality(Qt::WindowModal);
        progress.show();
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        int progress_count = 0;
        QuaZipFile zip_file(&zip);
        for (auto zipimage : imagenames) {
            zip.setCurrentFile(zipimage);
            if (zip_file.open(QIODevice::ReadOnly)) {
                images_bytelist.append(zip_file.readAll());
                zip_file.close();
            }
            progress.setValue(progress_count);
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
            progress_count++;
        }   
        zip.close();
    }
    return images_bytelist;
}

QStringList Utils::getCleanDBEntries(QMap<QString, QStringList> map) {
    QStringList removable_list;
    for (auto key : map.keys()) {
        QStringList db_hashes = map.value(key);
        if (db_hashes.length() > 1) {
            QString file_hash = Utils::getSHA1Hash(key);
            if (!Utils::isNullOrEmpty(file_hash)) {
                for (auto hash : db_hashes) {
                    if (QString::compare(file_hash, hash, Qt::CaseInsensitive) != 0) {
                        removable_list.append(hash);
                    }
                }
            }
        }
    }
    return removable_list;
}

QStringList Utils::getCleanDBHashes(QStringList hashes) {
    QStringList removable_list;
    for (auto it : hashes) {
        if (hashes.count(it) > 1) {
            removable_list.append(it);
        }
    }
    return removable_list;
}


QStringList Utils::getCleanDBPaths(QMap<QString, QStringList> map) {
    QStringList removable_list;
    for (auto key : map.keys()) {
        QStringList hashes = map.value(key);
        if (hashes.length() > 1) {
            for (auto hash : hashes) {
                removable_list.append(hash);
            }
        }
    }
    return removable_list;
}

bool Utils::fileExists(const QString file_path) {
    QFile file(file_path);
    if (file.exists()) {
        return true;
    }
    return false;
}
