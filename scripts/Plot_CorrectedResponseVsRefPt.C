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
// Plots the overall corrected response as a function
// of pT for fine eta bins.  
//
//////////////////////////////////////////////////////


using namespace std;

void Plot_CorrectedResponseVsRefPt(){

TFile *f1 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_Run3Winter22/Flat2018QCD/AK4CHS/Step4_applyPUPPIcorr/Merged.root"); 
TFile *f2 = new TFile("/eos/cms/store/group/phys_jetmet/ilias/JEC_Run3Winter22/Flat2018QCD/AK4PUPPI/Step4_pTcut6GeV/Merged.root"); 

double ptbins[52] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 20, 23, 27, 30, 35, 40, 45, 57, 72, 90, 120, 150, 200, 300, 400, 550,
750, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000};
char hname1[1024], hname2[1024];

TH1F *g1pos = new TH1F("g1pos","",51,ptbins);
TH1F *g1neg = new TH1F("g1neg","",51,ptbins);
TH1F *g2pos = new TH1F("g2pos","",51,ptbins);
TH1F *g2neg = new TH1F("g2neg","",51,ptbins);

//42->[0, 0.087] 	, 41->[-0.087, 0]
//49->[0.609,0.696]	, 34->[-0.696,-0.609]
//53->[0.957,1.044]	, 30->[-1.044,-0.957]
//56->[1.218,1.305]	, 27->[-1.305,-1.218]
//57->[1.305,1.392]	, 26->[-1.392,-1.305]
//59->[1.479,1.566]	, 24->[-1.566,-1.479]
//61->[1.653,1.74]	, 22->[-1.74,-1.653]
//64->[1.93,2.043]	, 19->[-2.043,-1.93]
//67->[2.322,2.5]	, 16->[-2.5,-2.322]
//68->[2.5,2.65]	, 15->[-2.65,-2.5]
//69->[2.65,2.853]	, 14->[-2.853,-2.65]
//70->[2.853,2.964]	, 13->[-2.964,-2.853]
//71->[2.964,3.139]	, 12->[-3.139,-2.964]
//76->[3.839,4.013]	,  7->[-4.013,-3.839]

int binpos = 67;
int binneg = 16;
double eta_min = 2.322;
double eta_max = 2.5;

for(int i=0; i<=50; i++)
{
	double ptmin = ptbins[i];
	double ptmax = ptbins[i+1];

	sprintf(hname1,"ak4pfchs/RelRspVsJetEta_RefPt%.0fto%.0f",ptmin,ptmax);
	sprintf(hname2,"ak4puppi/RelRspVsJetEta_RefPt%.0fto%.0f",ptmin,ptmax);

	TH2F *h1 = (TH2F*)(f1->Get(hname1));
	TH2F *h2 = (TH2F*)(f2->Get(hname2));

	TH1F *h1proj_pos = (TH1F*)h1->ProjectionY("_proj1_pos",binpos,binpos,"e");
	TH1F *h1proj_neg = (TH1F*)h1->ProjectionY("_proj1_neg",binneg,binneg,"e");

	TH1F *h2proj_pos = (TH1F*)h2->ProjectionY("_proj2_pos",binpos,binpos,"e");
	TH1F *h2proj_neg = (TH1F*)h2->ProjectionY("_proj2_neg",binneg,binneg,"e");

	if(h1proj_pos->GetEntries()>0)
	{
		double bincont1_pos = HistUtil::getHistogramMetric1D("median",h1proj_pos).first;
		double binerr1_pos = HistUtil::getHistogramMetric1D("median",h1proj_pos).second;

		g1pos->SetBinContent(i+1,bincont1_pos);
		g1pos->SetBinError(i+1,binerr1_pos);
	}
	else
	{
		g1pos->SetBinContent(i+1,0);
		g1pos->SetBinError(i+1,0);
	}

	if(h1proj_neg->GetEntries()>0)
	{
		double bincont1_neg = HistUtil::getHistogramMetric1D("median",h1proj_neg).first;
		double binerr1_neg = HistUtil::getHistogramMetric1D("median",h1proj_neg).second;

		g1neg->SetBinContent(i+1,bincont1_neg);
		g1neg->SetBinError(i+1,binerr1_neg);
	}
	else
	{
		g1neg->SetBinContent(i+1,0);
		g1neg->SetBinError(i+1,0);
	}

	if(h2proj_pos->GetEntries()>0)
	{
		double bincont2_pos = HistUtil::getHistogramMetric1D("median",h2proj_pos).first;
		double binerr2_pos = HistUtil::getHistogramMetric1D("median",h2proj_pos).second;

		g2pos->SetBinContent(i+1,bincont2_pos);
		g2pos->SetBinError(i+1,binerr2_pos);
	}
	else
	{
		g2pos->SetBinContent(i+1,0);
		g2pos->SetBinError(i+1,0);
	}


	if(h2proj_neg->GetEntries()>0)
	{
		double bincont2_neg = HistUtil::getHistogramMetric1D("median",h2proj_neg).first;
		double binerr2_neg = HistUtil::getHistogramMetric1D("median",h2proj_neg).second;

		g2neg->SetBinContent(i+1,bincont2_neg);
		g2neg->SetBinError(i+1,binerr2_neg);
	}
	else
	{
		g2neg->SetBinContent(i+1,0);
		g2neg->SetBinError(i+1,0);
	}

	//cout << "Pt = [" << ptmin << " , " << ptmax << " ] , " << "Cont = " << g1pos->GetBinContent(i+1) << " , error = " << g1pos->GetBinError(i+1) << endl;
	
}




g1pos->SetMarkerColor(kBlue);
g1pos->SetMarkerStyle(22);
g1neg->SetMarkerColor(kBlue-9);
g1neg->SetMarkerStyle(22);

g2pos->SetMarkerColor(kBlack);
g2pos->SetMarkerStyle(22);
g2neg->SetMarkerColor(kGray+2);
g2neg->SetMarkerStyle(22);


TCanvas *c = new TCanvas("c","c",800,700);
c->SetLogx(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetLeftMargin(0.14);
c->SetTopMargin(0.07);
c->SetBottomMargin(0.12);
c->SetRightMargin(0.02);
c->cd();

g1pos->SetStats(0);

g1pos->Draw("PΕ");
g1neg->Draw("PΕ SAME");
g2pos->Draw("PΕ SAME");
g2neg->Draw("PΕ SAME");

g1pos->GetXaxis()->SetTitle("p_{T}^{ptcl} [GeV]");
g1pos->GetXaxis()->SetTitleSize(0.04);
g1pos->GetXaxis()->SetTitleOffset(1.3);
g1pos->GetYaxis()->SetTitle("median(Response) = median(p_{T}^{reco} / p_{T}^{ptcl})");
g1pos->GetYaxis()->SetTitleSize(0.04);
g1pos->GetYaxis()->SetTitleOffset(1.7);

g1pos->GetYaxis()->SetRangeUser(0.94,1.06);
g1neg->GetYaxis()->SetRangeUser(0.94,1.06);
g2pos->GetYaxis()->SetRangeUser(0.94,1.06);
g2neg->GetYaxis()->SetRangeUser(0.94,1.06);

g1pos->GetXaxis()->SetRangeUser(20, 6000);
g1neg->GetXaxis()->SetRangeUser(20, 6000);
g2pos->GetXaxis()->SetRangeUser(20, 6000);
g2neg->GetXaxis()->SetRangeUser(20, 6000);

TLegend *l = new TLegend(0.65,0.65,0.9,0.9,"");
l->SetTextSize(0.03);
l->SetFillColor(0);
l->SetBorderSize(0);
l->SetTextFont(42);
//l->SetHeader("PUPPI corrections applied");
l->AddEntry(g1pos,"AK4 CHS (#eta > 0)","PE");
l->AddEntry(g1neg,"AK4 CHS (#eta < 0)","PE");
l->AddEntry(g2pos,"AK4 PUPPI (#eta > 0)","PE");
l->AddEntry(g2neg,"AK4 PUPPI (#eta < 0)","PE");
l->Draw();

char eta_leg[1024];
sprintf(eta_leg,"%.3f < |#eta| < %.3f",eta_min,eta_max);

TLegend *l2 = new TLegend(0.15,0.15,0.3,0.22,"");
//TLegend *l2 = new TLegend(0.15,0.8,0.3,0.9,"");
l2->SetTextSize(0.05);
l2->SetFillColor(0);
l2->SetBorderSize(0);
l2->SetTextFont(42);
l2->AddEntry((TObject*)0,eta_leg,"");
l2->Draw();

TLegend *l3 = new TLegend(0.3,0.22,0.9,0.4,"");
l3->SetTextSize(0.04);
l3->SetFillColor(0);
l3->SetBorderSize(0);
l3->SetTextFont(42);
l3->AddEntry((TObject*)0,"#splitline{L2L3 PUPPI corrections}{applied to CHS and PUPPI jets}","");
l3->Draw();

TLine *line1 = new TLine(20,1.01,6000,1.01);
TLine *line2 = new TLine(20,0.99,6000,0.99);
TLine *line3 = new TLine(20,1.00,6000,1.00);
line1->SetLineWidth(2);
line2->SetLineWidth(2);
line3->SetLineWidth(2);
line1->SetLineStyle(kDashed);
line2->SetLineStyle(kDashed);
line3->SetLineStyle(kDashed);
line1->Draw("same");
line2->Draw("same");
line3->Draw("same");

TPaveText *sample = new TPaveText(0.63,0.94,0.98,0.98,"NDC");
sample->AddText("Run3Winter22 (13.6 TeV)");
sample->SetTextFont(42);
sample->SetTextSize(0.04);
sample->SetBorderSize(0);
sample->SetFillColor(0); 
sample->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"CHS_vs_PUPPI_forAnalysis/CorrResponseVsGenPt_eta%.3fto%.3f.png",eta_min,eta_max);
sprintf(cname2,"CHS_vs_PUPPI_forAnalysis/CorrResponseVsGenPt_eta%.3fto%.3f.pdf",eta_min,eta_max);
c->SaveAs(cname1);
c->SaveAs(cname2);

}















