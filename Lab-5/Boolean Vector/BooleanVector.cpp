#include <assert.h>
#include <cmath>
#include "BooleanVector.h"

BoolVector::BoolVector() {
    vector = nullptr;
    size = 0;
}
BoolVector::BoolVector(int size, int data) {
    (*this).size = size;
    vector = new unsigned char[cellNumber()];
    (*this).setAll(data);
}
BoolVector::BoolVector(const char* data) {
    size = static_cast<int>(sizeof(data)) / static_cast<int>(sizeof(data[0]));
    if (size)
        vector = new unsigned char[cellNumber()];
    else
        vector = nullptr;

    int i = size-1;
    while (i>=0) {
        if (data[i] == '1') {
            setBit(i, 1);
        }
        else {
            setBit(i, 0);
        }
        i--;
    }
}
BoolVector::BoolVector(const BoolVector& other) {
    size = other.size;
    vector = new unsigned char[other.cellNumber()];
    for (int i = 0; i < other.cellNumber(); ++i) {
        vector[i] = other.vector[i];
    }
}

const void BoolVector::print() const{
    for (int i = 0; i < size; i++) {
        std::cout << getBit(i);
    }
}

// ћетоды дл€ установки и получени€ битов
void BoolVector::setBit(const int index, const bool value) {
    if (index<0 || index>size) {
        std::cerr << "Incorrect index in BoolVector::setBit, I=" << index;
        return;
    }
    if (value == 1) {
        vector[index / CELL_SIZE] |= (1 << index % CELL_SIZE);
    }
    else {
        vector[index / CELL_SIZE] &= (~(1 << index % CELL_SIZE));
    }
}

char BoolVector::getFirst() const {
    if (vector != nullptr) {
        return vector[0];
    }
}

bool BoolVector::getBit(const int index) const {
    if (index<0 || index>size) {
        std::cerr << "Incorrect index in BoolVector::getBit, I=" << index;
        return 0;
    }
    if ((vector[index / CELL_SIZE] & (1 << index % CELL_SIZE)) == 0)
        return 0;
    return 1;
}

int BoolVector::sizeOf() const {
    return size;
}

void BoolVector::swap(BoolVector& other){
    std::swap(size, other.size);
    std::swap(vector, other.vector);
}



void BoolVector::invert(const int index){
    assert(index > 0 && index < size);
    setBit(index, !getBit(index));
}

void BoolVector::invert() {
    for (int i = 0; i < size; i++) {
        invert(i);
    }
}

void BoolVector::setBits(int index, int count, bool value) {
    if (index<0 || index>size || count <= 0 || index + count >= size) {
        std::cerr << "Incorrect index in BoolVector::getBits, I=" << index;
        return;
    }
    for (int i = index; i <= index + count; i++) {
        setBit(i, value);
    }
}

void BoolVector::setAll(bool value) {
    for (int i = 0; i < cellNumber(); i++) {
        vector[i] = (value == 1 ? ((2<<CELL_SIZE)-1) : 0);
    }
}

int BoolVector::weight() const{
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (((vector[i/ CELL_SIZE] >> (i% CELL_SIZE)) & 1) == 1) {
            count++;
        }
    }
    return count;
}

// –еализаци€ побитовых операций

const bool BoolVector::operator[](int index) const {
    if (((vector[index / CELL_SIZE]>> (index % CELL_SIZE))&1) == 1)
        return 1;
    return 0;
}

BoolRank BoolVector::operator[](int index){
    if (((vector[index / CELL_SIZE] >> (index % CELL_SIZE)) & 1) == 1)
        return BoolRank(1, (*this).vector, index);
    return BoolRank(0, (*this).vector, index);
}

BoolVector& BoolVector::operator=(const BoolVector& other) {
    if (this == &other) {
        return *this;
    }
    if (size != other.size) {
        size = other.size;
        delete[] vector;
        vector = new unsigned char[other.cellNumber()];
    }
    for (int i = 0; i < cellNumber(); i++) {
        vector[i] = other.vector[i];
    }
    return *this;
}

BoolVector BoolVector::operator&(const BoolVector& other) const {
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i+=CELL_SIZE) {
        temp.vector[i/CELL_SIZE] &= other.vector[i/CELL_SIZE];
    }
    return temp;
}

BoolVector BoolVector::operator|(const BoolVector& other) const{
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i+=CELL_SIZE) {
        temp.vector[i] |= other.vector[i];
    }
    return temp;
}

BoolVector BoolVector::operator^(const BoolVector& other) const{
    BoolVector temp = (*this);
    int min = temp.size;
    if (temp.size > other.size) min = other.size;
    for (int i = 0; i <= min; i+=CELL_SIZE) {
        temp.vector[i] ^= other.vector[i];
    }
    return temp;
}

BoolVector& BoolVector::operator&=(const BoolVector& other) {
    (*this) = (*this) & other;
    return *this;
}

BoolVector& BoolVector::operator|=(const BoolVector& other) {
    (*this) = (*this) | other;
    return *this;
}

BoolVector& BoolVector::operator^=(const BoolVector& other) {
    (*this) = (*this) ^ other;
    return *this;
}

BoolVector BoolVector::operator~() const{
    BoolVector temp(*this);
    for (int i = 0; i < cellNumber(); i+=CELL_SIZE) {
        temp.vector[i] = ~temp.vector[i];
    }
    return temp;
}

// –еализаци€ побитовых сдвигов

BoolVector BoolVector::operator<<(int number) const{
    BoolVector temp(*this);
    temp <<= number;
    return temp;
}

BoolVector& BoolVector::operator<<=(int number) {
    if (number < 0) {
        std::cerr << "Incorrect number for shift in BoolVector:: operator<<, number= " << number;
        return ((*this) >>= -number);
    }

    for (int i = 0; i < number / CELL_SIZE; i += CELL_SIZE) { // —двигаем по €чейкам
        vector[i] = vector[i + number / CELL_SIZE];
    }
    for (int i = cellNumber() - 1; i > cellNumber() - number / CELL_SIZE - 1; i--) {
        vector[i] = 0;
    }

    for (int i = 0; i < cellNumber(); i ++) { // —двигаем внутри €чеек
        vector[i] >>= number % CELL_SIZE;
        if (i + 1 <= cellNumber()-1) {
            unsigned char mask = vector[i + 1];

            vector[i] |= (mask << (CELL_SIZE - number % CELL_SIZE));
        }
    }

    vector[(cellNumber() - 1)] &= (255 >> number % CELL_SIZE); // 255 - все позиции единицы, сдвигаем на кол-во сдвигов внутри €чеек, умножаем на последнюю €чейку
    
    return *this;
}

BoolVector BoolVector::operator>>(int number) const {
    BoolVector temp(*this);
    temp >>= number;
    return temp;
}

BoolVector& BoolVector::operator>>=(int number) {
    if (number < 0) {
        std::cerr << "Incorrect number for shift in BoolVector:: operator>>, number= " << number;
        return((*this)<<=-number);
    }

    for (int i = cellNumber()-1; i > cellNumber() - number / CELL_SIZE-1; i -= CELL_SIZE) { // —двигаем по €чейкам
        vector[i] = vector[i - number / CELL_SIZE];
    }
    for (int i = 0; i < number / CELL_SIZE; i += CELL_SIZE) {
        vector[i] = 0;
    }

    for (int i = cellNumber()-1; i >=0; i --) {
        vector[i] <<= number % CELL_SIZE;
        if (i - 1 >= 0) {
            unsigned char mask = vector[i- 1];

            vector[i] |= (mask >> (CELL_SIZE - number % CELL_SIZE));
        }
    }
    vector[0] &= (255 << number);
    return *this;
}

// –еализаци€ необходимых операций дл€ вспомогательного класса

void BoolRank::setValue() {
    if (index<0) {
        std::cerr << "Incorrect index in BoolRank::setValue, I=" << index;
        return;
    }

    if (value == 1) {
        ptr[index / BoolVector::CELL_SIZE] |= (1 << index % BoolVector::CELL_SIZE);
    }
    else {
        ptr[index / BoolVector::CELL_SIZE] &= (~(1 << index % BoolVector::CELL_SIZE));
    }
}

void BoolRank::operator=(bool value) {
    (*this).value = value;
    setValue();
}

BoolRank::operator bool() const {
    return value;
}

std::ostream& operator<<(std::ostream& os, const BoolVector& vector) {
    for (int i = 0; i < vector.sizeOf(); i++) {
        os << vector.getBit(i);
    }

    return os;
}

std::istream& operator>>(std::istream& is, BoolVector& vector) {
    std::string temp;
    is >> temp;
    vector = BoolVector(temp.c_str());
    return is;
}

bool BoolVector::operator==(const BoolVector& other) const{
    if (size != other.size) {
        return false;
    }
    if (((*this) & (~other)).weight() == 0)
        return true;
    return false;
}

bool BoolVector::operator!=(const BoolVector& other) const{
    return !((*this) == other);
}