#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>     
#include <stdlib.h>
#include <algorithm> 
using namespace std;

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
#include "TTree.h"
#include "TSpectrum.h"
#include "TChain.h"
#include "TPolyMarker.h"
#include "TStyle.h"

int main(int argc,char **argv)

{
  TApplication app("App", &argc, argv);
  gStyle->SetOptFit(1);
  
  Int_t stop=0;
   
  Int_t Flag=0;

  //  TFile *F=new TFile("../Test.root");
  //  char filename[100]="../RootFiles/April15.root"; //no filter
  //  char filename[100]="../RootFiles/April14.root"; //with filter

  TChain *tr=new TChain("PMT");
  //tr->Add(filename);
  // tr->Add("../RootFiles/April16.root");   //no filter
  //tr->Add("../RootFiles/April17.root");   //no filter
  //tr->Add("../RootFiles/April18.root");   //no filter
  //tr->Add("../RootFiles/Sample_6_Nov_18.root"); // No Cerium
  //tr->Add("../RootFiles/Sample_6_Nov_19.root");//  No Cerium
  
  tr->Add("../RootFiles/Test.root");
  // tr->Add("../RootFiles/Sample_9_Dec_5.root");
  // tr->Add("../RootFiles/Sample_9_Nov_24.root");
  //tr->Add("../RootFiles/Sample_9_Nov_26.root");
  //tr->Add("../RootFiles/Sample_9_Nov_27.root");

  TCanvas *c1= new TCanvas("c1"," ",200,10,1200,600);
  TCanvas *c2= new TCanvas("c2"," ",200,10,1200,800);

   c1->Divide(2,2);
   c2->Divide(2,2);
  //   c1->Update();
  //TTree *tr=new TTree("PMT","PMT");
 
  Double_t Nentries=0;

  // TTree *tr=new TTree();
  //  tr=(TTree*) F->Get("PMT");

  Double_t Time[10000];
  Double_t Amplitude1[10000];
  Double_t Amplitude2[10000];

  // Float_t A1[10000]={0};
  //  Float_t A2[10000]={0};
  // Float_t T[10000]={0};

  TGraph *gr1;
  TGraph *gr2;
  TMultiGraph *mg = new TMultiGraph();


  const Int_t nbins=10000;
  const Int_t startbin=2600;  //4500
   const Int_t endbin=3600;    //5500


  Double_t xmin =startbin;
  Double_t xmax=endbin;

    TH1D *Waveform1=new TH1D("Waveform1", "",endbin-startbin,xmin+0.5,xmax+0.5);
    TH1D *Waveform1_a=new TH1D("Waveform1_a","",endbin-startbin,xmin+0.5,xmax+0.5);  

    TH1D *Waveform2=new TH1D("Waveform2", "",endbin-startbin,xmin+0.5,xmax+0.5);
   TH1D *Waveform2_a=new TH1D("Waveform2_a","",nbins,xmin+0.5,xmax+0.5);  

 
  Double_t source1[nbins]={0};
  Double_t source2[nbins]={0};

  //Double_t source1[nbins]={0};
  //Float_t source2[nbins]={0};

  TGraph *PedestalG1;
  TGraph *PedestalG2;

  Double_t Pedestal1=0;
  Double_t Pedestal2=0;

  TH1D *Ped1=new TH1D("Pedestal1", " ",50,-0.01,0.01);
  TH1D *Ped2=new TH1D("Pedestal2", " ",50,-0.01,0.01);


  Double_t MaxADC1=0;
  Double_t MaxADC2=0;
  
  Double_t RiseTime1=0;
  Double_t RiseTime2=0;
  TH1D *RT1=new TH1D("RiseTime1", " ",500,0,10);
  TH1D *RT2=new TH1D("RiseTime2", " ",500,0,10);

  Double_t PulseSlope1=0;
  Double_t PulseSlope2=0;
  TH1D *PS1=new TH1D("PulseSlope1", " ",250,-0.51,0.49);      //Pulse Slope
  TH1D *PS2=new TH1D("PulseSlope2", " ",250,-0.51,0.49);

  TH1I *PA1=new TH1I("PulseAmplitude1", " ",200,-0.01,3.99);           //Peak Amplitude
  TH1I *PA2=new TH1I("PulseAmplitude2", " ",200,-0.01,3.99);


  Double_t Charge1=0;
  Double_t Charge2=0;

  TH1D *Ch1=new TH1D("Integral1 ", " ",1000,-100.5,100.5);           //Charge
  TH1D *Ch2=new TH1D("Integral2 ", " ",1000,-100.5,100.5);
  TH1D *Ch_S=new TH1D("Integral sum ", " ",1000,-100.5,100.5);

  Double_t fPositionX1[100]={0};
  Double_t fPositionY1[100]={0};
  Double_t fPositionX2[100]={0};
  Double_t fPositionY2[100]={0};

  TF1 *Fitt1=new TF1("Fitt1","pol0",-15,15);
  TF1 *Fitt2=new TF1("Fitt2","pol0",-15,15);

  const Int_t ADC_threshold=10;
  Double_t Peak_threshold1=0;
  Double_t Peak_threshold2=0;
 
   Double_t dest[nbins]={0};

  // Float_t dest[nbins]={0};

  Double_t a=0;
  Int_t i,bin,nfound;

  Int_t MinBin1=0;
  Int_t MinBin2=0;

  TH1I *MB1=new TH1I("MinBin1", " ",1000,-0.5,999.5);
  TH1I *MB2=new TH1I("MinBin2", " ",1000,-0.5,999.5);



  Double_t BIAS=0.0;


  mg->SetTitle(";Supply voltage, V;Peak amplitude, V");

  tr->SetBranchAddress("Amplitude1",&Amplitude1);
  tr->SetBranchAddress("Amplitude2",&Amplitude2);
  tr->SetBranchAddress("Time",&Time);

  Nentries=tr->GetEntries();
  cout<< " Number of entries "<<Nentries<<endl;

  for(int trigger=0;trigger<Nentries;trigger++)
    {

      
      if (Flag==1)
	{
	    c1->cd(1);
	    
	    gr1=new TGraph(10000,Time,Amplitude1);
	    gr1->GetXaxis()->SetTitle("Time, s"); 
	    gr1->GetYaxis()->SetTitle("Amplitude, V ");
	    
	    gr1->Draw("AL");
	    // gr1->GetXaxis()->SetRangeUser(-0.00000005,0.0000001);
	    gPad->Modified();
	    gPad->Update();
	    c1->Update();
	    
	    c1->cd(2);
     
	    
	    gr2=new TGraph(10000,Time,Amplitude2);
	    gr2->GetXaxis()->SetTitle("Time, s"); 
	    gr2->GetYaxis()->SetTitle("Amplitude, V ");
	    gr2->SetLineColor(kRed);
	    
	    
	    gr2->Draw("AL");
	    // gr2->GetXaxis()->SetRangeUser(-0.00000005,0.0000001);
	    gPad->Modified();
	    gPad->Update();
     
	    c1->Update();
	    
	  }
	    
	    
      MinBin1=0;
      MinBin2=0;
	    
      Pedestal1=0; 
      Pedestal2=0;

      Charge1=0;
      Charge2=0;
  
      a=0;
      bin=0;

   for(int i55=0;i55<100;i55++)
	{
	  fPositionX1[i55]=0;
	  fPositionY1[i55]=0;  
          fPositionX2[i55]=0;
	  fPositionY2[i55]=0; 
        } 
   
      mg = new TMultiGraph();

      tr->GetEntry(trigger);
      if (trigger % 1000 == 0) cout<< "Trigger N "<< trigger<<endl;

      //for(int i=0;i<10000;i++){cout<<Amplitude1[i]<<" "<<Amplitude2[i]<<" "<<Time[i]<<endl;}
      

       PedestalG1=new TGraph(30,Time,Amplitude1);
       PedestalG1->Fit("Fitt1","RQ");
       Pedestal1=Fitt1->GetParameter(0);
       // cout<<Pedestal1<<endl;
       Ped1->Fill(Pedestal1);
       
       PedestalG2=new TGraph(30,Time,Amplitude2);
       PedestalG2->Fit("Fitt2","RQ");
       Pedestal2=Fitt2->GetParameter(0);
       Ped2->Fill(Pedestal2);

       for (int l1=4050;l1<4250;l1++)
	 {
	   Charge1=Charge1-Amplitude1[l1]+Pedestal1;
	   Charge2=Charge2-Amplitude2[l1]+Pedestal2;
	 }
       // cout<<Charge1<<" "<<Charge2<<endl;
       Ch1->Fill(Charge1);
       Ch2->Fill(Charge2);
       Ch_S->Fill(Charge1+Charge2);

 
      for (int i1=0;i1<endbin-startbin;i1++)
	{
	 
	  Waveform1->SetBinContent(i1,-Amplitude1[startbin+i1]-Pedestal1+BIAS);
	  source1[i1]=Waveform1->GetBinContent(i1); 
   
	  Waveform2->SetBinContent(i1,-Amplitude2[startbin+i1]-Pedestal2+BIAS);
	  source2[i1]=Waveform2->GetBinContent(i1); 
 
	}
   
      MaxADC1=Waveform1->GetMaximum();
      MaxADC2=Waveform2->GetMaximum();
      
      //cout<<"Max1 "<<MaxADC1<<endl;
      //cout<<"Max2 "<<MaxADC1<<endl;

      Peak_threshold1=100.;
      Peak_threshold2=100.;

      // if (MaxADC1>0){Peak_threshold1=MaxADC1*0.5*100; cout<<Peak_threshold1<<endl;}
      // if (MaxADC2>0){Peak_threshold2=MaxADC2*0.5*100; cout<<Peak_threshold2<<endl;}
   
      //  c1->cd(3);
      //  Waveform1->Draw("L");
      // c1->Update(); 


      //  if (MaxADC1>0.015 && MaxADC1<2.0)    // Threshold !!!!

      //     if (MaxADC1>0.015 )    // Threshold !!!!
 if (MaxADC1>0.02 )  
      //  if(1)
     {
       TSpectrum *s1 = new TSpectrum();
       // nfound = s1->SearchHighRes(source1,dest,nbins-startbin,1,Peak_threshold1,kFALSE,3,kFALSE,3);
         nfound = s1->SearchHighRes(source1,dest,nbins-startbin,2,50,kFALSE,3,kFALSE,3);
          Double_t *xpeaks = s1->GetPositionX();
       // Float_t *xpeaks = s1->GetPositionX();
       
       for (int i2=0;i2<nfound;i2++)
	 {
	   a=xpeaks[i2];
	   bin=Int_t(a+0.5); 
	   // cout<<"Peak "<<i2<<" Bin "<<bin<<endl;
	  
	   if(i2==0){MinBin1=bin;}
	   if(MinBin1>bin){MinBin1=bin;}

	   fPositionX1[i2]=Waveform1->GetBinCenter(bin);
	   fPositionY1[i2]=Waveform1->GetBinContent(bin); 
	 } 

       // cout<<"Firstpeak "<<MinBin1+startbin<<" Value %"<<Waveform1->GetBinContent(bin-1)/Waveform1->GetBinContent(bin) <<endl;  
       // cout<<endl;
       
       MB1->Fill(MinBin1);

       RiseTime1=(4e-10)*0.8*Waveform1->GetBinContent(MinBin1)/((Waveform1->GetBinContent(MinBin1)-Waveform1->GetBinContent(MinBin1-5))/(MinBin1-MinBin1-5));
       PulseSlope1=(Waveform1->GetBinContent(MinBin1-1)-Waveform1->GetBinContent(MinBin1-5))/(MinBin1-1-MinBin1-5);

       

       // cout<<"Rise time ns"<<-(4e-10)*(1e09)*0.8*Waveform1->GetBinContent(bin)/((Waveform1->GetBinContent(bin-1)-Waveform1->GetBinContent(bin-3))/(bin-1-bin-4))<<endl;
       
       //  if(MinBin1<478 && MinBin1>466){RT1->Fill(-1*RiseTime1*1e09);PS1->Fill(PulseSlope1);PA1->Fill(Waveform1->GetBinContent(MinBin1));}   // Time bin Threshold!!!!
       if(MinBin1>80 && MinBin1<120){RT1->Fill(-1*RiseTime1*1e09);PS1->Fill(PulseSlope1);PA1->Fill(Waveform1->GetBinContent(MinBin1));}


       TPolyMarker *pm = (TPolyMarker*)Waveform1->GetListOfFunctions()->FindObject("TPolyMarker");
       if (pm)
	 {
	   Waveform1->GetListOfFunctions()->Remove(pm);
	   delete pm;
	 }
       pm= new TPolyMarker(nfound,fPositionX1,fPositionY1);
       Waveform1->GetListOfFunctions()->Add(pm);
       pm->SetMarkerStyle(23);
       pm->SetMarkerColor(kRed);
       pm->SetMarkerSize(1.3); 
     }

   if (Flag==1)
     {
       c1->cd(3);
       //    Waveform1->GetXaxis()->SetRangeUser(4500,5500); //April data
       Waveform1->GetXaxis()->SetRangeUser(0,10000);
       Waveform1->Draw("LP");
       c1->Update();
     }

   // if (MaxADC2>0.03 && MaxADC2<2.0)   // Threshold !!!!

   //if (MaxADC2>0.015)   // Threshold !!!!
    if(MaxADC2>0.02)
      {
       TSpectrum *s1 = new TSpectrum();
       // nfound = s1->SearchHighRes(source1,dest,nbins-startbin,1,Peak_threshold1,kFALSE,3,kFALSE,3);
         nfound = s1->SearchHighRes(source2,dest,nbins-startbin,2,50,kFALSE,3,kFALSE,3);
          Double_t *xpeaks = s1->GetPositionX();
       //Float_t *xpeaks = s1->GetPositionX();
       
       for (int i2=0;i2<nfound;i2++)
	 {
	   a=xpeaks[i2];
	   bin=Int_t(a+0.5); 
	   if(i2==0){MinBin2=bin;}
	   if(MinBin2>bin){MinBin2=bin;}
	   fPositionX2[i2]=Waveform2->GetBinCenter(bin);
	   fPositionY2[i2]=Waveform2->GetBinContent(bin);  
	 } 
       MB2->Fill(MinBin2);	    
       // cout<<"Firstpeak "<<MinBin2+startbin<<" Value %"<<Waveform2->GetBinContent(bin-1)/Waveform2->GetBinContent(bin) <<endl;  
       //cout<<endl;
       
       
       RiseTime2=(4e-10)*0.8*Waveform2->GetBinContent(MinBin2)/((Waveform2->GetBinContent(MinBin2)-Waveform2->GetBinContent(MinBin2-5))/(MinBin2-MinBin2-5));
       //cout<<"Rise time "<<-(4e-10)*(1e09)*0.8*Waveform2->GetBinContent(bin)/((Waveform2->GetBinContent(bin-1)-Waveform2->GetBinContent(bin-3))/(bin-1-bin-4))<<endl;
     
       PulseSlope2=(Waveform2->GetBinContent(MinBin2-1)-Waveform2->GetBinContent(MinBin2-5))/(MinBin2-1-MinBin2-5);
     
       //  if(MinBin2<466 && MinBin2>450 ){RT2->Fill(-1*RiseTime2*1e09);PS2->Fill(PulseSlope2);PA2->Fill(Waveform2->GetBinContent(MinBin2));}   // Threshold !!!!
 if(MinBin2>80 && MinBin2<120 ){RT2->Fill(-1*RiseTime2*1e09);PS2->Fill(PulseSlope2);PA2->Fill(Waveform2->GetBinContent(MinBin2));}   // Threshold !!!!


       TPolyMarker *pm = (TPolyMarker*)Waveform2->GetListOfFunctions()->FindObject("TPolyMarker");
       if (pm)
	 {
	   Waveform2->GetListOfFunctions()->Remove(pm);
	   delete pm;
	 }
       pm= new TPolyMarker(nfound,fPositionX2,fPositionY2);
       Waveform2->GetListOfFunctions()->Add(pm);
       pm->SetMarkerStyle(23);
       pm->SetMarkerColor(kRed);
       pm->SetMarkerSize(1.3); 
     }
 
   if (Flag==1)
     {
       c1->cd(4);
       // Waveform2->GetXaxis()->SetRangeUser(4500,5500); //April data
   Waveform2->GetXaxis()->SetRangeUser(0,10000);
       Waveform2->Draw("LP");
       c1->Update();
       cin>>stop;
     }
 
      // cin>>stop;
    }
  /*
  c2->cd(1);
  PA1->Draw();
  c2->cd(2);
  PA2->Draw();
  c2->cd(3);
  PS1->Draw();
  c2->cd(4);
  PS2->Draw();
  c2->Update();
  cin>>stop;
  */
   
  TFile *F1=new TFile("Test.root","RECREATE");
  F1->cd();
  RT1->Write();
  RT2->Write();
  PS1->Write();
  PS2->Write();
  MB2->Write();
  MB1->Write();
  Ped1->Write();
  Ped2->Write();
  PA2->Write();
  PA1->Write();
  Ch1->Write();
  Ch2->Write();
  Ch_S->Write();

  F1->Close();
}
