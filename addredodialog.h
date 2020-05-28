#ifndef ADDREDODIALOG_H
#define ADDREDODIALOG_H

#include "database.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddRedoDialog;
}

class AddRedoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRedoDialog(QWidget *parent = nullptr,
                           bool _redoMode = false,
                           uint64_t _redoIndex = 0);
    ~AddRedoDialog();

private slots:
    void on_dialogButtonBox_accepted();

    void on_comboBoxTrainerType_currentIndexChanged(int index);

    void on_dialogButtonBox_rejected();

private:
    bool redoMode;
    uint64_t redoIndex;
    Ui::AddRedoDialog *ui;

    QString windowTitle = "ИПС \"Спортивный комплекс\" ";
    QString addModeTitle = "Добавить";
    QString redoModeTitle = "Редактировать";


    void setAllDisabled();
    void setAllEnabled();
};

#endif // ADDREDODIALOG_H
