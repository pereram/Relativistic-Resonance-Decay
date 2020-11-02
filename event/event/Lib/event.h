// This is the header file
// of our event class for ROOT

#ifndef ROOT_event
#define ROOT_event

#include "vecLor.h"

#include "TObject.h"
#include "TBuffer.h"
#include "TObjArray.h"

//definition of our event class
class event : public TObject
{
  protected:

  int eventNumber;
  // our vecLor object array
  TObjArray *vecLorArray;

  public:

  // constructor
  event(); //default
  event(int nEv);

  // destructor
  virtual ~event();

  // Setter Functions
  void SetEventNumber(int nEv) {eventNumber=nEv;}

  // now we want to add a vecLor object ...
  // there are different ways and different issues
  // concerning object ownership (chap 8 and 16)
 
  void AddvecLor(vecLor *mv) {vecLorArray->AddLast(mv);}
  void AddvecLor(double mp0, double mp1, double mp2, double mp3);

  // Getter functions
  int GetEventNumber() {return eventNumber;}
  int GetNumberOfTracks() {return (int) vecLorArray->GetEntries();}
  // nicer getter function to avoid accessing the array itself
  vecLor* GetTrack(int nT) {return (vecLor*) vecLorArray->At(nT);}

  //our member functions
  void Print();
  void PrintTracks();

  void DoSort() {vecLorArray->Sort();}

  ClassDef(event,1); 
};
 
#endif //ROOT_vecLor
