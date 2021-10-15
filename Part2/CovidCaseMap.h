#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H

#include "CovidCase.h"

// TODO: your code goes here
#include <vector>
using std::vector;


class CovidCaseMap {


private:


public:
  vector<CovidCase> s;
        class TimeAndCaseData{
        private:
          int time;
          int nrCases;
        public:
          TimeAndCaseData(int t, int unit):time(t)
          {
            nrCases=getNrCases(unit);
          };

          int getNrCases(int unit)
          {
            int act=0;
            for(int i=0;i<s.size();i++)
            {
              if(s[i].getTime()+unit >= time)
                act++;
            }
            return act;
          }

          int getTime() const {return time;}
          int getNumberOfCases() const {return nrCases;}
        };

  void addCase(const CovidCase & cc)
  {
    s.push_back(cc);
  }

  vector<TimeAndCaseData> getCasesOverTime(int unit) const
  {
    vector<TimeAndCaseData> rez;
    for(auto &cc: s)
    {
      rez.push_back(new TimeAndCaseData(cc.getTime(), unit));
    }
  }


};


// don't write any code below this line

#endif
