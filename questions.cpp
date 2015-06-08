#include "questions.h"
#include "ui_questions.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <cstdlib>
#include <QTime>
#include <QTimer>
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
    ui->questionlist->setHidden(true);
    ui->QuestionListLabel->setHidden(true);

    mytimer = new QTimer(this);

    minutes = 5;
    seconds = 0;
    i = -1;
    timevalue = new QTime(0,5,0,0);

    QString val= timevalue->toString();
    ui->ledNumber->display(val);

    connect(mytimer, SIGNAL(timeout()),this, SLOT(timeoutslot()));
    QuestionList();
}

Questions::~Questions()
{
    delete ui;
}

void Questions::QuestionList()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int count=10, i=1;
    while(count){
        int x = qrand() % ((40 + 1) - 1) + 1;
        int index = qlist.indexOf(x);
        if(index==-1)
        {
            qlist.append(x);
            QString string = QString("Question %1").arg(i++);
            QuestionMapping[string]= x;
            ui->questionlist->addItem(string);
            count--;
        }
    }
}

void Questions::on_StartTest_pressed()
{

    if(!connection_open())
    QMessageBox::warning(this,"Warning","Database not connected");
    else
    {
        ui->StartTest->setVisible(false);
        ui->MarkAnswer->setHidden(false);
        ui->groupBox->setHidden(false);
        ui->questionlist->setHidden(false);
        ui->QuestionListLabel->setVisible(true);
        mytimer->start(1000);
    }

}

void Questions::on_MarkAnswer_clicked()
{
    QListWidgetItem *itm = ui->questionlist->currentItem();
    itm->setBackgroundColor(Qt::green);
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

void Questions::timeoutslot()
{
    QTime TimeChange, TimeOver;
    TimeOver.setHMS(0,0,0,0);
    TimeChange.setHMS(0,minutes,seconds,0);
    TimeChange = TimeChange.addSecs(i);
    if(TimeChange.toString() == TimeOver.toString())
    {
        on_EndTest_clicked();
    }
    else
    {
        QString val = TimeChange.toString();
        ui->ledNumber->display(val);
        i = i-1;
    }
}

void Questions::on_questionlist_itemSelectionChanged()
{
    if(!connection_open())
    QMessageBox::warning(this,"Warning","Database not connected");

    QListWidgetItem *itm = ui->questionlist->currentItem();
    int val = QuestionMapping.value(itm->text());

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(QuestionsDatabase);

    QString id = QString::number(val);

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
