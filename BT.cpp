//
//  BT.cpp
//  teamProject

#include "BT.h"

int BinaryTree::_findHeight(BinaryNode *nodePtr) const
{
    if(nodePtr==0)
        return 0;
    else
    {
        int lheight = _findHeight(nodePtr->getLeftPtr());
        int rheight = _findHeight(nodePtr->getRightPtr());
        
        if(lheight>rheight)
            return (lheight+1);
        else
            return(rheight +1);
    }
}
//call from print level order
//print the tree nodes from root-right-left
void BinaryTree::_printlevelorder(void visit(Clothes &),BinaryNode *nodePtr, int level) const
{
    if(nodePtr)
    {
        Clothes data;
        data.setPrimary(nodePtr->getItemPrimary());
        data.setSecondary(nodePtr->getItemSecondary());
        data.setPrice(nodePtr->getItemPrice());
        data.setMaterial(nodePtr->getItemMat());
        data.setType(nodePtr->getItemType());
        for(int i = 0; i < level; i++)
            cout << "\t";
        cout << level+1 << ". ";
        
        visit(data);
        level++;
        _printlevelorder(visit, nodePtr->getRightPtr(),level);
        _printlevelorder(visit, nodePtr->getLeftPtr(),level);
    }
}
//constructor
//copy the binary tree to a new binary tree
BinaryNode *BinaryTree::copyTree(const BinaryNode *nodePtr)
{
    BinaryNode *newNodePtr = 0;
    if(nodePtr)
    {
        newNodePtr = new BinaryNode();
        newNodePtr->setItemPrimary(nodePtr->getItemPrimary());
        newNodePtr->setItemSecondary(nodePtr->getItemSecondary());
        newNodePtr->setItemPrice(nodePtr->getItemPrice());
        newNodePtr->setItemMat(nodePtr->getItemMat());
        newNodePtr->setItemType(nodePtr->getItemType());
        newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
        newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
    }
    return newNodePtr;
}
//destructor

void BinaryTree::destroyTree(BinaryNode* nodePtr)
{
    if(nodePtr != 0)
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        free(nodePtr);
    }
}

//recursion function
//call from preorder function
//process them in pre order

void BinaryTree::_preorder(void visit(Clothes &), BinaryNode* nodePtr) const
{
    if (nodePtr != 0)
    {
        Clothes item;
        item.setPrimary(nodePtr->getItemPrimary());
        item.setSecondary(nodePtr->getItemSecondary());
        item.setPrice(nodePtr->getItemPrice());
        item.setMaterial(nodePtr->getItemMat());
        item.setType(nodePtr->getItemType());
        visit(item); //to print
        _preorder(visit, nodePtr->getLeftPtr()); //pass the function
        _preorder(visit, nodePtr->getRightPtr());
    }
}

//call from inorder function

void BinaryTree::_inorder(void visit(Clothes &), BinaryNode* nodePtr) const
{
    if(nodePtr != 0)
    {
        Clothes item;
        item.setPrimary(nodePtr->getItemPrimary());
        item.setSecondary(nodePtr->getItemSecondary());
        item.setPrice(nodePtr->getItemPrice());
        item.setMaterial(nodePtr->getItemMat());
        item.setType(nodePtr->getItemType());
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

//call from postorder function

void BinaryTree::_postorder(void visit(Clothes &), BinaryNode* nodePtr) const
{
    if(nodePtr != 0)
    {
        Clothes item;
        item.setPrimary(nodePtr->getItemPrimary());
        item.setSecondary(nodePtr->getItemSecondary());
        item.setPrice(nodePtr->getItemPrice());
        item.setMaterial(nodePtr->getItemMat());
        item.setType(nodePtr->getItemType());
        _postorder(visit, nodePtr->getLeftPtr()); //pass the function
        _postorder(visit, nodePtr->getRightPtr());
        visit(item);
    }
}


BinaryTree &BinaryTree::operator=(const BinaryTree & sourceTree)
{
    rootPtr = copyTree(sourceTree.rootPtr);
    return *this;
}

