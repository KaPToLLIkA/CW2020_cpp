#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QDialog>

namespace Ui {
class instruction;
}

class instruction : public QDialog
{
    Q_OBJECT

public:
    explicit instruction(QWidget *parent = nullptr);
    ~instruction();

private slots:
    void on_pushButton_clicked();

private:
    Ui::instruction *ui;
};

#endif // INSTRUCTION_H
