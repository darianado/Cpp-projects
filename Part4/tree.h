#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:

template<typename T>
class BinarySearchTree{
private:
    unique_ptr<TreeNode<T>> root;
public:
    BinarySearchTree(){}

    BinarySearchTree(BinarySearchTree const & other) {
        insertCopyNode(other.getRoot());
    }

    void insertCopyNode(TreeNode<T> * const & x)
    {
        if(x!=nullptr){
            insert(x->data);
            insertCopyNode(x->leftChild.get());
            insertCopyNode(x->rightChild.get());
        }
    }

    TreeNode<T> * getRoot() const
    {
        return root.get();
    }

    void write(ostream & print)
    {
        root->write(print);
    }

    TreeNode<T>* insert(T data)
    {
        
      TreeNode<T>* nou = new TreeNode<T>(data);
      TreeNode<T>* cur = root.get();
      while(cur){
          if(data<cur->data)
          {
              if(cur->leftChild==nullptr)
                {
                    cur->setLeftChild(nou);
                    nou->parent = cur;
                    return nou;
                }
              cur= cur->leftChild.get();
          }
          else if(cur->data < data){
               if(cur->rightChild==nullptr)
                {
                    cur->setRightChild(nou);
                    nou->parent = cur;
                    return nou;
                }
              cur=cur->rightChild.get();
          }
                else{
                    delete nou;
                    return cur;
                }
      }

        root.reset(nou);
        return nou;

    }
    
 TreeNode<T>* find(T const & data)
    {
        TreeNode<T>* cur = root.get();
        while(cur){
            if(data<cur->data)
            {
                cur= cur->leftChild.get();
            }
            else if(cur->data < data){
                cur=cur->rightChild.get();
            }
                    else{
                        return cur;
                    }
        }
        return nullptr;

    }
    
};



// do not edit below this line

#endif
