#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include <QWidget>
#include <QPushButton>

class MainGameScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainGameScreen(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;
    void updateNodesPosition();

private:
    std::vector<QPushButton*> nodes;
};

#endif // MAINGAMESCREEN_H

