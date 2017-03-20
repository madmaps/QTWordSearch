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
    random_device rd;
    myWordSearch = new QTWordSearch(15,15,rd());
    myWordSearch->setWindow(this);
    addWordFile(*myWordSearch,"words.txt",rd(),100);
    myWordSearch->complete();
    myWordSearch->print();
    windowUpdater = new TimeThread();
    windowUpdater->setWindow(this);
    windowUpdater->start();
}

MainWindow::~MainWindow()
{
    windowUpdater->stop();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    myWordSearch->draw();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        myWordSearch->mouseDown(event->x(),event->y());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    myWordSearch->mouseMove(event->x(),event->y());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    myWordSearch->mouseRelease();
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
