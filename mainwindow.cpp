#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QMouseEvent"
#include <random>
#include <fstream>

bool addWordFile(WordSearch& inWordSearch,const string inFile,const int inSeed,const int maxWords = 50);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newGameDialog = new NewGame(this);
    newGameDialog->show();
    random_device rd;
    myWordSearch = 0;
    windowUpdater = 0;
    //myWordSearch = new QTWordSearch(15,15,rd());
    //myWordSearch->setWindow(this);
    //addWordFile(*myWordSearch,"words.txt",rd(),100);
    //myWordSearch->complete();
    //myWordSearch->print();
    windowUpdater = new TimeThread();
    windowUpdater->setWindow(this);
    windowUpdater->start();
    connect(newGameDialog,SIGNAL(startTheGame()),this,SLOT(startGame()));

}

MainWindow::~MainWindow()
{
    if(windowUpdater!=0)
    {
        windowUpdater->stop();
        delete windowUpdater;
    }
    if(myWordSearch!=0)
    {
        delete myWordSearch;
    }
    delete newGameDialog;
    delete ui;
}

void MainWindow::startGame()
{
    if(myWordSearch!=0)
    {
        delete myWordSearch;
    }
    random_device rd;
    myWordSearch = new QTWordSearch(newGameDialog->getHeight(),newGameDialog->getWidth(),rd());
    myWordSearch->setWindow(this);
    addWordFile(*myWordSearch,newGameDialog->getFileName().toStdString().c_str(),rd(),newGameDialog->getMaxWords());
    myWordSearch->complete();
    newGameDialog->hide();
}

void MainWindow::paintEvent(QPaintEvent *event)
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

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(myWordSearch!=0)
    {
         myWordSearch->mouseRelease();
    }
}

bool addWordFile(WordSearch& inWordSearch,const string inFile,const int inSeed,const int maxWords)
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
    newGameDialog->show();
}
