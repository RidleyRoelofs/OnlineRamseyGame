#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleButton();

private:
    QStackedWidget *stackedWidget;
    QPushButton *nextButton;
    QLabel *screenLabel;
    QWidget *createStartScreen();
    QWidget *createMainScreen();
    QWidget *createEndScreen();
};

#endif // MAINWINDOW_H

