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

void HSSpacingPlot2(){

  std::cout << "Hello world!" << std::endl;

  TFile *myinputfile = new TFile("Hinv.root");
  TTreeReader fReader("jvttree", myinputfile);
  TTreeReaderValue<vector<float>> recozArray = {fReader, "recovx_z"};
  TTreeReaderValue<vector<float>> zArray = {fReader, "truthvx_z"};

  TH1F* my_histo = new TH1F("","",100,-500,500);
  TH1F* my_histo2 = new TH1F("","",100,-500,500);
  //TH2F* my_2Dhisto = new TH2F("","",100,-50,50,100,-50,50);
  vector<float> xvals;
  vector<float> yvals;
  //float sumSquare = 0;
  //int counter = 0;
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
    xvals.push_back(truthvx_z[0]);
    //yvals.push_back(recovx_z[0]);

    float minRecoZ = recovx_z[0];
    for(int j=1; j<5; j++) {
      float Distance = abs(truthvx_z[0]-recovx_z[j]);       
      if(Distance<abs(truthvx_z[0]-minRecoZ))
	 minRecoZ=recovx_z[j];
    }
    yvals.push_back(minRecoZ);
    //vector<float> sumPt = *tempPt;
    
    //my_histo->Fill(truthvx_z[0]-recovx_z[0],2);
    //sumSquare += pow(truthvx_z[0]-recovx_z[0],2);
    //counter++;
    
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
  
  TGraph *mygraph = new TGraph(xvals.size(),&xvals[0],&yvals[0]);
  mygraph->Draw("ap");
  //my_histo->Draw();

  //std::cout << "RMS separation:" << sqrt(sumSquare/counter) << std::endl;
  //std::cout << "Total values:" << counter << std::endl;
  //my_histo2->Draw("same");
  //my_histo2->Divide(my_histo);

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
  //gStyle->SetOptStat(0);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  mygraph->SetTitle("Hard scatter vertex separation in Hinv.root");
  mygraph->GetXaxis()->SetTitle("Truth vertex z");
  mygraph->GetYaxis()->SetTitle("Reconstructed vertex z");
  mygraph->GetYaxis()->SetNdivisions(505);
  mygraph->GetXaxis()->SetNdivisions(505);
  mygraph->GetXaxis()->SetTitleOffset(1.4);
  mygraph->GetYaxis()->SetTitleOffset(1.7);
  mygraph->SetMarkerSize(1);
  my_histo->SetLineColor(1);
  my_histo->SetMarkerColor(1);
  my_histo->SetMarkerStyle(20); 

  //my_histo2->SetLineColor(2);
  //my_histo2->SetLineWidth(2);
  //my_histo2->SetLineStyle(3);

  mygraph->Draw("ap");
  //my_histo->Fit("gaus");

  //TF1 *f1 = new TF1("lorentzian","[0]/(2*3.141926)/((x-[1])^2+([2]/2)^2)",-3,3);
  //my_histo->Fit("lorentzian");

  //my_histo2->Draw("same");
  //leg->Draw();
  
  c1->Print("plots/output_HSSpacingPlot2_2Dgraph_tol5.pdf");

}
