// This is the header file
// of our vecLor class for ROOT

#ifndef ROOT_vecLor
#define ROOT_vecLor

#include "TObject.h"
#include "TBuffer.h"
#include <cmath>

//definition of our vecLor class
class vecLor : public TObject
{
  protected:

  double p0;
  double p1;
  double p2;
  double p3;


  public:

  // constructor
  vecLor(); //default
  vecLor(double mp0, double mp1, double mp2, double mp3);
  // for how to better fill the event class
  // a copy constructor would be good ;-)

  // destructor
  virtual ~vecLor();

  //operators
  vecLor operator += (vecLor &);
  vecLor operator + (vecLor &);

  // Setter functions
  void SetP0(double mp0) {p0=mp0;}
  void SetP1(double mp1) {p1=mp1;}
  void SetP2(double mp2) {p2=mp2;}
  void SetP3(double mp3) {p3=mp3;}

  // Getter functions
  double GetP0() {return p0;}
  double GetP1() {return p1;}
  double GetP2() {return p2;}
  double GetP3() {return p3;}

  //BOOST
  void boost(double gamma);

  //RANDOM DIRECTION
  void randomDirection(double p1,double theta,double phi);

  //our member functions
  void Print();

  // small redefition (const retunr)
  // for function used to sort !
  // (make it also inline since it is
  // a simple operation!)

  double Length() const {return sqrt(p0*p0-p1*p1-p2*p2-p3*p3);}

  // Functions needed to use Sorting algorithms
  // in ROOT Container Classes!

  Bool_t IsSortable() const {return kTRUE;}

  Int_t Compare(const TObject *obj) const
  {
    if (Length() == ((vecLor*) obj)->Length())
      return 0;
    else if (Length() > ((vecLor*) obj)->Length())
      return -1;
    else if (Length() < ((vecLor*) obj)->Length())
      return 1;
    else
      return -9999;
  }

  ClassDef(vecLor,1); 
};
 
#endif //ROOT_vecLor
