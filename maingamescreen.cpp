#include "maingamescreen.h"
#include <cmath>

MainGameScreen::MainGameScreen(QWidget *parent) : QWidget(parent)
{
    for(int i = 0; i < 6; ++i) {
        QPushButton *node = new QPushButton(QString::number(i + 1), this);
        node->resize(50, 50); // set size of the buttons
        nodes.push_back(node);
    }
    updateNodesPosition();
}

void MainGameScreen::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateNodesPosition();
}

void MainGameScreen::updateNodesPosition()
{
    int radius = std::min(width(), height()) / 2 - nodes[0]->width() / 2;
    QPoint center = rect().center();
    for(int i = 0; i < nodes.size(); ++i) {
        double angle = i * 2 * M_PI / nodes.size();
        int x = center.x() + radius * std::cos(angle) - nodes[i]->width() / 2;
        int y = center.y() + radius * std::sin(angle) - nodes[i]->height() / 2;
        nodes[i]->move(x, y);
    }
}

