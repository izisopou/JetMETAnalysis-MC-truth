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
// Plots median(Response) before L2L3 as a function of 
// pTgen for various fine eta bins, for 3 sets.
//
//////////////////////////////////////////////////////

using namespace std;

void Plot_ResponseVsRefPt();

void Plot_ResponseVsRefPt(){

double eta_min = 3.839;
double eta_max = 4.013;

TFile *f1 = new TFile("/path1/to/l2.root"); 
TFile *f2 = new TFile("/path2/to/l2.root");
TFile *f3 = new TFile("/path3/to/l2.root"); 

char hname1pos[1024], hname1neg[1024], hname2pos[1024], hname2neg[1024], hname3pos[1024], hname3neg[1024];

sprintf(hname1pos,"ak4puppi/AbsRspVsRefPt_JetEta%.3fto%.3f",eta_min,eta_max);
sprintf(hname1neg,"ak4puppi/AbsRspVsRefPt_JetEta-%.3fto-%.3f",eta_max,eta_min);
sprintf(hname2pos,"ak4puppi/AbsRspVsRefPt_JetEta%.3fto%.3f",eta_min,eta_max);
sprintf(hname2neg,"ak4puppi/AbsRspVsRefPt_JetEta-%.3fto-%.3f",eta_max,eta_min);
sprintf(hname3pos,"ak4puppi/AbsRspVsRefPt_JetEta%.3fto%.3f",eta_min,eta_max);
sprintf(hname3neg,"ak4puppi/AbsRspVsRefPt_JetEta-%.3fto-%.3f",eta_max,eta_min);

TGraphErrors *g1pos = (TGraphErrors*)(f1->Get(hname1pos));
TGraphErrors *g1neg = (TGraphErrors*)(f1->Get(hname1neg));
TGraphErrors *g2pos = (TGraphErrors*)(f2->Get(hname2pos));
TGraphErrors *g2neg = (TGraphErrors*)(f2->Get(hname2neg));
TGraphErrors *g3pos = (TGraphErrors*)(f3->Get(hname3pos));
TGraphErrors *g3neg = (TGraphErrors*)(f3->Get(hname3neg));

g1pos->SetMarkerColor(kBlack);
g1neg->SetMarkerColor(kGray+2);
g2pos->SetMarkerColor(kRed);
g2neg->SetMarkerColor(kRed-7);
g3pos->SetMarkerColor(kBlue);
g3neg->SetMarkerColor(kViolet);

g1neg->SetMarkerStyle(47);
g2neg->SetMarkerStyle(47);
g3neg->SetMarkerStyle(47);

TCanvas *c = new TCanvas("c","c",800,700);
c->SetLogx(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetLeftMargin(0.14);
c->SetTopMargin(0.07);
c->SetBottomMargin(0.12);
c->SetRightMargin(0.02);
c->cd();

/*g1pos->Draw("AP");
g1pos->RemovePoint(0);
g1pos->Draw("AP");
g1pos->RemovePoint(0);
g1pos->Draw("AP");
g1pos->RemovePoint(0);
g1pos->Draw("AP");
g1pos->RemovePoint(0);
g1pos->Draw("AP");
g1pos->RemovePoint(0);
g1pos->Draw("AP");
g1pos->RemovePoint(0);
*/
g1pos->Draw("AP");
g1neg->Draw("P SAME");
g2pos->Draw("P SAME");
g2neg->Draw("P SAME");
g3pos->Draw("P SAME");
g3neg->Draw("P SAME");

g1pos->GetXaxis()->SetTitle("p_{T}^{ptcl} [GeV]");
g1pos->GetXaxis()->SetTitleSize(0.05);
g1pos->GetXaxis()->SetTitleOffset(1.);
g1pos->GetYaxis()->SetTitle("median(Response) = median(p_{T}^{reco} / p_{T}^{ptcl})");
g1pos->GetYaxis()->SetTitleSize(0.05);
g1pos->GetYaxis()->SetTitleOffset(1.3);

g1pos->GetYaxis()->SetRangeUser(0.4,1.4);
g1neg->GetYaxis()->SetRangeUser(0.4,1.4);
g2pos->GetYaxis()->SetRangeUser(0.4,1.4);
g2neg->GetYaxis()->SetRangeUser(0.4,1.4);

TLegend *l = new TLegend(0.5,0.5,0.9,0.92,"");
l->SetTextSize(0.035);
l->SetFillColor(0);
l->SetBorderSize(0);
l->AddEntry(g1pos,"#eta>0: first set","PE");
l->AddEntry(g2pos,"#eta>0: second set","PE");
l->AddEntry(g3pos,"#eta>0: third set","PE");
l->AddEntry((TObject*)0,"","");
l->AddEntry(g1neg,"#eta<0: first set","PE");
l->AddEntry(g2neg,"#eta<0: second set","PE");
l->AddEntry(g3neg,"#eta<0: third set","PE");
l->Draw();

TPaveText *l1 = new TPaveText(0.55,0.94,0.95,0.98,"NDC");
l1->SetFillColor(0);
l1->SetBorderSize(0);
l1->AddText("Winter22Run3 (13.6 TeV)");
l1->SetTextFont(42);
l1->SetTextSize(0.05);
l1->Draw();

char eta_leg[1024];
sprintf(eta_leg,"#bf{%.3f < |#eta| < %.3f}",eta_min, eta_max);

TPaveText *l2 = new TPaveText(0.75,0.15,0.9,0.25,"NDC");
l2->SetFillColor(0);
l2->SetBorderSize(0);
l2->AddText("AK4 PUPPI");
l2->AddText(eta_leg);
l2->SetTextFont(42);
l2->SetTextSize(0.04);
l2->Draw();

TPaveText *cms = new TPaveText(0.175,0.82,0.325,0.87,"NDC");
cms->AddText("#splitline{#bf{CMS}}{#splitline{#scale[0.7]{#it{Simulation}}}{#scale[0.7]{#it{Preliminary}}}}");
cms->SetTextFont(42);
cms->SetTextSize(0.05);
cms->SetBorderSize(0);
cms->SetFillColor(0);
cms->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"ResponseVsGenPt_AK4PUPPI_eta%.3fto%.3f.png",eta_min,eta_max);
sprintf(cname2,"ResponseVsGenPt_AK4PUPPI_eta%.3fto%.3f.pdf",eta_min,eta_max); 

c->SaveAs(cname1);
c->SaveAs(cname2);

}
