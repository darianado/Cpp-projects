#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
using std::ostream;

// TODO: your code  goes here
#include <string>
#include <string.h>
using std::string;

#include <cmath>
#include<algorithm>
#include<vector>

double toRadians(double l)
{
  return l*3.14/180;
}

class CovidCase {
private:
  double latitude;
  double longitude;
  string name;
  unsigned int age;
  int time;

public:
  CovidCase( double latitudeIn, double longitudeIn, string nameIn, int ageIn, int timeIn):
            latitude(latitudeIn), longitude(longitudeIn),name(nameIn), age(ageIn),time(timeIn){
            };
  CovidCase(string s){

    std::remove(s.begin(), s.end(), ' ');
    std::remove(s.begin(), s.end(), '"');
      std::remove(s.begin(), s.end(), '{');
    std::cout<<std::endl<<s<<std::endl;
    std::vector<string> el;
    string t="";
    for(int i = 0; i < s.length(); i++){
          if(s[i] == ','||s[i]=='}'){
              el.push_back(t);
              t = "";
          }
          else
              t += s[i];
      }
      el.push_back(t);

      latitude = std::stod(el[0]);
      longitude= std::stod(el[1]);
      name= el[2];
      age= std::stoi(el[3]);
      time= std::stoi(el[4]);


    // std::remove(s.begin(), s.end(), ' ');
    // std::remove(s.begin(), s.end(), '"');
    // string *p ;
    // p =strtok(&s+1,",");
    // latitude = std::stod(*p);
    // p =strtok(NULL, ",");
    // longitude = std::stod(*p);
    // p =strtok(NULL, ",");
    // name = *p;
    // p =strtok(NULL, ",");
    // age = std::stoi(*p);
    // p =strtok(NULL, "}");
    // time = std::stoi(*p);


  };

  void print(ostream & o) const
  {
    o<<"{"<<latitude<<", "<<longitude<<", \""<<name<<"\", "<<age<<", "<<time<<"}";
  }

  double getLatitude() const
  {
    return latitude;
  }
  double getLongitude () const
  {
    return longitude;
  }

   double distanceTo(const CovidCase & other) const
  {
        double lat1= toRadians(latitude);
        double lon1= toRadians(longitude);
        double lat2= toRadians(other.getLatitude());
        double lon2= toRadians(other.getLongitude());

        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);
        double c = 2 * atan2( sqrt(a), sqrt(1-a) );
        return 3960 * c;
  }

  bool operator==(const CovidCase & other){
    return (latitude==other.latitude &&
            longitude==other.longitude &&
            name==other.name &&
            age==other.age &&
            time==other.time);
  }


  double & getLatitude()
  {
    return latitude;
  }
  double & getLongitude()
  {
    return longitude;
  }
  string & getName(){
    return name;
  }
  unsigned int & getAge(){
    return age;
  }
  int & getTime(){
    return time;
  }

};

ostream & operator<<(ostream & o, const CovidCase & cc){
  cc.print(o);
  return o;
}


// don't write any code below this line

#endif
