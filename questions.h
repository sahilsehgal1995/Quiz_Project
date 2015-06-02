#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <QDialog>

namespace Ui {
class Questions;
}

class Questions : public QDialog
{
    Q_OBJECT

public:
    explicit Questions(QWidget *parent = 0);
    ~Questions();

private:
    Ui::Questions *ui;
};

#endif // QUESTIONS_H
