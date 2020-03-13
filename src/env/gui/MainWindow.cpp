//
// Created by Matthew Round on 03/03/2020.
//

#include "MainWindow.h"
#include "MoveRocketEvent.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QEvent>
#include "../interface/Interface.h"
#include <QKeyEvent>

#include <iostream>

MainWindow::MainWindow(int windowWidth, int windowHeight, int MPR, Interface& interface, QWidget *parent)
        : QMainWindow(parent),
          m_MPR{MPR},
          m_windowWidth{windowWidth},
          m_windowHeight{windowHeight},
          m_interface{interface} {
    this->setMinimumSize(scaleMPR(windowWidth), scaleMPR(windowHeight));
    m_scene = new QGraphicsScene(this);
    m_scene->installEventFilter(this);
    m_graphicsView = new QGraphicsView(this);
    m_stepUpGraphicsView();
    this->setStyleSheet("background-color: black;");
}

MainWindow::~MainWindow() {
    delete m_rocket;
    delete m_graphicsView;
    delete m_scene;
}

void MainWindow::m_stepUpGraphicsView() {
    m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphicsView->setRenderHint(QPainter::Antialiasing);
    m_graphicsView->setScene(m_scene);
    m_graphicsView->setSceneRect(0, 0, scaleMPR(m_windowWidth), scaleMPR(m_windowHeight));
    m_graphicsView->setFixedSize(scaleMPR(m_windowWidth), scaleMPR(m_windowHeight));
    //m_graphicsView->fitInView(0, 0, 25, 25, Qt::KeepAspectRatio);
}

void MainWindow::createGround(const int yPos, const int width) {
    QBrush greenFill = QBrush(Qt::darkBlue);
    QPen greenPen = QPen(Qt::NoPen);
    //QRect qGround = QRect(0, scaleMPR(yPos), scaleMPR(width), scaleMPR(100));
    std::cout << yPos << '\n';
    std::cout << width << '\n';
    QRect qGround = QRect(0, scaleMPR(yPos), scaleMPR(width), scaleMPR(1));
    m_scene->addRect(qGround, greenPen, greenFill);
}

void MainWindow::createRocket(const int xPos, const int yPos, const std::vector<b2Vec2> &body) {
    m_rocket = new Rocket();
    m_rocket->loadBody(body, m_MPR);
    m_scene->addItem(m_rocket);
}

Rocket* MainWindow::getRocket() {
    return m_rocket;
}

void MainWindow::setMPR(int ratio) {
    m_MPR = ratio;
}

int MainWindow::scaleMPR(int meters) {
    return meters * m_MPR;
}


void print() {
    std::cout << "Signal";
}

bool MainWindow::event(QEvent *event) {
    bool result = true;

    if(event->type() == QEvent::User) {
        auto* moveRocketEvent {reinterpret_cast<MoveRocketEvent*>(event)};
        m_rocket->moveRocket(moveRocketEvent->position, m_MPR);
        m_rocket->setAngle(moveRocketEvent->angle, m_MPR);
    } else {
        result = QMainWindow::event(event); //call direct parent's event here!
    }

    return result;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_scene) {
        if (event->type() == QEvent::KeyPress) {
            auto *keyEvent = dynamic_cast<QKeyEvent*>(event);

            enum KeyType {
                UP = 87,
                UP_ALT = 32,
                LEFT = 65,
                RIGHT = 68,
                RESET = 82
            };

            switch(keyEvent->key()) {
                case UP:
                case UP_ALT:
                    m_interface.thrust();
                    break;
                case LEFT:
                    m_interface.moveRocketLeft();
                    break;
                case RIGHT:
                    m_interface.moveRocketRight();
                    break;
                case RESET:
                    m_interface.reset();
                    break;
            }
            return true;
        } else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}
