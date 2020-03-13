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
#include "../interface/Interface.h"


class MainWindow : public QMainWindow {

public:
    MainWindow(int windowWidth, int windowHeight, int MPR, Interface &interface, QWidget *parent = nullptr);
    ~MainWindow() final;
    void createRocket(int xPos, int yPos, const std::vector<b2Vec2> &body);
    void createGround(int yPos, int width);
    void setMPR(int ratio); // set meters to pixels ratio i.e. how many pixels will represent a meter
    Rocket* getRocket();
    bool event(QEvent *event) override;

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_graphicsView;
    Rocket *m_rocket;
    void m_stepUpGraphicsView();
    int m_MPR; // meters to pixels ratio
    int m_windowWidth;
    int m_windowHeight;
    Interface &m_interface;
    int scaleMPR(int meters);
};


#endif //RSLR_MAINWINDOW_H
