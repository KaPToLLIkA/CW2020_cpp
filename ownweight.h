#ifndef OWNWEIGHTTRAINER_H
#define OWNWEIGHTTRAINER_H

#include "trainer.h"



class OwnWeightTrainer : public Trainer
{
public:
    OwnWeightTrainer(Vector3D<double> _size,
                     double _weight,
                     QString _manufacturer,
                     QString _model,
                     QString _name,
                     QString _description,
                     QString _otherCharacteristics):
        Trainer(OwnWeight, _size, _weight, _manufacturer,
                _model, _name, _description, _otherCharacteristics) {}

    OwnWeightTrainer();



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
