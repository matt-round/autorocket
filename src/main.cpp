// std includes
#include <iostream>
#include <string>
// Qt includes
#include <QApplication>
#include <QLabel>
#include <QWidget>
#include "env/functionaltests.cpp"
#include "env/gui/MainWindow.h"

int main(int argc, char *argv[]) {

    // if 'test' argument is passed then run tests else run application
    const std::string test {"test"};
    if(argc > 1 && test == argv[1]) {
        bool passed = functionalTests::runTests();
        std::cout << (passed ? "All tests passed" : "Tests failed");
    } else {
        QApplication app(argc, argv);
        MainWindow w;
        w.setMinimumSize(500, 500);
        w.show();
        return app.exec();
    }

    return 0;
}