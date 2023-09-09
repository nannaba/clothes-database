//
//  BST.cpp
//  teamProject


#include "BST.h"

bool BinarySearchTree::inSecondary(const Clothes& newEntry)
{
    BinaryNode* newNodePtr = new BinaryNode();
    newNodePtr->setItemPrimary(newEntry.getPrimary());
    newNodePtr->setItemSecondary(newEntry.getSecondary());
    newNodePtr->setItemPrice(newEntry.getPrice());
    newNodePtr->setItemMat(newEntry.getMaterial());
    newNodePtr->setItemType(newEntry.getType());
    this->rootPtr = _insSecondary(this->rootPtr, newNodePtr);
    return true;
}
bool BinarySearchTree::insert(const Clothes & newEntry)
{
    BinaryNode* newNodePtr = new BinaryNode();
    newNodePtr->setItemPrimary(newEntry.getPrimary());
    newNodePtr->setItemSecondary(newEntry.getSecondary());
    newNodePtr->setItemPrice(newEntry.getPrice());
    newNodePtr->setItemMat(newEntry.getMaterial());
    newNodePtr->setItemType(newEntry.getType());
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

bool BinarySearchTree::remove(const string & target)
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}

bool BinarySearchTree::removesec(const string & target)
{
    bool isSuccessful = false;
    this->rootPtr = _removesec(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}

bool BinarySearchTree::getEntry(const string & anEntry, Clothes & returnedItem) const
{
    BinaryNode* tempItem = this->rootPtr;
    BinaryNode* reItem;
    
    reItem = findNode(tempItem, anEntry);
    if(reItem == 0)
        return false;
    else
        if( anEntry == reItem->getItemPrimary())
        {
            returnedItem.setPrimary(reItem->getItemPrimary());
            returnedItem.setSecondary(reItem->getItemSecondary());
            returnedItem.setMaterial(reItem->getItemMat());
            returnedItem.setPrice(reItem->getItemPrice());
            returnedItem.setType(reItem->getItemType());
            return true;
        }
        else
            return false;
}
bool BinarySearchTree::getSecondary(const string & anEntry, Clothes & returnedItem) const
{
    BinaryNode* tempItem = this->rootPtr;
    BinaryNode* reItem;
    
    reItem = findNameNode(tempItem, anEntry);
    if(reItem == 0)
        return false;
    else
        if(anEntry == reItem->getItemSecondary())
        {
            returnedItem.setPrimary(reItem->getItemPrimary());
            returnedItem.setSecondary(reItem->getItemSecondary());
            returnedItem.setMaterial(reItem->getItemMat());
            returnedItem.setPrice(reItem->getItemPrice());
            returnedItem.setType(reItem->getItemType());
            return true;
        }
        else
            return false;
}


//////////////////////////// private functions ////////////////////////////////////////////

BinaryNode* BinarySearchTree::_insert(BinaryNode* nodePtr,BinaryNode* newNodePtr)
{
    if (nodePtr == 0)
    {
        return newNodePtr;
    }
    if (newNodePtr->getItemPrimary() >= nodePtr->getItemPrimary())
    {
        if (nodePtr->getRightPtr() != 0)
            _insert(nodePtr->getRightPtr(), newNodePtr);
        else
            nodePtr->setRightPtr(newNodePtr);
    }
    else if (newNodePtr->getItemPrimary() < nodePtr->getItemPrimary())
    {
        if (nodePtr->getLeftPtr() != 0)
            _insert(nodePtr->getLeftPtr(), newNodePtr);
        else
            nodePtr->setLeftPtr(newNodePtr);
    }
    return nodePtr;
}
BinaryNode* BinarySearchTree::_insSecondary(BinaryNode* nodePtr,BinaryNode* newNodePtr)
    {
        if (nodePtr == 0)
        {
            return newNodePtr;
        }
        if (newNodePtr->getItemSecondary() >= nodePtr->getItemSecondary())
        {
            if (nodePtr->getRightPtr() != 0)
                _insSecondary(nodePtr->getRightPtr(), newNodePtr);
            else
                nodePtr->setRightPtr(newNodePtr);
        }
        else if (newNodePtr->getItemSecondary() < nodePtr->getItemSecondary())
        {
            if (nodePtr->getLeftPtr() != 0)
                _insSecondary(nodePtr->getLeftPtr(), newNodePtr);
            else
                nodePtr->setLeftPtr(newNodePtr);
        }
        return nodePtr;
    }
//recursive function
BinaryNode* BinarySearchTree::_remove(BinaryNode* nodePtr,const string target,bool & success)

{
    if (nodePtr == 0)
    {
        success = false; //empty node
        return 0;
    }
    if (nodePtr->getItemPrimary() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    
    else if (nodePtr->getItemPrimary() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    
    else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}
BinaryNode* BinarySearchTree::_removesec(BinaryNode* nodePtr,const string target,bool & success)

{
    if (nodePtr == 0)
    {
        success = false; //empty node
        return 0;
    }
    if (nodePtr->getItemSecondary() > target)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    
    else if (nodePtr->getItemSecondary() < target)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    
    else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

BinaryNode* BinarySearchTree::deleteNode(BinaryNode* nodePtr)
{
    if (nodePtr->isLeaf()) //leaf function?
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        Clothes data;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), data));
        nodePtr->setItemPrimary(data.getPrimary());
        nodePtr->setItemSecondary(data.getSecondary());
        nodePtr->setItemPrice(data.getPrice());
        nodePtr->setItemType(data.getType());
        nodePtr->setItemMat(data.getMaterial());
        return nodePtr;
        
    }
}


BinaryNode* BinarySearchTree::removeLeftmostNode(BinaryNode* nodePtr,Clothes & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor.setPrimary(nodePtr->getItemPrimary());
        successor.setSecondary(nodePtr->getItemSecondary());
        successor.setPrice(nodePtr->getItemPrice());
        successor.setMaterial(nodePtr->getItemMat());
        successor.setType(nodePtr->getItemType());
        
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(),successor));
        return nodePtr;
    }
}

BinaryNode* BinarySearchTree::findNameNode(BinaryNode* nodePtr, const string & target) const
{
    if(nodePtr == 0)
    {
        return nodePtr;
    }
    if( target < nodePtr->getItemSecondary())
        return findNameNode(nodePtr->getLeftPtr(), target);
    else
        if (target > nodePtr->getItemSecondary())
            return findNameNode(nodePtr->getRightPtr(), target);
        else
            
            return nodePtr;
}
BinaryNode* BinarySearchTree::findNode(BinaryNode* nodePtr,const string & target) const
{
    if(nodePtr == 0)
    {
        return nodePtr;
    }
    if( target < nodePtr->getItemPrimary())
        return findNode(nodePtr->getLeftPtr(), target);
    else
        if (target > nodePtr->getItemPrimary())
            return findNode(nodePtr->getRightPtr(), target);
        else
            
            return nodePtr;
}
