//
// Created by Matthew Round on 03/03/2020.
//

#include "MainWindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_scene = new QGraphicsScene(this);
    m_graphicsView = new QGraphicsView(this);
    m_stepUpGraphicsView();
    m_rocket = new Rocket();
    m_scene->addItem(m_rocket);
}

void MainWindow::m_stepUpGraphicsView() {
    m_graphicsView->setRenderHint(QPainter::Antialiasing);
    m_graphicsView->setScene(m_scene);
    m_graphicsView->setSceneRect(0, 0, this->width(), this->height());
    m_graphicsView->setFixedSize(this->width(), this->height());
    m_graphicsView->fitInView(0, 0, this->width(), this->height(), Qt::KeepAspectRatio);
}

MainWindow::~MainWindow() {
    delete m_rocket;
    delete m_graphicsView;
    delete m_scene;
}
