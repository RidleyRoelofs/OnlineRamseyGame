#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QWidget>

class MainGameScreen : public QWidget {
    Q_OBJECT

public:
    explicit MainGameScreen(QWidget *parent = nullptr);
    ~MainGameScreen();

private slots:
    void drawLine();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *drawLineButton;
    std::vector<QGraphicsEllipseItem*> nodes;
};

#endif // MAINGAMESCREEN_H

