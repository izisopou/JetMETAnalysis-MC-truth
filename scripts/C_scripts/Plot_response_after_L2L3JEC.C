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

void Plot_response_after_L2L3JEC(double ptgen_min, double ptgen_max){

double eta_min = 3.0;
double eta_max = 5.0;

TPaveText *cms = new TPaveText(0.195,0.91,0.395,0.95,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.04);
cms->SetBorderSize(0);
cms->SetFillColor(0);

//TPaveText *sample = new TPaveText(0.57,0.91,0.97,0.95,"NDC");
TPaveText *sample = new TPaveText(0.8,0.91,0.97,0.95,"NDC"); 
//sample->AddText("Run3Winter22 (13.6 TeV)");
sample->AddText("13.6 TeV");
sample->SetTextFont(42);
sample->SetTextSize(0.04);
sample->SetBorderSize(0);
sample->SetFillColor(0);

TCanvas *c1 = new TCanvas("c1","c1",800,700);
c1->SetTickx(1);
c1->SetTicky(1);
c1->SetRightMargin(0.05);
c1->SetLeftMargin(0.14);
c1->cd();

TFile *f1 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods_Run3/Summer22/V1/Step4_AK4PUPPI_finer_in_eta/Merged.root","READ");
TFile *f2 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods_Run3/Summer22EE/V1_withVetoMap/Step4_AK4PUPPI_finer_in_eta/Merged.root","READ");
TFile *f3 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods_Run3/Summer23/V1_withVetoMap/Step4_AK4PUPPI_finer_in_eta/Merged.root","READ");
TFile *f4 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_NewMethods_Run3/Summer23BPix/V1_withVetoMap/Step4_AK4PUPPI_finer_in_eta/Merged.root","READ");

char hname1[1024], hname2[1024], hname3[1024], hname4[1024];

sprintf(hname1,"ak4puppi/RelRspVsRefPt_JetEta%.0fto%.0f",eta_min,eta_max);
sprintf(hname2,"ak4puppi/RelRspVsRefPt_JetEta%.0fto%.0f",eta_min,eta_max);
sprintf(hname3,"ak4puppi/RelRspVsRefPt_JetEta%.0fto%.0f",eta_min,eta_max);
sprintf(hname4,"ak4puppi/RelRspVsRefPt_JetEta%.0fto%.0f",eta_min,eta_max);

TH2F *histo1 = (TH2F*)f1->Get(hname1);
TH2F *histo2 = (TH2F*)f2->Get(hname2);
TH2F *histo3 = (TH2F*)f3->Get(hname3);
TH2F *histo4 = (TH2F*)f4->Get(hname4);

int ptbin = -999;

for(int i=1; i<=histo1->GetNbinsX(); i++)
{
	cout << "Bin " << i << " : [" << histo1->GetXaxis()->GetBinLowEdge(i) << ", " << histo1->GetXaxis()->GetBinLowEdge(i+1) << "] GeV" << endl;
	if (histo1->GetXaxis()->GetBinLowEdge(i) == ptgen_min && histo1->GetXaxis()->GetBinLowEdge(i+1) == ptgen_max)
	{
		ptbin = i;
	}
}

cout << "Bin used = " << ptbin << endl;

TH1D *h1 = (TH1D*)histo1->ProjectionY("h1",ptbin,ptbin,"e");
TH1D *h2 = (TH1D*)histo2->ProjectionY("h2",ptbin,ptbin,"e");
TH1D *h3 = (TH1D*)histo3->ProjectionY("h3",ptbin,ptbin,"e");
TH1D *h4 = (TH1D*)histo4->ProjectionY("h4",ptbin,ptbin,"e");

//h4->Rebin(5);
h1->SetLineWidth(3);
h2->SetLineWidth(3);
h3->SetLineWidth(3);
h4->SetLineWidth(3);
h1->SetXTitle("Corrected response");
h1->SetYTitle("Normalized entries");
h1->GetYaxis()->SetTitleSize(0.05);
h1->GetYaxis()->SetTitleOffset(1.4);
h1->SetLineColor(kBlue-4);
h2->SetLineColor(kRed-4);
h3->SetLineColor(kGreen-2);
h4->SetLineColor(kViolet);
h1->SetStats(0);
h1->SetTitle("");
h1->GetXaxis()->SetTitleSize(0.04);
h2->Scale(h1->Integral()/h2->Integral());
h3->Scale(h1->Integral()/h3->Integral());
h4->Scale(h1->Integral()/h4->Integral());
double max = h1->GetMaximum();
if(max < h2->GetMaximum()) max = h2->GetMaximum();
if(max < h3->GetMaximum()) max = h3->GetMaximum();
if(max < h4->GetMaximum()) max = h4->GetMaximum();
h1->GetYaxis()->SetRangeUser(0,max*1.05);
h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");
h4->Draw("hist same");

char text_metric1[1024], text_metric2[1024], text_metric3[1024], text_metric4[1024];

sprintf(text_metric1,"#splitline{Median = %.3f}{Mean = %.3f}", HistUtil::getHistogramMetric1D("median",h1).first, h1->GetMean());
sprintf(text_metric2,"#splitline{Median = %.3f}{Mean = %.3f}", HistUtil::getHistogramMetric1D("median",h2).first, h2->GetMean());
sprintf(text_metric3,"#splitline{Median = %.3f}{Mean = %.3f}", HistUtil::getHistogramMetric1D("median",h3).first, h3->GetMean());
sprintf(text_metric4,"#splitline{Median = %.3f}{Mean = %.3f}", HistUtil::getHistogramMetric1D("median",h4).first, h4->GetMean());

char leg_eta[1024], leg_pt[1024];
sprintf(leg_eta,"#bf{%.1f < |#eta^{rec}| < %.1f}",eta_min,eta_max);
sprintf(leg_pt,"#bf{p_{T}^{ptcl}: %.0f - %.0f GeV}",ptgen_min,ptgen_max);

TLegend *l1 = new TLegend(0.62,0.72,0.85,0.88,"");
l1->SetBorderSize(0);
l1->SetTextSize(0.04);
l1->AddEntry((TObject*)0,"AK4 PUPPI","");
l1->AddEntry((TObject*)0, leg_eta,"");
l1->AddEntry((TObject*)0, leg_pt,"");
l1->Draw();

TLegend *l1_2 = new TLegend(0.65,0.55,0.9,0.7,"");
//TLegend *l1_2 = new TLegend(0.45,0.12,0.6,0.42,"");
l1_2->SetBorderSize(0);
l1_2->SetTextSize(0.04);
//l1_2->SetHeader("L2L3 only");
l1_2->AddEntry(h1,"Summer22","L");
l1_2->AddEntry(h2,"Summer22EE","L");
l1_2->AddEntry(h3,"Summer23","L");
l1_2->AddEntry(h4,"Summer23BPix","L");
//l1_2->AddEntry(h3,"#splitline{|#Delta Z| < 0.2 cm}{p_{T}^{raw} > 0 GeV}","L");
//l1_2->AddEntry(h4,"#splitline{No |#Delta Z| cut}{p_{T}^{raw} > 6 GeV}","L");
//l1_2->AddEntry(h3,"#splitline{NM > 1}{p_{T}^{raw} > 0 GeV}","L");
//l1_2->AddEntry(h4,"#splitline{No NM cut}{p_{T}^{raw} > 6 GeV}","L");
l1_2->Draw();

//TLegend *l1metric = new TLegend(0.12,0.7,0.32,0.88,"");
TLegend *l1metric = new TLegend(0.65,0.20,0.9,0.52,"");
l1metric->SetBorderSize(0);
l1metric->SetTextSize(0.032);
l1metric->AddEntry(h1,text_metric1,"L");
l1metric->AddEntry(h2,text_metric2,"L");
l1metric->AddEntry(h3,text_metric3,"L");
l1metric->AddEntry(h4,text_metric4,"L");
l1metric->Draw();

sample->Draw();
cms->Draw();

//c1->Update();

//Draws a gray area to denote raw jet T cut at 8 GeV
//TBox *box = new TBox(0,gPad->GetUymin(),8./ptgen_max,gPad->GetUymax());
//box->SetFillColor(kGray+2);
//box->SetFillStyle(3001);
//box->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/response_distributions/CorrRspDistr_AK4PUPPI_Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix_RefPt%.0fto%.0f_JetEta%.1fto%.1f.png",ptgen_min,ptgen_max,eta_min,eta_max);
sprintf(cname2,"/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/response_distributions/CorrRspDistr_AK4PUPPI_Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix_RefPt%.0fto%.0f_JetEta%.1fto%.1f.pdf",ptgen_min,ptgen_max,eta_min,eta_max);

c1->SaveAs(cname1);
c1->SaveAs(cname2);

}
