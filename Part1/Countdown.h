#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <sstream>

// this is provided code for the last part of the README

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {

private:
    std::string solution;
    int value;

public:

    CountdownSolution() : solution(), value(0) {}

    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }

    const std::string & getSolution() const {
        return solution;
    }

    int getValue() const {
        return value;
    }

};

// Do not edit above this line

// TODO: write code here:
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using std::vector;
using std::string;

char operators[] = "+-*/";
string finsol="";
int finrez=0;


bool isOperation(char c)
{
    //std::cout<<"????????"<<c<<"\n";
  if(strchr(operators,c)) { return true;}
  return false;
}
double operation(char c, double a, double b)
{
  if(c=='+') return a+b;
  if(c=='-') return b-a;
  if(c=='*') return a*b;
  if(c=='/'&&a!=0) return b/a;
  return 0;
}
double evaluateCountdown(string s)
{
    //std::cout<<"........"<<s<<"\n";
    vector<string> tok;
    string c = "";
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == ' '){
            tok.push_back(c);
            c = "";
        }
        else{

          if(isOperation(s.at(i)))
          {
            double a= std::stod(tok.back());tok.pop_back();

            double b= std::stod(tok.back());tok.pop_back();

            double eu = operation(s[i],a,b);
            tok.push_back(std::to_string(eu));
            i++;
          }  else  c += s[i];
        }


    }
    //tok.push_back(c);
    //std::cout<<"---------------";std::cout<<tok.back();
    string rez=tok.back();
    return std::stod(rez);

}

void check_ops(string & sol, int nrops, vector<int> & ops, int index, double target)
{


  for(int i=0;i<4;i++)
  {
    ops.push_back(i);
    if(index==nrops-1)
      {
        string s=sol;
        for(int j=0;j<nrops;j++)
          {
            int x = ops[j];
            //std::cout<<"???"<<x<<"???"<<"\n";
            s.push_back(operators[x]);s.push_back(' ');

          }
          //std::cout<<"///...."<<s<<"///";
          double rez = evaluateCountdown(s);
          //std::cout<<"rez="<<rez<<"\n";
          if( abs(target-rez) < abs(target-finrez) )
              {finsol=s;finrez=rez; std::cout<<"---"<<finsol<<"========>>>>>>>>"<<finrez<<std::endl;}

      }
    else check_ops(sol,nrops,ops,index+1,target);
    ops.erase(ops.begin()+index, ops.end());
  }
}

void nr_in_str(vector<int>& v, int target, vector<int> & ops)
{
    string sol ="";
    for(int i=0;i<v.size();i++)
    {
      sol+= intToString(v[i])+" ";
    }
    check_ops(sol,v.size()-1,ops,0,target);
}

CountdownSolution solveCountdownProblem(vector<int> & v, double target)
{

    std::sort(v.begin(), v.end());
    vector<int> ops;
        do {
            nr_in_str(v,target, ops);
        } while(next_permutation(v.begin(), v.end()));
      CountdownSolution CDSol(finsol,finrez);
      std::cout<<">>>>>>>>>>>>>>>"<<CDSol.getSolution()<<"========>>>>>>>>"<<CDSol.getValue()<<std::endl;
    return CDSol;

}

// CountdownSolution solve(vector<int> v, double target, int v_size, CountdownSolution & rez)
// {
//   if(v_size<2) ;
//   else{
//   for (int i=1;i<=v_size;i++)
//   {
//       double a = v.back(); v.pop_back();
//       for(int j=1+i;j<=v_size;j++)
//       {
//         double b = v.back(); v.pop_back();
//                                                                         for(int eu=0;eu<v_size;eu++)
//                                                                           std::cout<<v[eu]<<" ";
//                                                                         std::cout<<std::endl;
//         for(int k=0;k<4;k++)
//         {
//           string s;
//           if(rez.getValue()!=0) s= rez.getSolution()+" ";
//           else s= intToString(a) +" ";
//           s+= intToString(b)+" "+op[k];
//           double aux=evaluateCountdown(s);
//           if(target-aux<=dif_min)
//           {
//             dif_min=target-aux;
//             rez=CountdownSolution(s,aux);
//             if(dif_min==0) return rez;
//                                                         std::cout<<rez.getValue()<<"->>>>"<<rez.getSolution()<<std::endl<<std::endl;
//           }
//           v.push_back(aux);
//
//           solve(v,target,v_size-1,rez);
//                                                             std::cout<<"(((((("<<std::endl;
//                                                           for(int eu=0;eu<v_size-1;eu++)
//                                                             std::cout<<v[eu]<<" ";
//                                                           std::cout<<std::endl;
//                                                           std::cout<<"(((((("<<std::endl;
//         }
//       }
//     }
//   }
//     return rez;
// }
// CountdownSolution solveCountdownProblem(vector<int> v, double target)
// {
//   CountdownSolution rez;
//
//   return solve(v,target,6,rez);;
// }
// Do not edit below this line


#endif
