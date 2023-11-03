/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gui/imageview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoadDB;
    QAction *actionAddDir;
    QAction *actionAddFile;
    QAction *actionExit;
    QAction *actionThemeDarkMaroon;
    QAction *actionThemeDarkGreen;
    QAction *actionThemeDarkPurple;
    QAction *actionThemeFusion;
    QAction *actionThemeWindows;
    QAction *actionCreateDB;
    QAction *actionUnloadDB;
    QAction *actionCleanDB;
    QAction *actionCleanHashes;
    QAction *actionCleanPaths;
    QAction *actionScaleImage;
    QAction *actionCheckDB;
    QAction *actionCheckPaths;
    QAction *actionShowLogs;
    QAction *actionFitInView;
    QAction *actionFitToWidth;
    QAction *actionFreeView;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutSearch;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonRandom;
    QPushButton *pushButtonRefresh;
    QLineEdit *lineEditSearch;
    QSplitter *splitterExplorer;
    QTreeWidget *treeWidget;
    ImageView *graphicsView;
    QStatusBar *statusBar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuLoad;
    QMenu *menuTheme;
    QMenu *menuSettings;
    QMenu *menuSettingsView;
    QMenu *menuInfo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 700);
        MainWindow->setMinimumSize(QSize(800, 600));
        actionLoadDB = new QAction(MainWindow);
        actionLoadDB->setObjectName(QString::fromUtf8("actionLoadDB"));
        actionAddDir = new QAction(MainWindow);
        actionAddDir->setObjectName(QString::fromUtf8("actionAddDir"));
        actionAddFile = new QAction(MainWindow);
        actionAddFile->setObjectName(QString::fromUtf8("actionAddFile"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionThemeDarkMaroon = new QAction(MainWindow);
        actionThemeDarkMaroon->setObjectName(QString::fromUtf8("actionThemeDarkMaroon"));
        actionThemeDarkGreen = new QAction(MainWindow);
        actionThemeDarkGreen->setObjectName(QString::fromUtf8("actionThemeDarkGreen"));
        actionThemeDarkPurple = new QAction(MainWindow);
        actionThemeDarkPurple->setObjectName(QString::fromUtf8("actionThemeDarkPurple"));
        actionThemeFusion = new QAction(MainWindow);
        actionThemeFusion->setObjectName(QString::fromUtf8("actionThemeFusion"));
        actionThemeWindows = new QAction(MainWindow);
        actionThemeWindows->setObjectName(QString::fromUtf8("actionThemeWindows"));
        actionCreateDB = new QAction(MainWindow);
        actionCreateDB->setObjectName(QString::fromUtf8("actionCreateDB"));
        actionUnloadDB = new QAction(MainWindow);
        actionUnloadDB->setObjectName(QString::fromUtf8("actionUnloadDB"));
        actionCleanDB = new QAction(MainWindow);
        actionCleanDB->setObjectName(QString::fromUtf8("actionCleanDB"));
        actionCleanHashes = new QAction(MainWindow);
        actionCleanHashes->setObjectName(QString::fromUtf8("actionCleanHashes"));
        actionCleanPaths = new QAction(MainWindow);
        actionCleanPaths->setObjectName(QString::fromUtf8("actionCleanPaths"));
        actionScaleImage = new QAction(MainWindow);
        actionScaleImage->setObjectName(QString::fromUtf8("actionScaleImage"));
        actionScaleImage->setCheckable(true);
        actionScaleImage->setChecked(true);
        actionCheckDB = new QAction(MainWindow);
        actionCheckDB->setObjectName(QString::fromUtf8("actionCheckDB"));
        actionCheckPaths = new QAction(MainWindow);
        actionCheckPaths->setObjectName(QString::fromUtf8("actionCheckPaths"));
        actionShowLogs = new QAction(MainWindow);
        actionShowLogs->setObjectName(QString::fromUtf8("actionShowLogs"));
        actionFitInView = new QAction(MainWindow);
        actionFitInView->setObjectName(QString::fromUtf8("actionFitInView"));
        actionFitInView->setCheckable(true);
        actionFitInView->setChecked(true);
        actionFitToWidth = new QAction(MainWindow);
        actionFitToWidth->setObjectName(QString::fromUtf8("actionFitToWidth"));
        actionFitToWidth->setCheckable(true);
        actionFreeView = new QAction(MainWindow);
        actionFreeView->setObjectName(QString::fromUtf8("actionFreeView"));
        actionFreeView->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayoutSearch = new QHBoxLayout();
        horizontalLayoutSearch->setObjectName(QString::fromUtf8("horizontalLayoutSearch"));
        pushButtonSearch = new QPushButton(centralwidget);
        pushButtonSearch->setObjectName(QString::fromUtf8("pushButtonSearch"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonSearch->sizePolicy().hasHeightForWidth());
        pushButtonSearch->setSizePolicy(sizePolicy);

        horizontalLayoutSearch->addWidget(pushButtonSearch);

        pushButtonRandom = new QPushButton(centralwidget);
        pushButtonRandom->setObjectName(QString::fromUtf8("pushButtonRandom"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonRandom->sizePolicy().hasHeightForWidth());
        pushButtonRandom->setSizePolicy(sizePolicy1);

        horizontalLayoutSearch->addWidget(pushButtonRandom);

        pushButtonRefresh = new QPushButton(centralwidget);
        pushButtonRefresh->setObjectName(QString::fromUtf8("pushButtonRefresh"));
        sizePolicy.setHeightForWidth(pushButtonRefresh->sizePolicy().hasHeightForWidth());
        pushButtonRefresh->setSizePolicy(sizePolicy);

        horizontalLayoutSearch->addWidget(pushButtonRefresh);

        lineEditSearch = new QLineEdit(centralwidget);
        lineEditSearch->setObjectName(QString::fromUtf8("lineEditSearch"));

        horizontalLayoutSearch->addWidget(lineEditSearch);

        horizontalLayoutSearch->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayoutSearch);

        splitterExplorer = new QSplitter(centralwidget);
        splitterExplorer->setObjectName(QString::fromUtf8("splitterExplorer"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(splitterExplorer->sizePolicy().hasHeightForWidth());
        splitterExplorer->setSizePolicy(sizePolicy2);
        splitterExplorer->setMinimumSize(QSize(0, 0));
        splitterExplorer->setOrientation(Qt::Horizontal);
        splitterExplorer->setHandleWidth(4);
        splitterExplorer->setChildrenCollapsible(false);
        treeWidget = new QTreeWidget(splitterExplorer);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Title"));
        __qtreewidgetitem->setFont(0, font);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy3);
        treeWidget->setMinimumSize(QSize(150, 0));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        treeWidget->setIndentation(1);
        splitterExplorer->addWidget(treeWidget);
        graphicsView = new ImageView(splitterExplorer);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(100);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy4);
        graphicsView->setMinimumSize(QSize(300, 0));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setInteractive(false);
        graphicsView->setAlignment(Qt::AlignCenter);
        splitterExplorer->addWidget(graphicsView);

        verticalLayout->addWidget(splitterExplorer);

        MainWindow->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 30));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuLoad = new QMenu(menubar);
        menuLoad->setObjectName(QString::fromUtf8("menuLoad"));
        menuTheme = new QMenu(menubar);
        menuTheme->setObjectName(QString::fromUtf8("menuTheme"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuSettingsView = new QMenu(menuSettings);
        menuSettingsView->setObjectName(QString::fromUtf8("menuSettingsView"));
        menuInfo = new QMenu(menubar);
        menuInfo->setObjectName(QString::fromUtf8("menuInfo"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuLoad->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuInfo->menuAction());
        menubar->addAction(menuTheme->menuAction());
        menuFile->addAction(actionAddFile);
        menuFile->addAction(actionAddDir);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuLoad->addAction(actionCreateDB);
        menuLoad->addSeparator();
        menuLoad->addAction(actionLoadDB);
        menuLoad->addAction(actionUnloadDB);
        menuLoad->addSeparator();
        menuLoad->addAction(actionCleanDB);
        menuLoad->addAction(actionCleanHashes);
        menuLoad->addAction(actionCleanPaths);
        menuLoad->addSeparator();
        menuLoad->addAction(actionCheckDB);
        menuLoad->addAction(actionCheckPaths);
        menuTheme->addAction(actionThemeDarkMaroon);
        menuTheme->addAction(actionThemeDarkGreen);
        menuTheme->addAction(actionThemeDarkPurple);
        menuTheme->addSeparator();
        menuTheme->addAction(actionThemeFusion);
        menuTheme->addAction(actionThemeWindows);
        menuSettings->addAction(actionScaleImage);
        menuSettings->addAction(menuSettingsView->menuAction());
        menuSettingsView->addAction(actionFitInView);
        menuSettingsView->addAction(actionFitToWidth);
        menuSettingsView->addSeparator();
        menuSettingsView->addAction(actionFreeView);
        menuInfo->addAction(actionShowLogs);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "HLib", nullptr));
        actionLoadDB->setText(QCoreApplication::translate("MainWindow", "Load DB", nullptr));
#if QT_CONFIG(statustip)
        actionLoadDB->setStatusTip(QCoreApplication::translate("MainWindow", "Load a database", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionLoadDB->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddDir->setText(QCoreApplication::translate("MainWindow", "Add Directory", nullptr));
#if QT_CONFIG(statustip)
        actionAddDir->setStatusTip(QCoreApplication::translate("MainWindow", "Add all archives in a directory", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionAddDir->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddFile->setText(QCoreApplication::translate("MainWindow", "Add File", nullptr));
#if QT_CONFIG(statustip)
        actionAddFile->setStatusTip(QCoreApplication::translate("MainWindow", "Add a single archive", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionAddFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
#if QT_CONFIG(statustip)
        actionExit->setStatusTip(QCoreApplication::translate("MainWindow", "Exists the program", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionThemeDarkMaroon->setText(QCoreApplication::translate("MainWindow", "Dark Maroon", nullptr));
#if QT_CONFIG(shortcut)
        actionThemeDarkMaroon->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionThemeDarkGreen->setText(QCoreApplication::translate("MainWindow", "Dark Green", nullptr));
#if QT_CONFIG(shortcut)
        actionThemeDarkGreen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionThemeDarkPurple->setText(QCoreApplication::translate("MainWindow", "Dark Purple", nullptr));
#if QT_CONFIG(shortcut)
        actionThemeDarkPurple->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionThemeFusion->setText(QCoreApplication::translate("MainWindow", "Fusion", nullptr));
#if QT_CONFIG(shortcut)
        actionThemeFusion->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+4", nullptr));
#endif // QT_CONFIG(shortcut)
        actionThemeWindows->setText(QCoreApplication::translate("MainWindow", "Windows", nullptr));
#if QT_CONFIG(shortcut)
        actionThemeWindows->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCreateDB->setText(QCoreApplication::translate("MainWindow", "Create DB", nullptr));
#if QT_CONFIG(statustip)
        actionCreateDB->setStatusTip(QCoreApplication::translate("MainWindow", "Create a new database", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionCreateDB->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUnloadDB->setText(QCoreApplication::translate("MainWindow", "Unload DB", nullptr));
#if QT_CONFIG(statustip)
        actionUnloadDB->setStatusTip(QCoreApplication::translate("MainWindow", "Unload a database", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionUnloadDB->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+U", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCleanDB->setText(QCoreApplication::translate("MainWindow", "Clean DB", nullptr));
#if QT_CONFIG(statustip)
        actionCleanDB->setStatusTip(QCoreApplication::translate("MainWindow", "Removes entries with the same path but different hash from the database, keeping the correct entry", nullptr));
#endif // QT_CONFIG(statustip)
        actionCleanHashes->setText(QCoreApplication::translate("MainWindow", "Clean hashes", nullptr));
#if QT_CONFIG(statustip)
        actionCleanHashes->setStatusTip(QCoreApplication::translate("MainWindow", "Removes all entries with the same hash from the database", nullptr));
#endif // QT_CONFIG(statustip)
        actionCleanPaths->setText(QCoreApplication::translate("MainWindow", "Clean paths", nullptr));
#if QT_CONFIG(statustip)
        actionCleanPaths->setStatusTip(QCoreApplication::translate("MainWindow", "Removes all entries with the same path from the database", nullptr));
#endif // QT_CONFIG(statustip)
        actionScaleImage->setText(QCoreApplication::translate("MainWindow", "Scale image to window", nullptr));
#if QT_CONFIG(statustip)
        actionScaleImage->setStatusTip(QCoreApplication::translate("MainWindow", "Enable or disables the image scaling", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionScaleImage->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCheckDB->setText(QCoreApplication::translate("MainWindow", "Check DB", nullptr));
#if QT_CONFIG(statustip)
        actionCheckDB->setStatusTip(QCoreApplication::translate("MainWindow", "Checks if the paths/hashes in db match the ones on disk", nullptr));
#endif // QT_CONFIG(statustip)
        actionCheckPaths->setText(QCoreApplication::translate("MainWindow", "Check paths", nullptr));
#if QT_CONFIG(statustip)
        actionCheckPaths->setStatusTip(QCoreApplication::translate("MainWindow", "Checks if only the paths in db match the ones on disk", nullptr));
#endif // QT_CONFIG(statustip)
        actionShowLogs->setText(QCoreApplication::translate("MainWindow", "Show logs", nullptr));
#if QT_CONFIG(statustip)
        actionShowLogs->setStatusTip(QCoreApplication::translate("MainWindow", "Shows the logs window", nullptr));
#endif // QT_CONFIG(statustip)
        actionFitInView->setText(QCoreApplication::translate("MainWindow", "Fit in view", nullptr));
#if QT_CONFIG(statustip)
        actionFitInView->setStatusTip(QCoreApplication::translate("MainWindow", "Fits the image in view", nullptr));
#endif // QT_CONFIG(statustip)
        actionFitToWidth->setText(QCoreApplication::translate("MainWindow", "Fit to width", nullptr));
#if QT_CONFIG(statustip)
        actionFitToWidth->setStatusTip(QCoreApplication::translate("MainWindow", "Fits the image to width", nullptr));
#endif // QT_CONFIG(statustip)
        actionFreeView->setText(QCoreApplication::translate("MainWindow", "Free view", nullptr));
#if QT_CONFIG(statustip)
        actionFreeView->setStatusTip(QCoreApplication::translate("MainWindow", "No fit, zoom in and out with scrollwheen and drag with middlebutton", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(statustip)
        pushButtonSearch->setStatusTip(QCoreApplication::translate("MainWindow", "Search the database", nullptr));
#endif // QT_CONFIG(statustip)
        pushButtonSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
#if QT_CONFIG(statustip)
        pushButtonRandom->setStatusTip(QCoreApplication::translate("MainWindow", "Select random from view", nullptr));
#endif // QT_CONFIG(statustip)
        pushButtonRandom->setText(QCoreApplication::translate("MainWindow", "Random", nullptr));
#if QT_CONFIG(statustip)
        pushButtonRefresh->setStatusTip(QCoreApplication::translate("MainWindow", "Refresh the search", nullptr));
#endif // QT_CONFIG(statustip)
        pushButtonRefresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuLoad->setTitle(QCoreApplication::translate("MainWindow", "Database", nullptr));
        menuTheme->setTitle(QCoreApplication::translate("MainWindow", "Theme", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuSettingsView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuInfo->setTitle(QCoreApplication::translate("MainWindow", "Info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
