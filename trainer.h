#ifndef TRAINER_H
#define TRAINER_H

#include "constarray.h"

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
    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(T _x, T _y, T _z): x(_x), y(_y), z(_z) {}
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
    static const uint64_t MAX_ITEMS_COUNT = 11;
    explicit Trainer();
    explicit Trainer(TrainerType _type, Trainer t) :
        type(_type),
        size(t.size),
        weigth(t.weigth),
        manufacturer(t.manufacturer),
        model(t.model),
        name(t.name),
        description(t.description),
        otherCharacteristics(t.otherCharacteristics)
    {}
    explicit Trainer(TrainerType _type,
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
    QString getOtherCharacteristics() { return otherCharacteristics; }
    double getWeight() { return weigth; }
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
        case Power: return new QTableWidgetItem("Силовой\nтренажёр");
        case Cardio: return new QTableWidgetItem("Кардио\nтренажёр");
        case OwnWeight: return new QTableWidgetItem("Тренажёр с\nсобственным\nвесом");
        case BenchesRacks: return new QTableWidgetItem("Скамьи\nи стойки");
        }
        return new QTableWidgetItem("");
    }

    QTableWidgetItem* getItemManufacturer() { return new QTableWidgetItem(manufacturer);}
    QTableWidgetItem* getItemName() { return new QTableWidgetItem(name);}
    QTableWidgetItem* getItemDescription() { return new QTableWidgetItem(description);}
    QTableWidgetItem* getItemModel() { return new QTableWidgetItem(model);}
    QTableWidgetItem* getItemOtherCharacteristics() { return new QTableWidgetItem(otherCharacteristics);}
    QTableWidgetItem* getItemWeight() {
        QString w;
        w.setNum(weigth);
        return new QTableWidgetItem(w);
    }

    QTableWidgetItem* getItemXYZ() {
        QString x; x.setNum(size.x);
        QString y; y.setNum(size.y);
        QString z; z.setNum(size.z);
        return new QTableWidgetItem(
                    "длина: " + x + "; ширина: " + y + "; высота: " + z
                    );
    }
    QTableWidgetItem* getItemEmpty() { return new QTableWidgetItem(""); }

    virtual void getItems(ConstArray<QTableWidgetItem*, Trainer::MAX_ITEMS_COUNT>& items) {}
    virtual void toQDataSteam(QDataStream &stream) {}
    virtual void fromQDataSteam(QDataStream &stream) {}
    virtual ~Trainer() {

    }
};

typedef ConstArray<QTableWidgetItem*, Trainer::MAX_ITEMS_COUNT> ItemsData;

#endif // TRAINER_H
