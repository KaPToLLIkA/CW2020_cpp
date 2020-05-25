#include "array.h"



void array::realloc()
{
    DataType* newData = new DataType[allocatedSize];
    memcpy(newData, data, sizeof(DataType) * size);
    delete[] data;
    data = newData;
}

void array::reallocMore()
{
    allocatedSize *= 2;
    realloc();
}

void array::reallocLess()
{
    allocatedSize /= 2;
    realloc();
}



void array::addElement(DataType newElement)
{
    if (size >= allocatedSize) reallocMore();
    data[size] = newElement;
    ++size;
}


void array::eraseElement(uint64_t index)
{
    if (size == 0) return;
    delete data[index];
    memcpy(&(data[index]), &(data[index + 1]), sizeof(DataType) * (size - index - 1));
    --size;

    if (size < allocatedSize / 2) reallocLess();
}

void array::replaceAt(uint64_t index, DataType value)
{
    if (index >= size) return;
    delete data[index];
    data[index] = value;
}

void array::insertAt(uint64_t index, DataType value)
{
    if (index > size) return;
    ++size;
    if (size >= allocatedSize) reallocMore();
    memcpy(&(data[index + 1]), &(data[index]), sizeof(DataType) * (size - index));
    data[index] = value;
}
