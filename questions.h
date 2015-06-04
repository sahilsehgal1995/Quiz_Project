#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QSqlQuery>
#include <QTime>
#include <QTimer>

namespace Ui {
class Questions;
}

class Questions : public QDialog
{
    Q_OBJECT

public:
    QSqlDatabase QuestionsDatabase;
    void connection_close();
    bool connection_open();

public:
    explicit Questions(QWidget *parent = 0);
    ~Questions();

private slots:
    void on_StartTest_pressed();

    void on_QuestionList_activated(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_MarkAnswer_clicked();

    void on_EndTest_clicked();

    void on_StartTest_clicked();

private:
    Ui::Questions *ui;

public:
    QTimer *mytimer;
    QTime *timevalue;
    int minutes,seconds,i;

public slots:
    void timeoutslot();
};

#endif // QUESTIONS_H
