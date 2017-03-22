#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QDialog>

namespace Ui {
class HighScores;
}

class HighScores : public QDialog
{
    Q_OBJECT

public:
    explicit HighScores(QWidget *parent = 0);
    ~HighScores();

private:
    Ui::HighScores *ui;
};

#endif // HIGHSCORES_H
