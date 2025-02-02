#pragma once
#include "ui/ui_logwindow.h"

#include <QMainWindow>
#include <QWidget>
#include <QLabel>

class LogWindow: public QMainWindow {
    Q_OBJECT
public:
    LogWindow(QWidget *parent = nullptr);
    ~LogWindow();
    void appendMessage(const QString &message);
    void clearLogs();
private:
    Ui::LogWindow ui;
    QLabel *log_status;
    void updateLogStatusBar();
private slots:
    void triggered_action_saveLog();
    void triggered_action_close();
    void triggered_action_clearLog();
};