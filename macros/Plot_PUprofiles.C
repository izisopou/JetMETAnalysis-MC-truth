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

void Plot_PUprofiles(){

TFile *f1 = new TFile("MyDataPUHisto_2022_erasCD_100Bins.root","READ");
TFile *f2 = new TFile("MyDataPUHisto_2022_erasEFG_100Bins.root","READ");
TFile *f3 = new TFile("MyDataPUHisto_2023_erasC_100Bins.root","READ");
TFile *f4 = new TFile("MyDataPUHisto_2023_erasD_100Bins.root","READ");

TH1D *h1 = (TH1D*)f1->Get("pileup");
TH1D *h2 = (TH1D*)f2->Get("pileup");
TH1D *h3 = (TH1D*)f3->Get("pileup");
TH1D *h4 = (TH1D*)f4->Get("pileup");

TCanvas *c = new TCanvas("c","",800,700);
c->SetTickx(1);
c->SetTicky(1);

h1->SetLineColor(kBlue-4);
h2->SetLineColor(kRed-4);
h3->SetLineColor(kGreen-2);
h4->SetLineColor(kViolet);

h1->SetLineWidth(3);
h2->SetLineWidth(3);
h3->SetLineWidth(3);
h4->SetLineWidth(3);

h1->GetXaxis()->SetTitle("Number of interactions per crossing");
h1->GetYaxis()->SetTitle("a.u.");

h1->SetStats(0);
h1->SetTitle("");

h1->GetXaxis()->SetTitleSize(0.05);
h1->GetXaxis()->SetTitleOffset(0.9);
h1->GetYaxis()->SetTitleOffset(1.35);

h1->GetXaxis()->SetRangeUser(0,90);

h1->Draw("hist");
h2->Scale(h1->Integral()/h2->Integral());
h3->Scale(h1->Integral()/h3->Integral());
h4->Scale(h1->Integral()/h4->Integral());
h2->Draw("hist same");
h3->Draw("hist same");
h4->Draw("hist same");

TLegend *l = new TLegend(0.65,0.65,0.85,0.83,"");
l->SetTextSize(0.035);
l->SetBorderSize(0);
l->AddEntry(h1,"2022CD","L");
l->AddEntry(h2,"2022EFG","L");
l->AddEntry(h3,"2023C","L");
l->AddEntry(h4,"2023D","L");
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


//c->SaveAs("/afs/cern.ch/user/i/izisopou/private/JEC_ANs/Run3_AN/AN-23-061/plots/PUprofiles_2022CD_vs_2022EFG_vs_2023CD.png");
//c->SaveAs("/afs/cern.ch/user/i/izisopou/private/JEC_ANs/Run3_AN/AN-23-061/plots/PUprofiles_2022CD_vs_2022EFG_vs_2023CD.pdf");

c->SaveAs("PU_profiles/Run3_PUprofile_2022CD_vs_2022EFG_vs_2023C_vs_2023D.png");
c->SaveAs("PU_profiles/Run3_PUprofile_2022CD_vs_2022EFG_vs_2023C_vs_2023D.pdf");

}
