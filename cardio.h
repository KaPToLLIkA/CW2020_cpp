#ifndef CARDIO_H
#define CARDIO_H

#include "trainer.h"



class CardioTrainer : public Trainer
{
private:
    QString typeOfLoad;
public:
    explicit CardioTrainer();

    explicit CardioTrainer(Trainer t, QString _typeOfLoad):
        Trainer(Cardio, t),
        typeOfLoad(_typeOfLoad)
    {}

    explicit CardioTrainer(Vector3D<double> _size,
                  double _weight,
                  QString _manufacturer,
                  QString _model,
                  QString _name,
                  QString _description,
                  QString _otherCharacteristics,
                  QString _typeOfLoad):
        Trainer(Cardio, _size, _weight, _manufacturer,
                _model, _name, _description, _otherCharacteristics),
        typeOfLoad(_typeOfLoad)
    {}




    QString getTypeOfLoad() {return typeOfLoad;}

    QTableWidgetItem* getItemTypeOfLoad() {
        return new QTableWidgetItem(typeOfLoad);
    }


    void getItems(ItemsData& items) override {
        items[0] = getItemType();
        items[1] = getItemName();
        items[2] = getItemManufacturer();
        items[3] = getItemModel();
        items[4] = getItemXYZ();
        items[5] = getItemWeight();
        items[6] = getItemOtherCharacteristics();
        items[7] = getItemDescription();
        items[8] = getItemTypeOfLoad();
        items[9] = getItemEmpty();
        items[10] = getItemEmpty();

    }


    void toQDataSteam(QDataStream &stream) override {
        stream << size.x;
        stream << size.y;
        stream << size.z;
        stream << weigth;
        stream << manufacturer;
        stream << model;
        stream << name;
        stream << description;
        stream << otherCharacteristics;
        stream << typeOfLoad;

    }
    void fromQDataSteam(QDataStream &stream) override {
        stream >> size.x;
        stream >> size.y;
        stream >> size.z;
        stream >> weigth;
        stream >> manufacturer;
        stream >> model;
        stream >> name;
        stream >> description;
        stream >> otherCharacteristics;
        stream >> typeOfLoad;
    }
};

#endif // CARDIO_H
