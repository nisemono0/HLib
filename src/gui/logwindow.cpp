#include "gui/logwindow.h"

#include <QMainWindow>
#include <QWidget>

#include <QScrollBar>

LogWindow::LogWindow(QWidget *parent) : QMainWindow(parent) {
    this->ui.setupUi(this);
}

LogWindow::~LogWindow() {
    
}

void LogWindow::appendMessage(const QString &message) {
    this->ui.logPlainTextEdit->appendPlainText(message);
    // this->ui.logPlainTextEdit->verticalScrollBar()->setValue(this->ui.logPlainTextEdit->verticalScrollBar()->maximum());
}

void LogWindow::clearLogs() {
    this->ui.logPlainTextEdit->clear();
}