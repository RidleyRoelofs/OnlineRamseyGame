#include <cmath>
#include "maingamescreen.h"
#include <QGraphicsLineItem>
#include <QVBoxLayout>

MainGameScreen::MainGameScreen(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    drawRedLineButton = new QPushButton("Draw Red line", this);
    drawBlueLineButton = new QPushButton("Draw Blue line", this);

    firstNodeSpinBox = new QSpinBox(this);
    firstNodeSpinBox->setRange(1, 6);

    secondNodeSpinBox = new QSpinBox(this);
    secondNodeSpinBox->setRange(1, 6);
    firstNodeSpinBox->setFixedSize(100,50);
    secondNodeSpinBox->setFixedSize(100,50);
    drawRedLineButton->setFixedSize(100,50);
    drawBlueLineButton->setFixedSize(100,50);

    // Adds "nodes" to the screen in a circular configuration
    for (int i = 0; i < 6; i++) {
        QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 20, 20);
        node->setPos(100 * cos(i * M_PI / 3.0), 100 * sin(i * M_PI / 3.0));
        nodes.push_back(node);
    }
    //connects the draw line button
    connect(drawRedLineButton, SIGNAL(clicked()), this, SLOT(drawRedLine()));
    connect(drawBlueLineButton, SIGNAL(clicked()), this, SLOT(drawBlueLine()));

  

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(firstNodeSpinBox);
    layout->addWidget(secondNodeSpinBox);
    layout->addWidget(drawRedLineButton);
    layout->addWidget(drawBlueLineButton);
    setLayout(layout);
}

MainGameScreen::~MainGameScreen() {}
// Draws a line connecting the first and second node, will update this to draw a line between specified nodes
void MainGameScreen::drawBlueLine() {

    QPointF point1 = nodes[firstNodeSpinBox->value()-1]->pos();
    QPointF point2 = nodes[secondNodeSpinBox->value()-1]->pos();

    scene->addLine(point1.x(), point1.y(), point2.x(), point2.y(), QPen(Qt::blue));

}

void MainGameScreen::drawRedLine() {
    QPointF point1 = nodes[firstNodeSpinBox->value()-1]->pos();
    QPointF point2 = nodes[secondNodeSpinBox->value()-1]->pos();

    scene->addLine(point1.x(), point1.y(), point2.x(), point2.y(), QPen(Qt::red));
}


