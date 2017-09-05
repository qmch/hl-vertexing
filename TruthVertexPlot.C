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

void TruthVertexPlot(){

  std::cout << "Hello world!" << std::endl;

  //
  // Reading from an ntuple
  //
  
  TFile *myinputfile = new TFile("Hinv.root");
  TTreeReader fReader("jvttree", myinputfile);
  TTreeReaderValue<vector<int>> value = {fReader, "truthvx_index"};
  TTreeReaderValue<float> muvalue = {fReader, "MU"};
  
  TH1F* my_histo = new TH1F("","",20,150,250);
  TH1F* my_histo2 = new TH1F("","",14,165,235);
  while (fReader.Next()) {
    vector<int> myvector = *value;
    int myvalue = myvector.size();
    my_histo->Fill(myvalue);
    double mymu = *muvalue;
    my_histo2->Fill(mymu);
  }

  my_histo->Draw();
  my_histo2->Draw("same");

  TLegend* leg = new TLegend(.6,.75,0.9,.9);
  leg->SetTextFont(42);
  leg->AddEntry(my_histo,"Truth vertex counts","l");
  leg->AddEntry(my_histo2,"Input mu values","l");       
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->Draw("same");

  TCanvas * c1 = new TCanvas("","",500,500);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  my_histo->SetTitle("Interaction counts in Hinv.root");
  my_histo->GetXaxis()->SetTitle("Truth vertex number/mu");
  my_histo->GetYaxis()->SetTitle("Counts");
  my_histo->GetYaxis()->SetNdivisions(505);
  my_histo->GetXaxis()->SetNdivisions(505);
  my_histo->GetXaxis()->SetTitleOffset(1.4);
  my_histo->GetYaxis()->SetTitleOffset(1.7);
  my_histo->SetMarkerSize(1);
  my_histo->SetLineColor(1);
  my_histo->SetMarkerColor(1);
  my_histo->SetMarkerStyle(20);

  my_histo2->SetLineColor(2);
  my_histo2->SetLineWidth(2);
  my_histo2->SetLineStyle(3);  
  my_histo->GetYaxis()->SetRangeUser(0,1.2*TMath::Max(my_histo->GetMaximum(),my_histo2->GetMaximum()));
  
  my_histo->Draw();
  my_histo2->Draw("same");
  leg->Draw();
  //my_histo->Draw("e1p");
  //my_histo->Scale(1./my_histo->Integral());  
  my_histo->Fit("gaus");

  c1->Print("plots/output_TruthVertexPlot_histo.pdf");

  //
  // NORMALIZING HISTOS
  //
  /*
  my_histo->Scale(1./my_histo->Integral());
  my_histo->GetYaxis()->SetRangeUser(0,1.2*(my_histo->GetMaximum()));
  //my_histo->GetYaxis()->SetTitle("Frequency / 0.25 GeV");
  c1->Print("test1D_2histos_norm.pdf");
  */

  /*
  //
  // Graphs
  //

  //First, need to generate some pseudo-data
  TH2F* my_template = new TH2F("","",5,0,1,5,0,1);
  for (int i=1; i<=my_template->GetNbinsX(); i++){
    my_template->SetBinContent(i,i,5);
    my_template->SetBinContent(i,i+1,1);
    my_template->SetBinContent(i,i-1,1);
  }
  my_template->Scale(1./my_template->Integral());
  my_template->Draw("colz");
  my_template->Draw("sametext");
  c1->Print("template.pdf");

  vector<double> xvals;
  vector<double> yvals;
  for (int i=0; i<100; i++){
    double x,y;
    my_template->GetRandom2(x,y);
    xvals.push_back(x);
    yvals.push_back(y);
  }
  TGraph *mygraph = new TGraph(xvals.size(),&xvals[0],&yvals[0]);
  gPad->SetRightMargin(0.05);
  mygraph->SetTitle("Energy of some processes");
  mygraph->GetXaxis()->SetTitle("Energy of Process 1 [GeV]");
  mygraph->GetYaxis()->SetTitle("Energy of Process 2 [GeV]");
  mygraph->GetYaxis()->SetNdivisions(505);
  mygraph->GetXaxis()->SetTitleOffset(1.4);
  mygraph->GetYaxis()->SetTitleOffset(1.7);
  mygraph->SetMarkerSize(1);
  mygraph->SetMarkerStyle(20); 
  mygraph->Draw("ap");  
  c1->Print("graph.pdf");

  //
  // Simple Fit
  //

  mygraph->Fit("pol1");
  TF1 *myfit = (TF1*)mygraph->GetFunction("pol1");
  myfit->SetLineColor(4);
  c1->Print("graph_fit.pdf");

  mygraph->Fit("pol6");
  TF1 *myfit2 = (TF1*)mygraph->GetFunction("pol6");
  myfit2->SetLineColor(2);
  c1->Print("graph_fit_more.pdf");
  */
}
