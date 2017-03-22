#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include <QString>

namespace Ui {
class NewGame;
}

class NewGame : public QDialog
{
    Q_OBJECT

public:
    explicit NewGame(QWidget *parent = 0);
    ~NewGame();
    QString getFileName()const;
    int getMaxWords()const;
    int getWidth()const;
    int getHeight()const;
    bool getHints()const;
    void setSeed(const unsigned long inSeed);
    unsigned long getSeed()const;

signals:
    void startTheGame();
private slots:
    void sendStart();


private:
    Ui::NewGame *ui;

};

#endif // NEWGAME_H
