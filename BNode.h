//
//  BNode.h
//  teamProject


#ifndef teamProject_BNode_h
#define teamProject_BNode_h
#include "Clothes.h"

class BinaryNode
{
private:
    Clothes    item;         // Data portion
    BinaryNode *leftPtr;		// Pointer to left child
    BinaryNode *rightPtr;		// Pointer to right child
    
public:
    // constructors
    BinaryNode() {item.setPrimary(" ");
        item.setSecondary(" ");
        item.setPrice('0');
        item.setMaterial(" ");
        item.setType(" ");
        leftPtr = NULL;
        rightPtr = NULL;}
    void setItemPrimary(string pri) {item.setPrimary(pri);}
    void setItemSecondary(string sec) {item.setSecondary(sec);}
    void setItemMat (string mat) {item.setMaterial(mat);}
    void setItemPrice (int val) {item.setPrice(val);}
    void setItemType (string cT) {item.setType(cT);}
    void setLeftPtr(BinaryNode* left) {leftPtr = left;}
    void setRightPtr(BinaryNode* right) {rightPtr = right;}
    BinaryNode* getLeftPtr() const  {return leftPtr;}
    BinaryNode* getRightPtr() const {return rightPtr;}
    
    string getItemPrimary() const {return item.getPrimary();}
    string getItemSecondary() const {return item.getSecondary();}
    string getItemMat ()const {return item.getMaterial();}
    string getItemType() const{return item.getType();}
    int getItemPrice() const{return item.getPrice();}
    
    bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
};

#endif
