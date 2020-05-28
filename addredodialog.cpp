#include "addredodialog.h"

#include "ui_addredodialog.h"



AddRedoDialog::AddRedoDialog(QWidget *parent,
                             bool _redoMode,
                             uint64_t _redoIndex) :
    QDialog(parent),
    redoMode(_redoMode),
    redoIndex(_redoIndex),
    ui(new Ui::AddRedoDialog)
{
    ui->setupUi(this);


    ui->doubleSpinBoxX->setRange(0, 1000);
    ui->doubleSpinBoxY->setRange(0, 1000);
    ui->doubleSpinBoxZ->setRange(0, 1000);
    ui->doubleSpinBoxMaxLoadWeight->setRange(0, 500);
    ui->doubleSpinBoxMaxUserWeight->setRange(0, 300);
    ui->doubleSpinBoxTrainerWeight->setRange(0, 1000);

    QString textValidator = "^[a-zA-Zа-яА-Я0-9\.\\,\'\"\/-][a-zA-Zа-яА-Я0-9\.,\\\s\'\"\/-]*";

    ui->lineEditName->setValidator(new QRegExpValidator(QRegExp(textValidator), this));
    ui->lineEditModel->setValidator(new QRegExpValidator(QRegExp(textValidator), this));
    ui->lineEditTypeOfLoad->setValidator(new QRegExpValidator(QRegExp(textValidator), this));
    ui->lineEditDescription->setValidator(new QRegExpValidator(QRegExp(textValidator), this));
    ui->lineEditManufacturer->setValidator(new QRegExpValidator(QRegExp(textValidator), this));
    //ui->textEditOtherCharacteristics->


    if(redoMode) {

        Trainer* element = DataBaseProvider::getInst()->getTrainer(redoIndex);
        ui->doubleSpinBoxX->setValue(element->getXYZ().x);
        ui->doubleSpinBoxY->setValue(element->getXYZ().y);
        ui->doubleSpinBoxZ->setValue(element->getXYZ().z);


        ui->lineEditName->setText(element->getName());
        ui->lineEditModel->setText(element->getModel());
        ui->lineEditDescription->setText(element->getDescription());
        ui->lineEditManufacturer->setText(element->getManufcturer());

        ui->doubleSpinBoxTrainerWeight->setValue(element->getWeight());
        ui->textEditOtherCharacteristics->setText(element->getOtherCharacteristics());

        switch (element->getType()) {
        case Power: {
            ui->comboBoxTrainerType->setCurrentIndex(1);

            PowerTrainer* t = dynamic_cast<PowerTrainer*>(element);

            ui->doubleSpinBoxMaxUserWeight->setValue(t->getMaxUserWeight());
            ui->doubleSpinBoxMaxLoadWeight->setValue(t->getMaxLoad());
        } break;
        case Cardio: {
            ui->comboBoxTrainerType->setCurrentIndex(2);

            CardioTrainer* t = dynamic_cast<CardioTrainer*>(element);

            ui->lineEditTypeOfLoad->setText(t->getTypeOfLoad());
        } break;
        case OwnWeight: {
            ui->comboBoxTrainerType->setCurrentIndex(3);
        } break;
        case BenchesRacks: {
            ui->comboBoxTrainerType->setCurrentIndex(4);

            BenchesRacksTrainer* t = dynamic_cast<BenchesRacksTrainer*>(element);

            ui->lineEditTypeOfLoad->setText(t->getTypeOfLoad());
        } break;
        }


        ui->comboBoxTrainerType->setEnabled(false);
        setWindowTitle(windowTitle + redoModeTitle);


    } else {
        setWindowTitle(windowTitle + addModeTitle);

        setAllDisabled();
    }
}

AddRedoDialog::~AddRedoDialog()
{
    delete ui;
}

void AddRedoDialog::on_dialogButtonBox_accepted()
{

    if(ui->comboBoxTrainerType->currentIndex() == 0)
    {
        QMessageBox::warning(this, "Внимание!", "Вы не выбрали тип тренажёра.");
        return;
    }

    if(!(ui->doubleSpinBoxX->value() > double(0.)
            && ui->doubleSpinBoxY->value() > double(0.)
            && ui->doubleSpinBoxZ->value() > double(0.)))
    {
        QMessageBox::warning(this, "Внимание!", "Размеры не могут быть равны 0.");
        return;
    }

    if(!(ui->doubleSpinBoxTrainerWeight->value() > double(0.)))
    {
        QMessageBox::warning(this, "Внимание!", "Вес тренажёра не может быть равным 0.");
        return;
    }

    if(ui->lineEditName->text().isEmpty())
    {
        QMessageBox::warning(this, "Внимание!", "Вы не заполнили поле названия.");
        return;
    }

    if(ui->lineEditDescription->text().isEmpty())
    {
        QMessageBox::warning(this, "Внимание!", "Вы не заполнили поле описания.");
        return;
    }

    if(ui->lineEditModel->text().isEmpty())
    {
        QMessageBox::warning(this, "Внимание!", "Вы не заполнили поле модели.");
        return;
    }


    if(ui->lineEditManufacturer->text().isEmpty())
    {
        QMessageBox::warning(this, "Внимание!", "Вы не заполнили поле производителя.");
        return;
    }


    switch(ui->comboBoxTrainerType->currentIndex()) {
    case 0: {
        QMessageBox::warning(this, "Внимание!", "Вы не выбрали тип тренажёра.");
        return;
    }
    case 1: {
        if(!(ui->doubleSpinBoxMaxLoadWeight->value() > double(0.)))
        {
            QMessageBox::warning(this, "Внимание!", "Максимальный вес нагрузки не может быть равным 0.");
            return;
        }

        if(!(ui->doubleSpinBoxMaxUserWeight->value() > double(0.)))
        {
            QMessageBox::warning(this, "Внимание!", "Максимальный вес пользователя не может быть равным 0.");
            return;
        }
    } break;
    case 2: {
        if(ui->lineEditTypeOfLoad->text().isEmpty())
        {
            QMessageBox::warning(this, "Внимание!", "Вы не заполнили поле типа нагрузки.");
            return;
        }
    } break;
    case 4: {
        if(ui->lineEditTypeOfLoad->text().isEmpty())
        {
            QMessageBox::warning(this, "Внимание!", "Вы не заполнили поле типа нагрузки.");
            return;
        }
    } break;
    }

    Trainer t(Power,
              Vector3D<double>(
                  ui->doubleSpinBoxX->value(),
                  ui->doubleSpinBoxY->value(),
                  ui->doubleSpinBoxZ->value()
                  ),
              ui->doubleSpinBoxTrainerWeight->value(),
              ui->lineEditManufacturer->text(),
              ui->lineEditModel->text(),
              ui->lineEditName->text(),
              ui->lineEditDescription->text(),
              ui->textEditOtherCharacteristics->toPlainText());


    if(redoMode) {
        switch(ui->comboBoxTrainerType->currentIndex()) {
        case 1: {

            DataBaseProvider::getInst()->replaceTrainerAt(
                    redoIndex,
                    new PowerTrainer(
                        t,
                        ui->doubleSpinBoxMaxLoadWeight->value(),
                        ui->doubleSpinBoxMaxUserWeight->value()
                        )
                    );

        } break;
        case 2: {
            DataBaseProvider::getInst()->replaceTrainerAt(
                    redoIndex,
                    new CardioTrainer(
                        t,
                        ui->lineEditTypeOfLoad->text()
                        )
                    );
        } break;
        case 3: {
            DataBaseProvider::getInst()->replaceTrainerAt(
                    redoIndex,
                    new OwnWeightTrainer(t)
                    );
        } break;
        case 4: {
            DataBaseProvider::getInst()->replaceTrainerAt(
                    redoIndex,
                    new BenchesRacksTrainer(
                        t,
                        ui->lineEditTypeOfLoad->text()
                        )
                    );
        } break;
        }
    } else {
        switch(ui->comboBoxTrainerType->currentIndex()) {
        case 1: {

            DataBaseProvider::getInst()->addTrainer(
                        new PowerTrainer(
                        t,
                        ui->doubleSpinBoxMaxLoadWeight->value(),
                        ui->doubleSpinBoxMaxUserWeight->value()
                        )
                    );

        } break;
        case 2: {
            DataBaseProvider::getInst()->addTrainer(
                        new CardioTrainer(
                        t,
                        ui->lineEditTypeOfLoad->text()
                        )
                    );
        } break;
        case 3: {
            DataBaseProvider::getInst()->addTrainer(
                        new OwnWeightTrainer(t)
                    );
        } break;
        case 4: {
            DataBaseProvider::getInst()->addTrainer(
                        new BenchesRacksTrainer(
                        t,
                        ui->lineEditTypeOfLoad->text()
                        )
                    );
        } break;
        }

    }

    this->accept();

}


void AddRedoDialog::on_dialogButtonBox_rejected()
{

    this->reject();
}

void AddRedoDialog::on_comboBoxTrainerType_currentIndexChanged(int index)
{
    switch(index) {
    case 0: {
        setAllDisabled();
    } return;
    case 1: {
        setAllEnabled();

        ui->lineEditTypeOfLoad->setEnabled(false);
    } return;
    case 2: {
        setAllEnabled();

        ui->doubleSpinBoxMaxLoadWeight->setEnabled(false);
        ui->doubleSpinBoxMaxUserWeight->setEnabled(false);
    } return;
    case 3: {
        setAllEnabled();
        ui->doubleSpinBoxMaxLoadWeight->setEnabled(false);
        ui->doubleSpinBoxMaxUserWeight->setEnabled(false);
        ui->lineEditTypeOfLoad->setEnabled(false);
    } return;
    case 4: {
        setAllEnabled();

        ui->doubleSpinBoxMaxLoadWeight->setEnabled(false);
        ui->doubleSpinBoxMaxUserWeight->setEnabled(false);
    } return;
    }
}

void AddRedoDialog::setAllDisabled()
{
    ui->comboBoxTrainerType->setCurrentIndex(0);
    ui->doubleSpinBoxX->setEnabled(false);
    ui->doubleSpinBoxY->setEnabled(false);
    ui->doubleSpinBoxZ->setEnabled(false);
    ui->doubleSpinBoxMaxLoadWeight->setEnabled(false);
    ui->doubleSpinBoxMaxUserWeight->setEnabled(false);
    ui->doubleSpinBoxTrainerWeight->setEnabled(false);
    ui->lineEditName->setEnabled(false);
    ui->lineEditModel->setEnabled(false);
    ui->lineEditTypeOfLoad->setEnabled(false);
    ui->lineEditDescription->setEnabled(false);
    ui->lineEditManufacturer->setEnabled(false);
    ui->textEditOtherCharacteristics->setEnabled(false);
}

void AddRedoDialog::setAllEnabled()
{

    ui->doubleSpinBoxX->setEnabled(true);
    ui->doubleSpinBoxY->setEnabled(true);
    ui->doubleSpinBoxZ->setEnabled(true);
    ui->doubleSpinBoxMaxLoadWeight->setEnabled(true);
    ui->doubleSpinBoxMaxUserWeight->setEnabled(true);
    ui->doubleSpinBoxTrainerWeight->setEnabled(true);
    ui->lineEditName->setEnabled(true);
    ui->lineEditModel->setEnabled(true);
    ui->lineEditTypeOfLoad->setEnabled(true);
    ui->lineEditDescription->setEnabled(true);
    ui->lineEditManufacturer->setEnabled(true);
    ui->textEditOtherCharacteristics->setEnabled(true);
}


