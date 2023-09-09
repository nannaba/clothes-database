//
//  HashTable.h
//  teamProject

#ifndef teamProject_HashTable_h
#define teamProject_HashTable_h
#include "HashNode.h"
#include "Clothes.h"
#include <vector>

using namespace std;

class HashTable
{
private:
    HashNode **table;
    vector <Clothes> overflow;
    int hsize, collisions, load;
    
public:
    HashTable(int s);
    ~HashTable();
    
    unsigned long hashFunction(string key);
    bool insertHash(Clothes &data);
    bool deleteHash(string key, Clothes &deleted);
    bool searchHash(string key, Clothes &foundData);
    bool searchSecondary(string key, Clothes &foundData);
    
    double getLoadFactor();
    int getCollisions();
    int countBucket(int index);
    void printHash();
    bool saveToFile(string fileName);
};
#endif
