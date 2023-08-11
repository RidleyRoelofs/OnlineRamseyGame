#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QWidget>
#include <QSpinBox>
#include "game_state.hpp"

class MainGameScreen : public QWidget {
    Q_OBJECT

public:
    explicit MainGameScreen(Game_State* game, QWidget *parent = nullptr);
    ~MainGameScreen();
    void clearLines();
signals:
    void gameEnded(); 
    
private slots:
    void drawRedLine();
    void drawBlueLine();
    void checkEndCondition();
    void endTurnHandler();
    void setButtonColor(QPushButton*,const QColor&);

private:
    bool edge_drawn = false;
    QVector<QGraphicsLineItem*> lines;
    QGraphicsPixmapItem *playerImage;
    QPixmap builderImage;
    QPixmap painterImage;
    QPixmap builderPixel;
    QPixmap painterPixel;
    Game_State* game;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *drawRedLineButton;
    QPushButton *drawBlueLineButton;
    QPushButton *endTurnButton;
QPushButton *checkEndConditionButton;
    QSpinBox *firstNodeSpinBox;
    QSpinBox *secondNodeSpinBox;
    std::vector<QGraphicsEllipseItem*> nodes;
};

#endif // MAINGAMESCREEN_H

