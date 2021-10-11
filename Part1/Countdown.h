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
using std::vector;
using std::string;

char isOperation(char c)
{
  if(c=='+'||c=='-'||c=='*'||c=='/') return c;
  return 0;
}
double operation(char c, double a, double b)
{
  // if(c=='+') return intToString(a+b);
  // if(c=='-') return intToString(b-a);
  // if(c=='*') return intToString(a*b);
  // if(c=='/') return intToString(b/a);
  if(c=='+') return a+b;
  if(c=='-') return b-a;
  if(c=='*') return a*b;
  if(c=='/') return b/a;
  return 0;

}
double evaluateCountdown(string s)
{
    vector<string> tok;
    string c = "";
    for(int i = 0; i < s.length(); i++){
        if(s[i] == ' '){
            std::cout<<"..."<<c<<std::endl;
            tok.push_back(c);
            c = "";
        }
        else
          if(isOperation(s[i])){
            double a= std::stod(tok.back());tok.pop_back();
            double b= std::stod(tok.back());tok.pop_back();
            double eu = operation(s[i],a,b);
            std::cout<<a<<b<<"->"<<eu<<std::endl;
            tok.push_back(std::to_string(eu));
            for(int i=0;i<tok.size();i++)
              std::cout<<tok[i]<<std::endl;
            i++;
          }
          else  c += s[i];
    }
    //tok.push_back(c);
    string rez=tok.back();
    return std::stod(rez);

}
// int main()
// {
//   cout<<"rez"<<evaluateCountdown("100 3 2 + / 17 +");
// }

// Do not edit below this line


#endif
