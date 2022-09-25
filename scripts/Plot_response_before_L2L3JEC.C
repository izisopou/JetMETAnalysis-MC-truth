#include "JetMETAnalysisMCtruth/JetUtilities/src/HistogramUtilities.cc"
#include "JetMETAnalysisMCtruth/JetUtilities/interface/HistogramUtilities.hh"
#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TDirectoryFile.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TMath.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TGraph2D.h>
#include <TStyle.h>
#include <TNamed.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <Math/MinimizerOptions.h>

//////////////////////////////////////////////////////
//
// Plots the raw response distribution (or after L1 for CHS)
// for 3 sets superimposed.
//
//////////////////////////////////////////////////////

void Plot_response_before_L2L3JEC(double ptgen_min, double ptgen_max){

double eta_min = 3.489;
double eta_max = 3.664;

TPaveText *cms = new TPaveText(0.15,0.91,0.35,0.95,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.04);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TPaveText *sample = new TPaveText(0.57,0.91,0.97,0.95,"NDC"); 
sample->AddText("Winter22Run3 (13.6 TeV)");
sample->SetTextFont(42);
sample->SetTextSize(0.04);
sample->SetBorderSize(0);
sample->SetFillColor(0);

TCanvas *c1 = new TCanvas("c1","c1",800,700);
c1->SetTickx(1);
c1->SetTicky(1);
c1->SetRightMargin(0.05);
c1->cd();

TFile *f1 = new TFile("/path1/in/eos/to/Step3/Merged.root","READ");
TFile *f2 = new TFile("/path2/in/eos/to/Step3/Merged.root","READ");
TFile *f3 = new TFile("/path3/in/eos/to/Step3/Merged.root","READ");

char hname1pos[1024], hname1neg[1024], hname2pos[1024], hname2neg[1024], hname3pos[1024], hname3neg[1024];

sprintf(hname1pos,"ak4puppi/RelRsp_JetEta%.3fto%.3f_RefPt%.0fto%.0f",eta_min,eta_max,ptgen_min,ptgen_max);
sprintf(hname1neg,"ak4puppi/RelRsp_JetEta-%.3fto-%.3f_RefPt%.0fto%.0f",eta_max,eta_min,ptgen_min,ptgen_max);
sprintf(hname2pos,"ak4puppi/RelRsp_JetEta%.3fto%.3f_RefPt%.0fto%.0f",eta_min,eta_max,ptgen_min,ptgen_max);
sprintf(hname2neg,"ak4puppi/RelRsp_JetEta-%.3fto-%.3f_RefPt%.0fto%.0f",eta_max,eta_min,ptgen_min,ptgen_max);
sprintf(hname3pos,"ak4puppi/RelRsp_JetEta%.3fto%.3f_RefPt%.0fto%.0f",eta_min,eta_max,ptgen_min,ptgen_max);
sprintf(hname3neg,"ak4puppi/RelRsp_JetEta-%.3fto-%.3f_RefPt%.0fto%.0f",eta_max,eta_min,ptgen_min,ptgen_max);

TH1D *h1pos = (TH1D*)f1->Get(hname1pos);
TH1D *h1neg = (TH1D*)f1->Get(hname1neg);
TH1D *h2pos = (TH1D*)f2->Get(hname2pos);
TH1D *h2neg = (TH1D*)f2->Get(hname2neg);
TH1D *h3pos = (TH1D*)f3->Get(hname3pos);
TH1D *h3neg = (TH1D*)f3->Get(hname3neg);

TH1D *h1 = (TH1D*)h1pos->Clone();
h1->Add(h1neg);
TH1D *h2 = (TH1D*)h2pos->Clone();
h2->Add(h2neg);
TH1D *h3 = (TH1D*)h3pos->Clone();
h3->Add(h3neg);

//h1->Rebin(2);
//h2->Rebin(2);
//h3->Rebin(2);
h1->SetLineWidth(3);
h2->SetLineWidth(3);
h3->SetLineWidth(3);
h1->SetXTitle("Raw response");
h1->SetYTitle("a.u.");
h1->GetYaxis()->SetTitleOffset(1.4);
h1->SetLineColor(kBlack);
h2->SetLineColor(kBlue);
h3->SetLineColor(kMagenta);
h1->SetStats(0);
h1->GetXaxis()->SetTitleSize(0.04);
h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");

char text_metric1[1024], text_metric2[1024], text_metric3[1024], text_metric4[1024], text_metric5[1024];

sprintf(text_metric1,"#splitline{Median = %.2f}{Mean = %.2f}", HistUtil::getHistogramMetric1D("median",h1).first, h1->GetMean());
sprintf(text_metric2,"#splitline{Median = %.2f}{Mean = %.2f}", HistUtil::getHistogramMetric1D("median",h2).first, h2->GetMean());
sprintf(text_metric3,"#splitline{Median = %.2f}{Mean = %.2f}", HistUtil::getHistogramMetric1D("median",h3).first, h3->GetMean());

char leg_eta[1024], leg_pt[1024];
sprintf(leg_eta,"#bf{%.3f < |#eta| < %.3f}",eta_min,eta_max);
sprintf(leg_pt,"#bf{p_{T}^{ptcl}: %.0f - %.0f GeV}",ptgen_min,ptgen_max);

TLegend *l1 = new TLegend(0.6,0.67,0.85,0.88,"");
l1->SetBorderSize(0);
l1->SetTextSize(0.04);
l1->AddEntry((TObject*)0,"#bf{AK4 PUPPI}","");
l1->AddEntry((TObject*)0, leg_eta,"");
l1->AddEntry((TObject*)0, leg_pt,"");
l1->Draw();

TLegend *l1_2 = new TLegend(0.65,0.5,0.9,0.65,"");
l1_2->SetBorderSize(0);
l1_2->SetTextSize(0.04);
l1_2->AddEntry(h1,"first set","L");
l1_2->AddEntry(h2,"second set","L");
l1_2->AddEntry(h3,"third set","L");
l1_2->Draw();

TLegend *l1metric = new TLegend(0.65,0.15,0.9,0.45,"");
l1metric->SetBorderSize(0);
l1metric->SetTextSize(0.04);
l1metric->AddEntry(h1,text_metric1,"L");
l1metric->AddEntry(h2,text_metric2,"L");
l1metric->AddEntry(h3,text_metric3,"L");
l1metric->Draw();

sample->Draw();
cms->Draw();

c1->Update();

//Draws a gray area to denote raw jet T cut at 8 GeV
TBox *box = new TBox(0,gPad->GetUymin(),8./ptgen_max,gPad->GetUymax());
box->SetFillColor(kGray+2);
box->SetFillStyle(3001);
box->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"RspDistrBeforeL2L3_AK4PUPPI_RefPt%.0fto%.0f_JetEta%.3fto%.3f.png",ptgen_min,ptgen_max,eta_min,eta_max);
sprintf(cname2,"RspDistrBeforeL2L3_AK4PUPPI_RefPt%.0fto%.0f_JetEta%.3fto%.3f.pdf",ptgen_min,ptgen_max,eta_min,eta_max);
c1->SaveAs(cname1);
c1->SaveAs(cname2);

}
