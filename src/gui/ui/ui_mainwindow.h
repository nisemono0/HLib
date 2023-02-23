/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
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
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutSearch;
    QPushButton *pushButtonSearch;
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

        pushButtonRefresh = new QPushButton(centralwidget);
        pushButtonRefresh->setObjectName(QString::fromUtf8("pushButtonRefresh"));
        sizePolicy.setHeightForWidth(pushButtonRefresh->sizePolicy().hasHeightForWidth());
        pushButtonRefresh->setSizePolicy(sizePolicy);

        horizontalLayoutSearch->addWidget(pushButtonRefresh);

        lineEditSearch = new QLineEdit(centralwidget);
        lineEditSearch->setObjectName(QString::fromUtf8("lineEditSearch"));

        horizontalLayoutSearch->addWidget(lineEditSearch);

        horizontalLayoutSearch->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayoutSearch);

        splitterExplorer = new QSplitter(centralwidget);
        splitterExplorer->setObjectName(QString::fromUtf8("splitterExplorer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitterExplorer->sizePolicy().hasHeightForWidth());
        splitterExplorer->setSizePolicy(sizePolicy1);
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
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy2);
        treeWidget->setMinimumSize(QSize(150, 0));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        treeWidget->setIndentation(1);
        splitterExplorer->addWidget(treeWidget);
        graphicsView = new ImageView(splitterExplorer);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(100);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy3);
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
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuLoad = new QMenu(menubar);
        menuLoad->setObjectName(QString::fromUtf8("menuLoad"));
        menuTheme = new QMenu(menubar);
        menuTheme->setObjectName(QString::fromUtf8("menuTheme"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuLoad->menuAction());
        menubar->addAction(menuTheme->menuAction());
        menuFile->addAction(actionAddFile);
        menuFile->addAction(actionAddDir);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuLoad->addAction(actionCreateDB);
        menuLoad->addSeparator();
        menuLoad->addAction(actionLoadDB);
        menuLoad->addAction(actionUnloadDB);
        menuTheme->addAction(actionThemeDarkMaroon);
        menuTheme->addAction(actionThemeDarkGreen);
        menuTheme->addAction(actionThemeDarkPurple);
        menuTheme->addSeparator();
        menuTheme->addAction(actionThemeFusion);
        menuTheme->addAction(actionThemeWindows);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoadDB->setText(QCoreApplication::translate("MainWindow", "Load DB", nullptr));
#if QT_CONFIG(shortcut)
        actionLoadDB->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddDir->setText(QCoreApplication::translate("MainWindow", "Add Directory", nullptr));
#if QT_CONFIG(shortcut)
        actionAddDir->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddFile->setText(QCoreApplication::translate("MainWindow", "Add File", nullptr));
#if QT_CONFIG(shortcut)
        actionAddFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
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
#if QT_CONFIG(shortcut)
        actionCreateDB->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUnloadDB->setText(QCoreApplication::translate("MainWindow", "Unload DB", nullptr));
#if QT_CONFIG(shortcut)
        actionUnloadDB->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+U", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButtonSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButtonRefresh->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuLoad->setTitle(QCoreApplication::translate("MainWindow", "Database", nullptr));
        menuTheme->setTitle(QCoreApplication::translate("MainWindow", "Theme", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
