#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
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

void Plot_PUprofile_DataVSMC(){

TFile *fdata = new TFile("MyDataPUHisto_2022.root","READ");
TFile *fmc = new TFile("MyMCPUHisto_Run3Winter22_Flat2018_13p6TeV_PremixedPU.root","READ");

TH1D *hdata = (TH1D*)fdata->Get("pileup");
TH1D *hmc = (TH1D*)fmc->Get("pileup");

TCanvas *c = new TCanvas("c","",800,700);
c->SetTickx(1);
c->SetTicky(1);

hdata->SetLineColor(kBlack);
hmc->SetLineColor(kBlue);

hdata->SetLineWidth(3);
hmc->SetLineWidth(3);

hdata->GetXaxis()->SetTitle("Number of pileup interactions (#mu)");
hdata->GetYaxis()->SetTitle("a.u.");

hdata->SetStats(0);
hdata->SetTitle("");

hdata->GetXaxis()->SetTitleSize(0.05);
hdata->GetXaxis()->SetTitleOffset(0.9);

hdata->Draw("hist");
hmc->Scale(hdata->Integral()/hmc->Integral());
hmc->Draw("hist same");

TLegend *l = new TLegend(0.6,0.6,0.8,0.8,"");
l->SetTextSize(0.05);
l->SetBorderSize(0);
l->AddEntry(hdata,"Data","L");
l->AddEntry(hmc,"QCD MC","L");
l->Draw();

TPaveText *cms = new TPaveText(0.155,0.75,0.28,0.85,"NDC");
cms->AddText("#splitline{#bf{CMS}}{#scale[0.7]{#it{Preliminary}}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);
cms->Draw();

TPaveText *lumileg = new TPaveText(0.72,0.915,0.92,0.935,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("13.6 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);
lumileg->Draw();

c->SaveAs("Run3_PUprofile_DataVSMC.png");
c->SaveAs("Run3_PUprofile_DataVsMC.pdf");

}
