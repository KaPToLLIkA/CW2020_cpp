#ifndef OWNWEIGHTTRAINER_H
#define OWNWEIGHTTRAINER_H

#include "trainer.h"



class OwnWeightTrainer : public Trainer
{
public:
    explicit OwnWeightTrainer();

    explicit OwnWeightTrainer(Trainer t): Trainer(OwnWeight, t) {}

    explicit OwnWeightTrainer(Vector3D<double> _size,
                     double _weight,
                     QString _manufacturer,
                     QString _model,
                     QString _name,
                     QString _description,
                     QString _otherCharacteristics):
        Trainer(OwnWeight, _size, _weight, _manufacturer,
                _model, _name, _description, _otherCharacteristics)
    {}




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


    }

};

#endif // OWNWEIGHTTRAINER_H
