/********************************************************************************
** Form generated from reading UI file 'logwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWINDOW_H
#define UI_LOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogWindow
{
public:
    QAction *actionSaveLog;
    QAction *actionClose;
    QAction *actionClearLog;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *logPlainTextEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *LogWindow)
    {
        if (LogWindow->objectName().isEmpty())
            LogWindow->setObjectName(QString::fromUtf8("LogWindow"));
        LogWindow->setEnabled(true);
        LogWindow->resize(800, 500);
        LogWindow->setMinimumSize(QSize(800, 500));
        actionSaveLog = new QAction(LogWindow);
        actionSaveLog->setObjectName(QString::fromUtf8("actionSaveLog"));
        actionClose = new QAction(LogWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClearLog = new QAction(LogWindow);
        actionClearLog->setObjectName(QString::fromUtf8("actionClearLog"));
        centralwidget = new QWidget(LogWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        logPlainTextEdit = new QPlainTextEdit(centralwidget);
        logPlainTextEdit->setObjectName(QString::fromUtf8("logPlainTextEdit"));
        logPlainTextEdit->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logPlainTextEdit->sizePolicy().hasHeightForWidth());
        logPlainTextEdit->setSizePolicy(sizePolicy);
        logPlainTextEdit->setAcceptDrops(false);
        logPlainTextEdit->setUndoRedoEnabled(false);
        logPlainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(logPlainTextEdit);

        LogWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(LogWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 30));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        LogWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSaveLog);
        menuFile->addAction(actionClearLog);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);

        retranslateUi(LogWindow);

        QMetaObject::connectSlotsByName(LogWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LogWindow)
    {
        LogWindow->setWindowTitle(QCoreApplication::translate("LogWindow", "Logs", nullptr));
        actionSaveLog->setText(QCoreApplication::translate("LogWindow", "Save log", nullptr));
#if QT_CONFIG(statustip)
        actionSaveLog->setStatusTip(QCoreApplication::translate("LogWindow", "Save the log to a file", nullptr));
#endif // QT_CONFIG(statustip)
        actionClose->setText(QCoreApplication::translate("LogWindow", "Close", nullptr));
#if QT_CONFIG(statustip)
        actionClose->setStatusTip(QCoreApplication::translate("LogWindow", "Close the window", nullptr));
#endif // QT_CONFIG(statustip)
        actionClearLog->setText(QCoreApplication::translate("LogWindow", "Clear log", nullptr));
#if QT_CONFIG(statustip)
        actionClearLog->setStatusTip(QCoreApplication::translate("LogWindow", "Clear the log", nullptr));
#endif // QT_CONFIG(statustip)
        menuFile->setTitle(QCoreApplication::translate("LogWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogWindow: public Ui_LogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWINDOW_H
