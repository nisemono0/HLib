#include "gui/mainwindow.h"
#include "gui/logwindow.h"
#include "utils/logging.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    app.setStyle("Fusion");

    MainWindow mainWin;

    Logging::setLoggerWindow(&mainWin);

    mainWin.setWindowFlag(Qt::Dialog);
    mainWin.show();

    return app.exec();
}