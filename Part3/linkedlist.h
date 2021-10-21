#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:

#include <initializer_list>


template<typename T>
class LinkedList{
private:
    Node<T>* head;
    Node<T>* tail;
    int count;
public:
    LinkedList():
        head(nullptr),tail(nullptr),count(0){}

    LinkedList(std::initializer_list<T> l){

        count=l.size();
        Node<T> *curr = new Node<T>(*l.begin());
       
        head= curr;
        tail= curr;

        auto itr = l.begin();
        ++itr;
         
        while(itr!=l.end()){
            push_back(*itr);
            ++itr;
        }
    }

    ~LinkedList()
    {
        Node<T> *curr = head;
        while(curr)
        {
            Node<T> *n = curr->next;
            delete curr;
            curr = n;
        }
        count=0;
    }

    NodeIterator<T> const & insert(NodeIterator<T> & nit, T const & elem)
    {
        Node<T> *n = new Node<T>(elem);
        count++;
        n->previous= nit.getNode()->previous;
        nit.getNode()->previous->next = n;
        n->next= nit.getNode();
        nit.getNode()->previous =n;

        nit = NodeIterator<T>(n);
        return nit;
        
    }
    
    NodeIterator<T> const & erase(NodeIterator<T> & nit)
    {
        count--;
        if(nit.getNode()->next)
            nit.getNode()->next->previous = nit.getNode()->previous;
        else tail= nit.getNode()->previous;
        if(nit.getNode()->previous)
            nit.getNode()->previous->next = nit.getNode()->next;
        else head= nit.getNode()->next;


        ++nit;
        return nit;
    }

    void push_front(const T & elem)
    {
        count ++;
        Node<T> * x = new Node<T>(elem);
        x->next = head;
        if (head) head->previous = x;
        else tail =x;
        head = x; 
    }

    T const & front() 
    {
        NodeIterator<T> n = NodeIterator<T>(head);
        return *n;
    }

    void push_back(const T & elem)
    {
        count++;
        Node<T> * x = new Node<T>(elem);
        if(tail) tail->next = x;
        else head = x;
        x->previous=tail;
        tail = x;
    }

     T const & back() 
    {
        NodeIterator<T> n = NodeIterator<T>(tail);
        return *n;
    }

    int size() const
    {
        return count;
    }

    NodeIterator<T> begin() 
    {
        return NodeIterator<T>(head);
    }

    NodeIterator<T> end()
    {
        return nullptr;
    }

    NodeIterator<T> const begin() const
    {
        return NodeIterator<T>(head);
    }

    NodeIterator<T> const end() const
    {
        return nullptr;
    }

    void reverse()
    {

        Node<T> * now = tail;
        head = tail;
        

        Node<T> * aux ;

        while(now !=nullptr)
        {
            aux = now->previous;
            now->previous = now->next;
            now->next = aux;
            tail=now;
            now=now->next;
        }
    }


};


// do not edit below this line

#endif
