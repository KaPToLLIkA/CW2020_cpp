#ifndef ARRAY_H
#define ARRAY_H
#include "trainer.h"

#include <QString>
#include <memory.h>
#include <stdint.h>


//mandatory typedef
typedef Trainer* DataType;

class array
{
private:
    DataType* data;
    uint64_t size;
    uint64_t allocatedSize;

    void realloc();
    void reallocMore();
    void reallocLess();
public:


    array() : data(new DataType[1]), size(0), allocatedSize(1) {}

    uint64_t length() { return size; }
    DataType at(uint64_t index) {
        if (index >= size) return nullptr;
        return data[index];
    }
    void addElement(DataType newElement);
    void eraseElement(uint64_t index);
    void replaceAt(uint64_t index, DataType value);
    void insertAt(uint64_t index, DataType value);
    void clear();

    DataType operator[](uint64_t index) {
        if (index >= size) return nullptr;
        return data[index];
    }
};

#endif // ARRAY_H
