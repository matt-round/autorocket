// std includes
#include <iostream>
#include <string>
// Qt includes
#include <QApplication>
#include <QLabel>
#include <QWidget>
#include "env/gui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.setMinimumSize(500, 500);
    w.show();
    return app.exec();
}