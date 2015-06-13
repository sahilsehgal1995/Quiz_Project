#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QSqlQuery>
#include "questions.h"
#include "settings.h"

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

    void on_actionBasic_settings_triggered();

private:
    Ui::LoginPage *ui;
    void DatabaseUpdation(const QString &username);
    Questions q_Dialog;
    settings mysettings;
    void BasicSettings();
};

#endif // LOGINPAGE_H
