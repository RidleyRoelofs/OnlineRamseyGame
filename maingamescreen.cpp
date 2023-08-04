#include <cmath>
#include "maingamescreen.h"
#include <QGraphicsLineItem>
#include <QVBoxLayout>

MainGameScreen::MainGameScreen(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    drawLineButton = new QPushButton("Draw line", this);

    // Adds "nodes" to the screen in a circular configuration
    for (int i = 0; i < 6; i++) {
        QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 20, 20);
        node->setPos(100 * cos(i * M_PI / 3.0), 100 * sin(i * M_PI / 3.0));
        nodes.push_back(node);
    }

    connect(drawLineButton, SIGNAL(clicked()), this, SLOT(drawLine()));


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(drawLineButton);
    setLayout(layout);
}

MainGameScreen::~MainGameScreen() {}
// Draws a line connecting the first and second node, will update this to draw a line between specified nodes
void MainGameScreen::drawLine() {
    if(nodes.size() >= 2) {
        QPointF point1 = nodes[0]->pos();
        QPointF point2 = nodes[1]->pos();

        scene->addLine(point1.x(), point1.y(), point2.x(), point2.y(), QPen(Qt::black));
    }
}


