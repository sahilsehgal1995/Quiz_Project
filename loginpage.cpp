#include "loginpage.h"
#include "ui_loginpage.h"
#include "questions.h"

void LoginPage::connection_close()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool LoginPage::connection_open()
{
    if(mydb.open())
        return true;
    else
        return false;
}

LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    ui->statusBar->setWindowTitle("Automatic Quiz Application");
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/sahil/qt/sequel/Sequel/loginusers.db");

    if(!connection_open())
    {
        ui->database_status->setText("Database not Connected");
    }
    else
    {
        ui->database_status->setText("Connected");
    }

}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_Login_button_clicked()
{
    if(!connection_open())
    {
        ui->database_status->setText("Database not Connected");
    }
    else
    {
        ui->database_status->setText("Connected");

        QString username,password;
        username = ui->Username_field->text();
        password = ui->Password_field->text();
        QSqlQuery query;

        query.prepare("select * from record where rno = '"+ username + "' and status = 'allow';");
        if (query.exec())
        {
            int count=0;
            while (query.next())
                count++;
            if (count == 1)
            {
                ui->Status->setText("Login Successfull");
                connection_close();
                Questions q_Dialog;
                q_Dialog.setModal(true);
                q_Dialog.exec();

            }
            else
                ui->Status->setText("Authentication Failed");
        }
    }

}
