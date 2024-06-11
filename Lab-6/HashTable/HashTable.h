#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "HashFunction.h"

template<typename T>
class HashTable
{
  public:

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

  public:

    HashTable();
    HashTable(const HashTable &other);
    ~HashTable();

    int size();

    void clear();

    T operator[](int key);
    pair *operator()(coordinates);
    HashTable operator=(const HashTable &other);
    void print();
    int rowSize(int row);

    coordinates addItem(int key, const T &value);
    bool removeItem(int key);

    coordinates findItem(int key);

    bool resize(int size);
    bool chooseHash(int index);

    bool changeValue(int key, T value);

  private:
    HashFunction *m_hash = new HashFunctionOne();
    int m_hash_index = 0;

    static constexpr int arrowLength = 3;

    std::vector<std::vector<pair*>*> m_items;
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

template <typename T> typename HashTable<T>::coordinates HashTable<T>::addItem(int key, const T &value)
{
    coordinates cords;
    if (!m_items.size())
    {
        cords.x = -1;
        cords.y = -1;
        return cords;
    }
    if (findItem(key).x != -1 || findItem(key).y != -1)
    {
        return findItem(key);
    }

    int row = m_hash->hash(key, m_items.size());
    pair *temp = new pair();
    temp->key = key;
    temp->value = value;
    m_items[row]->push_back(temp);
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

template <typename T> bool HashTable<T>::removeItem(const int key)
{
    if (!m_items.size())
    {
        return false;
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
            return true;
        }
    }
    return false;
}

template <typename T>
typename HashTable<T>::coordinates HashTable<T>::findItem(int key)
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

template <typename T> T HashTable<T>::operator[](int key)
{
    coordinates cords = findItem(key);
    return (*m_items[cords.x])[cords.y];
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

template <typename T> bool HashTable<T>::resize(int size)
{
    if (size < 0)
    {
        return false;
    }
    std::vector<pair *> temp;
    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items[i]->size(); ++j)
        {
            pair *tempCell = new pair();
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
        m_items[i] = new std::vector<pair *>();
    }

    for (int i = 0; i < temp.size(); ++i)
    {
        addItem(temp[i]->key, temp[i]->value);
    }
    return true;
}

template <typename T> bool HashTable<T>::chooseHash(int index)
{
    if (index < 0 || index > 2)
    {
        return false;
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
            return true;
        }
        case 1: {
            m_hash = new HashFunctionTwo();
            resize(m_items.size());
            return true;
        }
        case 2: {
            m_hash = new HashFunctionThree();
            resize(m_items.size());
            return true;
        }
        default: {
            return false;
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

template <typename T> typename HashTable<T>::pair *HashTable<T>::operator()(coordinates coord)
{
    return (*m_items[coord.x])[coord.y];
}

template <typename T> bool HashTable<T>::changeValue(int key, T value)
{
    coordinates coords = this->findItem(key);
    (*m_items[coords.x])[coords.y]->value = value;
}

template <typename T> int HashTable<T>::rowSize(int row)
{
    return static_cast<int>(m_items[row]->size());
}


