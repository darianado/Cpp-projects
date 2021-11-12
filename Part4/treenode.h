#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:

template<typename T>
class TreeNode{
public:
    T data;
    unique_ptr<TreeNode> leftChild;
    unique_ptr<TreeNode> rightChild;
    TreeNode * parent;

    TreeNode(T const & d):data(d), parent(nullptr){
    }

    void setLeftChild(TreeNode<T>* child)
    {
        leftChild.reset(child);
        child->parent = this;
    }

    void setRightChild(TreeNode<T>* child)
    {
        rightChild.reset(child);
        child->parent = this;
    }
    
    void write(ostream & print) const {
        if(leftChild) {leftChild->write(print); }
        print<<" ";
        print<<data;
        print<<" ";
        if(rightChild) {rightChild->write(print);}
    }

    int maxDepth()
    {
        if(!leftChild)
            if(!rightChild)
                return 1;
            else return 1 + rightChild->maxDepth();
        else 
            if(!rightChild) 
                return 1+leftChild->maxDepth();
            else 
                return 1 + std::max(rightChild->maxDepth(),leftChild->maxDepth());
      
    }

    int balanceFactor()
    {
        int lmd, rmd;
        if(leftChild) lmd = leftChild->maxDepth();
        else lmd = 0;

        if(rightChild) rmd = rightChild->maxDepth();
        else rmd = 0;

        return lmd - rmd;
    }

    bool rebalance()
    {
        if(balanceFactor() == 2 || balanceFactor() == -2) 
            return true;
        return false;
    }
};


template<typename T>
class TreeNodeIterator{
private:
    TreeNode<T> * current;
public:
    TreeNodeIterator(TreeNode<T> & node): current(&node){
    }

     TreeNodeIterator():current(nullptr){
     }

    T & operator*()
    {
        return current->data;
    }

    TreeNode<T> * & get()
    {
        return current;
    }

    bool operator==(TreeNodeIterator<T> const & other) const{
        return current==other.current;
    }

     bool operator!=(TreeNodeIterator<T> const & other) const{
        return current!=other.current;
    }

    void operator++()
    {
        T dela = current->data;
        if(current->rightChild==nullptr)
        {
            while(current->parent)
                current=current->parent;
        }
        else  current = current->rightChild.get();
        if(current->data<dela) current=nullptr;
    }

};

// do not edit below this line

#endif
