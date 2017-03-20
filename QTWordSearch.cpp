#include "QTWordSearch.h"
#include <iostream>
#include <sstream>
#include "QMainWindow"
using namespace std;

QTWordSearch::QTWordSearch(const int inSizeY,const int inSizeX,const int inSeed) : WordSearch(inSizeY,inSizeX,inSeed)
{
    boxSize = 30;
    isMouseDown = false;
    start = std::chrono::system_clock::now();
}

QTWordSearch::~QTWordSearch()
{

}

void QTWordSearch::draw()
{
    QPainter thePainter(theWindow);
    QPen thePen;
    QBrush theBrush;
    thePen.setStyle(Qt::SolidLine);
    thePen.setWidth(2);
    QColor theColor;
    theColor.setRgb(0,0,155);
    thePen.setColor(theColor);
    thePainter.setPen(thePen);
    for(int i = 0;i <= sizeX;i++)
    {
        thePainter.drawLine(40+i*boxSize,40,40+i*boxSize,40+sizeY*boxSize);
    }
    for(int i = 0;i <= sizeY;i++)
    {
        thePainter.drawLine(40,40+i*boxSize,40+sizeX*boxSize,40+i*boxSize);
    }
    theColor.setRgb(0,0,0);
    thePen.setColor(theColor);
    thePainter.setPen(thePen);
    for(int i = 0;i < sizeY;i++)
    {
        for(int j = 0;j < sizeX;j++)
        {
            thePainter.drawText(50+j*boxSize,60+i*boxSize,QString(charArray[i][j]));
        }
    }
    for(int i = 0;i < unFoundWords.size();i++)
    {

        thePainter.drawText(60+sizeX*boxSize,60+i*25,QString((*unFoundWords[i]).c_str()));
    }

    for(int i = 0;i < highlights.size();i++)
    {
        theColor.setRgb(highlights[i].red,highlights[i].green,highlights[i].blue);
        theColor.setAlpha(64);
        thePen.setColor(theColor);
        thePen.setWidth(20);
        thePainter.setPen(thePen);
        thePainter.drawLine(highlights[i].startX,highlights[i].startY,highlights[i].endX,highlights[i].endY);
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::ostringstream strs;
    strs << "Time: " << (double)floor(seconds.count()) << "" << "s";
    string str = strs.str();
    theColor.setRgb(255,0,0);
    QFont theFont;
    theFont.setPointSize(16);
    thePainter.setFont(theFont);
    thePen.setColor(theColor);
    thePainter.setPen(thePen);
    thePainter.drawText(60,90+boxSize*sizeY,QString(str.c_str()));
    std::ostringstream remaining;
    remaining << "Remaining: " << unFoundWords.size();
    string remainString = remaining.str();
    thePainter.drawText(300,90+boxSize*sizeY,QString(remainString.c_str()));
    if(isMouseDown)
    {
        if(mouseDownX > 40 && mouseDownX < 40+sizeX*boxSize && mouseDownY > 40 && mouseDownY < 40+sizeY*boxSize)
        {
            theColor.setRgb(60,200,60);
            theColor.setAlpha(128);
            thePen.setColor(theColor);

            theBrush.setColor(theColor);
            theBrush.setStyle(Qt::SolidPattern);
            thePainter.setBrush(theBrush);
            thePen.setWidth(20);
            thePainter.setPen(thePen);
            int tempX = floor((mouseDownX-40)/boxSize)*boxSize+boxSize/2+40;
            int tempY = floor((mouseDownY-40)/boxSize)*boxSize+boxSize/2+40;
            int endX = floor((mouseMoveX-40)/boxSize)*boxSize+boxSize/2+40;
            int endY = floor((mouseMoveY-40)/boxSize)*boxSize+boxSize/2+40;
            if(abs(endX-tempX)==abs(endY-tempY) || abs(endX-tempX) ==0 || abs(endY-tempY)== 0)
            {
                thePainter.drawLine(tempX,tempY,endX,endY);
            }
            else
            {
                theColor.setRgb(200,60,60);
                theColor.setAlpha(128);
                thePen.setColor(theColor);

                thePainter.setPen(thePen);
                thePainter.drawLine(tempX,tempY,endX,endY);
            }
        }

    }
}

void QTWordSearch::mouseDown(const int inLocX, const int inLocY)
{
    if(inLocX > 40 && inLocX < 40+sizeX*boxSize && inLocY > 40 && inLocY < 40+sizeY*boxSize)
    {
        isMouseDown = true;
        mouseDownX = inLocX;
        mouseDownY = inLocY;
    }
}

void QTWordSearch::mouseMove(const int inLocX,const int inLocY)
{
    if(isMouseDown)
    {
        mouseMoveX = inLocX;
        mouseMoveY = inLocY;
        theWindow->update();
    }
}

void QTWordSearch::mouseRelease()
{
    if(isMouseDown)
    {
        isMouseDown = false;
        int tempX = floor((mouseDownX-40)/boxSize)*boxSize+boxSize/2+40;
        int tempY = floor((mouseDownY-40)/boxSize)*boxSize+boxSize/2+40;
        int endX = floor((mouseMoveX-40)/boxSize)*boxSize+boxSize/2+40;
        int endY = floor((mouseMoveY-40)/boxSize)*boxSize+boxSize/2+40;
        int startLocX = (mouseDownX-40)/boxSize;
        int startLocY = (mouseDownY-40)/boxSize;
        int endLocX = (mouseMoveX-40)/boxSize;
        int endLocY = (mouseMoveY-40)/boxSize;
        bool matchFound = false;
        if(abs(endX-tempX)==abs(endY-tempY) || abs(endX-tempX) ==0 || abs(endY-tempY)== 0)
        {

            if(endX-tempX>0 && endY-tempY==0)
            {
                if(checkForMatch(0,startLocY,startLocX,abs(endLocX-startLocX)+1))
                {
                    matchFound = true;
                }
            }
            if(endX-tempX>0 && endY-tempY>0)
            {
                if(checkForMatch(1,startLocY,startLocX,abs(endLocX-startLocX)+1))
                {
                    matchFound = true;
                }
            }
            if(endX-tempX==0 && endY-tempY>0)
            {
                if(checkForMatch(2,startLocY,startLocX,abs(endLocY-startLocY)+1))
                {
                    matchFound = true;
                }
            }
            if(endX-tempX<0 && endY-tempY>0)
            {
                if(checkForMatch(3,startLocY,startLocX,abs(endLocY-startLocY)+1))
                {
                    matchFound = true;
                }
            }
            if(endX-tempX<0 && endY-tempY==0)
            {
                if(checkForMatch(4,startLocY,startLocX,abs(endLocX-startLocX)+1))
                {
                    matchFound = true;
                }
            }
            if(endX-tempX<0 && endY-tempY<0)
            {
                if(checkForMatch(5,startLocY,startLocX,abs(endLocX-startLocX)+1))
                {
                    matchFound = true;
                }
            }
            if(endX-tempX==0 && endY-tempY<0)
            {
                if(checkForMatch(6,startLocY,startLocX,abs(endLocY-startLocY)+1))
                {
                    matchFound = true;
                }
            }
            if(endX-tempX>0 && endY-tempY<0)
            {
                if(checkForMatch(7,startLocY,startLocX,abs(endLocX-startLocX)+1))
                {
                    matchFound = true;
                }
            }

            if(matchFound)
            {
                random_device rd;
                default_random_engine generator(rd());
                uniform_int_distribution<int> distribution(100,175);
                int randomRed = distribution(generator);
                int randomGreen = distribution(generator);
                int randomBlue = distribution(generator);
                wordHighlight temp;
                temp.startX = tempX;
                temp.startY = tempY;
                temp.endX = endX;
                temp.endY = endY;
                temp.red = randomRed;
                temp.green = randomGreen;
                temp.blue = randomBlue;
                highlights.push_back(temp);
            }




        }
        theWindow->update();

    }
}

void QTWordSearch::setWindow(QMainWindow* inWindow)
{
    theWindow = inWindow;
}
