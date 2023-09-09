//
//  HashNode.cpp
//  teamProject

#include "HashTable.h"
#include "Clothes.h"
#include "HashNode.h"

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Constructor: Creates the array for the hash table
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
HashTable :: HashTable(int s)
{
    collisions = 0;
    load = 0;
    hsize = s;
    table = new HashNode *[hsize]();
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Destructor: Destroys the hash table
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
HashTable :: ~HashTable()
{
    // destroy all buckets one by one
    for(int i = 0; i < hsize; i++)
    {
        HashNode *item = table[i];
        while(item != NULL)
        {
            HashNode *prev = item;
            item = item->getNext();
            delete prev;
        }
        table[i] = NULL;
    }
    
    // destroy hash table
    delete [] table;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Hash function: Creates a unique number from the key that is to be
 the index in an array
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
unsigned long HashTable :: hashFunction(string key)
{
    unsigned long sum = 0;
    
    for(unsigned int i = 0; i < key.length(); i++)
    {
        sum = sum*127 + key[i];
    }
    
    return sum%hsize;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Inserts new data into the hash table
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool HashTable :: insertHash(Clothes &data)
{
    unsigned long hashkey = hashFunction(data.getPrimary());
    HashNode *prev = NULL;
    HashNode *newData = table[hashkey];
    
    while(newData != NULL && newData->getKey() != data.getPrimary())
    {
        prev = newData;
        newData = newData->getNext();
    }
    
    if(newData == NULL)
    {
        newData = new HashNode(data.getPrimary(), data);
        // if first
        if(prev == NULL)
        {
            table[hashkey] = newData;
            load++;
        }
        else
        {
            prev->setNext(newData);
            collisions++;
        }
        return true;
    }
    
    // if bucket is full put in to overflow vector
    int c = countBucket(hashkey);
    if(c == 3)
    {
        overflow.push_back(data);
        return true;
    }
    
    return false;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Deletes an item from the hash table
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool HashTable :: deleteHash(string key, Clothes &deleted)
{
    unsigned long hashkey = hashFunction(key);
    HashNode *prev = NULL;
    HashNode *item = table[hashkey];
    
    while(item != NULL && item->getKey()!= key)
    {
        prev = item;
        item = item->getNext();
    }
    
    if(item == NULL)
    {
        return false;
    }
    
    else
    {
        deleted = item->getItem();
        
        if(prev == NULL)
        {
            table[hashkey] = item->getNext();
        }
        else
        {
            prev->setNext(item->getNext());
        }
        delete item;
        return true;
    }
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Searches for an item in the hash table, if the data is found the info is
 passed back to foundData
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool HashTable :: searchHash(string key, Clothes &foundData)
{
    unsigned long hashkey = hashFunction(key);
    HashNode *item = table[hashkey];
    
    // search bucket first
    while(item != NULL)
    {
        if(item->getKey() == key)
        {
            foundData = item->getItem();
            return true;
        }
        item = item->getNext();
    }
    
    // search the overflow vector next
    for(unsigned int i = 0; i < overflow.size(); i++)
    {
        if(overflow.at(i).getPrimary() == key)
        {
            foundData = overflow.at(i);
            return true;
        }
    }
    
    return false;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Searches for an item in the hash table, if the data is found the info is
 passed back to foundData (for the secondary key)
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool HashTable :: searchSecondary(string key, Clothes &foundData)
{
    HashNode *curr;
    
    // search bucket first
    for(int i = 0; i < hsize; i++)
    {
        curr = table[i];
        while(curr != NULL)
        {
            Clothes item = curr->getItem();
            if (item.getSecondary() == key)
            {
                foundData = item;
                return true;
            }
            curr = curr->getNext();
        }
    }
    
    // search the overflow vector next
    for(unsigned int i = 0; i < overflow.size(); i++)
    {
        if(overflow.at(i).getPrimary() == key)
        {
            foundData = overflow.at(i);
            return true;
        }
    }
    
    return false;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Calculates and returns the load factor
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
double HashTable :: getLoadFactor()
{
    return load/(double)hsize * 100;           // for percentage like 60% instead of .6
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Returns the number of collisions
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
int HashTable :: getCollisions()
{
    return collisions;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Counts the number of items in the bucket at this index
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
int HashTable :: countBucket(int index)
{
    int count = 0;
    HashNode *item = table[index];
    
    while(item->getNext() != NULL)
    {
        count++;
    }
    
    return count;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Prints out the hash table
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
void HashTable :: printHash()
{
    HashNode *curr;
    
    for(int i = 0; i < hsize; i++)
    {
        curr = table[i];
        while(curr != NULL)
        {
            Clothes now = curr->getItem();
            cout << now.getPrimary() << setw(30) << now.getSecondary() << setw(5) << "$" << fixed << setprecision(2)
            << now.getPrice() << setw(15) << now.getMaterial() << setw(15) << now.getType() << endl;
            curr = curr->getNext();
        }
    }
    
    for(unsigned int j = 0; j < overflow.size(); j++)
    {
        Clothes now = overflow.at(j);
        cout << now.getPrimary() << setw(30) << now.getSecondary() << setw(5) << "$"<< fixed <<setprecision(2)
        << now.getPrice() << setw(15) << now.getMaterial() << setw(15) << now.getType() << endl;
    }
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Writes the hash table to an output file
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool HashTable :: saveToFile(string fileName)
{
    bool status = false;
    ofstream outfile;
    outfile.open(fileName);
    
    if(outfile)
    {
        HashNode *curr;
        
        for(int i = 0; i < hsize; i++)
        {
            curr = table[i];
            while(curr != NULL)
            {
                Clothes now = curr->getItem();
                outfile << now.getPrimary() << setw(30) << now.getSecondary() << setw(5) << "$" << fixed << setprecision(2)
                << now.getPrice() << setw(15) << now.getMaterial() << setw(15) << now.getType() << endl;
                curr = curr->getNext();
            }
        }
        
        for(unsigned int j = 0; j < overflow.size(); j++)
        {
            Clothes now = overflow.at(j);
            outfile << now.getPrimary() << setw(30) << now.getSecondary() << setw(5) << "$"<< fixed <<setprecision(2)
            << now.getPrice() << setw(15) << now.getMaterial() << setw(15) << now.getType() << endl;
        }
        
        status = true;
    }
    
    outfile.close();
    return status;
}

