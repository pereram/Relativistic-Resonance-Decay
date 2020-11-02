// Implementation of our vecLor class for ROOT
// now we have to include our header
// file !!!

#include "vecLor.h"

#include <iostream>  

ClassImp(vecLor)

using namespace std;

vecLor vecLor::operator+(vecLor  &v)
{
  return vecLor(v.GetP0()+GetP0(),v.GetP1()+GetP1(),v.GetP2()+GetP2(),v.GetP3()+GetP3());
}

vecLor vecLor::operator+=(vecLor &v)
{
  //DEBUG:
  //cout<<x<<" "<<v.GetX()<<endl;
  //cout<<y<<" "<<v.GetY()<<endl;
  
  p0 += v.GetP0(); p1 +=v.GetP1(); p2 += v.GetP2(); p3 +=v.GetP3();

  //DEBUG:
  //cout<<"After Add : x = "<<x<<" "<<y<<endl;

  return *this;
}

vecLor::vecLor()
{
  //default constructor
  //DEBUG:
  //cout<<" vecLor: default constructor called"<<endl;

  p0=0;p1=0; p2=0;p3=0;
}

vecLor::vecLor(double mp0, double mp1, double mp2, double mp3)
{
  //user defined constructor
  //cout<<" vecLor: user defined constructor called"<<endl;

  p0=mp0; p1=mp1; p2=mp2; p3=mp3;
}

vecLor::~vecLor() 
{
  //cout<<" vecLor: default destructor called"<<endl;
}; 

void vecLor::Print()
{
  cout<<"vecLor Clas:"<<endl;
  cout<<"p0 = "<<p0<<endl;
  cout<<"p1 = "<<p1<<endl;
  cout<<"p2 = "<<p2<<endl;
  cout<<"p3 = "<<p3<<endl;
}

//BOOST IN THE Z DIRECTION
void vecLor::boost(double gamma)
{
	double beta=sqrt(1-(1/(gamma*gamma)));	

          double Eboost=gamma*(p0+beta*p1);
	  double p3boost=gamma*(p1+beta*p0);

          SetP0(Eboost);
          SetP3(p3boost);

}

  //RANDOM DIRECTION
void vecLor::randomDirection(double p1,double theta,double phi)
{

	  double p11=p1*sin(theta)*cos(phi);
	  double p21=p1*sin(theta)*sin(phi);
	  double p31=p1*cos(theta);

          SetP1(p11);
          SetP2(p21);
          SetP3(p31);
}

