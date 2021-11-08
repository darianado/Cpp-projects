#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <vector>
#include <set>
using std::set;
using std::vector;

// TODO: Your Sudoku class goes here:

class Sudoku
{
private:
    vector<vector<set<int>>> board;
    
public:
    Sudoku(int size){
        set<int> s {1,2,3,4,5,6,7,8,9};
        for(int i=0;i< size;i++)
            for(int j=0;j<size;j++)
                board[i][j]=s;
    }

    int getSquare(int row, int col)
    {
        if(board[row][col].size() > 1) return -1;
        return *board[row][col].begin();
    }
};


#endif
