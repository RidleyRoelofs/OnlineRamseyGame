#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QSpinBox>
#include "game_state.hpp"
#include "maingamescreen.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleButton();
    void handleConfirmButton();
    void handleEndGame(); 
    void handleResetButton();

private:
    Game_State game;
    int G1_size;
    int G2_size;
    MainGameScreen* mainScreen;
    QStackedWidget *stackedWidget;
    QPushButton *nextButton;
    QSpinBox *firstNumberSpinBox;  
    QSpinBox *secondNumberSpinBox; 
    QLabel *screenLabel;
    QWidget *createStartScreen();
    QWidget *createMainScreen();
    QWidget *createEndScreen();
    QLabel *pathLabel;
    QLabel *turnsLabel;
};

#endif // MAINWINDOW_H

