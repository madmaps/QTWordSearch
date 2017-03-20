#ifndef __QTWORDSEARCH__
#define __QTWORDSEARCH__
#include "wordSearch.h"
#include "QPainter"
#include "QMainWindow"
#include <vector>
#include <chrono>

class QTWordSearch : public WordSearch
{
	public:
	QTWordSearch(const int inSizeY,const int inSizeX,const int inSeed);
    ~QTWordSearch();
    void setWindow(QMainWindow* inWindow);
	virtual void draw();
    void mouseDown(const int inLocX,const int inLocY);
    void mouseMove(const int inLocX,const int inLocY);
    void mouseRelease();

private:
    QMainWindow* theWindow;
    int boxSize;
    bool isMouseDown;
    int mouseDownX;
    int mouseDownY;
    int mouseMoveX;
    int mouseMoveY;


    struct wordHighlight
    {
        int startX;
        int startY;
        int endX;
        int endY;
        int red;
        int green;
        int blue;
    };
    vector<wordHighlight> highlights;
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
};


#endif
