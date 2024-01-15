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

void Plot_CorrectionsVsEta_withRatios(){

TPaveText *cms1 = new TPaveText(0.11,0.955,0.46,0.975,"NDC");
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms1->SetFillColor(0);
cms1->SetBorderSize(0);
cms1->SetTextSize(0.065);
cms1->SetTextFont(42);

TPaveText *cms2 = new TPaveText(0.89,0.955,0.94,0.975,"NDC");
cms2->AddText("13.6 TeV");
cms2->SetFillColor(0);
cms2->SetBorderSize(0);
cms2->SetTextSize(0.065);
cms2->SetTextFont(42);

char cname_vsEta_1[1024], cname_vsEta_2[1024];


char Ptbins[10][100]={"p_{T}^{raw} = 10 GeV", "p_{T}^{raw} = 15 GeV", "p_{T}^{raw} = 20 GeV", "p_{T}^{raw} = 30 GeV", "p_{T}^{raw} = 50 GeV", "p_{T}^{raw} = 100 GeV", "p_{T}^{raw} = 300 GeV", "p_{T}^{raw} = 500 GeV", "p_{T}^{raw} = 1000 GeV","p_{T}^{raw} = 3000 GeV"};


//TFile *f1 = new TFile("../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3Correction_AK4PUPPI_Summer22_V1.root");
TFile *f1 = new TFile("../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3Correction_AK4PUPPI_Winter23_V1.root");

TFile *f2 = new TFile("../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3Correction_AK4PUPPI_Summer22EE_V1.root");

TFile *f3 = new TFile("../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3Correction_AK4PUPPI_Summer23_V1.root");

TFile *f4 = new TFile("../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3Correction_AK4PUPPI_Summer23BPix_V1.root");


//Corrections Vs Eta

TCanvas *canvas_vsEta = new TCanvas("canvas_vsEta","canvas_vsEta",900,1000);
canvas_vsEta->cd();
canvas_vsEta->Draw();
TPad *main_panel_vsEta = new TPad("main_panel_vsEta", "main_panel_vsEta", 0, 0.42, 1, 0.95);
main_panel_vsEta->SetTickx(1);
main_panel_vsEta->SetTicky(1);
main_panel_vsEta->SetRightMargin(0.02);
main_panel_vsEta->SetLeftMargin(0.12);
main_panel_vsEta->SetTopMargin(0.08);
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
	TH1F *cc3 = (TH1F*)f3->Get(hstr);
	TH1F *cc4 = (TH1F*)f4->Get(hstr);
	cc1->SetStats(0);
	cc2->SetStats(0);
	cc3->SetStats(0);
	cc4->SetStats(0);
	cc1->SetTitle("");
	cc2->SetTitle("");
	cc3->SetTitle("");
	cc4->SetTitle("");
	cc1->GetXaxis()->SetTitle("Jet #eta");
	cc1->GetYaxis()->SetTitle("Response (L2L3) correction");
      	cc1->GetYaxis()->SetTitleOffset(1.);
      	cc1->GetYaxis()->SetTitleSize(0.058);
      	cc1->GetXaxis()->SetTitleSize(0.058);
      	cc1->GetXaxis()->SetTitleOffset(0.80);
      	cc1->GetXaxis()->SetNdivisions(311);
      	cc1->GetYaxis()->SetRangeUser(0.91,2.49);
      	cc2->GetYaxis()->SetRangeUser(0.91,2.49);
      	cc3->GetYaxis()->SetRangeUser(0.91,2.49);
      	cc4->GetYaxis()->SetRangeUser(0.91,2.49);
	//cc1->SetLineColor(kBlue-4);
	cc1->SetLineColor(kBlack);
	cc2->SetLineColor(kRed-4);
	cc3->SetLineColor(kGreen-2);
	cc4->SetLineColor(kViolet);
	cc1->SetLineWidth(3);
	cc2->SetLineWidth(3);
	cc3->SetLineWidth(3);
	cc4->SetLineWidth(3);

	TPaveText * pave = new TPaveText(0.75,0.78,0.85,0.83,"NDC");
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
		cc3->GetXaxis()->SetRangeUser(-3.139,3.139);

	}*/

      	cc1->Draw("hist");
	//cc2->Draw("hist same");
	cc3->Draw("hist same");
	cc4->Draw("hist same");
      	pave->Draw();

	TLegend *l = new TLegend(0.4,0.63,0.6,0.88,"");
	l->SetBorderSize(0);
	l->SetTextSize(0.05);
	l->SetTextFont(42);
	l->AddEntry((TObject*)0,"AK4 PUPPI","");
	//l->AddEntry(cc1,"Summer22","L");
	l->AddEntry(cc1,"Winter23","L");
	//l->AddEntry(cc2,"Summer22EE","L");
	l->AddEntry(cc3,"Summer23","L");
	l->AddEntry(cc4,"Summer23BPix","L");
	l->Draw();

	cms1->Draw();
	cms2->Draw();

	ratio_panel_vsEta->cd();
	//ratio_panel_vsEta->SetGridy(1);

	TH1F *h_ratio_1 = (TH1F*)cc3->Clone();
	h_ratio_1->Divide(cc1);

	TH1F *h_ratio_2 = (TH1F*)cc4->Clone();
	h_ratio_2->Divide(cc1);

	TH1F *h_ratio_3 = (TH1F*)cc4->Clone();
	h_ratio_3->Divide(cc3);

	h_ratio_1->GetYaxis()->SetRangeUser(0.921, 1.119);
	h_ratio_1->GetYaxis()->SetTitle("Ratio");
	h_ratio_1->GetXaxis()->SetTitle("Jet #eta");
      	h_ratio_1->GetYaxis()->SetTitleOffset(0.6);
      	h_ratio_1->GetYaxis()->SetTitleSize(0.1);
      	h_ratio_1->GetXaxis()->SetTitleSize(0.12);
	h_ratio_1->GetYaxis()->SetLabelSize(0.08);
      	h_ratio_1->GetXaxis()->SetLabelSize(0.1);
      	h_ratio_1->GetXaxis()->SetTitleOffset(0.73);
	h_ratio_1->GetXaxis()->SetTickLength(0.08);
	h_ratio_1->GetYaxis()->SetNdivisions(310);
	h_ratio_1->GetXaxis()->SetNdivisions(311);
	h_ratio_1->GetYaxis()->CenterTitle(1);
	h_ratio_1->SetMarkerStyle(8);
	h_ratio_1->SetMarkerColor(kOrange+1);
	h_ratio_1->SetLineColor(kOrange+1);
	h_ratio_1->SetLineWidth(2);
	h_ratio_2->SetMarkerStyle(21);
	h_ratio_2->SetMarkerColor(kCyan-6);
	h_ratio_2->SetLineColor(kCyan-6);
	h_ratio_2->SetLineWidth(2);
	h_ratio_3->SetMarkerStyle(34);
	h_ratio_3->SetMarkerColor(kBlack);
	h_ratio_3->SetLineColor(kBlack);
	h_ratio_3->SetMarkerSize(1.3);
	h_ratio_3->SetLineWidth(2);

	/*if(c==7 || c==8)
	{
		h_ratio_1->GetXaxis()->SetRangeUser(-3.139,3.139);
		h_ratio_2->GetXaxis()->SetRangeUser(-3.139,3.139);
		h_ratio_3->GetXaxis()->SetRangeUser(-3.139,3.139);

	}*/

	h_ratio_1->Draw("CP");
	h_ratio_2->Draw("CP same");
	//h_ratio_3->Draw("CP same");

	double xrange = 5.2;
	//if(c==7 || c==8 || c==9) xrange = 3.139;

	TLine *line = new TLine(-1*xrange,1,xrange,1);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("same");
	
	TLine *line2 = new TLine(-1*xrange,1.025,xrange,1.025);
	line2->SetLineStyle(2);
	line2->SetLineWidth(2);
	line2->Draw("same");
	
	TLine *line3 = new TLine(-1*xrange,0.975,xrange,0.975);
	line3->SetLineStyle(2);
	line3->SetLineWidth(2);
	line3->Draw("same");


	TLegend *lr = new TLegend(0.37,0.73,0.57,0.93,"");
	lr->SetBorderSize(0);
	lr->SetTextSize(0.06);
	lr->SetTextFont(42);
	//lr->AddEntry(h_ratio_1,"Summer23 / Summer22","p");
	//lr->AddEntry(h_ratio_2,"Summer23BPix / Summer22","p");
	lr->AddEntry(h_ratio_1,"Summer23 / Winter23","p");
	lr->AddEntry(h_ratio_2,"Summer23BPix / Winter23","p");
	//lr->AddEntry(h_ratio_3,"Summer23BPix / Summer23","p");
	lr->Draw();


	//sprintf(cname_vsEta_1, "../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3CorrectionVsEta_AK4PUPPI_Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix_%d.png", c);
	//sprintf(cname_vsEta_2, "../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3CorrectionVsEta_AK4PUPPI_Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix_%d.pdf", c);
	sprintf(cname_vsEta_1, "../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3CorrectionVsEta_AK4PUPPI_Winter23_vs_Summer23_vs_Summer23BPix_%d.png", c);
	sprintf(cname_vsEta_2, "../Summer22_vs_Summer22EE_vs_Summer23_vs_Summer23BPix/Correction_Factors/L2L3CorrectionVsEta_AK4PUPPI_Winter23_vs_Summer23_vs_Summer23BPix_%d.pdf", c);
	canvas_vsEta->SaveAs(cname_vsEta_1);
	canvas_vsEta->SaveAs(cname_vsEta_2);
	
}



}
