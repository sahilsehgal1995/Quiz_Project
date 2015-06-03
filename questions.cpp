#include "questions.h"
#include "ui_questions.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <cstdlib>
#include <QDebug>

void Questions::connection_close()
{
    QuestionsDatabase.close();
    QuestionsDatabase.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Questions::connection_open()
{
    if(QuestionsDatabase.open())
    {
        ui->DatabaseStatus->setText("Connected");
        return true;
    }
    else
    {
        ui->DatabaseStatus->setText("Disconnected");
        return false;
    }
}

Questions::Questions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Questions)
{
    ui->setupUi(this);
    QuestionsDatabase = QSqlDatabase::addDatabase("QSQLITE");
    QuestionsDatabase.setDatabaseName("/home/sahil/qt/sequel/Sequel/questionare.db");

    if(!connection_open())
    QMessageBox::warning(this,"Warning","Database not connected");
    ui->groupBox->setHidden(true);
    ui->MarkAnswer->setHidden(true);
    ui->CorrectAnswer->setHidden(true);
}

Questions::~Questions()
{
    delete ui;
}

void Questions::on_StartTest_pressed()
{
    ui->StartTest->setVisible(false);
    ui->MarkAnswer->setHidden(false);
    if(!connection_open())
    QMessageBox::warning(this,"Warning","Database not connected");

    ui->groupBox->setHidden(false);

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(QuestionsDatabase);

    int number=4;
    int randomValue =rand() %number;
    QString id = QString::number(randomValue);

    query->prepare("select * from questions where id = '"+ id +"';");

    if(query->exec())
    {
        while(query->next())
        {
            ui->Question->setText(query->value(1).toString());
            ui->OptionA->setText(query->value(2).toString());
            ui->OptionB->setText(query->value(3).toString());
            ui->OptionC->setText(query->value(4).toString());
            ui->OptionD->setText(query->value(5).toString());
            ui->CorrectAnswer->setText(query->value(6).toString());
        }
    }
    model->setQuery(*query);

}

void Questions::on_tableView_clicked(const QModelIndex &index)
{
    ui->groupBox->setHidden(false);
    QString id = ui->tableView->model()->data(index).toString();
    if(!connection_open())
    QMessageBox::warning(this,"Warning","Database not connected");

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(QuestionsDatabase);

    query->prepare("select * from questions where id ='"+id+"';");
    if(query->exec())
    {
        while(query->next())
        {
            ui->Question->setText(query->value(1).toString());
            ui->OptionA->setText(query->value(2).toString());
            ui->OptionB->setText(query->value(3).toString());
            ui->OptionC->setText(query->value(4).toString());
            ui->OptionD->setText(query->value(5).toString());
        }
    }
    model->setQuery(*query);
}

void Questions::on_MarkAnswer_clicked()
{
    QString answer, correctanswer;
    correctanswer = ui->CorrectAnswer->text();
    if(ui->OptionA->isChecked())
    {
        answer= ui->OptionA->text();
        if (QString::compare(correctanswer, answer, Qt::CaseInsensitive))
            qDebug()<<"Option A is correct";
    }
    else if(ui->OptionB->isChecked())
    {
        answer= ui->OptionB->text();
        if (QString::compare(correctanswer, answer, Qt::CaseInsensitive))
            qDebug()<<"Option B is correct";
    }
    else if(ui->OptionC->isChecked())
    {
        answer= ui->OptionC->text();
        if (QString::compare(correctanswer, answer, Qt::CaseInsensitive))
            qDebug()<<"Option C is correct";
    }
    else if(ui->OptionD->isChecked())
    {
        answer= ui->OptionD->text();
        if (QString::compare(correctanswer, answer, Qt::CaseInsensitive))
            qDebug()<<"Option D is correct";
    }
    else
        QMessageBox::information(this,"Answer Status","Wrong Answer");

    on_StartTest_pressed();
}

void Questions::on_EndTest_clicked()
{
    this->close();
}
