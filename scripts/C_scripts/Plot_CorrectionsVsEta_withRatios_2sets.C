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
// Plots 2 sets of corrections vs eta and pT, along
// with their ratio.
//
//////////////////////////////////////////////////////

void Plot_CorrectionsVsEta_withRatios_2sets(){

TPaveText *cms1 = new TPaveText(0.08,0.97,0.43,0.99,"NDC");
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms1->SetFillColor(0);
cms1->SetBorderSize(0);
cms1->SetTextSize(0.05);
cms1->SetTextFont(42);

TPaveText *cms2 = new TPaveText(0.89,0.97,0.94,0.99,"NDC");
cms2->AddText("13.6 TeV");
cms2->SetFillColor(0);
cms2->SetBorderSize(0);
cms2->SetTextSize(0.05);
cms2->SetTextFont(42);

char cname_vsEta_1[1024], cname_vsEta_2[1024];


char Ptbins[10][100]={"p_{T}^{raw} = 10 GeV", "p_{T}^{raw} = 15 GeV", "p_{T}^{raw} = 20 GeV", "p_{T}^{raw} = 30 GeV", "p_{T}^{raw} = 50 GeV", "p_{T}^{raw} = 100 GeV", "p_{T}^{raw} = 300 GeV", "p_{T}^{raw} = 500 GeV", "p_{T}^{raw} = 1000 GeV", "p_{T}^{raw} = 3000 GeV"};


TFile *f1 = new TFile("../Winter23_vs_Summer22/L2L3Correction_AK4CHS_Winter23.root");

TFile *f2 = new TFile("../Winter23_vs_Summer22/L2L3Correction_AK4CHS_Summer22.root");


//Corrections Vs Eta

TCanvas *canvas_vsEta = new TCanvas("canvas_vsEta","canvas_vsEta",900,1000);
canvas_vsEta->cd();
canvas_vsEta->Draw();
TPad *main_panel_vsEta = new TPad("main_panel_vsEta", "main_panel_vsEta", 0, 0.42, 1, 0.95);
main_panel_vsEta->SetTickx(1);
main_panel_vsEta->SetTicky(1);
main_panel_vsEta->SetRightMargin(0.02);
main_panel_vsEta->SetLeftMargin(0.12);
main_panel_vsEta->SetTopMargin(0.05);
main_panel_vsEta->SetBottomMargin(0.001);
main_panel_vsEta->Draw();
TPad *ratio_panel_vsEta = new TPad("ratio_panel_vsEta", "ratio_panel_vsEta", 0, 0., 1, 0.4);
ratio_panel_vsEta->SetTickx(1);
ratio_panel_vsEta->SetTicky(1);
ratio_panel_vsEta->SetRightMargin(0.02);
ratio_panel_vsEta->SetLeftMargin(0.12);
ratio_panel_vsEta->SetTopMargin(0.);
ratio_panel_vsEta->SetBottomMargin(0.2);
ratio_panel_vsEta->Draw();

for(int c=0; c<=9; c++)
{
	TString hstr; 
	hstr.Form("EtaSF_%d",c);
	TH1F *cc1 = (TH1F*)f1->Get(hstr);
	TH1F *cc2 = (TH1F*)f2->Get(hstr);
	cc1->SetStats(0);
	cc2->SetStats(0);
	cc1->SetTitle("");
	cc2->SetTitle("");
	cc1->GetXaxis()->SetTitle("Jet #eta");
	cc1->GetYaxis()->SetTitle("Response (L2L3) correction");
      	cc1->GetYaxis()->SetTitleOffset(1.);
      	cc1->GetYaxis()->SetTitleSize(0.058);
      	cc1->GetXaxis()->SetTitleSize(0.058);
      	cc1->GetXaxis()->SetTitleOffset(0.80);
      	cc1->GetYaxis()->SetRangeUser(0.931,2.39);
      	cc2->GetYaxis()->SetRangeUser(0.931,2.39);
	cc1->SetLineColor(kRed);
	cc2->SetLineColor(kViolet);
	cc1->SetLineWidth(3);
	cc2->SetLineWidth(3);

	TPaveText * pave = new TPaveText(0.75,0.85,0.85,0.9,"NDC");
      	pave->AddText(Ptbins[c]);      
      	pave->SetFillColor(0);
      	pave->SetShadowColor(0);
      	pave->SetBorderSize(0);
	pave->SetTextFont(42);
      	pave->SetTextSize(0.06);

	main_panel_vsEta->cd();

	/*if(c==7 || c==8 || c==9)
	{
		cc1->GetXaxis()->SetRangeUser(-3.139,3.139);
		cc2->GetXaxis()->SetRangeUser(-3.139,3.139);

	}*/

      	cc1->Draw("hist");
	cc2->Draw("hist same");
      	pave->Draw();

	TLegend *l = new TLegend(0.4,0.65,0.6,0.9,"");
	l->SetBorderSize(0);
	l->SetTextSize(0.05);
	l->SetTextFont(42);
	l->SetHeader("AK4 CHS");
	l->AddEntry(cc1,"Winter23","L");
	l->AddEntry(cc2,"Summer22","L");
	l->Draw();

	cms1->Draw();
	cms2->Draw();

	ratio_panel_vsEta->cd();
	ratio_panel_vsEta->SetGridy(1);

	TH1F *h_ratio_1 = (TH1F*)cc1->Clone();
	h_ratio_1->Divide(cc2);

	h_ratio_1->GetYaxis()->SetRangeUser(0.71, 1.29);
	h_ratio_1->GetYaxis()->SetTitle("Winter23 / Summer22");
	h_ratio_1->GetXaxis()->SetTitle("Jet #eta");
      	h_ratio_1->GetYaxis()->SetTitleOffset(0.7);
      	h_ratio_1->GetYaxis()->SetTitleSize(0.09);
      	h_ratio_1->GetXaxis()->SetTitleSize(0.12);
	h_ratio_1->GetYaxis()->SetLabelSize(0.1);
      	h_ratio_1->GetXaxis()->SetLabelSize(0.1);
      	h_ratio_1->GetXaxis()->SetTitleOffset(0.7);
	h_ratio_1->GetXaxis()->SetTickLength(0.08);
	h_ratio_1->GetYaxis()->SetNdivisions(310);
	h_ratio_1->SetMarkerStyle(8);
	h_ratio_1->SetMarkerColor(kBlack);

	/*if(c==7 || c==8 || c==9)
	{
		h_ratio_1->GetXaxis()->SetRangeUser(-3.139,3.139);

	}*/

	h_ratio_1->Draw("P");

	double xrange = 5.2;
	//if(c==7 || c==8 || c==9) xrange = 3.139;

	TLine *line = new TLine(-1*xrange,1,xrange,1);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("same");



	sprintf(cname_vsEta_1, "../Winter23_vs_Summer22/plots_AK4CHS/L2L3CorrectionVsEta_AK4CHS_Winter23_vs_Summer22_%d.png", c);
	sprintf(cname_vsEta_2, "../Winter23_vs_Summer22/plots_AK4CHS/L2L3CorrectionVsEta_AK4CHS_Winter23_vs_Summer22_%d.pdf", c);
	canvas_vsEta->SaveAs(cname_vsEta_1);
	canvas_vsEta->SaveAs(cname_vsEta_2);
	
}



}
