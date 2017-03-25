#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TimeThread.h"
#include "QTWordSearch.h"
#include "newgame.h"
#include "highscores.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void startGame();

    void on_actionNew_Game_triggered();

    //void on_actionHigh_Scores_triggered();

    void on_actionExit_triggered();

    void on_actionEasy_triggered();

    void on_actionMedium_triggered();

    void on_actionHard_triggered();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    Ui::MainWindow *ui;
    TimeThread* windowUpdater;
    QTWordSearch* myWordSearch;
    NewGame* newGameDialog;
    HighScores* easyHiScores;
    HighScores* mediumHiScores;
    HighScores* hardHiScores;
    int difficulty;



};

#endif // MAINWINDOW_H
