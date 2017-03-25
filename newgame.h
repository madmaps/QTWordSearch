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
    int getDifficutly()const;

signals:
    void startTheGame();
private slots:
    void sendStart();


    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_FileBrowserButton_clicked();

private:
    Ui::NewGame *ui;

    int difficulty;

};

#endif // NEWGAME_H
