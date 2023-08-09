#include <cmath>
#include "maingamescreen.h"
#include <QGraphicsLineItem>
#include <QVBoxLayout>
#include <algorithm>
#include<iostream>
#include <QPainter>


MainGameScreen::MainGameScreen(Game_State* game,QWidget *parent) : QWidget(parent), game(game)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    int viewWidth = view->viewport()->width();
    int viewHeight = view->viewport()->height();
    
    builderImage.load("Images/Builder.png");
    painterImage.load("Images/Painter.png");
    builderPixel = builderImage.scaled(100, 100, Qt::KeepAspectRatio);
    painterPixel = painterImage.scaled(100, 100, Qt::KeepAspectRatio);
    playerImage= new QGraphicsPixmapItem(builderPixel);
    scene->addItem(playerImage);
    QPointF topRightScene = view->mapToScene(viewWidth -builderPixel.width(), 0);
    playerImage->setPos(topRightScene);
    view->setRenderHint(QPainter::Antialiasing);
    drawRedLineButton = new QPushButton("Draw Red line", this);
    drawBlueLineButton = new QPushButton("Draw Blue line", this);
    checkEndConditionButton = new QPushButton("Check Path and Cycle", this);
    endTurnButton = new QPushButton("End Turn", this);
    endTurnButton->setFixedSize(100,50);
    setButtonColor(drawRedLineButton, Qt::red);
    setButtonColor(drawBlueLineButton, Qt::blue);
    setButtonColor(endTurnButton, Qt::green);
    firstNodeSpinBox = new QSpinBox(this);
    firstNodeSpinBox->setRange(1, 6);

    secondNodeSpinBox = new QSpinBox(this);
    secondNodeSpinBox->setRange(1, 6);
    firstNodeSpinBox->setFixedSize(100,50);
    secondNodeSpinBox->setFixedSize(100,50);
    drawRedLineButton->setFixedSize(100,50);
    drawBlueLineButton->setFixedSize(100,50);
    checkEndConditionButton->setFixedSize(100,100);
    
    const int node_radius = 120;
    const int label_offset = 20;
    for (int i = 0; i < 6; i++) {
        QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 20, 20);
        node->setPos(node_radius * cos(i * M_PI / 3.0), node_radius * sin(i * M_PI / 3.0));
        QBrush brush(Qt::black);
        node->setBrush(brush);
        nodes.push_back(node);
        double labelX = (node_radius + label_offset)*cos(i * M_PI / 3.0);
	double labelY = (node_radius + label_offset) * sin(i * M_PI / 3.0);
	QGraphicsTextItem *label = scene->addText(QString::number(i + 1));
	label->setPos(labelX, labelY);
    }

    connect(drawRedLineButton, SIGNAL(clicked()), this, SLOT(drawRedLine()));
    connect(drawBlueLineButton, SIGNAL(clicked()), this, SLOT(drawBlueLine()));
    connect(checkEndConditionButton, SIGNAL(clicked()), this, SLOT(checkEndCondition()));
    connect(endTurnButton, SIGNAL(clicked()), this, SLOT(endTurnHandler()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);

    QHBoxLayout *middleLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(firstNodeSpinBox);
    leftLayout->addWidget(secondNodeSpinBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(drawRedLineButton);
    rightLayout->addWidget(drawBlueLineButton);

    middleLayout->addLayout(leftLayout);
    middleLayout->addWidget(endTurnButton);
    middleLayout->addLayout(rightLayout);

    mainLayout->addLayout(middleLayout);
    mainLayout->addWidget(checkEndConditionButton);

    setLayout(mainLayout);
}
void MainGameScreen::setButtonColor(QPushButton* button, const QColor& color)
{
    QColor lighterColor = color.lighter(130); 
    QString qss = QString("background-color: %1").arg(lighterColor.name());
    button->setStyleSheet(qss);
}

MainGameScreen::~MainGameScreen() {}
void MainGameScreen::drawBlueLine() {
    QPointF point1 = nodes[firstNodeSpinBox->value()-1]->pos();
    QPointF point2 = nodes[secondNodeSpinBox->value()-1]->pos();
    game->addBlueEdge(std::min(firstNodeSpinBox->value()-1,secondNodeSpinBox->value()-1),std::max(firstNodeSpinBox->value()-1,secondNodeSpinBox->value()-1));

    QPen pen(Qt::blue);
    pen.setWidth(6); 
    QGraphicsLineItem* line = scene->addLine(point1.x()+10, point1.y()+10, point2.x()+10, point2.y()+10, pen);
    lines.push_back(line);
}

void MainGameScreen::checkEndCondition(){
	bool isPath = game->DFS_Check_Red();
	bool isCycle = game->DFS_Check_Blue();
	std::cout << "Path is " << isPath <<"\n"; //debug
	std::cout <<"Cycle is "<<isCycle<<"\n"; //debug
	if(isPath || isCycle) {
            emit gameEnded();
        }
}
void MainGameScreen::endTurnHandler(){
    if(game->isPaintersTurn()){
        checkEndCondition();
        game->swapTurn();
        game->incrementTurn();
        playerImage->setPixmap(builderPixel);
    } else 
    if(game->isBuildersTurn()){
        
        game->swapTurn();
        playerImage->setPixmap(painterPixel);
    }
    
}

void MainGameScreen::drawRedLine() {
    QPointF point1 = nodes[firstNodeSpinBox->value()-1]->pos();
    QPointF point2 = nodes[secondNodeSpinBox->value()-1]->pos();
    game->addRedEdge(std::min(firstNodeSpinBox->value()-1,secondNodeSpinBox->value()-1),std::max(firstNodeSpinBox->value()-1,secondNodeSpinBox->value()-1));

    QPen pen(Qt::red);
    pen.setWidth(6);

    QGraphicsLineItem* line = scene->addLine(point1.x()+10, point1.y()+10, point2.x()+10, point2.y()+10, pen);
    lines.push_back(line);
}

void MainGameScreen::clearLines() {
    for (auto line : lines) {
        scene->removeItem(line);
        delete line;
    }
    lines.clear();
}


