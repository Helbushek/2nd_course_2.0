#pragma once

#include <vector>
#include <list>
#include <string>

#include "HashFunction.h"

struct pair
{
    int key;
    std::string value;
};

struct coordinates
{
    int x;
    int y;
};

class HashTable
{
  public:
    HashTable();
    HashTable(const HashTable &other);
    ~HashTable();

    int size();

    void clear();

    coordinates operator[](int key);
    pair *operator()(coordinates);
    void print();
    std::vector<pair *>* at(int index);

    coordinates addItem(int key, const std::string &value);
    std::string removeItem(int key);

    coordinates findItem(int key);

    std::string resize(int size);
    std::string chooseHash(int index);

  private:
    HashFunction *m_hash = new HashFunctionOne();
    int m_hash_index = 0;

    static const int arrowLength = 3;

    std::vector<std::vector<pair*>*> m_items;
};
