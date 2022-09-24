#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH3I.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TLatex.h"

//////////////////////////////////////////////////////
//
// Combines the L1L2L3 closure of the 4 Run2 epochs
// weighting with lumi
//
//////////////////////////////////////////////////////


void Combine_L1L2L3Closures(){

TFile *f_UL16APV = new TFile("test_style/L1L2L3ClosureVsPt_AK8PUPPI_UL16APV.root","READ");
TFile *f_UL16nonAPV = new TFile("test_style/L1L2L3ClosureVsPt_AK8PUPPI_UL16nonAPV.root","READ");
TFile *f_UL17 = new TFile("test_style/L1L2L3ClosureVsPt_AK8PUPPI_UL17.root","READ");
TFile *f_UL18 = new TFile("test_style/L1L2L3ClosureVsPt_AK8PUPPI_UL18.root","READ");

TH1F *h_BB_UL16APV = (TH1F*)f_UL16APV->Get("ak8puppi/ClosureVsRefPt_JetEta0to1.3");
TH1F *h_EI_UL16APV = (TH1F*)f_UL16APV->Get("ak8puppi/ClosureVsRefPt_JetEta1.3to2.5");
TH1F *h_EO_UL16APV = (TH1F*)f_UL16APV->Get("ak8puppi/ClosureVsRefPt_JetEta2.5to3");
TH1F *h_FF_UL16APV = (TH1F*)f_UL16APV->Get("ak8puppi/ClosureVsRefPt_JetEta3to5");

TH1F *h_BB_UL16nonAPV = (TH1F*)f_UL16nonAPV->Get("ak8puppi/ClosureVsRefPt_JetEta0to1.3");
TH1F *h_EI_UL16nonAPV = (TH1F*)f_UL16nonAPV->Get("ak8puppi/ClosureVsRefPt_JetEta1.3to2.5");
TH1F *h_EO_UL16nonAPV = (TH1F*)f_UL16nonAPV->Get("ak8puppi/ClosureVsRefPt_JetEta2.5to3");
TH1F *h_FF_UL16nonAPV = (TH1F*)f_UL16nonAPV->Get("ak8puppi/ClosureVsRefPt_JetEta3to5");

TH1F *h_BB_UL17 = (TH1F*)f_UL17->Get("ak8puppi/ClosureVsRefPt_JetEta0to1.3");
TH1F *h_EI_UL17 = (TH1F*)f_UL17->Get("ak8puppi/ClosureVsRefPt_JetEta1.3to2.5");
TH1F *h_EO_UL17 = (TH1F*)f_UL17->Get("ak8puppi/ClosureVsRefPt_JetEta2.5to3");
TH1F *h_FF_UL17 = (TH1F*)f_UL17->Get("ak8puppi/ClosureVsRefPt_JetEta3to5");

TH1F *h_BB_UL18 = (TH1F*)f_UL18->Get("ak8puppi/ClosureVsRefPt_JetEta0to1.3");
TH1F *h_EI_UL18 = (TH1F*)f_UL18->Get("ak8puppi/ClosureVsRefPt_JetEta1.3to2.5");
TH1F *h_EO_UL18 = (TH1F*)f_UL18->Get("ak8puppi/ClosureVsRefPt_JetEta2.5to3");
TH1F *h_FF_UL18 = (TH1F*)f_UL18->Get("ak8puppi/ClosureVsRefPt_JetEta3to5");

const int nBins = 51;

const double PtBinning[52] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 20, 23, 27, 30, 35, 40, 45, 57, 72, 90, 120, 150, 200, 300, 400, 550, 750, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000};

TH1F *h_BB_allyears = new TH1F("ClosureVsRefPt_JetEta0to1.3","ClosureVsRefPt_JetEta0to1.3",nBins,PtBinning);
TH1F *h_EI_allyears = new TH1F("ClosureVsRefPt_JetEta1.3to2.5","ClosureVsRefPt_JetEta1.3to2.5",nBins,PtBinning);
TH1F *h_EO_allyears = new TH1F("ClosureVsRefPt_JetEta2.5to3","ClosureVsRefPt_JetEta2.5to3",nBins,PtBinning);
TH1F *h_FF_allyears = new TH1F("ClosureVsRefPt_JetEta3to5","ClosureVsRefPt_JetEta3to5",nBins,PtBinning);

//in /pb
double lumi_UL16APV = 19536.411965199;
double lumi_UL16nonAPV = 16796.968108718;
double lumi_UL17 = 41479.680528762;
double lumi_UL18 = 59832.475339089;
double lumi_Run2 = 137645.54;

double frac_UL16APV = lumi_UL16APV/lumi_Run2;
double frac_UL16nonAPV = lumi_UL16nonAPV/lumi_Run2;
double frac_UL17 = lumi_UL17/lumi_Run2;
double frac_UL18 = lumi_UL18/lumi_Run2;

for(int i=1; i<=h_BB_allyears->GetNbinsX(); i++)
{
	double val = frac_UL16APV*h_BB_UL16APV->GetBinContent(i) + frac_UL16nonAPV*h_BB_UL16nonAPV->GetBinContent(i) + frac_UL17*h_BB_UL17->GetBinContent(i) + frac_UL18*h_BB_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power(frac_UL16APV*h_BB_UL16APV->GetBinError(i), 2) +  TMath::Power(frac_UL16nonAPV*h_BB_UL16nonAPV->GetBinError(i), 2) + TMath::Power(frac_UL17*h_BB_UL17->GetBinError(i), 2) + TMath::Power(frac_UL18*h_BB_UL18->GetBinError(i), 2) );

	h_BB_allyears->SetBinContent(i, val);
	h_BB_allyears->SetBinError(i, valerr);

}

for(int i=1; i<=h_EI_allyears->GetNbinsX(); i++)
{
	double val = frac_UL16APV*h_EI_UL16APV->GetBinContent(i) + frac_UL16nonAPV*h_EI_UL16nonAPV->GetBinContent(i) + frac_UL17*h_EI_UL17->GetBinContent(i) + frac_UL18*h_EI_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power(frac_UL16APV*h_EI_UL16APV->GetBinError(i), 2) +  TMath::Power(frac_UL16nonAPV*h_EI_UL16nonAPV->GetBinError(i), 2) + TMath::Power(frac_UL17*h_EI_UL17->GetBinError(i), 2) + TMath::Power(frac_UL18*h_EI_UL18->GetBinError(i), 2) );

	h_EI_allyears->SetBinContent(i, val);
	h_EI_allyears->SetBinError(i, valerr);

}

for(int i=1; i<=h_EO_allyears->GetNbinsX(); i++)
{
	double val = frac_UL16APV*h_EO_UL16APV->GetBinContent(i) + frac_UL16nonAPV*h_EO_UL16nonAPV->GetBinContent(i) + frac_UL17*h_EO_UL17->GetBinContent(i) + frac_UL18*h_EO_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power(frac_UL16APV*h_EO_UL16APV->GetBinError(i), 2) +  TMath::Power(frac_UL16nonAPV*h_EO_UL16nonAPV->GetBinError(i), 2) + TMath::Power(frac_UL17*h_EO_UL17->GetBinError(i), 2) + TMath::Power(frac_UL18*h_EO_UL18->GetBinError(i), 2) );

	h_EO_allyears->SetBinContent(i, val);
	h_EO_allyears->SetBinError(i, valerr);

}

for(int i=1; i<=h_FF_allyears->GetNbinsX(); i++)
{
	double val = frac_UL16APV*h_FF_UL16APV->GetBinContent(i) + frac_UL16nonAPV*h_FF_UL16nonAPV->GetBinContent(i) + frac_UL17*h_FF_UL17->GetBinContent(i) + frac_UL18*h_FF_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power(frac_UL16APV*h_FF_UL16APV->GetBinError(i), 2) +  TMath::Power(frac_UL16nonAPV*h_FF_UL16nonAPV->GetBinError(i), 2) + TMath::Power(frac_UL17*h_FF_UL17->GetBinError(i), 2) + TMath::Power(frac_UL18*h_FF_UL18->GetBinError(i), 2) );

	h_FF_allyears->SetBinContent(i, val);
	h_FF_allyears->SetBinError(i, valerr);

}

TFile *fout = new TFile("test_style/L1L2L3ClosureVsPt_AK8PUPPI_ULRun2.root","RECREATE"); 
fout->cd();

TDirectoryFile *dir = new TDirectoryFile("ak8puppi","ak8puppi");
dir->cd();

h_BB_allyears->Write();
h_EI_allyears->Write();
h_EO_allyears->Write();
h_FF_allyears->Write();

fout->Close();
}
