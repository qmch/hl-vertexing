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

void efficiency_pTPlot(){

  std::cout << "Hello world!" << std::endl;

  TFile *myinputfile = new TFile("Hinv.root");
  TTreeReader fReader("jvttree", myinputfile);
  TTreeReaderValue<vector<float>> recozArray = {fReader, "recovx_z"};
  TTreeReaderValue<vector<float>> zArray = {fReader, "truthvx_z"};
  TTreeReaderValue<vector<float>> tempPt = {fReader, "recovx_sumPt"};

  TH1F* my_histo = new TH1F("","",20,0,1000);
  TH1F* my_histo2 = new TH1F("","",20,0,1000);
  while (fReader.Next()) {
    //float weight = *tempWeight;
    /*
    old method of 2 histos
    vector<float> myArray = *zArray;
    for (int i = 1; i <= myArray.size(); i++){
      my_histo->Fill(myArray[i]);
    }
    vector<float> myArray2 = *recozArray;
    for (int j = 1; j <= myArray2.size(); j++){
      my_histo2->Fill(myArray2[j]);
    }
    */
    //new-- based on Ariel's code
    
    vector<float> truthvx_z = *zArray;
    vector<float> recovx_z = *recozArray;
    vector<float> sumPt = *tempPt;
    
    my_histo->Fill(sumPt[0]);
    
    if (abs(truthvx_z[0]-recovx_z[0])<1){
      my_histo2->Fill(sumPt[0]);
    }
    
    //for (int i = 1; i <= truthvx_z.size(); i++){
    /*
    bool found = false;
    for(int j=0; j<3; j++) {
      float Distance = abs(truthvx_z[0]-recovx_z[j]);       
      if(Distance<1) { found = true;}
    }
    if(found) my_histo2->Fill(recovx_z[0]);
    */
    //}
  }

  //my_histo->Draw();
  my_histo2->Draw("same");
  my_histo2->Divide(my_histo);

  /*
  TLegend* leg = new TLegend(.15,.75,0.4,.9);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->AddEntry(my_histo,"Truth vertices","l");
  leg->AddEntry(my_histo2,"Reconstructed vertices","l");       
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->Draw();
  */

  TCanvas * c1 = new TCanvas("","",500,500);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  my_histo2->SetTitle("Efficiency ratio (reco/truth) in Hinv.root");
  my_histo2->GetXaxis()->SetTitle("Sum pT");
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
  //leg->Draw();
  
  //c1->Print("plots/output_efficiencyPlot_sumpT_ratio.pdf");

}
