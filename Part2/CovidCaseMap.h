#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H

#include "CovidCase.h"

// TODO: your code goes here
#include <vector>
#include <cfloat>
using std::vector;

class TimeAndCaseData{
  private:
    int time;
    int nrCases;
  public:
  TimeAndCaseData(int t, int nr):time(t),nrCases(nr)  {};

    int getTime() const {return time;}
    int getNumberOfCases() const {return nrCases;}
};

bool alldone(vector<int> v)
{
  for(auto &i :v) if(v[i]==0) return false;
  return true;
}

class CovidCaseMap {
  private:
    vector<CovidCase> s;

  public:

    void addCase(const CovidCase & cc)
    {
      s.push_back(cc);
    }

    int getNrCases(int time,int unit) const
    {
      int act=0;
      for(int i=0;i<s.size();i++)
      {
        if(s[i].getTime()<=time && s[i].getTime()+unit > time)
          act++;
      }
      return act;
    }

    vector<TimeAndCaseData> getCasesOverTime(int unit) const
    {
      vector<TimeAndCaseData> rez;
      vector<int> times;
      rez.push_back( TimeAndCaseData( 0,  0 ) );
      for(auto &cc: s)
      {
        times.push_back(cc.getTime());
        times.push_back(cc.getTime()+unit);
      }
      std::sort(times.begin(),times.end());
      for(int &i: times)
      {
        rez.push_back( TimeAndCaseData( i,  getNrCases(i,unit) ) );
      }
      return rez;
    }

    double supportVisitGreedyTSP (double lati, double lon, int time, int unit)
    {
      // double la=lati; double lo=long;
      CovidCase strt = CovidCase(lati,lon ,"",0,time);
      vector<int> visited(s.size());
      double rez=0;
      int aici=-1;
      CovidCase curr = strt;
      do
      {
        double min = DBL_MAX;
        for(int i=0;i<s.size();i++)
        {
          if(visited[i]==0 && curr.distanceTo(s[i]) < min)
          {
            min=curr.distanceTo(s[i]);
            std::cout<<min<<"----";
            aici=i;
          }
        }
        std::cout<<std::endl;
        rez+=min;
        visited[aici]=1;
        curr=s[aici];
      }while(!alldone(visited));
      //rez+= curr.distanceTo(strt);
      return rez;
      }
};




// don't write any code below this line

#endif
