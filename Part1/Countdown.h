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
            s.push_back(operators[x]);s.push_back(' ');

          }
          double rez = evaluateCountdown(s);
          if( abs(target-rez) < abs(target-finrez) )
              {finsol=s;finrez=rez; }

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
    return CDSol;

}

// Do not edit below this line


#endif
