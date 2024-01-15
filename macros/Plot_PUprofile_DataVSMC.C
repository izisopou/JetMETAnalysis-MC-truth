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

TFile *fdata = new TFile("MyDataPUHisto_2023_erasBC.root","READ");
TFile *fmc = new TFile("MyMCPUHisto_Run3Winter23_PremixedPU.root","READ");

TH1D *hdata = (TH1D*)fdata->Get("pileup");
TH1D *hmc = (TH1D*)fmc->Get("pileup");

TCanvas *c = new TCanvas("c","",800,700);
c->SetTickx(1);
c->SetTicky(1);

hdata->SetLineColor(kBlue+1);
hmc->SetLineColor(kRed+1);

//hdata->SetLineStyle(kDashed);

hdata->SetLineWidth(3);
hmc->SetLineWidth(3);

hdata->GetXaxis()->SetTitle("Number of pileup interactions (#mu)");
hdata->GetYaxis()->SetTitle("a.u.");

hdata->SetStats(0);
hdata->SetTitle("");

hdata->GetXaxis()->SetTitleSize(0.05);
hdata->GetXaxis()->SetTitleOffset(0.9);
hdata->GetYaxis()->SetTitleOffset(1.35);

hdata->Draw("hist");
hmc->Scale(hdata->Integral()/hmc->Integral());
hmc->Draw("hist same");

TLegend *l = new TLegend(0.55,0.78,0.75,0.88,"");
l->SetTextSize(0.035);
l->SetBorderSize(0);
l->AddEntry(hdata,"2023 data - eras BC","L");
l->AddEntry(hmc,"Winter23 PremixedPU","L");
l->Draw();

TPaveText *cms = new TPaveText(0.155,0.75,0.28,0.85,"NDC");
cms->AddText("#splitline{#bf{CMS}}{#scale[0.7]{#it{Preliminary}}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);
cms->Draw();

TPaveText *lumileg = new TPaveText(0.73,0.915,0.93,0.935,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("13.6 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.04);
lumileg->Draw();

char text_mean_1[1024], text_mean_2[1024];
sprintf(text_mean_1,"<#mu> = %.1f",hdata->GetMean());
sprintf(text_mean_2,"<#mu> = %.1f",hmc->GetMean());

TPaveText *mean1 = new TPaveText(0.6,0.6,0.8,0.65,"NDC");
mean1->SetFillColor(0);
mean1->SetBorderSize(0);
mean1->SetTextFont(42);
mean1->SetTextSize(0.04);
mean1->AddText(text_mean_1);
mean1->SetTextColor(kBlue+1);
mean1->Draw();

TPaveText *mean2 = new TPaveText(0.6,0.53,0.8,0.58,"NDC");
mean2->SetFillColor(0);
mean2->SetBorderSize(0);
mean2->SetTextFont(42);
mean2->SetTextSize(0.04);
mean2->AddText(text_mean_2);
mean2->SetTextColor(kRed+1);
mean2->Draw();

c->SaveAs("Run3_PUprofile_2023BC_vs_Winter23.png");
c->SaveAs("Run3_PUprofile_2023BC_vs_Winter23.pdf");

}
