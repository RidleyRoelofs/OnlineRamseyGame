#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel> // Include QLabel
#include "maingamescreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      stackedWidget(new QStackedWidget(this)),
      nextButton(new QPushButton("Next", this)),
      screenLabel(new QLabel("Start Screen", this))
{
    stackedWidget->addWidget(createStartScreen());
    stackedWidget->addWidget(createMainScreen());
    stackedWidget->addWidget(createEndScreen());

    connect(nextButton, SIGNAL(clicked()), this, SLOT(handleButton()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(screenLabel); 
    layout->addWidget(stackedWidget);
    layout->addWidget(nextButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleButton()
{
    int currentIndex = stackedWidget->currentIndex();
    if(currentIndex < stackedWidget->count() - 1) {
        stackedWidget->setCurrentIndex(currentIndex + 1);
    }
    else {
        stackedWidget->setCurrentIndex(0);
    }

    if (currentIndex == 0) {
        screenLabel->setText("Main Screen");
    } else if (currentIndex == 1) {
        screenLabel->setText("End Screen");
    } else {
        screenLabel->setText("Start Screen");
    }
}
// Create and return a new QWidget for the start screen
QWidget *MainWindow::createStartScreen()
{
    return new QWidget(this);
}

// Create and return a new QWidget for the main screen
QWidget *MainWindow::createMainScreen()
{
    return new MainGameScreen(this);
}
// Create and return a new QWidget for the end screen
QWidget *MainWindow::createEndScreen()
{
    return new QWidget(this);
}

