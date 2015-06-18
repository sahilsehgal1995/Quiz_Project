#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

public:
    int NoOfQuestions;
    int NoOfHours;
    int NoOfMinutes;
    int NoOfSeconds;
    int testquestions;
    QString ShowResult;

private slots:
    void on_Enter_clicked();

    void on_buttonBox_accepted();

private:
    Ui::settings *ui;
};

#endif // SETTINGS_H
