#include "TRandom3.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TVector2.h"
#include "TH2F.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "TGenPhaseSpace.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TColor.h"
//#include "TRoot.h"
#include "TGraph.h"

void efficiencyCutPlot(){

  std::cout << "Hello world!" << std::endl;

  TFile *myinputfile = new TFile("Hinv.root");
  TTreeReader fReader("jvttree", myinputfile);
  TTreeReaderValue<vector<float>> recozArray = {fReader, "recovx_z"};
  TTreeReaderValue<vector<float>> zArray = {fReader, "truthvx_z"};
  TTreeReaderValue<vector<vector<float>>> vtxtrkpt = {fReader, "vtxtrkpt"};
  TTreeReaderValue<vector<vector<int>>> vtxtrktruthvertex = {fReader, "vtxtrktruthvertex"};

  TH1F* my_histo = new TH1F("","",30,-150,150);
  TH1F* my_histo2 = new TH1F("","",30,-150,150);
  TH1F* my_histo3 = new TH1F("","",30,-150,150);

  //int counter = 0;
  while (fReader.Next()) {
    //counter++;
    //if (counter%1000 == 0){
    //  cout << "loop counter: "<< counter << endl;
    //}
    //old method of 2 histos
    vector<float> myArray = *zArray;
    for (int i = 0; i < myArray.size(); i++){
      my_histo3->Fill(myArray[i]);
    }
    int trackCounts[400]={0};
    
    //initialize the number of track counts per truth vertex to zero
    
    //for(int i=0; i<500; i++) trackCounts[i] = 0;
    
    //get the z positions for all reco vertices
    vector<float> recovx_z = *recozArray;
    //cout << "size of reco: " << recovx_z.size() << endl;
    //cout << "size of trkpt: " << vtxtrkpt->size() << endl;
    for (int j = 0; j < recovx_z.size(); j++){
      //and store them in my_histo2
      my_histo2->Fill(recovx_z[j]);
      
      //now loop over all tracks associated with each vertex
      //cout << vtxtrkpt->at(j).size() << endl;
      /*
      if (counter%100 == 0){
	cout << vtxtrkpt->at(j).size() << endl;
      }
      */
      for (int i=0; i<vtxtrkpt->at(j).size(); i++){
        //get the pT
	float pt = vtxtrkpt->at(j)[i];
	//make a pt cut
	if(pt<0.9 || pt>45.) continue;

	//if it passes, find the truth vertex it corresponds to
	int vertexID = vtxtrktruthvertex->at(j)[i];

	//this shouldn't trigger for these files-- if it does, simply
	//make trackCounts bigger
	if(vertexID>500) {
	  cout << "WARNING!!" << endl;
	  return;
	}
	
	//and increment the truth vertex ID if the track passes the pt cut
	trackCounts[vertexID]++;
      }
	
	
	
      }
      //now loop over the track counts and if a vertex is reconstructible,
      //i.e. has at least 3 tracks above the cut, add it to the histogram
      for (int i=0; i<400; i++){
	if (trackCounts[i]>=3){
	  my_histo->Fill(myArray[i]);
	}
      }
  }

  //my_histo->Draw();
  my_histo2->Draw("same");
  //my_histo3->Draw("same");
  //make this my_histo if you want selection on
  //and my_histo3 to compare without pt selection
  my_histo2->Divide(my_histo);

  
  TLegend* leg = new TLegend(.15,.75,0.4,.9);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  //leg->AddEntry(my_histo,"Truth vertices","l");
  leg->AddEntry(my_histo2,"0.9<p_T<45 GeV","l");       
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->Draw();
  

  TCanvas * c1 = new TCanvas("","",500,500);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  my_histo2->SetTitle("Efficiency ratio (reco/truth) in Hinv.root");
  my_histo2->GetXaxis()->SetTitle("Z-position (mm)");
  my_histo2->GetYaxis()->SetTitle("Ratio of counts");
  my_histo2->GetYaxis()->SetNdivisions(505);
  my_histo2->GetXaxis()->SetNdivisions(505);
  my_histo2->GetXaxis()->SetTitleOffset(1.4);
  my_histo2->GetYaxis()->SetTitleOffset(1.7);
  my_histo2->SetMarkerSize(1);
  my_histo2->SetLineColor(1);
  my_histo2->SetMarkerColor(1);
  my_histo2->SetMarkerStyle(20); 

  //my_histo2->SetLineColor(2);
  //my_histo2->SetLineWidth(2);
  //my_histo2->SetLineStyle(3);

  //my_histo->Draw();
  my_histo2->Draw("same");
  leg->Draw();
  
  c1->Print("plots/output_efficiencyCutPlot_ptcut.pdf");

}
