#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QSpinBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleButton();
    void handleConfirmButton();

private:
    int G1_size;
    int G2_size;
    QStackedWidget *stackedWidget;
    QPushButton *nextButton;
    QSpinBox *firstNumberSpinBox;  
    QSpinBox *secondNumberSpinBox; 
    QLabel *screenLabel;
    QWidget *createStartScreen();
    QWidget *createMainScreen();
    QWidget *createEndScreen();
};

#endif // MAINWINDOW_H

