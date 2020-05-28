#ifndef POWER_H
#define POWER_H

#include "trainer.h"



class PowerTrainer : public Trainer
{
private:
    double maxLoad;
    double maxUserWeight;
public:
    explicit PowerTrainer();


    explicit PowerTrainer(Trainer t,
                          double _maxLoad,
                          double _maxUserWeight) :
        Trainer(Power, t),
        maxLoad(_maxLoad),
        maxUserWeight(_maxUserWeight)
    {}


    explicit PowerTrainer(Vector3D<double> _size,
                 double _weight,
                 QString _manufacturer,
                 QString _model,
                 QString _name,
                 QString _description,
                 QString _otherCharacteristics,
                 double _maxLoad,
                 double _maxUserWeight) :
        Trainer(Power, _size, _weight, _manufacturer,
                _model, _name, _description, _otherCharacteristics),
        maxLoad(_maxLoad),
        maxUserWeight(_maxUserWeight)
    {}




    double getMaxLoad() { return maxLoad; }
    double getMaxUserWeight() { return maxUserWeight; }
//    void setMaxLoad(double value) { maxLoad = value; }
//    void setMaxUserWeight(double value) { maxUserWeight = value; }


    QTableWidgetItem* getItemMaxLoad() {
        QString w;
        w.setNum(maxLoad);
        return new QTableWidgetItem(w);
    }

    QTableWidgetItem* getItemMaxUserWeight() {
        QString w;
        w.setNum(maxUserWeight);
        return new QTableWidgetItem(w);
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
        items[8] = getItemEmpty();
        items[9] = getItemMaxLoad();
        items[10] = getItemMaxUserWeight();
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
        stream << maxLoad;
        stream << maxUserWeight;

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
        stream >> maxLoad;
        stream >> maxUserWeight;
    }
};

#endif // POWER_H
