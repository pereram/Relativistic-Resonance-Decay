void eventTest()
{
  gSystem->Load("../Lib/libEvent.so");
  
  TFile *f=new TFile("eventTest.root","recreate");
  TTree *t1=new TTree("event","a simple Tree with our event class");
  
  event *ev=0;

  t1->Branch("event",&ev); 

  Int_t meanTracksPerEvent=25;

// DECAY: lambda -> proton + pi meson

//ENERGIES IN GeV
  Double_t mother=1.116;
  Double_t child1=0.938;
  Double_t child2=0.140;

  Double_t Elab=10;
  
  Double_t gamma=Elab/mother;
//  Double_t beta=sqrt(1-(1/(gamma*gamma)));


  // nice way to debug root classes in
  // memory. Useful to find memory leaks
  // activate by add or create a .rootrc
  // in home directory and add/change:
  // Root.ObjectStat:         1
  // (turn off if no debug is needed,
  // slows down execution!)
  //gObjectTable->Print();

  // fill the tree
  for (Int_t i=0; i<1000; i++) 
    {
      ev=new event(i);     
      
      // distribute the number of tracks per event
      // according to a poisson!!!
      Int_t nTracksPerEvent=gRandom->Poisson(meanTracksPerEvent);

      for (Int_t k=0;k<nTracksPerEvent;k++)
	{
	  // not the most flexible and elegant, but safest method
	  //ev->AddvecLor(gRandom->Uniform(-20,20),gRandom->Uniform(-20,20));

	  // more generic/cleaner notation wise more obvious
	  // but only works since the TObjArray is the owner
	  // so hence we are not allowed to delete v here
	  // (so here explicitly not every new needs a delete
	  // therefore a bit more dangerous ...)
	  // Remark: Try to implement both to be safe!!!!

//CHOOSING ENERGY AND MOMENTUM OF CHILD1 AND CHILD2

	  Double_t E1=gRandom->Uniform(child1,mother);
	  Double_t E2=mother-E1;
	  Double_t p1=sqrt(E1*E1-child1*child1);
	  Double_t p2=-p1;

//INTRODUCING UNCERTAINTY ON THE ENERGY

          Double_t deltaEnergy=0.01;
	  Double_t deltaE1=gRandom->Gaus(0,deltaEnergy);
	  Double_t deltaE2=gRandom->Gaus(0,deltaEnergy);

//DEFINING 4-MOMENTUM OF CHILD1 AND CHILD2

	  vecLor *v1=new vecLor(E1+deltaE1,0,0,p1);
	  vecLor *v2=new vecLor(E2+deltaE1,0,0,p2);

//CHOOSING A RANDOM ORIENTATION

	  Double_t theta=gRandom->Uniform(0,3.14159);
	  Double_t phi=gRandom->Uniform(0,2*3.14159);

//INTRODUCING UNCERTAINTY ON THE ANGLES MEASUREMENT

          Double_t sigma=0.01;
	  Double_t deltaTheta1=gRandom->Gaus(0,sigma);
	  Double_t deltaPhi1=gRandom->Gaus(0,sigma);
	  Double_t deltaTheta2=gRandom->Gaus(0,sigma);
	  Double_t deltaPhi2=gRandom->Gaus(0,sigma);

//SETTING RANDOM ORIENTATTION WITH UNCERTAINTY
	  v1->randomDirection(p1,theta+deltaTheta1,phi+deltaPhi1);
	  v2->randomDirection(p2,theta+deltaTheta2,phi+deltaPhi2);

//BOOST TO LAB FRAME IN Z DIRECTION

          v1->boost(gamma);
          v2->boost(gamma);

//	  vecLor *v=new vecLor(v1->GetP0()+v2->GetP0(),v1->GetP1()+v2->GetP1(),v1->GetP2()+v2->GetP2(),v1->GetP3()+v2->GetP3());
	  vecLor *v=new vecLor();
	  *v=(*v1)+(*v2);

	  ev->AddvecLor(v);

	  // adding the delete will cause a crash, since
	  // delete e; with eevent as the owner, trys
	  // to delete too!!!
	  //delete v;
	}

      // sort them by length!!!
      ev->DoSort();

      t1->Fill();

      //DEBUG:
      //ev->Print();
      if (i<10)
	ev->PrintTracks();

      delete ev;   
    }

//CHECK OF THE GAMMA FACTOR
  cout<<"gamma factor: "<<gamma<<endl;
  
  //DEBUG:
  //gObjectTable->Print();
  
  t1->Write();
  
  f->Write();
  f->Close();
}
