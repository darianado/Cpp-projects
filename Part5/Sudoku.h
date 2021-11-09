#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"

#include <vector>
using std::vector;
#include <set>
using std::set;
#include <math.h> 

#include <iostream>
using std::cout;
using std::endl;

// TODO: Your Sudoku class goes here:

class Sudoku : public Searchable
{
private:
    vector<vector<set<int>>> board;
    
public:
    Sudoku(int size){
       set<int> s;
    	for (int i = 1; i <= size; i++) {
    		s.insert(i);
    	}

        for(int i=0;i< size;i++)
        {
           vector<set<int>> r;
            for(int j=0;j<size;j++)
                {
                    r.push_back(s);
                }
            board.push_back(r); 
        }
    }

    Sudoku(Sudoku const * other){
        board=other->getBoard();
    }

    vector<vector<set<int>>> const & getBoard() const
    {
        return board;
    }
    int getSquare(int row, int col) const
    {
        if(board[row][col].size() > 1) return -1;
        else return *board[row][col].begin();
    }
    int getval(int i, int j)
    {
        // if(board[i][j].size()==1)
        //     return *board[i][j].begin();
        return board[i][j].size();
    }

    bool setSquare(int row, int col, int value)
    {
        //board[row][col].clear();
        // board[row][col].insert(value);
        board[row][col] = {value};
        //std::cout<<"-------"<<*board[row][col].begin()<<"\n";

        // if(!updateSetSquare(row,col,value)) return false;
        for(int i=0;i< board.size();i++)
        {
            for(int j=0;j<board.size();j++)
            {
                if(board[i][j].size()==1)
                    if(!updateSetSquare(row,col,value)) return false;
            }
        }
        return true;
        
    }
    bool updateSetSquare(int row, int col, int value)
    {
        for(int i=0;i< board.size() ;i++)
        {
            if(i!=col && board[row][i].erase(value)) {
                
                if(board[row][i].empty()) return false;
                if(board[row][i].size()==1) 
                    if(!updateSetSquare(row,i,*board[row][i].begin())) return false;
            }
        }

        for(int i=0;i< board.size() ;i++)
        {
            if(i!=row && board[i][col].erase(value)){
                
                if(board[i][col].empty()) return false;
                if(board[i][col].size()==1)
                        if(!updateSetSquare(i,col,*board[i][col].begin())) return false;
            }
        }

        int boxsize = sqrt(board.size());
        int rowboxnr = row - row % boxsize;
        int colboxnr = col - col % boxsize ;
        // std::cout<<" for row "<<row<<" col "<<col<<" and val "<<value<<" box starts at row "<<rowboxnr<<" and col "<<colboxnr<<"\n";
        for(int i=rowboxnr; i< rowboxnr+boxsize; i++)
        {
            for(int j=colboxnr; j< colboxnr+boxsize; j++)
            {
                if(i!=row || j!=col){  

                    if(board[i][j].erase(value)){
                        if(board[i][j].empty()) 
                            return false;
                        if(board[i][j].size()==1 )
                            if(!updateSetSquare(i,j,*board[i][j].begin())) return false;
                    }
                }
            }
        }

        return true;

                
    }

    virtual bool isSolution() const override{
        for(int i=0;i< board.size();i++)
        {
            for(int j=0;j<board.size();j++)
            {
                if(board[i][j].size()!=1) return false;
            }
        }
        return true;
    }
    virtual void write(ostream & o) const{
        for (int i=0;i<board.size();i++) 
        {
            for(int j=0;j<board.size();j++)
                if(getSquare(i,j)==-1)cout << " ";
                else cout << getSquare(i,j);
            cout<<"\n";
        }
    }
    
    virtual vector<unique_ptr<Searchable> > successors() const
    {
        vector<unique_ptr<Searchable>> v;
        int row=-1,col=-1;
        for (int i=0;i<board.size();i++) 
        {
            for(int j=0;j<board.size();j++)
            {
                if(board[i][j].size()!=1)
                    {row=i;col=j;break;}
            }
            if(row>=0) break;
        }

        for(auto x: board[row][col])
        {
            Sudoku* copy = new Sudoku(this);
            if(copy->setSquare(row,col,x))
            {
                v.emplace_back(copy);
            }
            else delete copy;

        }


        return v;
    }
};


#endif
