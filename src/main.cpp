#include "gui/mainwindow.h"
#include "gui/logwindow.h"
#include "utils/utilfuncs.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    app.setStyle("Fusion");

    MainWindow mainWin;

    Utils::log_window = new LogWindow(&mainWin);

    mainWin.show();

    return app.exec();
}