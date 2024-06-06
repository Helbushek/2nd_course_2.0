#include <iostream>
#include "HashTable.h"
#include "HashFunction.h"

HashTable::HashTable()
{}

HashTable::HashTable(const HashTable &other)
    :HashTable()
{
    resize(0);
    for (int i = 0; i < other.m_items.size(); ++i)
    {
        for (int j = 0; j < other.m_items[i]->size(); ++j)
        {
            addItem((*other.m_items[i])[j]->key, (*other.m_items[i])[j]->value);
        }
    }
}

HashTable::~HashTable()
{
    resize(0);
}

coordinates HashTable::addItem(int key, const std::string &value)
{
    if (!m_items.size())
    {
        coordinates temp;
        temp.x = -1;
        temp.y = -1;
        return temp;
    }
    if (findItem(key).x != -1 || findItem(key).y!= -1)
    {
        return findItem(key);
    }

    int row = m_hash->hash(key, m_items.size());
    pair *temp = new pair();
    temp->key = key;
    temp->value = value;
    m_items[row]->push_back(temp);
    coordinates cords;
    cords.y = row;
    cords.x = m_items[row]->size() - 1;
    return cords;
}

std::string HashTable::removeItem(const int key)
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

coordinates HashTable::findItem(int key)
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

coordinates HashTable::operator[](int key)
{
    return findItem(key);
}

std::vector<pair *> *HashTable::at(int index)
{
    return m_items[index];
}

void HashTable::clear()
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

std::string HashTable::resize(int size)
{
    if (size < 0)
    {
        return "invalid size: size should be 0 or more";
    }
    std::vector<pair*> temp;
    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items[i]->size(); ++j)
        {
            pair* tempCell = new pair();
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
        m_items[i] = new std::vector<pair*>();
    }

    for (int i = 0; i < temp.size(); ++i)
    {
        addItem(temp[i]->key, temp[i]->value);
    }
    return("success: resize");
}

std::string HashTable::chooseHash(int index)
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
        default:
            {
                return "failure: unknown";
            }
        }
    }

}

int HashTable::size()
{
    return m_items.size();
}

void HashTable::print()
{
    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items[i]->size(); ++j)
        {
            std::cout << "[key: " << (*m_items[i])[j]->key << " | value: " << (*m_items[i])[j]->value
                      << "]";
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

pair* HashTable::operator()(coordinates coord)
{
    return (*m_items[coord.x])[coord.y];
}

