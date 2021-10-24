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

    void setLeftChild(TreeNode* child)
    {
        leftChild.reset(child);
        child->parent = this;
    }

    void setRightChild(TreeNode* child)
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



};


// do not edit below this line

#endif
