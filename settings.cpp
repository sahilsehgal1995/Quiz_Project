#include "settings.h"
#include "ui_settings.h"
#include <QtCore>
#include <QtGui>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    NoOfQuestions=40;
    NoOfHours=0;
    NoOfMinutes=5;
    NoOfSeconds=0;
    testquestions=10;
    ui->questions->setText(QString::number(40));
    ui->hours->setText(QString::number(0));
    ui->minutes->setText(QString::number(5));
    ui->seconds->setText(QString::number(0));
    ui->testquestions->setText(QString::number(10));
    ui->splitter_2->setHidden(true);
}

settings::~settings()
{
    delete ui;
}

void settings::on_Enter_clicked()
{
    int y=QString::compare(ui->password->text(), "uiet", Qt::CaseInsensitive);
    if(y==0)
    {
        ui->splitter_2->setHidden(false);
    }
    else
    {
        ui->splitter_2->setHidden(true);
    }
    ui->password->setText("");
}

void settings::on_buttonBox_accepted()
{
    NoOfQuestions=ui->questions->text().toInt();
    NoOfHours=ui->hours->text().toInt();
    NoOfMinutes=ui->minutes->text().toInt();
    NoOfSeconds=ui->seconds->text().toInt();
    testquestions=ui->testquestions->text().toInt();

    ui->splitter_2->setHidden(true);
}
