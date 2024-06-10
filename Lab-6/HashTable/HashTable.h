#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "HashFunction.h"

template<typename T>
struct pair
{
    int key;
    T value;
};

struct coordinates
{
    int x;
    int y;
};

template<typename T>
class HashTable
{
  public:
    HashTable();
    HashTable(const HashTable &other);
    ~HashTable();

    int size();

    void clear();

    coordinates operator[](int key);
    pair<T> *operator()(coordinates);
    HashTable operator=(const HashTable &other);
    void print();
    std::vector<pair<T> *>* at(int index);

    coordinates addItem(int key, const T &value);
    std::string removeItem(int key);

    coordinates findItem(int key);

    std::string resize(int size);
    std::string chooseHash(int index);

    bool changeValue(int key, T value);

  private:
    HashFunction *m_hash = new HashFunctionOne();
    int m_hash_index = 0;

    static const int arrowLength = 3;

    std::vector<std::vector<pair<T>*>*> m_items;
};

template <typename T> HashTable<T>::HashTable()
{
}

template <typename T> HashTable<T>::HashTable(const HashTable<T> &other) : HashTable<T>()
{
    *this = other;
}

template <typename T> HashTable<T>::~HashTable()
{
    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items[i]->size(); ++j)
        {
            delete (*m_items[i])[j];
        }
        delete m_items[i];
    }
}

template <typename T> coordinates HashTable<T>::addItem(int key, const T &value)
{
    if (!m_items.size())
    {
        coordinates temp;
        temp.x = -1;
        temp.y = -1;
        return temp;
    }
    if (findItem(key).x != -1 || findItem(key).y != -1)
    {
        return findItem(key);
    }

    int row = m_hash->hash(key, m_items.size());
    pair<T> *temp = new pair<T>();
    temp->key = key;
    temp->value = value;
    m_items[row]->push_back(temp);
    coordinates cords;
    cords.y = row;
    cords.x = m_items[row]->size() - 1;
    return cords;
}

template <typename T> HashTable<T> HashTable<T>::operator=(const HashTable<T> &other)
{
    resize(0);
    for (int i = 0; i < other.m_items.size(); ++i)
    {
        for (int j = 0; j < other.m_items[i]->size(); ++j)
        {
            addItem((*other.m_items[i])[j]->key, (*other.m_items[i])[j]->value);
        }
    }
    return *this;
}

template <typename T> std::string HashTable<T>::removeItem(const int key)
{
    if (!m_items.size())
    {
        return "size is 0";
    }

    int row = m_hash->hash(key, m_items.size());
    for (int i = 0; i < m_items[row]->size(); ++i)
    {
        if ((*m_items[row])[i]->key == key)
        {
            auto iter = m_items[row]->begin();
            iter += i;
            m_items[row]->erase(iter);
            resize(m_items.size());
            return "success: remove";
        }
    }
    return "fail remove: item not found";
}

template <typename T> coordinates HashTable<T>::findItem(int key)
{
    int i = m_hash->hash(key, m_items.size());
    for (int j = 0; j < m_items[i]->size(); ++j)
        if ((*m_items[i])[j]->key == key)
        {
            coordinates temp;
            temp.x = i;
            temp.y = j;
            return temp;
        }

    coordinates temp;
    temp.x = -1;
    temp.y = -1;
    return temp;
}

template <typename T> coordinates HashTable<T>::operator[](int key)
{
    return findItem(key);
}

template <typename T> std::vector<pair<T> *> *HashTable<T>::at(int index)
{
    return m_items[index];
}

template <typename T> void HashTable<T>::clear()
{
    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items[i]->size(); ++j)
        {
            delete (*m_items[i])[j];
            (*m_items[i])[j] = nullptr;
        }
    }
}

template <typename T> std::string HashTable<T>::resize(int size)
{
    if (size < 0)
    {
        return "invalid size: size should be 0 or more";
    }
    std::vector<pair<T> *> temp;
    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items[i]->size(); ++j)
        {
            pair<T> *tempCell = new pair<T>();
            tempCell->key = (*m_items[i])[j]->key;
            tempCell->value = (*m_items[i])[j]->value;
            temp.push_back(tempCell);
        }
    }
    for (int i = m_items.size() - 1; i >= size; --i)
    {
        delete m_items[i];
    }

    m_items.resize(size);
    for (int i = 0; i < size; ++i)
    {
        m_items[i] = new std::vector<pair<T> *>();
    }

    for (int i = 0; i < temp.size(); ++i)
    {
        addItem(temp[i]->key, temp[i]->value);
    }
    return ("success: resize");
}

template <typename T> std::string HashTable<T>::chooseHash(int index)
{
    if (index < 0 || index > 2)
    {
        return "fail: index out of range";
    }
    else
    {
        if (m_hash_index != index && m_hash)
        {
            delete m_hash;
        }
        m_hash_index = index;
        switch (index)
        {
        case 0: {
            m_hash = new HashFunctionOne();
            resize(m_items.size());
            return "success: hash One";
        }
        case 1: {
            m_hash = new HashFunctionTwo();
            resize(m_items.size());
            return "success: hash One";
        }
        case 2: {
            m_hash = new HashFunctionThree();
            resize(m_items.size());
            return "success: hash One";
        }
        default: {
            return "failure: unknown";
        }
        }
    }
}

template <typename T> int HashTable<T>::size()
{
    return m_items.size();
}

template <typename T> void HashTable<T>::print()
{
    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items[i]->size(); ++j)
        {
            std::cout << "[key: " << (*m_items[i])[j]->key << " | value: " << (*m_items[i])[j]->value << "]";
            if (j < m_items[i]->size() - 1)
            {
                for (int k = 0; k < arrowLength; ++k)
                {
                    std::cout << "-";
                }
                std::cout << ">";
            }
        }
        std::cout << std::endl;
    }
}

template <typename T> pair<T> *HashTable<T>::operator()(coordinates coord)
{
    return (*m_items[coord.x])[coord.y];
}

template <typename T> bool HashTable<T>::changeValue(int key, T value)
{
    coordinates coords = this->operator[](key);
    (*m_items[coords.x])[coords.y]->value = value;
}



