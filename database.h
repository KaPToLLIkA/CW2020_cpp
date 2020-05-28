#ifndef DATABASE_H
#define DATABASE_H

#include "array.h"
#include "ownweight.h"
#include "power.h"
#include "benchesracks.h"
#include "cardio.h"

#include <QFile>
#include <QFileDialog>
#include <QString>


struct SearchRequest {

    TrainerType type;
    QRegExp name;
    QRegExp model;
    QRegExp manufacturer;
    double weightMax, weightMin;

    bool typeSearchEnabled = false;
    bool nameSearchEnabled = false;
    bool modelSearchEnabled = false;
    bool manufacturerSearchEnabled = false;
    bool weightSearchEnabled = false;

};


class DataBase
{
private:

    array data;

    QString path = "";
    bool openedExist = false;


    Trainer* getObjectFromStream(QDataStream &stream);

public:
    void addTrainer(DataType newTrainer);
    void eraseTrainer(uint64_t index);
    DataType getTrainer(uint64_t index);
    DataType getLastTrainer();
    void replaceTrainerAt(uint64_t index, DataType newTrainer);
    uint64_t getLength();
    QString getFilePath();
    void clearData();
    bool searchTo(uint64_t index, SearchRequest &request);


    void save(QWidget *parent);
    bool saveAs(QWidget *parent);
    bool open(QWidget *parent);

    bool getOpenedExistFlag();

};



class DataBaseProvider {
private:
    static DataBase *dbInstance;
public:
    static DataBase* getInst() {
        if(dbInstance == nullptr) {
            dbInstance = new DataBase();
        }
        return dbInstance;
    }
};

#endif // DATABASE_H
