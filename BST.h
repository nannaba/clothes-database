//
//  BST.h
//  teamProject


#ifndef teamProject_BST_h
#define teamProject_BST_h
#include "BT.h"
class BinarySearchTree:public BinaryTree
{
private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNode);
    
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode* _remove(BinaryNode* nodePtr, const string target, bool & success);
    
    // delete target node from tree, called by internal remove node
    BinaryNode* deleteNode(BinaryNode* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, Clothes & successor);
    
    BinaryNode* _removesec(BinaryNode* nodePtr, const string target, bool & success);
    // search for target node
    BinaryNode* findNode(BinaryNode* treePtr, const string & target) const;
        
    
    BinaryNode* findNameNode(BinaryNode* nodePtr, const string & target) const;
    BinaryNode* _insSecondary(BinaryNode* nodePtr, BinaryNode* newNode);
public:
    
    // insert a node at the correct location
    virtual bool insert(const Clothes& newEntry) override;
    // remove a node if found
    virtual bool remove(const string& anEntry) override;
    // find a target node
    bool getEntry(const string & target, Clothes & returnedItem) const override;
    bool inSecondary ( const Clothes& newEntry);
    virtual bool removesec(const string& anEntry);
    bool getSecondary(const string & target, Clothes & returnedItem) const;
    
};

#endif
