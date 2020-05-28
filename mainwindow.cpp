#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    columnsTitles[0] = "Тип";
    columnsTitles[1] = "Название";
    columnsTitles[2] = "Производитель";
    columnsTitles[3] = "Модель";
    columnsTitles[4] = "Габариты\n "
                       "(длина, ширина, высота)\n"
                       "в см.";
    columnsTitles[5] = "Вес тренажёра\n"
                       "(кг)";
    columnsTitles[6] = "Прочие характеристики";
    columnsTitles[7] = "Описание";
    columnsTitles[8] = "Тип нагрузки\n"
                       "на человека";
    columnsTitles[9] = "Максимальная нагрузка\n"
                       "на человека\n"
                       "(кг)";
    columnsTitles[10] = "Максимально допустимый"
                        "\nвес пользователя\n"
                        "(кг)";

   int arg1 = 0;
    ui->comboBoxType->setEnabled(arg1);

    ui->lineEditManufacturer->setEnabled(arg1);

    ui->lineEditModel->setEnabled(arg1);

    ui->lineEditName->setEnabled(arg1);

    ui->doubleSpinBoxMaxWeight->setEnabled(arg1);
    ui->doubleSpinBoxMinWeight->setEnabled(arg1);

    ui->pushButtonSearch->setEnabled(false);
    ui->pushButtonReset->setEnabled(false);


    QString textValidator = "^[a-zA-Zа-яА-Я0-9\.\\,\'\"\/-][a-zA-Zа-яА-Я0-9\.,\\\s\'\"\/-]*";
    ui->lineEditName->setValidator(new QRegExpValidator(QRegExp(textValidator), this));
    ui->lineEditModel->setValidator(new QRegExpValidator(QRegExp(textValidator), this));
    ui->lineEditManufacturer->setValidator(new QRegExpValidator(QRegExp(textValidator), this));

    ui->doubleSpinBoxMaxWeight->setRange(0, 1000);
    ui->doubleSpinBoxMinWeight->setRange(0, 1000);


    setWindowTitle(windowTitle + openedFile + notSavedFileName);

    for(uint64_t i = 0; i < columnsTitles.length(); ++i) {
        ui->tableWidget->insertColumn(0);
    }
    initTable();

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(DataBaseProvider::getInst()->getOpenedExistFlag()) {
        switch(QMessageBox(QMessageBox::Question,
                           "Сохранить?",
                           "Сохранить последние изменения перед закрытием?",
                           QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                           this).exec()) {
        case QMessageBox::Yes: {
            DataBaseProvider::getInst()->save(this);
        } break;
        case QMessageBox::No: {

        } break;
        case QMessageBox::Cancel: {
            event->ignore();
        } return;

        }


    } else {
        if(DataBaseProvider::getInst()->getLength() != 0) {
            switch(QMessageBox(QMessageBox::Question,
                               "Сохранить?",
                               "Сохранить документ перед закрытием?",
                               QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                               this).exec()) {
            case QMessageBox::Yes: {
                DataBaseProvider::getInst()->saveAs(this);
            } break;
            case QMessageBox::No: {

            } break;
            case QMessageBox::Cancel: {
                event->ignore();
            } return;

            }
        }

    }
    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkSearchParamsFlags()
{
    return ui->checkBoxName->checkState() == Qt::CheckState::Checked
            || ui->checkBoxType->checkState() == Qt::CheckState::Checked
            || ui->checkBoxModel->checkState() == Qt::CheckState::Checked
            || ui->checkBoxWeight->checkState() == Qt::CheckState::Checked
            || ui->checkBoxManufacturer->checkState() == Qt::CheckState::Checked;
}

QRegExp MainWindow::createRegex(const QString &str)
{
    try {
        return QRegExp("\\S*" + str + "\\S*", Qt::CaseSensitivity::CaseInsensitive);
    } catch (...) {
        return QRegExp("\\S*", Qt::CaseSensitivity::CaseInsensitive);
    }
}


void MainWindow::on_actionCreate_triggered()
{
    switch (QMessageBox(QMessageBox::Question,
                        "Новый документ.",
                        "Создание нового документа. Сохранить текущий?",
                        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                        this).exec()) {
    case QMessageBox::Yes: {
        DataBaseProvider::getInst()->save(this);
    } break;
    case QMessageBox::No: {

    } break;
    case QMessageBox::Cancel: {
        return;
    }
    }

    ui->tableWidget->clear();
    initTable();
    DataBaseProvider::getInst()->clearData();

    setWindowTitle(windowTitle + openedFile + notSavedFileName);
}

void MainWindow::on_actionSave_triggered()
{
    DataBaseProvider::getInst()->save(this);
}

void MainWindow::on_actionSaveAs_triggered()
{
    if(DataBaseProvider::getInst()->saveAs(this))
    {
        setWindowTitle(windowTitle + openedFile + DataBaseProvider::getInst()->getFilePath());
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if(DataBaseProvider::getInst()->open(this)) {
        setWindowTitle(windowTitle + openedFile + DataBaseProvider::getInst()->getFilePath());
        fillTable();

    }
}

void MainWindow::on_actionHelp_triggered()
{
    if(instructionDialog != nullptr) {
        delete instructionDialog;
    }
    instructionDialog = new instruction(this);
    instructionDialog->show();
}

void MainWindow::on_actionAbout_triggered()
{
    if(aboutDialog != nullptr) {
        delete aboutDialog;
    }
    aboutDialog = new about(this);
    aboutDialog->show();
}

void MainWindow::on_pushButtonAdd_clicked()
{
    if(addRedoDialog != nullptr) {
        delete addRedoDialog;
    }
    addRedoDialog = new AddRedoDialog(this);
    if(addRedoDialog->exec() == QDialog::Accepted) {
        ItemsData data;
        DataBaseProvider::getInst()->getLastTrainer()->getItems(data);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        for(uint64_t i = 0; i < data.length(); ++i) {
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, i, data[i]);
        }
    }
}

void MainWindow::on_pushButtonRedo_clicked()
{
    if(0 > cellCoords.y() || cellCoords.y() > DataBaseProvider::getInst()->getLength())
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите строку для редактирования.");
        return;
    }

    if(addRedoDialog != nullptr) {
        delete addRedoDialog;
    }
    addRedoDialog = new AddRedoDialog(this, true, cellCoords.y());
    if(addRedoDialog->exec() == QDialog::Accepted) {
        ItemsData data;
        DataBaseProvider::getInst()->getTrainer(cellCoords.y())->getItems(data);

        for(uint64_t i = 0; i < data.length(); ++i) {
            ui->tableWidget->setItem(cellCoords.y(), i, data[i]);
        }
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    cellCoords.setX(column);
    cellCoords.setY(row);
}

void MainWindow::on_pushButtonDelete_clicked()
{
    if(0 > cellCoords.y() || cellCoords.y() > DataBaseProvider::getInst()->getLength())
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите строку для удаления.");
        return;
    }

    if(!searchRequestMode)
    {
        DataBaseProvider::getInst()->eraseTrainer(cellCoords.y());
        ui->tableWidget->removeRow(cellCoords.y());
    }
}

void MainWindow::fillTable()
{
    clearTable();
    ItemsData data;
    for(uint64_t i = 0; i < DataBaseProvider::getInst()->getLength(); ++i)
    {
        DataBaseProvider::getInst()->getTrainer(i)->getItems(data);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());


        for(uint64_t ii = 0; ii < data.length(); ++ii) {
            ui->tableWidget->setItem(i, ii, data[ii]);
        }
    }
}

void MainWindow::initTable()
{


    QFont font("Segoe UI", 9);
    QFontMetrics x(font);

    for(uint64_t i = 0; i < columnsTitles.length(); ++i) {
        ui->tableWidget->setHorizontalHeaderItem(
                    static_cast<int>(i),
                    new QTableWidgetItem(columnsTitles[i]));
        ui->tableWidget->setColumnWidth(
                    static_cast<int>(i),
                    static_cast<int>(x.width(columnsTitles[i])*1.3f));
    }

    ui->tableWidget->setEditTriggers(nullptr);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::clearTable()
{
    while(ui->tableWidget->rowCount() != 0)
        ui->tableWidget->removeRow(0);
}



void MainWindow::on_checkBoxType_stateChanged(int arg1)
{
    ui->comboBoxType->setEnabled(arg1);
    if(checkSearchParamsFlags()) {
        ui->pushButtonSearch->setEnabled(true);
    } else {
        ui->pushButtonSearch->setEnabled(false);
    }

}

void MainWindow::on_checkBoxManufacturer_stateChanged(int arg1)
{
    ui->lineEditManufacturer->setEnabled(arg1);
    if(checkSearchParamsFlags()) {
        ui->pushButtonSearch->setEnabled(true);
    } else {
        ui->pushButtonSearch->setEnabled(false);
    }
}

void MainWindow::on_checkBoxModel_stateChanged(int arg1)
{
    ui->lineEditModel->setEnabled(arg1);
    if(checkSearchParamsFlags()) {
        ui->pushButtonSearch->setEnabled(true);
    } else {
        ui->pushButtonSearch->setEnabled(false);
    }
}

void MainWindow::on_checkBoxName_stateChanged(int arg1)
{
    ui->lineEditName->setEnabled(arg1);
    if(checkSearchParamsFlags()) {
        ui->pushButtonSearch->setEnabled(true);
    } else {
        ui->pushButtonSearch->setEnabled(false);
    }
}

void MainWindow::on_checkBoxWeight_stateChanged(int arg1)
{
    ui->doubleSpinBoxMaxWeight->setEnabled(arg1);
    ui->doubleSpinBoxMinWeight->setEnabled(arg1);
    if(checkSearchParamsFlags()) {
        ui->pushButtonSearch->setEnabled(true);
    } else {
        ui->pushButtonSearch->setEnabled(false);
    }
}



void MainWindow::on_pushButtonSearch_clicked()
{


    SearchRequest request;
    if(ui->checkBoxName->checkState() == Qt::CheckState::Checked) {
        if(ui->lineEditName->text().isEmpty()) {
            QMessageBox::warning(this, "Внимание!", "Заполните поле имени.");
            return;
        }

        request.nameSearchEnabled = true;
        request.name = createRegex(ui->lineEditName->text());
    }


    if(ui->checkBoxModel->checkState() == Qt::CheckState::Checked) {
        if(ui->lineEditModel->text().isEmpty()) {
            QMessageBox::warning(this, "Внимание!", "Заполните поле модели.");
            return;
        }


        request.modelSearchEnabled = true;
        request.model = createRegex(ui->lineEditModel->text());
    }

    if(ui->checkBoxManufacturer->checkState() == Qt::CheckState::Checked) {
        if(ui->lineEditManufacturer->text().isEmpty()) {
            QMessageBox::warning(this, "Внимание!", "Заполните поле производителя.");
            return;
        }

        request.manufacturerSearchEnabled = true;
        request.manufacturer = createRegex(ui->lineEditManufacturer->text());
    }


    if(ui->checkBoxWeight->checkState() == Qt::CheckState::Checked) {
        if(ui->doubleSpinBoxMaxWeight->value() < ui->doubleSpinBoxMinWeight->value()
                || ui->doubleSpinBoxMaxWeight->value() <= double(0.)
                || ui->doubleSpinBoxMinWeight->value() <= double(0.)) {
            QMessageBox::warning(this, "Внимание!", "Введен некорректный диапазон для массы тренажёра (возможно она равна 0, или минимальное значение превысило максимальное).");
            return;
        }

        request.weightSearchEnabled = true;
        request.weightMin = ui->doubleSpinBoxMinWeight->value();
        request.weightMax = ui->doubleSpinBoxMaxWeight->value();
    }

    if(ui->checkBoxType->checkState() == Qt::CheckState::Checked) {
        if(ui->comboBoxType->currentIndex() == 0) {
            QMessageBox::warning(this, "Внимание!", "Выберите тип тренажёра.");
            return;
        }

        request.typeSearchEnabled = true;
        request.type = static_cast<TrainerType>(ui->comboBoxType->currentIndex() - 1);
    }
    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonRedo->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
    ui->pushButtonSearch->setEnabled(false);
    ui->pushButtonReset->setEnabled(true);
    ui->checkBoxName->setEnabled(false);
    ui->checkBoxType->setEnabled(false);
    ui->checkBoxModel->setEnabled(false);
    ui->checkBoxWeight->setEnabled(false);
    ui->checkBoxManufacturer->setEnabled(false);
    ui->labelTable->setText("Таблица (Результаты поиска)");

    clearTable();

    for(uint64_t i = 0; i < DataBaseProvider::getInst()->getLength(); ++i) {
        if(DataBaseProvider::getInst()->searchTo(i, request)) {
            ItemsData data;

            DataBaseProvider::getInst()->getTrainer(i)->getItems(data);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            for(uint64_t ii = 0; ii < data.length(); ++ii) {
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, ii, data[ii]);
            }
        }

    }

}

void MainWindow::on_pushButtonReset_clicked()
{
    fillTable();

    ui->pushButtonAdd->setEnabled(true);
    ui->pushButtonRedo->setEnabled(true);
    ui->pushButtonDelete->setEnabled(true);
    ui->pushButtonReset->setEnabled(false);
    ui->pushButtonSearch->setEnabled(true);
    ui->checkBoxName->setEnabled(true);
    ui->checkBoxType->setEnabled(true);
    ui->checkBoxModel->setEnabled(true);
    ui->checkBoxWeight->setEnabled(true);
    ui->checkBoxManufacturer->setEnabled(true);
    ui->labelTable->setText("Таблица (Все данные)");

}

void MainWindow::on_action_Close_triggered()
{
    this->close();
}
