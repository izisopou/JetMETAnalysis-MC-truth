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
// Plots the [median(Response)]^-1 as a function of
// pTreco for a fine eta bin, along with the std+Gaus fit
//
//////////////////////////////////////////////////////

using namespace std;

void Plot_InverseOfResponseVsJetPt();

void Plot_InverseOfResponseVsJetPt(){

TPaveText *cms = new TPaveText(0.21,0.94,0.36,0.98,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.04);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TPaveText *mc = new TPaveText(0.87,0.94,0.97,0.98,"NDC");
mc->SetFillColor(0);
mc->SetBorderSize(0);
mc->AddText("13.6 TeV");
mc->SetTextFont(42);
mc->SetTextSize(0.035);

double eta_min = 2.964;
double eta_max = 3.139;

double ymin = 0.8;
double ymax = 2.2;

TFile *f1 = new TFile("/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/condor_AK4PUPPI/Files/Winter23_V1/L2L3_output/l2.root"); 
TFile *f2 = new TFile("/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/condor_AK4PUPPI/Files/Summer22_V1/L2L3_output/l2.root"); 

char hname1pos[1024], hname1neg[1024], hname2pos[1024], hname2neg[1024];

sprintf(hname1pos,"ak4puppi/AbsCorVsJetPt_JetEta%.3fto%.3f",eta_min,eta_max);
sprintf(hname1neg,"ak4puppi/AbsCorVsJetPt_JetEta-%.3fto-%.3f",eta_max,eta_min);
sprintf(hname2pos,"ak4puppi/AbsCorVsJetPt_JetEta%.3fto%.3f",eta_min,eta_max);
sprintf(hname2neg,"ak4puppi/AbsCorVsJetPt_JetEta-%.3fto-%.3f",eta_max,eta_min);

TGraphErrors *g1pos = (TGraphErrors*)(f1->Get(hname1pos));
TGraphErrors *g1neg = (TGraphErrors*)(f1->Get(hname1neg));
TGraphErrors *g2pos = (TGraphErrors*)(f2->Get(hname2pos));
TGraphErrors *g2neg = (TGraphErrors*)(f2->Get(hname2neg));

g1pos->SetMarkerColor(kRed);
g1neg->SetMarkerColor(kRed);
g2pos->SetMarkerColor(kViolet);
g2neg->SetMarkerColor(kViolet);

g1pos->SetLineColor(kRed);
g1neg->SetLineColor(kRed);
g2pos->SetLineColor(kViolet);
g2neg->SetLineColor(kViolet);

TF1 *fit1pos = (TF1*)g1pos->GetFunction("fit");
TF1 *fit1neg = (TF1*)g1neg->GetFunction("fit");
TF1 *fit2pos = (TF1*)g2pos->GetFunction("fit");
TF1 *fit2neg = (TF1*)g2neg->GetFunction("fit");

fit1pos->SetLineColor(kGreen+2);
fit1neg->SetLineColor(kGreen+2);
fit2pos->SetLineColor(kGreen+2);
fit2neg->SetLineColor(kGreen+2);

char chi1pos[1024], chi1neg[1024], chi2pos[1024], chi2neg[1024];
sprintf(chi1pos,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", fit1pos->GetChisquare(), fit1pos->GetNDF(), fit1pos->GetProb());
sprintf(chi1neg,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", fit1neg->GetChisquare(), fit1neg->GetNDF(), fit1neg->GetProb());
sprintf(chi2pos,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", fit2pos->GetChisquare(), fit2pos->GetNDF(), fit2pos->GetProb());
sprintf(chi2neg,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", fit2neg->GetChisquare(), fit2neg->GetNDF(), fit2neg->GetProb());

//------ pos ------

TCanvas *c1 = new TCanvas("c1","c1",800,700);
c1->SetLogx(1);
c1->SetTickx(1);
c1->SetTicky(1);
c1->SetLeftMargin(0.14);
c1->SetTopMargin(0.07);
c1->SetBottomMargin(0.12);
c1->SetRightMargin(0.02);
c1->cd();

double lastx,lasty;
g1pos->GetPoint(g1pos->GetN()-1,lastx,lasty);
double xmax = lastx*1.1;

auto frame1 = c1->DrawFrame(5.,ymin,xmax,ymax);

g1pos->Draw("P SAME");
g2pos->Draw("P SAME");

frame1->GetXaxis()->SetTitle("p_{T}^{rec} [GeV]");
frame1->GetXaxis()->SetTitleSize(0.05);
frame1->GetXaxis()->SetTitleOffset(1.05);
frame1->GetYaxis()->SetTitle("L2L3 Correction = [median(Response)]^{-1}");
frame1->GetYaxis()->SetTitleSize(0.05);
frame1->GetYaxis()->SetTitleOffset(1.3);

frame1->GetXaxis()->SetLabelSize(0.04);
frame1->GetYaxis()->SetLabelSize(0.04);

TLegend *lpos = new TLegend(0.68,0.75,0.9,0.9,"");
lpos->SetTextSize(0.04);
lpos->SetFillColor(0);
lpos->SetBorderSize(0);
lpos->AddEntry(g1pos,"Winter23","PE");
lpos->AddEntry(g2pos,"Summer22","PE");
lpos->Draw();

//TLegend *lchipos = new TLegend(0.18,0.15,0.43,0.3,"");
TLegend *lchipos = new TLegend(0.5,0.15,0.8,0.3,"");
lchipos->SetTextSize(0.03);
lchipos->SetFillColor(0);
lchipos->SetBorderSize(0);
lchipos->SetTextColor(kGreen+2);
lchipos->SetHeader("Fit with standard+Gaussian function:");
lchipos->AddEntry(g1pos,chi1pos,"PE");
lchipos->AddEntry(g2pos,chi2pos,"PE");
lchipos->Draw();


char eta_leg_pos[1024];
sprintf(eta_leg_pos,"#bf{%.3f < #eta < %.3f}",eta_min, eta_max);

TPaveText *l2pos = new TPaveText(0.2,0.8,0.4,0.9,"NDC");
l2pos->SetFillColor(0);
l2pos->SetBorderSize(0);
l2pos->AddText("AK4 PUPPI");
l2pos->AddText(eta_leg_pos);
l2pos->SetTextFont(42);
l2pos->SetTextSize(0.04);
l2pos->Draw();

cms->Draw();
mc->Draw();

char cname1pos[1024], cname2pos[1024];
sprintf(cname1pos,"/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/Winter23_vs_Summer22/plots/InverseOfResponseVsRecoPt_PremixedPU_AK4PUPPI_Winter23_vs_Summer22_eta%.3fto%.3f.png",eta_min,eta_max);
sprintf(cname2pos,"/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/Winter23_vs_Summer22/plots/InverseOfResponseVsRecoPt_PremixedPU_AK4PUPPI_Winter23_vs_Summer22_eta%.3fto%.3f.pdf",eta_min,eta_max);  

c1->SaveAs(cname1pos);
c1->SaveAs(cname2pos);


//------ neg ------

TCanvas *c2 = new TCanvas("c2","c2",800,700);
c2->SetLogx(1);
c2->SetTickx(1);
c2->SetTicky(1);
c2->SetLeftMargin(0.14);
c2->SetTopMargin(0.07);
c2->SetBottomMargin(0.12);
c2->SetRightMargin(0.02);
c2->cd();

g1neg->GetPoint(g1neg->GetN()-1,lastx,lasty);
xmax = lastx*1.1;

auto frame2 = c2->DrawFrame(5.,ymin,xmax,ymax);

g1neg->Draw("P SAME");
g2neg->Draw("P SAME");

frame2->GetXaxis()->SetTitle("p_{T}^{rec} [GeV]");
frame2->GetXaxis()->SetTitleSize(0.05);
frame2->GetXaxis()->SetTitleOffset(1.05);
frame2->GetYaxis()->SetTitle("L2L3 Correction = [median(Response)]^{-1}");
frame2->GetYaxis()->SetTitleSize(0.05);
frame2->GetYaxis()->SetTitleOffset(1.3);

frame2->GetXaxis()->SetLabelSize(0.04);
frame2->GetYaxis()->SetLabelSize(0.04);

TLegend *lneg = new TLegend(0.68,0.75,0.9,0.9,"");
lneg->SetTextSize(0.035);
lneg->SetFillColor(0);
lneg->SetBorderSize(0);
lneg->AddEntry(g1neg,"Winter23","PE");
lneg->AddEntry(g2neg,"Summer22","PE");
lneg->Draw();


//TLegend *lchineg = new TLegend(0.18,0.15,0.43,0.3,"");
TLegend *lchineg = new TLegend(0.5,0.15,0.8,0.3,"");
lchineg->SetTextSize(0.03);
lchineg->SetFillColor(0);
lchineg->SetBorderSize(0);
lchineg->SetTextColor(kGreen+2);
lchineg->SetHeader("Fit with standard+Gaussian function:");
lchineg->AddEntry(g1neg,chi1neg,"PE");
lchineg->AddEntry(g2neg,chi2neg,"PE");
lchineg->Draw();


char eta_leg_neg[1024];
sprintf(eta_leg_neg,"#bf{-%.3f < #eta < -%.3f}",eta_max, eta_min);

TPaveText *l2neg = new TPaveText(0.2,0.8,0.4,0.9,"NDC");
l2neg->SetFillColor(0);
l2neg->SetBorderSize(0);
l2neg->AddText("AK4 PUPPI");
l2neg->AddText(eta_leg_neg);
l2neg->SetTextFont(42);
l2neg->SetTextSize(0.04);
l2neg->Draw();

cms->Draw();
mc->Draw();

char cname1neg[1024], cname2neg[1024];
sprintf(cname1neg,"/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/Winter23_vs_Summer22/plots/InverseOfResponseVsRecoPt_PremixedPU_AK4PUPPI_Winter23_vs_Summer22_eta-%.3fto-%.3f.png",eta_max,eta_min);
sprintf(cname2neg,"/afs/cern.ch/work/i/izisopou/public/JEC_NewMethods/CMSSW_13_0_3/src/JetMETAnalysisMCtruth/Winter23_vs_Summer22/plots/InverseOfResponseVsRecoPt_PremixedPU_AK4PUPPI_Winter23_vs_Summer22_eta-%.3fto-%.3f.pdf",eta_max,eta_min);  

c2->SaveAs(cname1neg);
c2->SaveAs(cname2neg);

}
