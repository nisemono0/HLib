#include "utils/logging.h"
#include "gui/logwindow.h"

#include <QWidget>
#include <QString>

void Logging::setLoggerWindow(QWidget *parent) {
    if (Logging::log_window == nullptr) {
        Logging::log_window = new LogWindow(parent);
        Logging::log_window->setWindowFlag(Qt::Dialog);
    }
}

void Logging::showLoggingWindow() {
    if (Logging::log_window != nullptr) {
        Logging::log_window->show();
    }
}

void Logging::clearLoggingWindow() {
    if (Logging::log_window != nullptr) {
        Logging::log_window->clearLogs();
    }
}

void Logging::logMessage(const QString message) {
    if (Logging::log_window != nullptr) {
        Logging::log_window->appendMessage(message);
    }
}
