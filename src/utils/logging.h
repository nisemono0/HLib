#pragma once
#include "gui/logwindow.h"

#include <QWidget>
#include <QString>

class Logging {
public:
    static void setLoggerWindow(QWidget *parent = nullptr);
    static void showLoggingWindow();
    static void logMessage(const QString message);
    static void clearLoggingWindow();
private:
    static inline LogWindow *log_window = nullptr;
};