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
#include <QWidgetAction>
#include <QSlider>
#include <QActionGroup>
#include <QTimer>
#include <QSettings>

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow ui;
    
    SQLiteDB *db;
    
    QGraphicsPixmapItem *pixitem;
    QGraphicsScene *scene;
    
    QLabel *tree_status;
    QLabel *img_status;
    
    QSlider *scale_slider;
    QWidgetAction *action_scale_slider;
    
    QActionGroup *settings_view_group;

    unsigned int loaded_archives_num;
    unsigned int filtered_archives_num;

    QTimer *search_timer;
    QString old_search;
    bool select_first_result;

    QSettings settings;
    QString last_db_dir_path;
    QString last_add_dir_path;
    QString last_add_file_path;

    void lockWindowItems();
    void unlockWindowItems();
    void clearTree();
    void clearView();
    void populateTree();
    void resetTreeStatusMessage();
    void setTreeStatusMessage();
    void loadAllImages(const QString file_path, const QString title);
    void loadFIrstImage(const QString file_path, const QString title);
    QTreeWidgetItem *getFirstVisibleItem();
    bool removeTreeItem(QTreeWidgetItem *item);
    void saveSettings();
    void loadSettings();
private slots:
    void triggered_action_addDir();
    void triggered_action_addFile();
    void triggered_action_createDB();
    void triggered_action_loadDB();
    void triggered_action_unloadDB();
    void triggered_action_cleanDB();
    void triggered_action_cleanHashes();
    void triggered_action_cleanPaths();
    void triggered_action_checkDB();
    void triggered_action_checkPaths();
    void triggered_action_scaleimage(bool checked);
    void triggered_action_scalechanged(int value);
    void triggered_action_viewfit(QAction *action);
    void triggered_action_search_typing(bool checked);
    void triggered_action_select_first_result(bool checked);
    void triggered_search_timer();
    void triggered_action_showlogs();
    void triggered_action_changeTheme(const MyTheme::MyTheme theme);
    void searchTreeItems(const QString search_str);
    void treeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void treeScrollToItem();
    void showTreeContextMenu(const QPoint &pos);
    void treeDoubleClick(QTreeWidgetItem *item, int column);
    void randomButtonClicked();
    void refreshButtonClicked();
};