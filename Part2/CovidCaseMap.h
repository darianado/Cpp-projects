#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H

#include "CovidCase.h"

// TODO: your code goes here
#include <vector>
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


  };


// don't write any code below this line

#endif
