#pragma once
#include <QtMath>

class HashFunction
{
  public:
    ~HashFunction() = default;
    virtual int hash(int key, int size) = 0;
};

class HashFunctionOne : public HashFunction
{ //  hi(K) = (hi-1(K) + c × i + d × i2) mod N | h0(k) = k mod N | c = k mod 5 | d = k mod 7
  public:
    int hash(int key, int size) override
    {
        return (key % size + key % 5 + key % 7) % size;
    }
};

class HashFunctionTwo : public HashFunction
{ // hi(K) = [hi-1(K) × a × N] mod N; a = – (1 – √5) ÷ 2, | h0(k) = k mod N
  public:
    int hash(int key, int size) override
    {
        return ((key % size) * (-(1 - sqrt(5)) / 2) * size);
    }
};

class HashFunctionThree : public HashFunction
{ // hi(K) = (K mod N) + i × (1+ K mod (N – 2)) mod N
  public:
    int hash(int key, int size) override
    {
        if (size==2) {
            return (key%size + 1%size);
        }
        return (key%size + (1+key%(size-2))%size);
    }
};
