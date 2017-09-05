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

void MUPlot(){

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
  TTreeReaderValue<float> value = {fReader, "MU"};

  TH1F* my_histo = new TH1F("","",14,165,235);
  while (fReader.Next()) {
    double myvalue = *value;
    my_histo->Fill(myvalue);
  }

  my_histo->Draw();

  TCanvas * c1 = new TCanvas("","",500,500);
  gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  my_histo->SetTitle("Mu in Hinv.root");
  my_histo->GetXaxis()->SetTitle("Mu");
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
  //my_histo->Fit("gaus");
  c1->Print("plots/output_MUPlot_histo.pdf");

  //my_histo->Scale(1./my_histo->Integral());
  //c1->Print("output_NPVPlot_norm.pdf");

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
