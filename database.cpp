#include "database.h"

DataBase* DataBaseProvider::dbInstance = nullptr;

Trainer *DataBase::getObjectFromStream(QDataStream &stream)
{
    int tmpType;
    Trainer *obj = nullptr;


    stream >> tmpType;

    switch (tmpType) {
    case Power:
    {
        obj = new PowerTrainer();
        obj->fromQDataSteam(stream);
    } break;
    case Cardio:
    {
        obj = new CardioTrainer();
        obj->fromQDataSteam(stream);
    } break;
    case OwnWeight:
    {
        obj = new OwnWeightTrainer();
        obj->fromQDataSteam(stream);
    } break;
    case BenchesRacks:
    {
        obj = new BenchesRacksTrainer();
        obj->fromQDataSteam(stream);

    } break;
    }
    return obj;
}

void DataBase::save()
{
    if(!openedExist) return;

    QFile outFile(path);
    outFile.open(QIODevice::WriteOnly);
    QDataStream outStream(&outFile);

    outStream << data.length();
    for(uint64_t i = 0; i < data.length(); ++i) {
        outStream << data[i]->getType();
        data[i]->toQDataSteam(outStream);
    }
}

bool DataBase::saveAs(QWidget *parent)
{
    QString tmpPath = QFileDialog::getSaveFileName(parent, "Save as...", "", "*.txt");
    if(tmpPath == "") return false;

    path = tmpPath;
    openedExist = true;

    save();
    return true;
}

bool DataBase::open(QWidget *parent)
{
    QString tmpPath = QFileDialog::getOpenFileName(parent, "Open from...", "", "*.txt");
    if(tmpPath == "") return false;

    path = tmpPath;
    openedExist = true;

    data.clear();
    QFile inFile(path);
    inFile.open(QIODevice::ReadOnly);
    QDataStream inStream(&inFile);

    uint64_t size;
    inStream >> size;

    for(uint64_t i = 0; i < size; ++i) {
        data.addElement(getObjectFromStream(inStream));
    }

    return true;
}
