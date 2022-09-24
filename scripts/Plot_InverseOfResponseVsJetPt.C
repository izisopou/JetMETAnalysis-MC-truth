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

double eta_min = 2.964;
double eta_max = 3.139;

TFile *f1 = new TFile("condor_AK4PUPPI/Files/Run3Winter22_Flat2018QCD/V1_JECs/L2L3_output/pTcut6GeV/l2.root"); 
TFile *f2 = new TFile("condor_AK4PUPPI/Files/Run3Winter22_Flat2018QCD/With_DZ_NM_cuts_and_PUreweight/L2L3_output/l2.root"); 

char hname1pos[1024], hname1neg[1024], hname2pos[1024], hname2neg[1024];

sprintf(hname1pos,"ak4puppi/AbsCorVsJetPt_JetEta%.3fto%.3f",eta_min,eta_max);
sprintf(hname1neg,"ak4puppi/AbsCorVsJetPt_JetEta-%.3fto-%.3f",eta_max,eta_min);
sprintf(hname2pos,"ak4puppi/AbsCorVsJetPt_JetEta%.3fto%.3f",eta_min,eta_max);
sprintf(hname2neg,"ak4puppi/AbsCorVsJetPt_JetEta-%.3fto-%.3f",eta_max,eta_min);

TGraphErrors *g1pos = (TGraphErrors*)(f1->Get(hname1pos));
TGraphErrors *g1neg = (TGraphErrors*)(f1->Get(hname1neg));
TGraphErrors *g2pos = (TGraphErrors*)(f2->Get(hname2pos));
TGraphErrors *g2neg = (TGraphErrors*)(f2->Get(hname2neg));

g1pos->SetMarkerColor(kBlack);
g1neg->SetMarkerColor(kGray+2);
g2pos->SetMarkerColor(kBlue);
g2neg->SetMarkerColor(kViolet);


TCanvas *c = new TCanvas("c","c",800,700);
c->SetLogx(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetLeftMargin(0.14);
c->SetTopMargin(0.07);
c->SetBottomMargin(0.12);
c->SetRightMargin(0.02);
c->cd();

g1pos->Draw("AP");
g1neg->Draw("P SAME");
g2pos->Draw("P SAME");
g2neg->Draw("P SAME");

g1pos->GetXaxis()->SetTitle("p_{T}^{reco} [GeV]");
g1pos->GetXaxis()->SetTitleSize(0.05);
g1pos->GetXaxis()->SetTitleOffset(1.05);
g1pos->GetYaxis()->SetTitle("C_{L2L3} = [median(Response)]^{-1}");
g1pos->GetYaxis()->SetTitleSize(0.05);
g1pos->GetYaxis()->SetTitleOffset(1.3);

g1pos->GetXaxis()->SetLabelSize(0.04);
g1pos->GetYaxis()->SetLabelSize(0.04);

g1pos->GetYaxis()->SetRangeUser(0.2,2.5);
g1neg->GetYaxis()->SetRangeUser(0.2,2.5);
g2pos->GetYaxis()->SetRangeUser(0.2,2.5);
g2neg->GetYaxis()->SetRangeUser(0.2,2.5);

TLegend *l = new TLegend(0.5,0.6,0.8,0.8,"");
l->SetTextSize(0.035);
l->SetFillColor(0);
l->SetBorderSize(0);
l->AddEntry(g1pos,"Previous (V1) iteration (#eta > 0)","PE");
l->AddEntry(g1neg,"Previous (V1) iteration (#eta < 0)","PE");
l->AddEntry(g2pos,"New iteration (#eta > 0)","PE");
l->AddEntry(g2neg,"New iteration (#eta < 0)","PE");
l->Draw();

TF1 *fit1pos = (TF1*)g1pos->GetFunction("fit");
TF1 *fit1neg = (TF1*)g1neg->GetFunction("fit");
TF1 *fit2pos = (TF1*)g2pos->GetFunction("fit");
TF1 *fit2neg = (TF1*)g2neg->GetFunction("fit");

char chi1pos[1024], chi1neg[1024], chi2pos[1024], chi2neg[1024];
sprintf(chi1pos,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", fit1pos->GetChisquare(), fit1pos->GetNDF(), fit1pos->GetProb());
sprintf(chi1neg,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", fit1neg->GetChisquare(), fit1neg->GetNDF(), fit1neg->GetProb());
sprintf(chi2pos,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", fit2pos->GetChisquare(), fit2pos->GetNDF(), fit2pos->GetProb());
sprintf(chi2neg,"#chi^{2} / ndf = %.1f / %d, Prob. = %.2f", fit2neg->GetChisquare(), fit2neg->GetNDF(), fit2neg->GetProb());

TLegend *lchi = new TLegend(0.4,0.15,0.65,0.35,"");
lchi->SetTextSize(0.04);
lchi->SetFillColor(0);
lchi->SetBorderSize(0);
lchi->SetTextColor(kRed);
lchi->SetHeader("Fits with standard+Gaussian function:");
lchi->AddEntry(g1pos,chi1pos,"PE");
lchi->AddEntry(g1neg,chi1neg,"PE");
lchi->AddEntry(g2pos,chi2pos,"PE");
lchi->AddEntry(g2neg,chi2neg,"PE");
lchi->Draw();


TPaveText *l1 = new TPaveText(0.55,0.94,0.95,0.98,"NDC");
l1->SetFillColor(0);
l1->SetBorderSize(0);
l1->AddText("Run3Winter22 (13.6 TeV)");
l1->SetTextFont(42);
l1->SetTextSize(0.05);
l1->Draw();

char eta_leg[1024];
sprintf(eta_leg,"#bf{%.3f < |#eta| < %.3f}",eta_min, eta_max);

TPaveText *l2 = new TPaveText(0.68,0.8,0.88,0.9,"NDC");
l2->SetFillColor(0);
l2->SetBorderSize(0);
l2->AddText("AK4 PUPPI");
l2->AddText(eta_leg);
l2->SetTextFont(42);
l2->SetTextSize(0.05);
l2->Draw();

TPaveText *cms = new TPaveText(0.175,0.82,0.325,0.87,"NDC");
cms->AddText("#splitline{#bf{CMS}}{#splitline{#scale[0.7]{#it{Simulation}}}{#scale[0.7]{#it{Preliminary}}}}");
cms->SetTextFont(42);
cms->SetTextSize(0.05);
cms->SetBorderSize(0);
cms->SetFillColor(0);
cms->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"condor_AK4PUPPI/Files/Run3Winter22_Flat2018QCD/V1_JECs_VERSUS_With_DZ_NM_cuts_and_PUreweight/InverseOfResponseVsRecoPt_AK4PUPPI_eta%.3fto%.3f.png",eta_min,eta_max);
sprintf(cname2,"condor_AK4PUPPI/Files/Run3Winter22_Flat2018QCD/V1_JECs_VERSUS_With_DZ_NM_cuts_and_PUreweight/InverseOfResponseVsRecoPt_AK4PUPPI_eta%.3fto%.3f.pdf",eta_min,eta_max);  

c->SaveAs(cname1);
c->SaveAs(cname2);
}















