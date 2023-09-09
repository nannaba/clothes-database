//
//  HashNode.h
//  teamProject

#ifndef teamProject_HashNode_h
#define teamProject_HashNode_h
#include "Clothes.h"
class HashNode
{
private:
    Clothes item;
    string key;
    HashNode *nextPtr;
    
public:
    // constructors
    HashNode(string prikey, const Clothes & anItem) {key = prikey; item = anItem; nextPtr = NULL;}
    
    // accessors
    void setKey(string prikey) {key = prikey;}
    void setItem(const Clothes & anItem) {item = anItem;}
    void setNext(HashNode *next) {nextPtr = next;}
    
    // mutators
    string getKey() const {return key;}
    Clothes getItem() const	{return item;}
    HashNode* getNext() const  {return nextPtr;}
};


#endif
