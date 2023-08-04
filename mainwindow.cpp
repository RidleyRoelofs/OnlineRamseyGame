#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel> 
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
    QWidget *startScreenWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    firstNumberSpinBox = new QSpinBox(this);
    firstNumberSpinBox->setRange(3, 6);

    secondNumberSpinBox = new QSpinBox(this);
    secondNumberSpinBox->setRange(3, 6);

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(handleConfirmButton()));

    layout->addWidget(firstNumberSpinBox);
    layout->addWidget(secondNumberSpinBox);
    layout->addWidget(confirmButton);

    startScreenWidget->setLayout(layout);
    return startScreenWidget;
}

void MainWindow::handleConfirmButton()
{
    G1_size = firstNumberSpinBox->value();
    G2_size = secondNumberSpinBox->value();
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

