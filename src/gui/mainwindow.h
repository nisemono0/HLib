#pragma once
#include "ui/ui_mainwindow.h"
#include "gui/imageview.h"
#include "db/dbmanager.h"
#include "utils/utildefs.h"

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTreeWidgetItem>
#include <QString>
#include <QClipboard>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow ui;
    SQLiteDB db;
    QGraphicsPixmapItem *pixitem;
    QGraphicsScene *scene;
    QLabel *tree_status;
    QLabel *img_status;
    int loaded_archives_num;
    void lockWindowItems();
    void unlockWindowItems();
    void clearTree();
    void clearView();
    void resetTreeStatusMessage();
    void setTreeStatusMessage();
    void setTreeStatusMessage(const QString file_path);
    void loadAllImages(const QString file_path, const QString title);
    void loadFIrstImage(const QString file_path, const QString title);
private slots:
    void triggered_action_addDir();
    void triggered_action_addFile();
    void triggered_action_createDB();
    void triggered_action_loadDB();
    void triggered_action_unloadDB();
    void triggered_action_changeTheme(const MyTheme::MyTheme theme);
    void populateTree();
    void searchTreeItems(const QString search_str);
    void treeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void showTreeContextMenu(const QPoint &pos);
    void treeDoubleClick(QTreeWidgetItem *item, int column);
};