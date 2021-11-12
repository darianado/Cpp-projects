#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H


#include <string>
using std::string;




// TODO: your code goes here:

#include<vector>
using std::vector;


void substrings(string s, vector<int> & cur, int start) 
{
    int n =  s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
     {
        if (i <= r)
            z[i] = std::min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;

        if(z[i]>cur[i+start])cur[i+start]=z[i];
    }
}


int stringConstruction(string s,int cl,int ap)
{
  vector<int> costs(s.size(),0);
  for(int i=0;i<s.size()-1;i++)
  {
     substrings(s.substr(i),costs,i);
  }

  int here=0;
  for (int i=0;i<costs.size();i++)
  {
      if(costs[i]==0)here+=ap;
      else 
        if(costs[i]>i) here+=ap;
        else
        {
          if(cl<=costs[i]*ap && costs[i]>costs[i+1])
            {here+=cl;i+=costs[i]-1;}
          else here+=ap;
        }
  }
  return here;
}



// do not write or edit anything below this line

#endif
