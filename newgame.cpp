#include "newgame.h"
#include "ui_newgame.h"
#include <sstream>
#include <string>

NewGame::NewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGame)
{
    difficulty = 3;
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

int NewGame::getDifficutly()const
{
    return difficulty;
}

NewGame::~NewGame()
{
    delete ui;
}

void NewGame::on_radioButton_clicked()
{
    difficulty = 0;
    ui->HeightSpinBox->setValue(10);
    ui->WidthSpinBox->setValue(10);
    ui->MaxWordsSpinBox->setValue(10);
    ui->HintsCheckBox->setChecked(true);
    ui->HintsCheckBox->setDisabled(true);
    ui->HeightSpinBox->setDisabled(true);
    ui->WidthSpinBox->setDisabled(true);
    ui->MaxWordsSpinBox->setDisabled(true);

}

void NewGame::on_radioButton_2_clicked()
{
    difficulty = 1;
    ui->HeightSpinBox->setValue(15);
    ui->WidthSpinBox->setValue(15);
    ui->MaxWordsSpinBox->setValue(50);
    ui->HintsCheckBox->setChecked(true);
    ui->HintsCheckBox->setDisabled(true);
    ui->HeightSpinBox->setDisabled(true);
    ui->WidthSpinBox->setDisabled(true);
    ui->MaxWordsSpinBox->setDisabled(true);
}



void NewGame::on_radioButton_3_clicked()
{
    difficulty = 2;
    ui->HeightSpinBox->setValue(20);
    ui->WidthSpinBox->setValue(20);
    ui->MaxWordsSpinBox->setValue(100);
    ui->HintsCheckBox->setChecked(false);
    ui->HintsCheckBox->setDisabled(true);
    ui->HeightSpinBox->setDisabled(true);
    ui->WidthSpinBox->setDisabled(true);
    ui->MaxWordsSpinBox->setDisabled(true);
}

void NewGame::on_radioButton_4_clicked()
{
    difficulty = 3;
    ui->HintsCheckBox->setEnabled(true);
    ui->HeightSpinBox->setEnabled(true);
    ui->WidthSpinBox->setEnabled(true);
    ui->MaxWordsSpinBox->setEnabled(true);
}
