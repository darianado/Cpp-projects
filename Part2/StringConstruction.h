#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <iostream>
#include <string>
using std::string;
#include<vector>
using std::vector;



// TODO: your code goes here:
// void createString(string s,int cl,int a,int costNow=0,string strNow=""){
//
//   vector<string> prefixes;
//   for(int i=0;i<s.size();i++)
//   {
//     prefixes.push_back(substr(s.begin(),i+1));
//   }
//
//
//   if(!nchar(s))
//     return costNow;
//
//   else{
//     y={}
//     # prepend the first letter of s (=append operation) to
//     # the prefixes in p that are contained in strNow (=clone operations)
//     for(i in c(substring(s,1,1),p[mapply(grepl,p,x)])){
//       # perform first the append then the clone operations and recurse,
//       # storing the cost in y if lower than previous
//       # (if y is NULL is an append operation otherwise is a clone, we use the right costs)
//       y = min(y,f(substring(s,nchar(i)+1),a,c,k+'if'(any(y),c,a),paste0(x,i)))
//     }
//     # return the current cost
//     y
//   }
// }






int best_clone(string s){
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


int stringConstruction(string s,int cl,int ap){
  vector<int> costs;
  costs.push_back(0);
  for (int i=0;i<s.size();i++)
    {
        int cost = costs[i] + ap;
        int j = best_clone( s.substr(0, i+1) );
        if (j <= i){
           //std::cout<<cost<<" saaau "<<costs[j] + cl<<"\n";
           cost = std::min(cost, costs[j] + cl);

        }
        costs.push_back(cost);
        //std::cout<<"-------"<<cost<<"\n";
    }
  return costs.back();
}



// do not write or edit anything below this line

#endif
