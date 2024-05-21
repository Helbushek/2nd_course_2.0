#pragma once
#include <vector>
#include <iostream>

class BoolVector;

class BoolRank {
    BoolRank(bool value, unsigned char* ptr, int index) {
        (*this).value = value; 
        (*this).ptr = ptr;
        (*this).index = index;
    }
    friend BoolVector;
    int index=0;
    bool value = 0;
    unsigned char* ptr;
    
public:
    void setValue();
    void operator=(bool value);
    operator bool() const;
};

class BoolVector {
public:
    static const int CELL_SIZE = 8;
public:
    BoolVector();
    BoolVector(int size, int data);
    BoolVector(const char* data);
    BoolVector(const BoolVector& other);


    ~BoolVector() {
       if (vector!=nullptr)
           delete[] vector;
    }

    const void print() const; 

    // Методы для установки и получения битов
    void setBit(int index, bool value=1);

    bool getBit(int index) const;

    int cellNumber() const {
        return(size / CELL_SIZE + (size % CELL_SIZE > 0));
    }

    int sizeOf() const;

    void swap(BoolVector& other);

    void invert(const int index);

    void invert();

    void setBits(int index, int count, bool value);

    void setAll(bool value);

    int weight() const;

    char getFirst() const;

    // Реализация побитовых операций

    const bool operator[](int index) const;

    BoolRank operator[](int index);

    BoolVector& operator=(const BoolVector& other);

    BoolVector operator&(const BoolVector& other) const;

    BoolVector operator|(const BoolVector& other) const;

    BoolVector operator^(const BoolVector& other) const;

    BoolVector operator~() const;

    BoolVector& operator&=(const BoolVector& other);

    BoolVector& operator|=(const BoolVector& other);

    BoolVector& operator^=(const BoolVector& other); 

    bool operator==(const BoolVector& other) const;

    bool operator!=(const BoolVector& other) const;

    // Реализация побитовых сдвигов

    BoolVector operator<<(int number) const;

    BoolVector& operator<<=(int number);

    BoolVector operator>>(int number) const;

    BoolVector& operator>>=(int number);

protected:
    int size;
    unsigned char* vector;
};

std::ostream& operator<<(std::ostream& os, const BoolVector& vector);

std::istream& operator>>(std::istream& is, BoolVector& vector);