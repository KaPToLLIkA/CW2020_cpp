#include "addredodialog.h"
#include "ui_addredodialog.h"

AddRedoDialog::AddRedoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRedoDialog)
{
    ui->setupUi(this);
}

AddRedoDialog::~AddRedoDialog()
{
    delete ui;
}
