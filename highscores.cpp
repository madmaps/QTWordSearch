#include "highscores.h"
#include "ui_highscores.h"
#include <fstream>
#include <sstream>

HighScores::HighScores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighScores)
{
    ui->setupUi(this);
}

void HighScores::gameCompleted(const std::chrono::time_point<chrono::_V2::system_clock> &inDate, const std::chrono::duration<double> &inTime)
{
    lastWinDate = new std::chrono::time_point<chrono::_V2::system_clock>(inDate);
    lastWinTime = new std::chrono::duration<double>(inTime);
    ui->HighScoreOkButton->setEnabled(true);
    ui->scoreName->setEnabled(true);
    std::ostringstream strs;
    strs << "Time: " << (double)floor(lastWinTime->count()) << "" << "s";
    string str = strs.str();
    ui->ScoreLabel->setText(QString(str.c_str()));
}

HighScores::~HighScores()
{
    delete ui;
}

void HighScores::on_HighScoreOkButton_clicked()
{
    ui->HighScoreOkButton->setDisabled(true);
    ui->scoreName->setDisabled(true);
    Score tempScore(ui->scoreName->text().toStdString(),*lastWinDate,*lastWinTime);
    ui->scoreName->setText(QString(""));

    topScores.push_back(tempScore);
    sort(topScores.begin(),topScores.end());

    ui->listWidget->clear();
    for(Score insert:topScores)
    {
        ui->listWidget->addItem(QString(insert.getScore().c_str()));
    }
}

bool HighScores::loadScores(const string &inFileName)
{
    ifstream inFile;
    inFile.open(inFileName);
    string line;
    int tempMonth,tempDay,tempYear;
    string tempName;
    int tempTime;
    while(getline(inFile,line))
    {
        tempMonth = std::stoi(line);
        getline(inFile,line);
        tempDay = std::stoi(line);
        getline(inFile,line);
        tempYear = std::stoi(line);
        getline(inFile,line);
        tempName.assign(line);
        getline(inFile,line);
        tempTime = std::stoi(line);
        topScores.push_back(Score(tempName,tempMonth,tempDay,tempYear,tempTime));
    }
    for(Score insert:topScores)
    {
        ui->listWidget->addItem(QString(insert.getScore().c_str()));
    }
    inFile.close();
    return true;
}

bool HighScores::saveScores(const string &inFileName)
{
    ofstream outFile;
    outFile.open(inFileName);
    for(Score current:topScores)
    {
        outFile << current.toFile();
    }
    outFile.close();
    return true;
}
