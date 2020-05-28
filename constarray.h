#ifndef CONSTARRAY_H
#define CONSTARRAY_H

#include <stdint.h>

template<class T, uint64_t size>
class ConstArray
{
private:
    uint64_t _size = size;
    T *array = new T[size];

public:
    explicit ConstArray() {}

    T& operator[](uint64_t index) {
       return array[index];
    }

    uint64_t length() {return _size;}

    ~ConstArray() {delete[] array;}
};

#endif // CONSTARRAY_H
