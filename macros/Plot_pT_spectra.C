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

void Plot_pT_spectra(){

TFile *f1 = new TFile("pT_spectra/Gen_pT_spectrum_Run3Summer22_PremixedPU.root","READ");
TFile *f2 = new TFile("pT_spectra/Gen_pT_spectrum_Run3Summer22EE_PremixedPU.root","READ");
TFile *f3 = new TFile("pT_spectra/Gen_pT_spectrum_Run3Winter23_Flat2022_PremixedPU.root","READ");
TFile *f4 = new TFile("pT_spectra/Gen_pT_spectrum_Run3Summer23_PremixedPU.root","READ");
TFile *f5 = new TFile("pT_spectra/Gen_pT_spectrum_Run3Summer23BPix_PremixedPU.root","READ");

TH1D *h1 = (TH1D*)f1->Get("gen_pt_3leading");
TH1D *h2 = (TH1D*)f2->Get("gen_pt_3leading");
TH1D *h3 = (TH1D*)f3->Get("gen_pt_3leading");
TH1D *h4 = (TH1D*)f4->Get("gen_pt_3leading");
TH1D *h5 = (TH1D*)f5->Get("gen_pt_3leading");

TCanvas *c = new TCanvas("c","",800,700);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.03);
c->SetLogy(1);
c->SetLogx(1);

auto frame = c->DrawFrame(1,0.5,9999,100000000);
frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitleOffset(0.85);
frame->GetXaxis()->SetTitle("p_{T}^{ptcl} [GeV]");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(0.9);
frame->GetYaxis()->SetTitle("Number of jets (normalized to area)");

h1->SetLineColor(kBlue-4);
h2->SetLineColor(kRed-4);
h3->SetLineColor(kBlack);
h4->SetLineColor(kGreen-2);
h5->SetLineColor(kViolet);

h1->SetMarkerColor(kBlue-4);
h2->SetMarkerColor(kRed-4);
h3->SetMarkerColor(kBlack);
h4->SetMarkerColor(kGreen-2);
h5->SetMarkerColor(kViolet);

h1->SetMarkerStyle(8);
h2->SetMarkerStyle(21);
h3->SetMarkerStyle(22);
h4->SetMarkerStyle(23);
h5->SetMarkerStyle(34);

h1->SetMarkerSize(1.);
h2->SetMarkerSize(1.2);
h3->SetMarkerSize(1.4);
h4->SetMarkerSize(1.4);
h5->SetMarkerSize(1.4);

h1->SetLineWidth(2);
h2->SetLineWidth(2);
h3->SetLineWidth(2);
h4->SetLineWidth(2);
h5->SetLineWidth(2);

h1->GetXaxis()->SetTitle("p_{T}^{gen} [GeV]");
h1->GetYaxis()->SetTitle("Number of jets (normalized to area)");

h1->SetStats(0);
h1->SetTitle("");

h1->GetXaxis()->SetTitleSize(0.05);
h1->GetXaxis()->SetTitleOffset(0.85);
h1->GetYaxis()->SetTitleSize(0.05);
h1->GetYaxis()->SetTitleOffset(1.);

h1->GetYaxis()->SetRangeUser(0.5,100000000);

h2->Scale(h1->Integral()/h2->Integral());
h3->Scale(h1->Integral()/h3->Integral());
h4->Scale(h1->Integral()/h4->Integral());
h5->Scale(h1->Integral()/h5->Integral());

h1->Draw("PE same");
h2->Draw("PE same");
h3->Draw("PE same");
h4->Draw("PE same");
h5->Draw("PE same");

TLegend *l = new TLegend(0.12,0.12,0.5,0.3,"");
l->SetTextSize(0.04);
l->SetBorderSize(0);
l->AddEntry(h1,"Summer22 (Flat)","LPE");
l->AddEntry(h2,"Summer22EE (Flat)","LPE");
l->AddEntry(h3,"Winter23 (Flat2022)","LPE");
l->AddEntry(h4,"Summer23","LPE");
l->AddEntry(h5,"Summer23BPix","LPE");
l->Draw();

TPaveText *cms = new TPaveText(0.14,0.918,0.44,0.938,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.05);
cms->SetBorderSize(0);
cms->SetFillColor(0);
cms->Draw();

TPaveText *text = new TPaveText(0.25,0.33,0.45,0.43,"NDC");
text->AddText("No weights applied");
text->AddText("3 leading gen jets considered");
//text->AddText("All gen jets considered");
text->SetTextFont(42);
text->SetTextSize(0.04);
text->SetBorderSize(0);
text->SetFillColor(0);
text->Draw();

TPaveText *lumileg = new TPaveText(0.79,0.918,0.99,0.938,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("13.6 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);
lumileg->Draw();

//c->SaveAs("/afs/cern.ch/user/i/izisopou/private/JEC_ANs/Run3_AN/AN-23-061/plots/GenPtSpectra.png");
//c->SaveAs("/afs/cern.ch/user/i/izisopou/private/JEC_ANs/Run3_AN/AN-23-061/plots/GenPtSpectra.pdf");

c->SaveAs("pT_spectra/GenPtSpectra_Summer22_Summer22EE_Winter23_Summer23_Summer23BPix.png");
c->SaveAs("pT_spectra/GenPtSpectra_Summer22_Summer22EE_Winter23_Summer23_Summer23BPix.pdf");

}
