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

void zDistPlot(){

  std::cout << "Hello world!" << std::endl;
  /*
  //
  // ONE HISTO ON ONE PLOT
  //

  TH1F* my_histo = new TH1F("","",5,0,1);
  my_histo->SetBinContent(1,1);
  my_histo->SetBinContent(2,2);
  my_histo->SetBinContent(3,1);
  my_histo->Draw();

  TCanvas * c1 = new TCanvas("","",500,500);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  my_histo->SetTitle("Energy spectrum of some process");
  my_histo->GetXaxis()->SetTitle("Energy [GeV]");
  my_histo->GetYaxis()->SetTitle("Events / 0.25 GeV");
  my_histo->GetYaxis()->SetNdivisions(505);
  my_histo->GetXaxis()->SetTitleOffset(1.4);
  my_histo->GetYaxis()->SetTitleOffset(1.7);
  my_histo->SetLineColor(4);
  my_histo->SetLineWidth(2);
  my_histo->Draw();

  //c1->Print("test1D.pdf");
  */

  //
  // Reading from an ntuple
  //
  
  TFile *myinputfile = new TFile("Hinv.root");
  TTreeReader fReader("jvttree", myinputfile);
  TTreeReaderValue<float> value = {fReader, "NPV"};
  TTreeReaderValue<vector<float>> zArray = {fReader, "truthvx_z"};

  TH1F* my_histo = new TH1F("","",30,-150,150);
  while (fReader.Next()) {
    vector<float> myArray = *zArray;
    for (int i = 1; i <= myArray.size(); i++){
      my_histo->Fill(myArray[i]);
    }
  }

  my_histo->Draw();

  TLatex latex;
  latex.SetTextSize(0.04);
  latex.DrawLatex(100,800e3,"#sigma=44.93");
  latex.DrawLatex(100,750e3,"#mu=2.50e-3");

  TCanvas * c1 = new TCanvas("","",500,500);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  my_histo->SetTitle("Z-distribution of truth vertices in Hinv.root");
  my_histo->GetXaxis()->SetTitle("Truth z-position");
  my_histo->GetYaxis()->SetTitle("Counts");
  my_histo->GetYaxis()->SetNdivisions(505);
  my_histo->GetXaxis()->SetNdivisions(505);
  my_histo->GetXaxis()->SetTitleOffset(1.4);
  my_histo->GetYaxis()->SetTitleOffset(1.7);
  my_histo->SetMarkerSize(1);
  my_histo->SetLineColor(1);
  my_histo->SetMarkerColor(1);
  my_histo->SetMarkerStyle(20); 
  //my_histo->Draw("e1p");
  //my_histo->Scale(1./my_histo->Integral());  
  my_histo->Fit("gaus");
  
  c1->Print("plots/output_zDistPlot.pdf");

}
