#include "gui/mainwindow.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QFile file(":DarkMaroon.qss");
    
    app.setStyle("Fusion");
    
    if (file.exists()) {
        file.open(QFile::ReadOnly);
        if (file.isOpen()) {
            app.setStyleSheet(QString::fromLatin1(file.readAll()));
            file.close();
        }
    } else {
        app.setStyleSheet("");
    }

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}