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

    bool operator<(TimeAndCaseData const & other) const
    {
      return (nrCases<other.nrCases);
    }
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

    vector<CovidCase> const getActiveCasesAt(int time,int unit) const
    {
      vector<CovidCase> rez;
      for(int i=0;i<s.size();i++)
      {
        if(s[i].getTime()<=time && s[i].getTime()+unit > time)
          rez.push_back(s[i]);
      }
      return rez;
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

    //vector<CovidCase>
    // void getActiveCasesAt(int time, int unit)
    // {
    //   vector<TimeAndCaseData> rez=getCasesOverTime(unit);
    //
    //   int max=(*max_element(rez.begin(),rez.end())).getTime();
    //
    //   //return NULL;
    // }

    double supportVisitGreedyTSP (double lati, double lon, int time, int unit)
    {

      CovidCase strt = CovidCase(lati,lon ,"",0,time);
      vector<CovidCase> ac = getActiveCasesAt(time,unit);
      vector<int> visited(ac.size());
      double rez=0;
      int aici=-1;
      CovidCase curr = strt;
      do
      {
        double min = DBL_MAX;
        for(int i=0;i<ac.size();i++)
        {
          if(visited[i]==0 && curr.distanceTo(ac[i]) < min)
          {
            min=curr.distanceTo(ac[i]);
            std::cout<<min<<"----";
            aici=i;
          }
        }
        std::cout<<std::endl;
        rez+=min;
        visited[aici]=1;
        curr=ac[aici];
      }while(!alldone(visited));
      rez+= curr.distanceTo(strt);
      return rez;
      }
};




// don't write any code below this line

#endif
