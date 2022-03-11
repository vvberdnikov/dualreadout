#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

// root include files
#include "TApplication.h"  // needed to display canvas
#include "TSystem.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TMath.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TROOT.h"
#include "TNtuple.h"

int main()
{
  
   char filename[100];
   string line;
   char a; 

   Int_t nlines = 0;
   Double_t time, Ampl1, Ampl2, Ampl3, Ampl4; 

   Double_t Time[10000]={0.};
   Double_t Amplitude1[10000]={0.};
   Double_t Amplitude2[10000]={0.};
  
   // TFile *f = new TFile("RootFiles/April18.root","RECREATE");
  
  
   TFile *f = new TFile("./RootFiles/Test.root","RECREATE");
   // TFile *f = new TFile("/home/berdnik/Test.root","RECREATE");
   TTree *Tree= new TTree("PMT","PMT");
   
   Tree->Branch("Time",&Time,"Time[10000]/D");
   Tree->Branch("Amplitude1",&Amplitude1,"Amplitude1[10000]/D");
   Tree->Branch("Amplitude2",&Amplitude2,"Amplitude2[10000]/D");

   // Number of aquired scope files
  
   //  Int_t Triggers=22237; //April 9   UG5 GG435
   //  Int_t Triggers=10786; //April 12  UG5 GG435
   //  Int_t Triggers=9186;  //April 13  UG5 GG435
   //  Int_t Triggers=2933;  //April 14  UG5 GG435

   // Int_t Triggers=10176; //April 15 no filters 
   //  Int_t Triggers=2784; //April 16 no filters 
   //  Int_t Triggers=10068; //April 17 no filters 
   //    Int_t Triggers=10361; //April 18 no filters 

   // Int_t Triggers=32402; //sample6 Nov_19

   Int_t Triggers=4489; 


   Int_t l=0;


   for (l=0;l<Triggers;l++)  // Start loop over triggers
   
     { 
       // filename="./Data/DataLog_0006_Analog.csv";   
       /*
       if(l<10)       { sprintf(filename,"../Data/April_9/DualReadout_000%d_Analog.csv",l);}
       else if(l<100) { sprintf(filename,"../Data/April_9/DualReadout_00%d_Analog.csv",l);}
       else if(l<1000){ sprintf(filename,"../Data/April_9/DualReadout_0%d_Analog.csv",l);}
       else           { sprintf(filename,"../Data/April_9/DualReadout_%d_Analog.csv",l);}
             
       if(l<10)       { sprintf(filename,"../Data/April18/DataLog_000%d_Analog.csv",l);}
       else if(l<100) { sprintf(filename,"../Data/April18/DataLog_00%d_Analog.csv",l);}
       else if(l<1000){ sprintf(filename,"../Data/April18/DataLog_0%d_Analog.csv",l);}
       else           { sprintf(filename,"../Data/April18/DataLog_%d_Analog.csv",l);}
 

       if(l<10)       { sprintf(filename,"../Data/Sample_6_Nov_19/DataLog_000%d_Analog.csv",l);}
       else if(l<100) { sprintf(filename,"../Data/Sample_6_Nov_19/DataLog_00%d_Analog.csv",l);}
       else if(l<1000){ sprintf(filename,"../Data/Sample_6_Nov_19/DataLog_0%d_Analog.csv",l);}
       else if(l>=1000 && l<=2893){ sprintf(filename,"../Data/Sample_6_Nov_19/DataLog_%d_Analog.csv",l);}
       else if(l>2893 && l<=9999){continue;}
       else if(l>9999){ sprintf(filename,"../Data/Sample_6_Nov_19/DataLog_%d_Analog.csv",l);}

      if(l<10)       { sprintf(filename,"../Data/Sample_6_Nov18/DataLog_000%d_Analog.csv",l);}
       else if(l<100) { sprintf(filename,"../Data/Sample_6_Nov18/DataLog_00%d_Analog.csv",l);}
       else if(l<1000){ sprintf(filename,"../Data/Sample_6_Nov18/DataLog_0%d_Analog.csv",l);}
       else           { sprintf(filename,"../Data/Sample_6_Nov18/DataLog_%d_Analog.csv",l);}

 

       if(l<10)       { sprintf(filename,"../Data/Sample_9_Dec_5_F/DataLog_000%d_Analog.csv",l);}
       else if(l<100) { sprintf(filename,"../Data/Sample_9_Dec_5_F/DataLog_00%d_Analog.csv",l);}

      else if(l<1000){ sprintf(filename,"../Data/Sample_9_Dec_5_F/DataLog_0%d_Analog.csv",l);}
       else           { sprintf(filename,"../Data/Sample_9_Dec_5_F/DataLog_%d_Analog.csv",l);}

	*/

     cout<<"Here are the contents of "<< filename<<":\n";
       sprintf(filename,"../Data/2022-03-11-Sample6/DataLog_%d.csv",l);
      
      ifstream in(filename);
     
      //cout<<"Here are the contents of "<< filename<<":\n";
      
      nlines=0;

      for( int i=0;i<21;i++)
	{
	  getline(in,line);
	  //  cout<<line<<endl;
	}
      
      do 
	{
	  
	  getline(in,line);
	  in>>time>>a>>Ampl1>>a>>Ampl2>>a>>Ampl3>>a>>Ampl4; 
	  // cout<<time<<" "<<a<<" "<<Ampl1<<" "<<a<<" "<<Ampl2<<a<<" "<<Ampl3<<" "<<a<<" "<<Ampl4<<endl;
	  //cout<<l<<endl;
	  Time[nlines]=time;
	  Amplitude1[nlines]=Ampl1;
	  Amplitude2[nlines]=Ampl2;
	  //   Tree->Fill();  
	  nlines++;
	  // cout<<nlines<<endl;
	}
      while(!in.eof() && nlines<10000);
      
      // cout<<"Found "<<nlines<<" lines"<<endl;
      // printf(" found %d points\n",nlines);
      Tree->Fill();  
      in.close();
      
     }// end of triggers loop


   Tree->Write();
   f->Write();


}
