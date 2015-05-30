#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QSqlQuery>

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT
public:
    QSqlDatabase mydb;
    void connection_close();
    bool connection_open();

public:
    explicit LoginPage(QWidget *parent = 0);
    ~LoginPage();

private slots:
    void on_Login_button_clicked();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
