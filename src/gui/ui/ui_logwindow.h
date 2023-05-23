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
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *logPlainTextEdit;

    void setupUi(QMainWindow *LogWindow)
    {
        if (LogWindow->objectName().isEmpty())
            LogWindow->setObjectName(QString::fromUtf8("LogWindow"));
        LogWindow->setEnabled(true);
        LogWindow->resize(800, 500);
        LogWindow->setMinimumSize(QSize(800, 500));
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

        retranslateUi(LogWindow);

        QMetaObject::connectSlotsByName(LogWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LogWindow)
    {
        LogWindow->setWindowTitle(QCoreApplication::translate("LogWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogWindow: public Ui_LogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWINDOW_H
