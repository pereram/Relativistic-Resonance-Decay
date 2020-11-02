// Implementation of our event class for ROOT
// now we have to include our header
// file !!!

#include "event.h"

#include <iostream>  

ClassImp(event)

using namespace std;

event::event()
{
  //default constructor
  //DEBUG:
  //cout<<" event: default constructor called"<<endl;

  eventNumber=-1;
  vecLorArray=new TObjArray();

  // Set explicityly that the 
  // array is the owner!
  // This is important to properly
  // allow to delete memory !!!!
  // This is a caveat/inconsitency 
  // in ROOT, so the best way is to
  // play around and try to create
  // an memory leak/error to truly
  // undertsand this aspect!!!
  vecLorArray->SetOwner(kTRUE);

}

event::event(int nEv)
{
  //user defined constructor
  //cout<<" event: user defined constructor called"<<endl;

  eventNumber=nEv;
  vecLorArray=new TObjArray(50);
  vecLorArray->SetOwner(kTRUE);
}

event::~event() 
{
  //cout<<" event: default destructor called"<<endl;
  vecLorArray->Delete();
  delete vecLorArray;
}; 

void event::AddvecLor(double mp0, double mp1, double mp2, double mp3)
{
  vecLor *v=new vecLor(mp0,mp1,mp2,mp3);
  vecLorArray->AddLast(v);
}

void event::Print()
{
  cout<<"Event Class:"<<endl;
  cout<<"Event # = "<<eventNumber<<endl;
  cout<<"# vecLor = "<<vecLorArray->GetEntries()<<endl;
  cout<<endl;
}

void event::PrintTracks()
{
  cout<<"Event Class:"<<endl;
  cout<<"Event # = "<<eventNumber<<endl;
  cout<<"# vecLor = "<<vecLorArray->GetEntries()<<endl; 

  for (int i=0;i<(int) vecLorArray->GetEntries();i++)
    {
      cout<<"Track "<<i<<" with length "<<GetTrack(i)->Length()<<endl;
    }

  cout<<endl;
}
