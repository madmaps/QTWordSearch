#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QDialog>
#include <vector>
#include "Scores.h"
#include <chrono>

namespace Ui {
class HighScores;
}

class HighScores : public QDialog
{
    Q_OBJECT

public:
    explicit HighScores(QWidget *parent = 0);
    void gameCompleted(const std::chrono::time_point<chrono::_V2::system_clock> &inDate,const std::chrono::duration<double> &inTime);

    bool loadScores(const string& inFileName);
    bool saveScores(const string& inFileName);
    ~HighScores();

private slots:
    void on_HighScoreOkButton_clicked();

private:
    std::vector<Score> topScores;
    Ui::HighScores *ui;
    std::chrono::time_point<chrono::_V2::system_clock>* lastWinDate;
    std::chrono::duration<double>* lastWinTime;

};

#endif // HIGHSCORES_H
