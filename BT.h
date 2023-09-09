//
//  BT.h
//  teamProject

#ifndef teamProject_BT_h
#define teamProject_BT_h

#include "BNode.h"


class BinaryTree
{
private:
    		// ptr to root node (sentinel node)
    int count;							// number of nodes in tree
    void destroyTree(BinaryNode* nodePtr);
    
    // copy from the tree rooted at nodePtr and returns a pointer to the copy
    BinaryNode* copyTree(const BinaryNode *nodePtr);
    
    
    // internal traverse
    void _preorder(void visit(Clothes &), BinaryNode *nodePtr) const;
    void _inorder(void visit(Clothes &), BinaryNode *nodePtr) const;
    void _postorder(void visit(Clothes &), BinaryNode *nodePtr) const;
    void _breadthFirst(void visit(Clothes &), BinaryNode *nodePtr) const;
    int _findHeight(BinaryNode *nodePtr)const;
    void _printlevelorder(void visit(Clothes &),BinaryNode *nodePtr, int level) const;

public:
    // "admin" functions
    BinaryNode *rootPtr;
    BinaryTree() {rootPtr = 0; count = 0;}
    BinaryTree(const BinaryTree &tree){rootPtr = copyTree(tree.rootPtr);}
    virtual ~BinaryTree() { }
    BinaryTree & operator = (const BinaryTree &sourceTree);
    
    // common functions for all binary trees
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void preOrder(void visit(Clothes &)) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(Clothes &)) const  {_inorder(visit, rootPtr);}
    void postOrder(void visit(Clothes &)) const{_postorder(visit, rootPtr);}
    
    //to print the node in breath first order
    void breadthFirst(void visit(Clothes &)) const{_breadthFirst(visit,rootPtr);}
    
    //to print nodes by level order
    void printlevelOrder(void visit(Clothes &)) const {int level=0; _printlevelorder(visit,rootPtr,level);}
    
    //find the height of the tree
    void findHeight() const {_findHeight(rootPtr);}
    
    
    
    // abstract functions to be implemented by derived class
    virtual bool insert(const Clothes & newData) = 0;
    virtual bool remove(const string & data) = 0;
    virtual bool getEntry(const string & anEntry, Clothes & returnedItem) const = 0;
    // delete all nodes from the tree
};
//////////////////////////////////////////////////////////////////////////

//call from find height function
//find the height of the binary tree

#endif