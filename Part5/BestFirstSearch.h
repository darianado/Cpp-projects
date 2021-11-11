#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <memory>
using std::unique_ptr;

#include <deque>
using std::deque;

#include <algorithm>

class BestFirstSearch {

protected:

     /** A queue of incomplete solutions: initially, the board we start with */
    deque<unique_ptr<Searchable> > Q;
    
    /** How many nodes (boards) we made successors for, in order to solve the problem */    
    int nodes = 0;
    
    
public:

    BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        // TODO Put startFrom onto the queue:
        Q.push_back(std::move(startFrom));
    }
    
    int getNodesExpanded() const {
        return nodes;
    }
    
    Searchable * solve() {
            
        // TODO Implement search, returning a pointer to the solution (if one is found)
         // If there are still incomplete solutions on the queue
        while (!Q.empty()) 
        {
            
            // If the solution on the front of the queue is a solution 
            if (Q.front()->isSolution()) {
                return Q.front().get(); // return the pointer 
            }
                  
            ++nodes; // we've now looked at one more node, increment our counter
            
            // Steal the pointer to the board at the front of the queue, by moving it into a unique_ptr here
            // After this, the pointer on the front of the queue is `nullptr`...
            unique_ptr<Searchable> current(std::move(Q.front()));
            
            // ...which can then be popped off the front of the queue
            Q.pop_front();
            
            // Get the successors...
            vector<unique_ptr<Searchable>> successors = current->successors();
            
            for (auto & successor : successors) {
                // and push each one onto the back of queue.
                //std::cout<<successor->heuristicValue()<<"->";
                Q.push_back(std::move(successor));
            }
            std::sort(Q.begin(),Q.end());
        }
        return nullptr;
    }
};


// Do not edit below this line

#endif
