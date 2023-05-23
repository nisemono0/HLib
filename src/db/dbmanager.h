#pragma once
#include "gui/logwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QObject>
#include <QMap>

class SQLiteDB : public QObject {
    Q_OBJECT
public:
    SQLiteDB(const QString con_name, LogWindow *log_window, QObject *parent = nullptr);
    ~SQLiteDB();
    
    void setDBPath(const QString db_path);
    bool openDB();
    void closeDB();
    bool insert(QMap<QString, QString> info_map);
    bool insert(QList<QMap<QString, QString>> map_list);
    bool removeFromDB(const QString del_hash);
    bool removeFromDB(QStringList del_hashes);
    QList<QMap<QString, QVariant>> selectAll();
    QStringList selectTags(const QString tag_search);
    QStringList selectAllHashes();
    QStringList selectAllFilepaths();
private:
    QSqlDatabase db;
    LogWindow *log_window;
};
