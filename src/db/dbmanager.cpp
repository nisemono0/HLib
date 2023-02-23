#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

SQLiteDB::SQLiteDB(const QString con_name, QObject *parent): QObject(parent) {
    this->db = QSqlDatabase::addDatabase("QSQLITE", con_name);
}

SQLiteDB::~SQLiteDB() {
    if (this->db.isOpen()) {
        this->db.close();
    }
}

void SQLiteDB::setDBPath(const QString db_path) {
    this->db.setDatabaseName(db_path);
}

bool SQLiteDB::openDB() {
    if (this->db.open()) {
        return true;
    }
    return false;
}

void SQLiteDB::closeDB() {
    if (this->db.isOpen()) {
        this->db.close();
    }
}

bool SQLiteDB::insert(const QMap<QString, QString> info_map) {
    bool success = false;
    if (this->db.isOpen()) {
        QSqlQuery query(this->db);
        query.prepare("INSERT OR IGNORE INTO HLib (file_hash, title, file_path, tags) VALUES (:file_hash, :title, :file_path, :tags)");
        query.bindValue(":file_hash", info_map["file_hash"]);
        query.bindValue(":title", info_map["title"]);
        query.bindValue(":file_path", info_map["file_path"]);
        query.bindValue(":tags", info_map["tags"]);
        
        if (query.exec()) {
            success = true;
        } else {
            qDebug() << "[insertFile error]:" << query.lastError();
        }
        query.clear();
        this->db.commit();
    }
    return success;
}

bool SQLiteDB::insert(QList<QMap<QString, QString>> map_list) {
    bool success = false;

    if (this->db.isOpen()) {
        QSqlQuery query(this->db);
        query.prepare("INSERT OR IGNORE INTO HLib (file_hash, title, file_path, tags) VALUES (:file_hash, :title, :file_path, :tags)");

        QVariantList file_hash;
        QVariantList title;
        QVariantList file_path;
        QVariantList tags;
        for (auto it : map_list) {
            file_hash.append(it["file_hash"]);
            title.append(it["title"]);
            file_path.append(it["file_path"]);
            tags.append(it["tags"]);
        }
        query.bindValue(":file_hash", file_hash);
        query.bindValue(":title", title);
        query.bindValue(":file_path", file_path);
        query.bindValue(":tags", tags);

        if (query.execBatch()) {
            success = true;
        } else {
            qDebug() << "[insertFile error]:" << query.lastError();
        }
        query.clear();
        this->db.commit();
    }
    return success;
}

QList<QMap<QString, QVariant>> SQLiteDB::select() {
    QList<QMap<QString, QVariant>> results_list;
    if (this->db.isOpen()) {
        QSqlQuery query(this->db);
        query.prepare("SELECT DISTINCT * FROM HLib");
        if (query.exec()) {
            while (query.next()) {
                results_list.append({ {"file_hash", query.value(0)}, {"title", query.value(1)},
                                    {"file_path", query.value(2)}, {"tags", query.value(3)} });
            }
        } else {
            qDebug() << "[select() error]:" << query.lastError();
        }
        query.clear();
    }
    return results_list;
}

QStringList SQLiteDB::select(const QString tag_search) {
    QStringList hash_list;
    if (this->db.isOpen()) {
        QSqlQuery query(this->db);
        query.prepare("SELECT DISTINCT * FROM HLib WHERE tags MATCH :tag_search OR title MATCH :tag_search");
        query.bindValue(":tag_search", tag_search);
        if (query.exec()) {
            while (query.next()) {
                hash_list.append(query.value(0).toString());
            }
        } else {
            qDebug() << "[select(tag_search) error]:" << query.lastError();
        }
        query.clear();
    }
    return hash_list;
}

QStringList SQLiteDB::selectAllHashes() {
    QStringList hash_list;
    if (this->db.isOpen()) {
        QSqlQuery query(this->db);
        query.prepare("SELECT DISTINCT file_hash FROM HLib");
        if (query.exec()) {
            while (query.next()) {
                hash_list.append(query.value(0).toString());
            }
        } else {
            qDebug() << "[selectAllHashes() error]:" << query.lastError();
        }
        query.clear();
    }
    return hash_list;
}
