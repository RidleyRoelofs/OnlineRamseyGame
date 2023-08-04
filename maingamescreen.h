#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QWidget>
#include <QSpinBox>
class MainGameScreen : public QWidget {
    Q_OBJECT

public:
    explicit MainGameScreen(QWidget *parent = nullptr);
    ~MainGameScreen();

private slots:
    void drawRedLine();
    void drawBlueLine();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *drawRedLineButton;
    QPushButton *drawBlueLineButton;
    QSpinBox *firstNodeSpinBox;
    QSpinBox *secondNodeSpinBox;
    std::vector<QGraphicsEllipseItem*> nodes;
};

#endif // MAINGAMESCREEN_H

