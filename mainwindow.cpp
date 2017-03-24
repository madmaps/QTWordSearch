#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QMouseEvent"
#include <random>
#include <fstream>


bool addWordFile(WordSearch& inWordSearch, const string inFile, const long inSeed, const int maxWords = 50);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    random_device rd;
    ui->setupUi(this);
    hiScores = new HighScores(this);
    hiScores->loadScores(".hiScores.txt");

    hiScores->hide();
    newGameDialog = new NewGame(this);
    newGameDialog->setSeed(rd());
    newGameDialog->show();
    myWordSearch = 0;
    windowUpdater = new TimeThread();
    windowUpdater->setWindow(this);
    windowUpdater->start();
    connect(newGameDialog,SIGNAL(startTheGame()),this,SLOT(startGame()));

}

MainWindow::~MainWindow()
{
    hiScores->saveScores(".hiScores.txt");
    if(windowUpdater!=0)
    {
        windowUpdater->stop();
        windowUpdater->wait();
        delete windowUpdater;
    }
    if(myWordSearch!=0)
    {
        delete myWordSearch;
    }
    delete hiScores;
    delete newGameDialog;
    delete ui;
}

void MainWindow::startGame()
{
    if(myWordSearch!=0)
    {
        delete myWordSearch;
    }
    myWordSearch = new QTWordSearch(newGameDialog->getHeight(),newGameDialog->getWidth(),newGameDialog->getSeed());
    myWordSearch->setWindow(this);
    addWordFile(*myWordSearch,newGameDialog->getFileName().toStdString().c_str(),newGameDialog->getSeed(),newGameDialog->getMaxWords());
    myWordSearch->complete();
    newGameDialog->hide();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    if(myWordSearch!=0)
    {
        myWordSearch->draw();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(myWordSearch!=0)
    {
        if(event->button()==Qt::LeftButton)
        {
            myWordSearch->mouseDown(event->x(),event->y());
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(myWordSearch!=0)
    {
         myWordSearch->mouseMove(event->x(),event->y());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    if(myWordSearch!=0)
    {
         myWordSearch->mouseRelease();
         if(myWordSearch->gameOver())
         {
             chrono::time_point<std::chrono::system_clock> tempDate = chrono::system_clock::now();
             hiScores->gameCompleted(tempDate,myWordSearch->getTime());
             hiScores->show();
         }
    }
}

bool addWordFile(WordSearch& inWordSearch,const string inFile,const long inSeed,const int maxWords)
{
    list<string> wordList;
    list<string>::iterator iter;
    int randomValue = 0;
    default_random_engine generator(inSeed);

    string line;
    ifstream myFile(inFile);
    if(myFile.is_open())
    {
        while(getline(myFile,line))
        {
            transform(line.begin(), line.end(), line.begin(), ::toupper);
            wordList.push_back(line);
        }
        int wordListSize = wordList.size();
        for(int j = 0;j < maxWords && j < wordListSize;j++)
        {
            uniform_int_distribution<int> distribution(0,wordList.size()-1);
            randomValue = distribution(generator);
            iter = wordList.begin();
            for(int i = 0;i < randomValue;i++)
            {
                iter++;
            }
            inWordSearch.addWord(*iter);
            wordList.erase(iter);
        }

    }
    return true;
}

void MainWindow::on_actionNew_Game_triggered()
{
    random_device rd;
    newGameDialog->setSeed(rd());
    newGameDialog->show();
}

void MainWindow::on_actionHigh_Scores_triggered()
{
    hiScores->show();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
