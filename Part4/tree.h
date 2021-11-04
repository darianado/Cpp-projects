#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:

#include <sstream>

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

    void write(ostream & print) const
    {
        root->write(print);
    }

    TreeNode<T>* insert(T const & data)
    {
        TreeNode<T>* nou = new TreeNode<T>(data);
        std::ostringstream s;
        nou->write(s);
        std::cout<<"=> "<<s.str()<<"\n";

        if(!root){
            root.reset(nou);
            return nou;
        }

      TreeNode<T>* cur = root.get();
      while(cur){
          if(data<cur->data)
          {
              if(cur->leftChild==nullptr)
                {
                    cur->setLeftChild(nou);
                    nou->parent = cur;
                    break;
                    //return nou;
                }
              cur= cur->leftChild.get();
          }
          else if(cur->data < data){
               if(cur->rightChild==nullptr)
                {
                    cur->setRightChild(nou);
                    nou->parent = cur;
                    break;
                    //return nou;
                }
              cur=cur->rightChild.get();
          }
                else{
                    delete nou;
                    return cur;
                }
      }
      if(nou->parent && nou->parent->parent)
        if(nou->parent->parent->rebalance())
            {
                    // std::ostringstream s2;
                    // root->write(s2);
                    // std::cout<<"avl inainte: "<<s2.str()<<"\n";
                avl(nou);
            }

    // std::ostringstream s1;
    // nou->write(s1);
    // std::cout<<"--- "<<s1.str()<<"\n";

    return nou;
    
    }


    void avl(TreeNode<T> *  c)
    {
        TreeNode<T> * p1 = c->parent;
        TreeNode<T> * p2 = p1->parent;

        if(c->data < p1->data) 
            if (p1->data < p2->data)//p1 mij, p2 in rightchild p1
            {
                p1= p2->leftChild.release();

                if(p2 == root.get())
                {
                    p2 = root.release();
                    root.reset(p1);
                    
                }else
                {
                    TreeNode<T>* aux = p2->parent;
                    if(aux->data < p1->data)
                    {
                        p2= aux->rightChild.release();
                        aux->setRightChild(p1);
                    }  
                    else {
                        p2= aux->leftChild.release();
                        aux->setLeftChild(p1);
                    }
                }
                p1->setRightChild(p2);   
            }
                
            else //p2 ia val c, c cu val lu p2 in stanga
            {
                T aux = p2->data;
                p2->data = c->data;
                c->data= aux;

                c= p1->leftChild.release();
                p2->setLeftChild(c);
            }
        else
            if( p1->data < p2->data) //p1 mij, p2 mutat leftchild p1
            {
                T aux = p2->data;
                p2->data = c->data;
                c->data= aux;

                c= p1->rightChild.release();
                p2->setRightChild(c);

            }
            else // p2 mij, c mutat rightchild p2
            {
                p1= p2->rightChild.release();

                if(p2 == root.get())
                {
                    p2 = root.release();
                    root.reset(p1);
                    
                }else
                {
                    TreeNode<T>* aux = p2->parent;
                    if(aux->data < p1->data)
                    {
                        p2= aux->rightChild.release();
                        aux->setRightChild(p1);
                    }  
                    else {
                        p2= aux->leftChild.release();
                        aux->setLeftChild(p1);
                    }
                }
                p1->setLeftChild(p2);
            }
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
    
    TreeNodeIterator<T> begin()
    {
        TreeNode<T>* b = root.get();
        if(b==nullptr) return TreeNodeIterator<T>();

        while(b->leftChild) 
             b = b->leftChild.get();
        return TreeNodeIterator<T>(*b);  

    }

    TreeNodeIterator<T> end()
    {
        return TreeNodeIterator<T>();
    }

    int maxDepth()
    {
        if(!root) return 0;

        return root->maxDepth();
    }

};



// do not edit below this line

#endif
