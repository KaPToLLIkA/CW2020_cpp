#ifndef POWER_H
#define POWER_H

#include "trainer.h"



class PowerTrainer : public Trainer
{
private:
    double maxLoad;
    double maxUserWeight;
public:
    PowerTrainer(Vector3D<double> _size,
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
        maxUserWeight(_maxUserWeight) {}

    PowerTrainer();


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
