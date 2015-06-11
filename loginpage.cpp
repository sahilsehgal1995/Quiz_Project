#include "loginpage.h"
#include "ui_loginpage.h"
#include "questions.h"
#include <QDebug>
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
    ui->statusBar->setHidden(false);
    ui->statusBar->setWindowOpacity(0.5);

    ui->statusBar->showMessage("University Institute of Engineering Technology, Panjab University");
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
void LoginPage::DatabaseUpdation(const QString &username)
{
    if(!connection_open())
    {
        ui->database_status->setText("Database not Connected");
    }
    else
    {
        ui->database_status->setText("Connected");
        QSqlQuery query;
        query.prepare("update record set status='not allowed' where rno = '"+ username + "'");
        if(query.exec())
        return;
    }
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
                DatabaseUpdation(username);
                connection_close();
                Questions q_Dialog;
                q_Dialog.setModal(true);
                q_Dialog.loginid(username);
                q_Dialog.exec();
                this->close();

            }
            else
                ui->Status->setText("Authentication Failed");
        }
    }

}
