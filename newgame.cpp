#include "newgame.h"
#include "ui_newgame.h"

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

NewGame::~NewGame()
{
    delete ui;
}
