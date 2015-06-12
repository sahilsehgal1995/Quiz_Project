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
    void QuestionList();
    void loginid(const QString &logid);
    QString id;

private slots:
    void on_StartTest_pressed();

    void on_MarkAnswer_clicked();

    void on_EndTest_clicked();

    void on_questionlist_itemSelectionChanged();

    void on_UnMarkAnswer_clicked();

    void on_NextQuestion_clicked();

    void on_PreviousQuestion_clicked();

private:
    Ui::Questions *ui;
    QList<int> qlist;
    QHash<QString, int> QuestionMapping;
    QHash<QString, QString> Responses;
    QHash<QString, int> OptionMarked;
    int NumberofQuestions;

public:
    QTimer *mytimer;
    QTime *timevalue;
    int minutes,seconds,i;
    void Result_File(const QString &score);
public slots:
    void timeoutslot();
};

#endif // QUESTIONS_H
