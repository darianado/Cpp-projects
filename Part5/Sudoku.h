#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include "SudokuSquare.h"

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;
#include <set>
using std::set;
#include <math.h> 





// TODO: Your Sudoku class goes here:

class Sudoku : public Searchable
{
private:
    vector<vector<SudokuSquareSet>> board;
    vector<bool> seted;
    
public:
    Sudoku(int size){
        seted.resize(size*size, false);
       SudokuSquareSet s;
    	for (int i = 1; i <= size; i++) {
    		s.insert(i);
    	}

        for(int i=0;i< size;i++)
        {
           vector<SudokuSquareSet> r;
            for(int j=0;j<size;j++)
                {
                    r.push_back(s);
                }
            board.push_back(r); 
        }
    }

    Sudoku(Sudoku const * other){
        seted=other->seted;
        board=other->getBoard();
    }

    void operator==(Sudoku const & other){
        board= other.board;
    }
    vector<vector<SudokuSquareSet>> const & getBoard() const
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
        return board[i][j].size();
    }


    bool setSquare(int row, int col, int value)
    {
        board[row][col].clear();
        board[row][col].insert(value);

        for(int i=0;i< board.size();i++)
        {
            for(int j=0;j<board.size();j++)
            {
                if(board[i][j].size()==1 && !seted[i*board.size()+j]){
                    seted[i*board.size()+j]=true;
                    if(!updateSetSquare(row,col,value)) return false;}
            }
        }
        return true;
    }

    bool solveDuplicHoriz(int row,int col,int howMany)
    {
        int found=1;
        for(int i=0;i<board.size();i++)
        {
            if(i!=col && board[row][i]==board[row][col])
            {
                found++;
                if(found==howMany)
                {     
                   for(int j=0;j<board.size();j++)
                    {
                        if(board[row][j]!=board[row][col])
                        {
                            
                            for(auto x:board[row][col])
                                board[row][j].erase(x);

                            if(board[row][j].empty()) return false;
                            
                            if(board[row][j].size()==1){
                                // seted[row*board.size()+j]=true;
                                if(!updateSetSquare(row,j,*board[row][j].begin())) 
                                    return false;}
                            
                        }
                    }
                }
            }
        }

        return true;
    }

    bool solveDuplicVert(int row,int col,int howMany)
    {
        int found=1;
        for(int i=0;i<board.size();i++)
        {
            if(i!=row && board[i][col]==board[row][col])
            {
                found++;
                if(found==howMany)
                {     
                for(int j=0;j<board.size();j++)
                    {
                        if(board[j][col]!=board[row][col])
                        {
                            for(auto x:board[row][col])
                                board[j][col].erase(x);

                            if(board[j][col].empty()) return false;

                            if(board[j][col].size()==1){
                                // seted[j*board.size()+col]=true;
                                if(!updateSetSquare(j,col,*board[j][col].begin())) 
                                    return false;}
                        }
                    }
                }
            }
        }
         return true;
    }

    bool solveDuplicBox(int row,int col,int howMany)
    {
        int found=1;
        int boxsize = sqrt(board.size());
        int rowboxnr = row - row % boxsize;
        int colboxnr = col - col % boxsize ;

        for(int i=rowboxnr; i< rowboxnr+boxsize; i++)
        {
            for(int j=colboxnr; j< colboxnr+boxsize; j++)
            {
                if(i!=row || j!=col)
                    if(board[i][j]==board[row][col])
                    {  
                        found++;
                        if(found==howMany)
                        {
                            for(int k=rowboxnr; k< rowboxnr+boxsize; k++)
                            {
                                for(int l=colboxnr; l< colboxnr+boxsize; l++)
                                {
                                    if(board[k][l]!=board[row][col])
                                    {
                                        for(auto x:board[row][col])
                                            board[k][l].erase(x);

                                        if(board[k][l].empty()) return false;

                                        if(board[k][l].size()==1){
                                            // seted[k*board.size()+l]=true;
                                            if(!updateSetSquare(k,l,*board[k][l].begin())) 
                                                return false;}
                                    }
                                }
                            }
                        }
                    }
            }
        }
        return true;
    }

        
    
    bool updateSetSquare(int row, int col, int value)
    {
        for(int i=0;i< board.size() ;i++)
        {
            if(i!=col && board[row][i].erase(value))
            {
                if(board[row][i].empty()) return false;
                if(board[row][i].size()==1) {seted[row*board.size()+i]=true;
                    if(!updateSetSquare(row,i,*board[row][i].begin())) return false;}

                else if(board[row][i].size()<=(board.size()/3))
                        if(!solveDuplicHoriz(row,i,board[row][i].size()))return false;
            }
        }

        for(int i=0;i< board.size() ;i++)
        {
            if(i!=row && board[i][col].erase(value))
            {
                if(board[i][col].empty()) return false;
                if(board[i][col].size()==1){seted[i*board.size()+col]=true;
                    if(!updateSetSquare(i,col,*board[i][col].begin())) return false;}
                else if(board[row][i].size()<=(board.size()/3))
                        if(!solveDuplicVert(row,i,board[row][i].size()))return false;
            }
        }

        int boxsize = sqrt(board.size());
        int rowboxnr = row - row % boxsize;
        int colboxnr = col - col % boxsize ;

        for(int i=rowboxnr; i< rowboxnr+boxsize; i++)
        {
            for(int j=colboxnr; j< colboxnr+boxsize; j++)
            {
                if(i!=row && j!=col)
                {  

                    if(board[i][j].erase(value))
                    {
                        if(board[i][j].empty()) 
                            return false;
                        if(board[i][j].size()==1 ){seted[i*board.size()+j]=true;
                            if(!updateSetSquare(i,j,*board[i][j].begin())) return false;}
                        else if(board[row][i].size()<=(board.size()/3))
                                if(!solveDuplicBox(row,i,board[row][i].size()))return false;
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
        
        if(v.size()==1){
            if(!v.front()->isSolution())
                return v.front()->successors();
        }
        return v;
    }

    virtual int heuristicValue() const override
    {
        int c=0;
        for (int i=0;i<board.size();i++) 
        {
            for(int j=0;j<board.size();j++)
            {
                if(board[i][j].size()>1) c++;
            }
        }
        return c;
    }

    
};


#endif