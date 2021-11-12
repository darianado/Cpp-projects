#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <iostream>
#include <string>
using std::string;
#include<vector>
using std::vector;



// TODO: your code goes here:
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
    //return z;
}


int best_clone(string s)
{
    int j = s.size() - 1;

  //std::cout<<s.substr(0,j)<<" find  "<<s.substr(0+j)<<"=>"<<s.substr(0,j).find(s.substr(j))<<"\n";
    while (  j>0&& s.substr(0,j).find(s.substr(j))!=std::string::npos )//s[j:] in s[:j]:
      {
          //std::cout<<s.substr(0,j)<<" find  "<<s.substr(0+j)<<"\n";
          j--;
      }
    //std::cout<<j+1<<"\n";
    return j + 1;
  }


int stringConstruction(string s,int cl,int ap)
{
  vector<int> costs(s.size(),0);
  for(int i=0;i<s.size()-1;i++)
  {
     substrings(s.substr(i),costs,i);

      // for (int i: costs)
      // std::cout << i << ' ';
      // std::cout<<"\n";

    // for(int j=i;i<s.size()-1;j++)
    //   if(c[j]>costs[j]) costs[j]=c[j];
  }


  // vector<int> costs = z_function(s);
  
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
      //std::cout<<here<<" la elem "<<i<<"\n";

  }

  // costs.push_back(0);
  // for (int i=0;i<s.size();i++)
  //   {
  //       int cost = costs[i] + ap;
  //       int j = best_clone( s.substr(0, i+1) );
  //       if (j <= i){
  //          //std::cout<<cost<<" saaau "<<costs[j] + cl<<"\n";
  //          cost = std::min(cost, costs[j] + cl);

  //       }
  //       costs.push_back(cost);
  //       //std::cout<<"-------"<<cost<<"\n";
  //   }
  // return costs.back();
  return here;
}



// do not write or edit anything below this line

#endif
