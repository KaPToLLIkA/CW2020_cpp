#include "instruction.h"
#include "ui_instruction.h"

instruction::instruction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instruction)
{
    ui->setupUi(this);
    setWindowTitle("Руководство");
}

instruction::~instruction()
{
    delete ui;
}

void instruction::on_pushButton_clicked()
{
    this->close();
}
