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
    QString name;
    QString model;
    QString manufacturer;
    double weightMax, weightMin;

};


class DataBase
{
private:

    array data;

    QString path = "";
    bool openedExist = false;


    Trainer* getObjectFromStream(QDataStream &stream);

public:

    void save();
    bool saveAs(QWidget *parent);
    bool open(QWidget *parent);

    const array& getData() {return data;}

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
