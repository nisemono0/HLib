#include "gui/logwindow.h"

#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>

LogWindow::LogWindow(QWidget *parent) : QMainWindow(parent) {
    this->ui.setupUi(this);

    this->log_status = new QLabel(this);
    this->ui.statusBar->addWidget(log_status);

    connect(this->ui.actionSaveLog, &QAction::triggered, this, &LogWindow::triggered_action_saveLog);
    connect(this->ui.actionClearLog, &QAction::triggered, this, &LogWindow::triggered_action_clearLog);
    connect(this->ui.actionClose, &QAction::triggered, this, &LogWindow::triggered_action_close);
}

LogWindow::~LogWindow() {
    delete this->log_status;
}

void LogWindow::appendMessage(const QString &message) {
    this->ui.logPlainTextEdit->appendPlainText(message);
    this->updateLogStatusBar();
}

void LogWindow::clearLogs() {
    this->ui.logPlainTextEdit->clear();
    this->updateLogStatusBar();
}

void LogWindow::updateLogStatusBar() {
    int blocks = this->ui.logPlainTextEdit->blockCount();
    this->log_status->setText(QString("Lines: %1").arg(QString::number(blocks)));
}

void LogWindow::triggered_action_saveLog() {
    QString save_path = QFileDialog::getSaveFileName(this, "Log save", QDir::homePath(), { "Text file (*.txt) ;; All files (*)" });

    QFile file(save_path);
    if (file.open(QFile::ReadWrite)) {
        QTextStream stream(&file);
        stream << this->ui.logPlainTextEdit->toPlainText();
        stream.flush();
        if (stream.status() == QTextStream::Ok) {
            QMessageBox::information(this, "Info", "Log written to file");
        } else if (stream.status() == QTextStream::WriteFailed) {
            QMessageBox::warning(this, "Warning", "Couldn't write log file");
        }
        file.close();
    }
}

void LogWindow::triggered_action_close() {
    this->hide();
}

void LogWindow::triggered_action_clearLog() {
    this->clearLogs();
}
