#include "newgame.h"
#include "ui_newgame.h"
#include <sstream>
#include <string>

NewGame::NewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);
    connect(ui->StartButton,SIGNAL(clicked()),this,SLOT(sendStart()));
}

QString NewGame::getFileName()const
{
    return ui->fileNameEdit->text();
}

int NewGame::getMaxWords()const
{
    return ui->MaxWordsSpinBox->value();
}

void NewGame::sendStart()
{
    startTheGame();
}

int NewGame::getWidth()const
{
    return ui->WidthSpinBox->value();
}

int NewGame::getHeight()const
{
    return ui->HeightSpinBox->value();
}

bool NewGame::getHints()const
{
    return ui->HintsCheckBox->isChecked();
}

void NewGame::setSeed(const unsigned long inSeed)
{
    std::ostringstream oss;
    oss << inSeed;
    ui->SeedText->setText(QString(oss.str().c_str()));
}

unsigned long NewGame::getSeed()const
{
    return ui->SeedText->text().toLong();
}

NewGame::~NewGame()
{
    delete ui;
}
