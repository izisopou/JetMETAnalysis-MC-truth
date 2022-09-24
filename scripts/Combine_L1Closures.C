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
// Combines the L1 closure of the 4 Run2 epochs
// weighting with lumi
//
//////////////////////////////////////////////////////

void Combine_L1Closures(){

TFile *f_UL16APV = new TFile("test_style/OffsetWithoutL1VsPt_AK8PUPPI_UL16APV.root","READ");
TFile *f_UL16nonAPV = new TFile("test_style/OffsetWithoutL1VsPt_AK8PUPPI_UL16nonAPV.root","READ");
TFile *f_UL17 = new TFile("test_style/OffsetWithoutL1VsPt_AK8PUPPI_UL17.root","READ");
TFile *f_UL18 = new TFile("test_style/OffsetWithoutL1VsPt_AK8PUPPI_UL18.root","READ");

TH1D *h_PU0to10_UL16APV = (TH1D*)f_UL16APV->Get("histograms/OffMeantnpuRef_FF_0");
TH1D *h_PU10to20_UL16APV = (TH1D*)f_UL16APV->Get("histograms/OffMeantnpuRef_FF_1");
TH1D *h_PU20to30_UL16APV = (TH1D*)f_UL16APV->Get("histograms/OffMeantnpuRef_FF_2");
TH1D *h_PU30to40_UL16APV = (TH1D*)f_UL16APV->Get("histograms/OffMeantnpuRef_FF_3");

TH1D *h_PU0to10_UL16nonAPV = (TH1D*)f_UL16nonAPV->Get("histograms/OffMeantnpuRef_FF_0");
TH1D *h_PU10to20_UL16nonAPV = (TH1D*)f_UL16nonAPV->Get("histograms/OffMeantnpuRef_FF_1");
TH1D *h_PU20to30_UL16nonAPV = (TH1D*)f_UL16nonAPV->Get("histograms/OffMeantnpuRef_FF_2");
TH1D *h_PU30to40_UL16nonAPV = (TH1D*)f_UL16nonAPV->Get("histograms/OffMeantnpuRef_FF_3");

TH1D *h_PU0to10_UL17 = (TH1D*)f_UL17->Get("histograms/OffMeantnpuRef_FF_0");
TH1D *h_PU10to20_UL17 = (TH1D*)f_UL17->Get("histograms/OffMeantnpuRef_FF_1");
TH1D *h_PU20to30_UL17 = (TH1D*)f_UL17->Get("histograms/OffMeantnpuRef_FF_2");
TH1D *h_PU30to40_UL17 = (TH1D*)f_UL17->Get("histograms/OffMeantnpuRef_FF_3");
TH1D *h_PU40to50_UL17 = (TH1D*)f_UL17->Get("histograms/OffMeantnpuRef_FF_4");

TH1D *h_PU0to10_UL18 = (TH1D*)f_UL18->Get("histograms/OffMeantnpuRef_FF_0");
TH1D *h_PU10to20_UL18 = (TH1D*)f_UL18->Get("histograms/OffMeantnpuRef_FF_1");
TH1D *h_PU20to30_UL18 = (TH1D*)f_UL18->Get("histograms/OffMeantnpuRef_FF_2");
TH1D *h_PU30to40_UL18 = (TH1D*)f_UL18->Get("histograms/OffMeantnpuRef_FF_3");
TH1D *h_PU40to50_UL18 = (TH1D*)f_UL18->Get("histograms/OffMeantnpuRef_FF_4");

const int nBins = 51;

const double PtBinning[52] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 20, 23, 27, 30, 35, 40, 45, 57, 72, 90, 120, 150, 200, 300, 400, 550, 750, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000};

TH1D *h_PU0to10_allyears = new TH1D("OffMeantnpuRef_FF_0","OffMeantnpuRef_FF_0",nBins,PtBinning);
TH1D *h_PU10to20_allyears = new TH1D("OffMeantnpuRef_FF_1","OffMeantnpuRef_FF_1",nBins,PtBinning);
TH1D *h_PU20to30_allyears = new TH1D("OffMeantnpuRef_FF_2","OffMeantnpuRef_FF_2",nBins,PtBinning);
TH1D *h_PU30to40_allyears = new TH1D("OffMeantnpuRef_FF_3","OffMeantnpuRef_FF_3",nBins,PtBinning);
TH1D *h_PU40to50_allyears = new TH1D("OffMeantnpuRef_FF_4","OffMeantnpuRef_FF_4",nBins,PtBinning);

//in /pb
double lumi_UL16APV = 19536.411965199;
double lumi_UL16nonAPV = 16796.968108718;
double lumi_UL17 = 41479.680528762;
double lumi_UL18 = 59832.475339089;
double lumi_Run2 = 137645.54;
double lumi_UL17andUL18 = 101312.16;

double frac_UL16APV = lumi_UL16APV/lumi_Run2;
double frac_UL16nonAPV = lumi_UL16nonAPV/lumi_Run2;
double frac_UL17 = lumi_UL17/lumi_Run2;
double frac_UL18 = lumi_UL18/lumi_Run2;

for(int i=1; i<=h_PU0to10_allyears->GetNbinsX(); i++)
{
	double val = frac_UL16APV*h_PU0to10_UL16APV->GetBinContent(i) + frac_UL16nonAPV*h_PU0to10_UL16nonAPV->GetBinContent(i) + frac_UL17*h_PU0to10_UL17->GetBinContent(i) + frac_UL18*h_PU0to10_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power(frac_UL16APV*h_PU0to10_UL16APV->GetBinError(i), 2) +  TMath::Power(frac_UL16nonAPV*h_PU0to10_UL16nonAPV->GetBinError(i), 2) + TMath::Power(frac_UL17*h_PU0to10_UL17->GetBinError(i), 2) + TMath::Power(frac_UL18*h_PU0to10_UL18->GetBinError(i), 2) );

	h_PU0to10_allyears->SetBinContent(i, val);
	h_PU0to10_allyears->SetBinError(i, valerr);

}

for(int i=1; i<=h_PU10to20_allyears->GetNbinsX(); i++)
{
	double val = frac_UL16APV*h_PU10to20_UL16APV->GetBinContent(i) + frac_UL16nonAPV*h_PU10to20_UL16nonAPV->GetBinContent(i) + frac_UL17*h_PU10to20_UL17->GetBinContent(i) + frac_UL18*h_PU10to20_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power(frac_UL16APV*h_PU10to20_UL16APV->GetBinError(i), 2) +  TMath::Power(frac_UL16nonAPV*h_PU10to20_UL16nonAPV->GetBinError(i), 2) + TMath::Power(frac_UL17*h_PU10to20_UL17->GetBinError(i), 2) + TMath::Power(frac_UL18*h_PU10to20_UL18->GetBinError(i), 2) );

	h_PU10to20_allyears->SetBinContent(i, val);
	h_PU10to20_allyears->SetBinError(i, valerr);

}

for(int i=1; i<=h_PU20to30_allyears->GetNbinsX(); i++)
{
	double val = frac_UL16APV*h_PU20to30_UL16APV->GetBinContent(i) + frac_UL16nonAPV*h_PU20to30_UL16nonAPV->GetBinContent(i) + frac_UL17*h_PU20to30_UL17->GetBinContent(i) + frac_UL18*h_PU20to30_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power(frac_UL16APV*h_PU20to30_UL16APV->GetBinError(i), 2) +  TMath::Power(frac_UL16nonAPV*h_PU20to30_UL16nonAPV->GetBinError(i), 2) + TMath::Power(frac_UL17*h_PU20to30_UL17->GetBinError(i), 2) + TMath::Power(frac_UL18*h_PU20to30_UL18->GetBinError(i), 2) );

	h_PU20to30_allyears->SetBinContent(i, val);
	h_PU20to30_allyears->SetBinError(i, valerr);

}

for(int i=1; i<=h_PU30to40_allyears->GetNbinsX(); i++)
{
	double val = frac_UL16APV*h_PU30to40_UL16APV->GetBinContent(i) + frac_UL16nonAPV*h_PU30to40_UL16nonAPV->GetBinContent(i) + frac_UL17*h_PU30to40_UL17->GetBinContent(i) + frac_UL18*h_PU30to40_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power(frac_UL16APV*h_PU30to40_UL16APV->GetBinError(i), 2) +  TMath::Power(frac_UL16nonAPV*h_PU30to40_UL16nonAPV->GetBinError(i), 2) + TMath::Power(frac_UL17*h_PU30to40_UL17->GetBinError(i), 2) + TMath::Power(frac_UL18*h_PU30to40_UL18->GetBinError(i), 2) );

	h_PU30to40_allyears->SetBinContent(i, val);
	h_PU30to40_allyears->SetBinError(i, valerr);

}

for(int i=1; i<=h_PU40to50_allyears->GetNbinsX(); i++)
{
	double val = (lumi_UL17/lumi_UL17andUL18)*h_PU40to50_UL17->GetBinContent(i) + (lumi_UL18/lumi_UL17andUL18)*h_PU40to50_UL18->GetBinContent(i);

	double valerr = TMath::Sqrt( TMath::Power((lumi_UL17/lumi_UL17andUL18)*h_PU40to50_UL17->GetBinError(i), 2) + TMath::Power((lumi_UL18/lumi_UL17andUL18)*h_PU40to50_UL18->GetBinError(i), 2) );

	h_PU40to50_allyears->SetBinContent(i, val);
	h_PU40to50_allyears->SetBinError(i, valerr);

}

//TFile *fout = new TFile("test_style/OffsetWithoutL1VsPt_AK8PUPPI_ULRun2.root","RECREATE");
TFile *fout = new TFile("test_style/OffsetWithoutL1VsPt_AK8PUPPI_ULRun2.root","UPDATE"); 
fout->cd();

//TDirectoryFile *dir = new TDirectoryFile("histograms","histograms");
TDirectoryFile *dir = (TDirectoryFile*)fout->Get("histograms");
dir->cd();

h_PU0to10_allyears->Write();
h_PU10to20_allyears->Write();
h_PU20to30_allyears->Write();
h_PU30to40_allyears->Write();
h_PU40to50_allyears->Write();

fout->Close();
}
