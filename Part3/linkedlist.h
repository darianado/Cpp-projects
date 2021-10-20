#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:

template<typename T>
class LinkedList{
private:
    Node<T>* head;
    Node<T>* tail;
    int count;
public:
    LinkedList():
        head(nullptr),tail(nullptr),count(0){}

    ~LinkedList()
    {
        Node<T> *curr = head;
        while(curr)
        {
            Node<T> *n = curr->next;
            delete curr;
            curr = n;
        }
    }
    
    void push_front(const T & elem)
    {
        count ++;
        Node<T> * x = new Node<T>(elem);
        x->next = head;
        head->previous = x;
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
        if(tail) {tail->next = x; x->previous=tail;}
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
