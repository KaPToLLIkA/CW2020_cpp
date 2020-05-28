#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "about.h"
#include "addredodialog.h"
#include "instruction.h"

#include <QMainWindow>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    bool checkSearchParamsFlags();
    QRegExp createRegex(const QString &str);
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_actionCreate_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionOpen_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_pushButtonAdd_clicked();

    void on_pushButtonRedo_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButtonDelete_clicked();

    void on_checkBoxType_stateChanged(int arg1);

    void on_checkBoxManufacturer_stateChanged(int arg1);

    void on_checkBoxModel_stateChanged(int arg1);

    void on_checkBoxName_stateChanged(int arg1);

    void on_checkBoxWeight_stateChanged(int arg1);

    void on_pushButtonSearch_clicked();

    void on_pushButtonReset_clicked();

    void on_action_Close_triggered();

private:
    ConstArray<QString, Trainer::MAX_ITEMS_COUNT> columnsTitles;
    QPoint cellCoords = {-1, -1};
    bool searchRequestMode = false;
    QString windowTitle = "ИПС \"Спортивный комплекс\" ";
    QString openedFile = "Открыт файл: ";
    QString notSavedFileName = "Документ1";

    AddRedoDialog *addRedoDialog = nullptr;
    about *aboutDialog = nullptr;
    instruction *instructionDialog = nullptr;
    Ui::MainWindow *ui;


    void fillTable();
    void initTable();
    void clearTable();

};
#endif // MAINWINDOW_H
