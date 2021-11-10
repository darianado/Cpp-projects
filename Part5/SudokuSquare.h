#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

// Do not add any #include statements to this file


class SudokuSquareSet {

    // TODO: write your code here
private:
    unsigned int vals;
    int count;
public:
    SudokuSquareSet(){
        vals = 0;
        count=0;
    }

    int size() const
    {
        //std::cout<<"------size";
        return count;
    }

    bool empty() const 
    {
        return count==0;
    }

    void clear()
    {
        vals=0;
        count=0;
    }

    bool operator==(SudokuSquareSet const & other) const
    {
        return vals==other.vals;
    }

    bool operator!=(SudokuSquareSet const & other) const
    {
        return vals!=other.vals;
    }



     class SudokuSquareSetIterator
    {
        private:
            SudokuSquareSet* itr;
            int pos;
        public:
            SudokuSquareSetIterator(SudokuSquareSet * set): itr(set){
                unsigned int aux = itr->vals;
                pos=-1;
                do pos++;
                while( !(aux & (1<<pos)) );
            }

            SudokuSquareSetIterator(): itr(nullptr), pos(0){}

            void operator++()
            {
                unsigned int aux = itr->vals;
                do pos++;
                while( !(aux & (1<<pos)) );


                if(pos>=32) {
                    itr = nullptr;
                    pos=0;
                }
            }

            void setPos(int x)
            {
                pos = x;
            }

            int getPos()
            {
                return pos;
            }

            int operator*()
            {
                //if( (*itr << pos)  & 1) 
                return pos+1;
            }

            bool operator==(SudokuSquareSetIterator const & other)
            {
                return itr==other.itr && pos==other.pos;
            }

            bool operator!=(SudokuSquareSetIterator const & other)
            {
                return !(itr==other.itr && pos==other.pos);
            }


            
    };





    SudokuSquareSetIterator begin()
    {
        SudokuSquareSetIterator itr(this); 
        return itr;
    }

    SudokuSquareSetIterator end()
    {
        return SudokuSquareSetIterator();
    }

    SudokuSquareSetIterator insert(int what)
    {
        count++;
        //std::cout<<"------insert"<<what;
        unsigned int mask = 1;
        for(int i= 1;i<what;i++)
            mask= mask*2;
        //std::cout<<"->mask"<<mask;
        
        vals = vals | mask;
        //std::cout<<"->vals"<<vals;
        SudokuSquareSetIterator itr(this);
        itr.setPos(what-1);
        // while(what){
        //     ++itr; what--;
        // }
        //std::cout<<"->itr"<<*itr<<std::endl;
        return itr;
    }

    SudokuSquareSetIterator find(int what)
    {
        SudokuSquareSetIterator itr(this);
        
        while( itr.getPos()!=what-1)
            {
                ++itr;
                if(itr==end()) return end();
            } 
        //std::cout<<"found "<<what<<"at pos"<<*itr<<"\n";

        //if(itr==end()) return end();
        return itr;
        
    }

    void erase(int what)
    {
       SudokuSquareSetIterator itr = find(what);
       //std::cout<<"erase now from pos"<<*itr<<"\n";
       if(itr==end());
       else
       {
           //std::cout<<"val before"<<vals<<"\n";
            count--;
            unsigned int mask = 1;
            for(int i= 1;i<=itr.getPos();i++)
                mask= mask*2;
            //std::cout<<"the mask for delet"<<mask<<"\n";
            vals = vals - mask;
            //std::cout<<"val after del"<<vals<<"\n\n";
       }

    }

    void erase(SudokuSquareSetIterator itr)
    {
        count--;
        unsigned int mask = 1;
        for(int i= 1;i<=itr.getPos();i++)
            mask= mask*2;
        vals = vals - mask;
    }


};

 


// Do not write any code below this line
static_assert(sizeof(SudokuSquareSet) == sizeof(unsigned int) + sizeof(int), "The SudokuSquareSet class needs to have exactly two 'int' member variables, and no others");


#endif
