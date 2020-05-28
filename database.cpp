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

void DataBase::addTrainer(DataType newTrainer)
{
    data.addElement(newTrainer);
}

void DataBase::eraseTrainer(uint64_t index)
{
    data.eraseElement(index);
}

DataType DataBase::getTrainer(uint64_t index)
{
    return data.at(index);
}

DataType DataBase::getLastTrainer()
{
    return data.at(data.length() - 1);
}

void DataBase::replaceTrainerAt(uint64_t index, DataType newTrainer)
{
    data.replaceAt(index, newTrainer);
}

uint64_t DataBase::getLength()
{
    return data.length();
}

QString DataBase::getFilePath()
{
    return path;
}

void DataBase::clearData()
{
    data.clear();
}

bool DataBase::searchTo(uint64_t index, SearchRequest &request)
{
    bool searchResult = true;
    if(request.nameSearchEnabled) {
        if(!request.name.exactMatch(data[index]->getName())) {
            searchResult = false;
        }
    }

    if(request.modelSearchEnabled) {
        if(!request.model.exactMatch(data[index]->getModel())) {
            searchResult = false;
        }
    }

    if(request.manufacturerSearchEnabled) {
        if(!request.manufacturer.exactMatch(data[index]->getManufcturer())) {
            searchResult = false;
        }
    }


    if(request.weightSearchEnabled) {
        if(data[index]->getWeight() < request.weightMin
        || data[index]->getWeight() > request.weightMax) {
            searchResult = false;
        }
    }

    if(request.typeSearchEnabled) {
        if(request.type != data[index]->getType()) {
            searchResult = false;
        }

    }

    return searchResult;
}

void DataBase::save(QWidget *parent)
{
    if(!openedExist)
    {
        saveAs(parent);
        return;
    }

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

    save(parent);
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

bool DataBase::getOpenedExistFlag()
{
    return openedExist;
}
