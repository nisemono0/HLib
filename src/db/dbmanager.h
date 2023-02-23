#pragma once

#include <QApplication>
#include <QSqlDatabase>
#include <QObject>
#include <QMap>

class SQLiteDB : public QObject {
    Q_OBJECT
public:
    SQLiteDB(const QString con_name, QObject *parent = nullptr);
    ~SQLiteDB();
    
    void setDBPath(const QString db_path);
    bool openDB();
    void closeDB();
    bool insert(QMap<QString, QString> info_map);
    bool insert(QList<QMap<QString, QString>> map_list);
    QList<QMap<QString, QVariant>> select();
    QStringList select(const QString tag_search);
    QStringList selectAllHashes();
private:
    QSqlDatabase db;
};