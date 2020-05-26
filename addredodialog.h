#ifndef ADDREDODIALOG_H
#define ADDREDODIALOG_H

#include <QDialog>

namespace Ui {
class AddRedoDialog;
}

class AddRedoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRedoDialog(QWidget *parent = nullptr);
    ~AddRedoDialog();

private:
    Ui::AddRedoDialog *ui;
};

#endif // ADDREDODIALOG_H
