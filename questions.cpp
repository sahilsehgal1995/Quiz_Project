#include "questions.h"
#include "ui_questions.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QModelIndex>

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
}

Questions::~Questions()
{
    delete ui;
}

void Questions::on_StartTest_pressed()
{
    ui->StartTest->setVisible(false);
    if(!connection_open())
    QMessageBox::warning(this,"Warning","Database not connected");

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery(QuestionsDatabase);

    query->prepare("select id from questions");
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);

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
