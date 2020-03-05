//
// Created by Matthew Round on 03/03/2020.
//

#ifndef RSLR_MAINWINDOW_H
#define RSLR_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Rocket.h"


class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() final;


private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_graphicsView;
    Rocket *m_rocket;
    void m_stepUpGraphicsView();
};


#endif //RSLR_MAINWINDOW_H
