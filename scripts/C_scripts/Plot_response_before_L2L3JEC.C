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

double eta_min = 3.0;
double eta_max = 5.0;

TPaveText *cms = new TPaveText(0.15,0.91,0.35,0.95,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.04);
cms->SetBorderSize(0);
cms->SetFillColor(0);

//TPaveText *sample = new TPaveText(0.57,0.91,0.97,0.95,"NDC"); 
TPaveText *sample = new TPaveText(0.72,0.91,0.97,0.95,"NDC"); 
//sample->AddText("Run3Winter23 (13.6 TeV)");
sample->AddText("13.6 TeV");
sample->SetTextFont(42);
sample->SetTextSize(0.04);
sample->SetBorderSize(0);
sample->SetFillColor(0);

TCanvas *c1 = new TCanvas("c1","c1",800,700);
c1->SetTickx(1);
c1->SetTicky(1);
c1->SetRightMargin(0.05);
c1->cd();

TFile *f1 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods_Run3/Winter23/V1/Step3_AK4CHS_CoarseBinning/Merged.root","READ");
TFile *f2 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods_Run3/Summer22/V1/Step3_AK4CHS_CoarseBinning/Merged.root","READ");
//TFile *f3 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods/Winter22/Matching_Efficiency_Fake_Rates/Step3_AK4PUPPI_PremixedPU_NMeqt1/Merged.root","READ");
//TFile *f4 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods/Winter22/Matching_Efficiency_Fake_Rates/Step3_AK4PUPPI_PremixedPU_NMeqt2/Merged.root","READ");
//TFile *f5 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods/Winter22/Matching_Efficiency_Fake_Rates/Step3_AK4PUPPI_PremixedPU_NMgt2/Merged.root","READ");

char hname1pos[1024], hname1neg[1024], hname2pos[1024], hname2neg[1024], hname3pos[1024], hname3neg[1024], hname4pos[1024], hname4neg[1024], hname5pos[1024], hname5neg[1024];

sprintf(hname1pos,"ak4pfchsl1/RelRsp_JetEta%.0fto%.0f_RefPt%.0fto%.0f",eta_min,eta_max,ptgen_min,ptgen_max);
sprintf(hname1neg,"ak4pfchsl1/RelRsp_JetEta-%.0fto-%.0f_RefPt%.0fto%.0f",eta_max,eta_min,ptgen_min,ptgen_max);
sprintf(hname2pos,"ak4pfchsl1/RelRsp_JetEta%.0fto%.0f_RefPt%.0fto%.0f",eta_min,eta_max,ptgen_min,ptgen_max);
sprintf(hname2neg,"ak4pfchsl1/RelRsp_JetEta-%.0fto-%.0f_RefPt%.0fto%.0f",eta_max,eta_min,ptgen_min,ptgen_max);
//sprintf(hname3pos,"ak4puppi/RelRsp_JetEta%.1fto%.0f_RefPt%.0fto%.0f",eta_min,eta_max,ptgen_min,ptgen_max);
//sprintf(hname3neg,"ak4puppi/RelRsp_JetEta-%.0fto-%.1f_RefPt%.0fto%.0f",eta_max,eta_min,ptgen_min,ptgen_max);
//sprintf(hname4pos,"ak4puppi/RelRsp_JetEta%.1fto%.0f_RefPt%.0fto%.0f",eta_min,eta_max,ptgen_min,ptgen_max);
//sprintf(hname4neg,"ak4puppi/RelRsp_JetEta-%.0fto-%.1f_RefPt%.0fto%.0f",eta_max,eta_min,ptgen_min,ptgen_max);
//sprintf(hname5pos,"ak4puppi/RelRsp_JetEta%.1fto%.0f_RefPt%.0fto%.0f",eta_min,eta_max,ptgen_min,ptgen_max);
//sprintf(hname5neg,"ak4puppi/RelRsp_JetEta-%.0fto-%.1f_RefPt%.0fto%.0f",eta_max,eta_min,ptgen_min,ptgen_max);

TH1D *h1pos = (TH1D*)f1->Get(hname1pos);
TH1D *h1neg = (TH1D*)f1->Get(hname1neg);
TH1D *h2pos = (TH1D*)f2->Get(hname2pos);
TH1D *h2neg = (TH1D*)f2->Get(hname2neg);
//TH1D *h3pos = (TH1D*)f3->Get(hname3pos);
//TH1D *h3neg = (TH1D*)f3->Get(hname3neg);
//TH1D *h4pos = (TH1D*)f4->Get(hname4pos);
//TH1D *h4neg = (TH1D*)f4->Get(hname4neg);
//TH1D *h5pos = (TH1D*)f5->Get(hname5pos);
//TH1D *h5neg = (TH1D*)f5->Get(hname5neg);

TH1D *h1 = (TH1D*)h1pos->Clone();
h1->Add(h1neg);
TH1D *h2 = (TH1D*)h2pos->Clone();
h2->Add(h2neg);
//TH1D *h3 = (TH1D*)h3pos->Clone();
//h3->Add(h3neg);
//TH1D *h4 = (TH1D*)h4pos->Clone();
//h4->Add(h4neg);
//TH1D *h5 = (TH1D*)h5pos->Clone();
//h5->Add(h5neg);

h1->SetLineWidth(3);
h2->SetLineWidth(3);
//h3->SetLineWidth(3);
//h4->SetLineWidth(3);
//h5->SetLineWidth(3);
h1->SetXTitle("Response");
h1->SetYTitle("a.u.");
h1->GetYaxis()->SetTitleOffset(1.4);
h1->SetLineColor(kRed);
h2->SetLineColor(kViolet);
//h3->SetLineColor(kOrange);
//h4->SetLineColor(kGreen+2);
//h5->SetLineColor(kBlue-2);
h1->SetStats(0);
h1->GetXaxis()->SetTitleSize(0.04);
h2->Scale(h1->Integral()/h2->Integral());
//h3->Scale(h1->Integral()/h3->Integral());
double max = h1->GetMaximum();
if(max < h2->GetMaximum()) max = h2->GetMaximum();
//if(max < h3->GetMaximum()) max = h3->GetMaximum();
//if(max < h4->GetMaximum()) max = h4->GetMaximum();
//if(max < h5->GetMaximum()) max = h5->GetMaximum();
h1->GetYaxis()->SetRangeUser(0,max*1.05);
h1->Draw("hist");
h2->Draw("hist same");
//h3->Draw("hist same");
//h4->Draw("hist same");
//h5->Draw("hist same");

char text_metric1[1024], text_metric2[1024], text_metric3[1024], text_metric4[1024], text_metric5[1024];

sprintf(text_metric1,"#splitline{Median = %.2f}{Mean = %.2f}", HistUtil::getHistogramMetric1D("median",h1).first, h1->GetMean());
sprintf(text_metric2,"#splitline{Median = %.2f}{Mean = %.2f}", HistUtil::getHistogramMetric1D("median",h2).first, h2->GetMean());
//sprintf(text_metric3,"#splitline{Median = %.2f}{Mean = %.2f}", HistUtil::getHistogramMetric1D("median",h3).first, h3->GetMean());
//sprintf(text_metric4,"#splitline{Median = %.2f}{Mean = %.2f}", HistUtil::getHistogramMetric1D("median",h4).first, h4->GetMean());
//sprintf(text_metric5,"#splitline{Median = %.2f}{Mean = %.2f}", HistUtil::getHistogramMetric1D("median",h5).first, h5->GetMean());

char leg_eta[1024], leg_pt[1024];
sprintf(leg_eta,"#bf{%.1f < |#eta^{rec}| < %.1f}",eta_min,eta_max);
sprintf(leg_pt,"#bf{p_{T}^{gen}: %.0f - %.0f GeV}",ptgen_min,ptgen_max);

//TLegend *l1 = new TLegend(0.58,0.22,0.83,0.38,"");
TLegend *l1 = new TLegend(0.58,0.72,0.83,0.88,"");
l1->SetBorderSize(0);
l1->SetTextSize(0.04);
l1->AddEntry((TObject*)0,"AK4 CHS","");
//l1->AddEntry((TObject*)0,"#bf{PU}","");
l1->AddEntry((TObject*)0, leg_eta,"");
l1->AddEntry((TObject*)0, leg_pt,"");
l1->Draw();

TLegend *l1_2 = new TLegend(0.65,0.6,0.9,0.7,"");
l1_2->SetBorderSize(0);
l1_2->SetTextSize(0.04);
//l1_2->SetHeader("New Methods");
l1_2->AddEntry(h1,"Winter23","L");
l1_2->AddEntry(h2,"Summer22","L");
//l1_2->AddEntry(h3,"NM = 1","L");
//l1_2->AddEntry(h4,"NM = 2","L");
//l1_2->AddEntry(h5,"NM > 2","L");
l1_2->Draw();

TLegend *l1metric = new TLegend(0.63,0.21,0.88,0.41,"");
l1metric->SetBorderSize(0);
l1metric->SetTextSize(0.04);
l1metric->AddEntry(h1,text_metric1,"L");
l1metric->AddEntry(h2,text_metric2,"L");
//l1metric->AddEntry(h3,text_metric3,"L");
//l1metric->AddEntry(h4,text_metric4,"L");
//l1metric->AddEntry(h5,text_metric5,"L");
l1metric->Draw();

sample->Draw();
cms->Draw();

c1->Update();

//Draws a gray area to denote raw jet T cut at 8 GeV
//TBox *box = new TBox(0,gPad->GetUymin(),8./ptgen_max,gPad->GetUymax());
//box->SetFillColor(kGray+2);
//box->SetFillStyle(3001);
//box->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/Winter23_vs_Summer22/plots_AK4CHS/RawRspDistr_AK4CHS_Winter23_vs_Summer22_RefPt%.0fto%.0f_JetEta%.1fto%.1f.png",ptgen_min,ptgen_max,eta_min,eta_max);
sprintf(cname2,"/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/Winter23_vs_Summer22/plots_AK4CHS/RawRspDistr_AK4CHS_Winter23_vs_Summer22_RefPt%.0fto%.0f_JetEta%.1fto%.1f.pdf",ptgen_min,ptgen_max,eta_min,eta_max);

c1->SaveAs(cname1);
c1->SaveAs(cname2);

}
