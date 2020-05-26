#ifndef TRAINER_H
#define TRAINER_H

#include <QTableWidget>
#include <qstring.h>


enum TrainerType {
    Power,
    Cardio,
    OwnWeight,
    BenchesRacks
};

template <typename T>
struct Vector3D {
    T x,y,z;
};


class Trainer
{
protected:
    TrainerType type;
    Vector3D<double> size;
    double weigth;
    QString manufacturer;
    QString model;
    QString name;
    QString description;
    QString otherCharacteristics;
public:
    Trainer();
    Trainer(TrainerType _type,
            Vector3D<double> _size,
            double _weight,
            QString _manufacturer,
            QString _model,
            QString _name,
            QString _description,
            QString _otherCharacteristics) :
        type(_type),
        size(_size),
        weigth(_weight),
        manufacturer(_manufacturer),
        model(_model),
        name(_name),
        description(_description),
        otherCharacteristics(_otherCharacteristics)
    {}

    QString getManufcturer() { return manufacturer; }
    QString getName() { return name; }
    QString getDescription() { return description; }
    QString getModel() { return model; }
    double getWieght() { return weigth; }
    TrainerType getType() { return type; }
    Vector3D<double> getXYZ() {return size; }

//    QString setManufcturer() { return manufacturer; }
//    QString setName() { return name; }
//    QString setDescription() { return description; }
//    QString setModel() { return model; }
//    double setWieght() { return weigth; }
//    TrainerType setType() { return type; }
//    Vector3D<double> setXYZ() {return size; }

    QTableWidgetItem* getItemType() {
        switch (type) {
        case Power: return new QTableWidgetItem("Power");
        case Cardio: return new QTableWidgetItem("Cardio");
        case OwnWeight: return new QTableWidgetItem("Own weight");
        case BenchesRacks: return new QTableWidgetItem("Benches or racks");
        }
    }

    QTableWidgetItem* getItemManufacturer() { return new QTableWidgetItem(manufacturer);}
    QTableWidgetItem* getItemName() { return new QTableWidgetItem(name);}
    QTableWidgetItem* getItemDescription() { return new QTableWidgetItem(description);}
    QTableWidgetItem* getItemModel() { return new QTableWidgetItem(model);}
    QTableWidgetItem* getWeight() {
        QString w;
        w.setNum(weigth);
        return new QTableWidgetItem(w);
    }

    QTableWidgetItem* getItemXYZ() {
        QString x; x.setNum(size.x);
        QString y; y.setNum(size.y);
        QString z; z.setNum(size.z);
        return new QTableWidgetItem(
                    "width: " + x + "; length: " + y + "; height: " + z
                    );
    }


    virtual void toQDataSteam(QDataStream &stream) = 0;
    virtual void fromQDataSteam(QDataStream &stream) = 0;
    virtual ~Trainer() {

    }
};

#endif // TRAINER_H
