#include "questions.h"
#include "ui_questions.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <cstdlib>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QButtonGroup>

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
    ui->UnMarkAnswer->setHidden(true);
    ui->NextQuestion->setHidden(true);
    ui->PreviousQuestion->setHidden(true);
    NumberofQuestions=10;

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
    int count, i=1;
    count=NumberofQuestions;
    while(count){
        int x = qrand() % ((40 + 1) - 1) + 1;
        int index = qlist.indexOf(x);
        if(index==-1)
        {
            qlist.append(x);
            QString string = QString("Question %1").arg(i++);
            QuestionMapping[string]= x;
            ui->questionlist->addItem(string);
            Responses[string] = "Wrong Answer";
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
        ui->UnMarkAnswer->setHidden(false);
        ui->NextQuestion->setHidden(false);
        ui->PreviousQuestion->setHidden(false);
        mytimer->start(1000);
        ui->questionlist->setCurrentRow(0);
    }

}

void Questions::on_MarkAnswer_clicked()
{
    QListWidgetItem *itm = ui->questionlist->currentItem();
    itm->setBackgroundColor(Qt::green);
    int y;

    QString answer, correctanswer;
    correctanswer = ui->CorrectAnswer->text();
    int x;
    if(ui->OptionA->isChecked())
    {
        answer= ui->OptionA->text();
        OptionMarked[itm->text()]=1;
        x = (QString::compare(correctanswer, answer, Qt::CaseInsensitive));
        if (x==0)
        {
            y=(QString::compare(Responses[itm->text()], "Wrong Answer", Qt::CaseInsensitive));
            if(y==0)
            {
                Responses[itm->text()]="Correct Answer";
            }
        }
        else
           {
                Responses[itm->text()]="Wrong Answer";
           }
    }
    else if(ui->OptionB->isChecked())
    {
        answer= ui->OptionB->text();
        OptionMarked[itm->text()]=2;
        x = (QString::compare(correctanswer, answer, Qt::CaseInsensitive));
        if (x==0)
        {
            y=(QString::compare(Responses[itm->text()], "Wrong Answer", Qt::CaseInsensitive));
            if(y==0)
            {
                Responses[itm->text()]="Correct Answer";
            }
        }
        else
        {
             Responses[itm->text()]="Wrong Answer";
        }
    }
    else if(ui->OptionC->isChecked())
    {
        answer= ui->OptionC->text();
        OptionMarked[itm->text()]=3;
        x = (QString::compare(correctanswer, answer, Qt::CaseInsensitive));
        if (x==0)
        {
            y=(QString::compare(Responses[itm->text()], "Wrong Answer", Qt::CaseInsensitive));
            if(y==0)
            {
                Responses[itm->text()]="Correct Answer";
            }
        }
        else
        {
             Responses[itm->text()]="Wrong Answer";
        }
    }
    else if(ui->OptionD->isChecked())
    {
        answer= ui->OptionD->text();
        OptionMarked[itm->text()]=4;
        x = (QString::compare(correctanswer, answer, Qt::CaseInsensitive));
        if (x==0)
        {
            y=(QString::compare(Responses[itm->text()], "Wrong Answer", Qt::CaseInsensitive));
            if(y==0)
            {
                Responses[itm->text()]="Correct Answer";
            }
        }
        else
        {
             Responses[itm->text()]="Wrong Answer";
        }
    }
    on_NextQuestion_clicked();
}

void Questions::on_EndTest_clicked()
{
    int score=0,x;
    QHash<QString, QString>::const_iterator i = Responses.constBegin();
     while (i != Responses.constEnd())
     {
         qDebug()<< i.key() << ": " << i.value();
         x=(QString::compare(i.value(), "Correct Answer", Qt::CaseInsensitive));
         if(x==0)
         {
             ++score;
         }
         ++i;
     }
    QString Finalscore = "Your Final Score is " + QString::number(score);
    this->close();
    QMessageBox::information(this,"Test completition", Finalscore);
}

void Questions::timeoutslot()
{
    QTime TimeChange, TimeOver, LastTime;
    TimeOver.setHMS(0,0,0,0);
    LastTime.setHMS(0,1,0,0);
    TimeChange.setHMS(0,minutes,seconds,0);
    TimeChange = TimeChange.addSecs(i);
    if(TimeChange.toString() == TimeOver.toString())
    {
        on_EndTest_clicked();
    }
    else
    {
        QString val = TimeChange.toString();
        if(TimeChange.toString() == LastTime.toString())
        {
            ui->ledNumber->setPalette(Qt::red);
        }
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
    switch (OptionMarked[itm->text()])
    {
    case 1:ui->OptionA->setChecked(true);
        break;
    case 2:ui->OptionB->setChecked(true);
        break;
    case 3:ui->OptionC->setChecked(true);
        break;
    case 4:ui->OptionD->setChecked(true);
        break;
    default:
    {
        QButtonGroup *group = new QButtonGroup(this);
        group->addButton(ui->OptionA);
        group->addButton(ui->OptionB);
        group->addButton(ui->OptionC);
        group->addButton(ui->OptionD);

        QAbstractButton* checked = group->checkedButton();
        if (checked)
        {
            group->setExclusive(false);
            checked->setChecked(false);
            group->setExclusive(true);
        }
        break;
    }
    }

    model->setQuery(*query);
}

void Questions::on_UnMarkAnswer_clicked()
{
    QListWidgetItem *itm = ui->questionlist->currentItem();
    itm->setBackgroundColor(Qt::white);
    Responses[itm->text()]= "Wrong Answer";
    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->OptionA);
    group->addButton(ui->OptionB);
    group->addButton(ui->OptionC);
    group->addButton(ui->OptionD);

    QAbstractButton* checked = group->checkedButton();
    if (checked)
    {
        group->setExclusive(false);
        checked->setChecked(false);
        group->setExclusive(true);
    }

}

void Questions::on_NextQuestion_clicked()
{
    int row = ui->questionlist->currentRow();
    if(row != NumberofQuestions-1)
    ui->questionlist->setCurrentRow(row+1);
    else
        ui->questionlist->setCurrentRow(0);
}
