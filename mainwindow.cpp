#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel> 
#include "maingamescreen.h"
#include <QLabel>
#include "game_state.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      stackedWidget(new QStackedWidget(this)),
      nextButton(new QPushButton("Next", this)),
      screenLabel(new QLabel("Start Screen", this))
{
    /*Adds three game screens to stacked widget*/
    stackedWidget->addWidget(createStartScreen());
    stackedWidget->addWidget(createMainScreen());
    stackedWidget->addWidget(createEndScreen());
    nextButton->hide();
    screenLabel->hide();
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
/*Creates and returns a QWidget for the start screen*/
QWidget *MainWindow::createStartScreen()
{
    // Create the main layout
    QVBoxLayout *layout = new QVBoxLayout;

    // Create the header label with desired text
    QLabel *headerLabel = new QLabel("Welcome to the Online Ramsey Game on K<sub>6</sub>", this);
    QFont font = headerLabel->font();
    font.setPointSize(18); // Set the desired font size
    headerLabel->setFont(font);
    headerLabel->setAlignment(Qt::AlignCenter); // Center the text

    // Load images
    QPixmap leftImage("Images/Builder.png");
    QPixmap rightImage("Images/Painter.png");
    leftImage = leftImage.scaled(100, 100, Qt::KeepAspectRatio);
    rightImage = rightImage.scaled(100, 100, Qt::KeepAspectRatio);
    QLabel *leftImageLabel = new QLabel(this);
    QLabel *rightImageLabel = new QLabel(this);
    leftImageLabel->setPixmap(leftImage);
    rightImageLabel->setPixmap(rightImage);

    // Create a horizontal layout for the header
    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->addStretch();
    headerLayout->addWidget(leftImageLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(headerLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(rightImageLabel);
    headerLayout->addStretch();
    // Add header layout to main layout
    layout->addLayout(headerLayout);

    QLabel *firstNumberLabel = new QLabel("Red Path Size For Painter To Avoid:", this);
    QLabel *secondNumberLabel = new QLabel("Blue Cycle Size For Painter To Avoid:", this);

    QWidget *startScreenWidget = new QWidget(this);

    firstNumberSpinBox = new QSpinBox(this);
    firstNumberSpinBox->setRange(3, 6); //RED PATH

    secondNumberSpinBox = new QSpinBox(this);
    secondNumberSpinBox->setRange(3, 6); //BLUE CYCLE

    firstNumberSpinBox->setFixedSize(100,50);
    secondNumberSpinBox->setFixedSize(100,50);

    QPushButton *confirmButton = new QPushButton("Confirm", this);
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(handleConfirmButton()));
    
    QHBoxLayout *firstNumberLayout = new QHBoxLayout;
    firstNumberLayout->addWidget(firstNumberLabel);
    firstNumberLayout->addWidget(firstNumberSpinBox);

    QHBoxLayout *secondNumberLayout = new QHBoxLayout;
    secondNumberLayout->addWidget(secondNumberLabel);
    secondNumberLayout->addWidget(secondNumberSpinBox);

    layout->addLayout(firstNumberLayout);
    layout->addLayout(secondNumberLayout);
    layout->addWidget(confirmButton);
    
    startScreenWidget->setLayout(layout);
    return startScreenWidget;
}
/*Function to set the sizes of G1 and G2*/
void MainWindow::handleConfirmButton()
{
    G1_size = firstNumberSpinBox->value();
    G2_size = secondNumberSpinBox->value();
    game.setG1Size(G1_size);
    game.setG2Size(G2_size);
    int currentIndex = stackedWidget->currentIndex();
    stackedWidget->setCurrentIndex(currentIndex + 1);
}
/*Sets labels displayed on the end game screen once a path or cycle has been found*/
void MainWindow::handleEndGame() {
    pathLabel->setText(QString::fromStdString(game.getEndGameString()));
    turnsLabel->setText("Number of Turns: "+ QString::number(game.getTurnNumber()-1));
    if(game.getTurnNumber() == 16 && game.getEndGameString() == ""){
        
    	turnsLabel->setText("A tie! All edges have been colored in 15 turns ");
    }
    stackedWidget->setCurrentIndex(2);  
}

/*Creates and returns a QWidget for the main game screen*/
QWidget* MainWindow::createMainScreen() {
    mainScreen = new MainGameScreen(&game, this);
    connect(mainScreen, SIGNAL(gameEnded()), this, SLOT(handleEndGame()));
    return mainScreen;
}
/*Creates and returns a QWidget for the end game screen*/
QWidget* MainWindow::createEndScreen() {
    QWidget *endScreenWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    pathLabel = new QLabel(this);
    turnsLabel = new QLabel(this);

    QPushButton *resetButton = new QPushButton("Reset", this);
    connect(resetButton, SIGNAL(clicked()), this, SLOT(handleResetButton()));

    layout->addWidget(pathLabel);
    layout->addWidget(turnsLabel);
    layout->addWidget(resetButton);

    endScreenWidget->setLayout(layout);
    return endScreenWidget;
}


/*Function to reset the game after user clicks the reset button*/
void MainWindow::handleResetButton() {
    game.resetGameState();
    mainScreen->clearLines();
    stackedWidget->setCurrentIndex(0);
    screenLabel->setText("Start Screen");
}



