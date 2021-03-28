#include<bits/stdc++.h>
#include "Node.h"

int Node::ID = 1;

/* Constructors */
Node::Node() {
   this->myID = ID++;
   this->counter = 0;
   this->parent = new Node(-1);
   this->leftChild = new Node(-1);
   this->setChildParent(this->leftChild);
   this->rightChild = new Node(-1);
   this->setChildParent(this->rightChild);
}
/* End of Constructors */

/* Setters and Updates */
    /* Private */
void Node::updateTable(int newID, int fromID){
    if(fromID == this->getLeftChildID())
        this->leftChildTab.insert(newID);
    else if(fromID == this->getRightChildID())
        this->rightChildTab.insert(newID);
    else{
        std::cout << "Error inserting ID : " << newID << " on vertex : " << this->myID << std::endl;
        return;
    }
    if(this->getParentID() != -1)
        this->parent->updateTable(newID, this->myID);
}
void Node::updateTable(int side){
    std::set<int> left, right;
    if(side == 0){
        this->leftChildTab.clear();
        if(this->getLeftChildID() == -1) return;
        left = this->leftChild->getLeftChildTab();
        right = this->leftChild->getRightChildTab();
        for(int x : left) this->leftChildTab.insert(x);
        for(int x : right) this->leftChildTab.insert(x);
        int x = this->leftChild->getMyID();
        if(x != -1)
            this->leftChildTab.insert(x);
    }else if(side == 1){
        this->rightChildTab.clear();
        if(this->getRightChildID() == -1) return;
        left = this->rightChild->getLeftChildTab();
        right = this->rightChild->getRightChildTab();
        for(int x : left) this->rightChildTab.insert(x);
        for(int x : right) this->rightChildTab.insert(x);
        int x = this->rightChild->getMyID();
        if(x != -1)
            this->rightChildTab.insert(x);
    }else{
        std::cout << "Not clear about which child's table the vertex : " << this->myID << " should update" << std::endl;
        return;
    }
}
    /* End of Private */
    /* Public */
void Node::activate(){
    this->counter++;
}
void Node::addChild(Node *newChild){
    if(this->getLeftChildID() == -1){
        this->leftChild = newChild;
        this->leftChildTab.insert(this->getLeftChildID());
    }else if(this->getRightChildID() == -1){
        this->rightChild = newChild;
        this->rightChildTab.insert(this->getRightChildID());
    }else{
        std::cout << "Not enough space on vertex : " << this->myID << " to add new child" << std::endl;
        return;
    }
    if(this->getParentID() != -1)
       	this->parent->updateTable(newChild->getMyID(), this->myID);
    this->setChildParent(newChild);
}
void Node::setChildParent(Node *newChild){
    newChild->setMyParent(this);
}
void Node::setMyParent(Node *parent){
    this->parent = parent;
}
void Node::fix(Node *newChild, Node *formerChild){
    if(formerChild->amRightChild()){
        this->rightChild = newChild;
        this->setChildParent(newChild);
    }else if(formerChild->amRightChild() == 0){
        this->leftChild = newChild;
        this->setChildParent(newChild);
    }else{
        std::cout << formerChild->getMyID() << " is not a son of Vertex : " << this->getMyID() << std::endl;
        return;
    }
}
    /* End of Public */
/* End of Setters and Updates */

/* Route Checkers */
bool Node::amHigh(int srchID){
    if(this->isRightDesc(srchID) or this->isLeftDesc(srchID))
        return 1;
    return 0;
}
bool Node::amI(int srchID){
    return srchID == this->myID;
}
int Node::amRightChild(){
    if(this->parent->getMyID() == -1) return 1;
    return (this->parent->getRightChildID() == this->getMyID() ? 1 : 0);
}
bool Node::isChild(int srchID){
    return (srchID == this->getLeftChildID()) or (srchID == this->getRightChildID());
}
bool Node::isRightDesc(int srchID){
    auto itID = this->rightChildTab.find(srchID);
    if(itID != this->rightChildTab.end())
        return true;
    return false;
}
bool Node::isLeftDesc(int srchID){
    auto itID = this->leftChildTab.find(srchID);
    if(itID != this->leftChildTab.end())
        return true;
    return false;
}
/* End of Route Checkers */

/* Getters */
Node *Node::getRightChild(){
    return this->rightChild;
}
Node *Node::getLeftChild(){
    return this->leftChild;
}
Node *Node::getOtherChild(Node *pref){
    if(this->leftChild == pref)
        return this->rightChild;
    if(this->rightChild == pref)
        return this->leftChild;
    std::cout << pref->getMyID() << " is not a child of the vertex : " << this->getMyID() << std::endl;
    return new Node(-1);
}
Node *Node::getParent(){
    return this->parent;
}
int Node::getMyID(){
    return this->myID;
}
int Node::getLeftChildID(){
    return this->leftChild->getMyID();
}
int Node::getRightChildID(){
    return this->rightChild->getMyID();
}
int Node::getParentID(){
    return this->parent->getMyID();
}
int Node::getCounter(){
    return this->counter;
}
std::set<int> Node::getRightChildTab(){
    return this->rightChildTab;
}
std::set<int> Node::getLeftChildTab(){
    return this->leftChildTab;
}
/* End of Getters */

/* Friend Functions */
void replaceChild(Node *target, Node *receiver, int typ){
    if(typ == 0){
        std::swap(receiver->leftChildTab, target->leftChildTab);
        std::swap(receiver->leftChild, target->leftChild);
        target->leftChild = receiver;
        receiver->setChildParent(receiver->leftChild);
        target->setChildParent(target->leftChild);
        target->updateTable(0);
    }else if(typ == 1){
        std::swap(receiver->leftChildTab, target->rightChildTab);
        std::swap(receiver->leftChild, target->rightChild);
        target->rightChild = receiver;
        receiver->setChildParent(receiver->leftChild);
        target->setChildParent(target->rightChild);
        target->updateTable(1);
    }else if(typ == 2){
        std::swap(receiver->rightChildTab, target->leftChildTab);
        std::swap(receiver->rightChild, target->leftChild);
        target->leftChild = receiver;
        receiver->setChildParent(receiver->rightChild);
        target->setChildParent(target->leftChild);
        target->updateTable(0);
    }else if(typ == 3){
        std::swap(receiver->rightChildTab, target->rightChildTab);
        std::swap(receiver->rightChild, target->rightChild);
        target->rightChild = receiver;
        receiver->setChildParent(receiver->rightChild);
        target->setChildParent(target->rightChild);
        target->updateTable(1);
    }else{
        std::cout << "Invalid type of rotation : " << typ << std::endl;
        return;
    }
}
void childSwap(Node *oldNext, Node *curr, Node *newNext, Node *other){
    if(newNext->amRightChild()){
        oldNext->rightChild = other;
        if(other->amRightChild()){
            curr->rightChild = newNext;
            std::swap(oldNext->rightChildTab, curr->rightChildTab);
            curr->updateTable(0);
        }else{
            curr->leftChild = newNext;
            std::swap(oldNext->rightChildTab, curr->leftChildTab);
            curr->updateTable(1);
        }
    }else{
        oldNext->leftChild = other;
        if(other->amRightChild()){
            curr->rightChild = newNext;
            std::swap(oldNext->leftChildTab, curr->rightChildTab);
            curr->updateTable(0);
        }else{
            curr->leftChild = newNext;
            std::swap(oldNext->leftChildTab, curr->leftChildTab);
            curr->updateTable(1);
        }
    }
    oldNext->setChildParent(other);
    curr->setChildParent(newNext);
}
void printNode(Node *toPrint){
    if(toPrint->myID == -1){
        std::cout << "Empty vertex" << std::endl;
        return;
    }
    std::cout << "Vertex's ID : " << toPrint->myID << std::endl;
    std::cout << "Vertex's Parent : " << toPrint->getParentID() << std::endl;
    std::cout << "Vertex's Left Child : " << toPrint->getLeftChildID() << " || Vertex's Right Child : " << toPrint->getRightChildID() << std::endl;
    std::cout << "Vertex Descendants : " << std::endl;
    for(int x : toPrint->getLeftChildTab()) std::cout << x << " | ";
    for(int x : toPrint->getRightChildTab()) std::cout << " | " << x;
    std::cout << std::endl;
}
/* End of Friend Functions */
