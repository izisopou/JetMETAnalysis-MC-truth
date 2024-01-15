#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TStyle.h>

//////////////////////////////////////////////////////
//
// Plots the offset distribution for 2 sets and fits them
// around the peak to find the M.P.V.
//
//////////////////////////////////////////////////////

TF1* FindBestGaussianCoreFit(TH1D* histo)
{

	double mean = histo->GetMean();
	double rms = histo->GetRMS();
	bool quiet_mode = true; //minimum prints on terminal
	
	int HalfMaxBinLow = histo->FindFirstBinAbove(histo->GetMaximum()/2);
	int HalfMaxBinHigh = histo->FindLastBinAbove(histo->GetMaximum()/2);
	double WidthAtHalfMaximum = 0.5*(histo->GetBinCenter(HalfMaxBinHigh) - histo->GetBinCenter(HalfMaxBinLow));
    	double Xmax  = histo->GetXaxis()->GetBinCenter(histo->GetMaximumBin());

	TF1 *gausTF1;

	double Pvalue = 0;
	double ChiSquare;
	double ndf;

	double rms_step_plus;	
	double RangeLow = 0.;
	double RangeUp = 5.;
	double meanForRange;
	double spreadForRange;

	double PvalueBest = 0;
	double RangeLowBest = 0;
	double RangeUpBest = 0;
	double ChiSquareBest;
	double ndfBest;
	double StepMinusBest;
	double StepPlusBest;

	if(Xmax < mean) meanForRange = Xmax;
	else meanForRange = mean; //because some entries with LARGE errors sometimes falsely become the maximum

	if(WidthAtHalfMaximum < rms && WidthAtHalfMaximum>0) spreadForRange = WidthAtHalfMaximum;
	else spreadForRange = rms; //because WHF does not take into account weights and sometimes it turns LARGE

	double rms_step_minus = 2.2; //2.2
	while (rms_step_minus>0.5)
	{ 
		RangeLow = meanForRange - rms_step_minus*spreadForRange;
//		rms_step_plus = 2.2;
		rms_step_plus = rms_step_minus;  

		while ( rms_step_plus>0.5  )
		{	
			RangeUp = meanForRange + rms_step_plus*spreadForRange;
			if(quiet_mode)	histo->Fit("gaus","0Q","0",RangeLow, RangeUp);
			else 		histo->Fit("gaus","0","0",RangeLow, RangeUp);
			gausTF1 = (TF1*)	histo->GetListOfFunctions()->FindObject("gaus");
			ChiSquare = gausTF1->GetChisquare();
			ndf       = gausTF1->GetNDF();
			Pvalue = TMath::Prob(ChiSquare, ndf);			
	
			if (Pvalue > PvalueBest)
			{
				PvalueBest = Pvalue;
				RangeLowBest = RangeLow;
				RangeUpBest = RangeUp;
				ndfBest = ndf;
				ChiSquareBest = ChiSquare;
				StepMinusBest = rms_step_minus; 
				StepPlusBest = rms_step_plus; 
				meanForRange = gausTF1->GetParameter(1);
			}

			if(!quiet_mode)
			{
				cout << "\n\nFitting range used: [Mean - " << rms_step_minus  << " sigma,  Mean + " << rms_step_plus << " sigma ] "<< endl;
				cout << "ChiSquare = " << ChiSquare << " NDF = " << ndf << " Prob =  " << Pvalue << "  Best Prob so far = " << PvalueBest << endl;
			}
			rms_step_plus = rms_step_plus - 0.1;
		}
		rms_step_minus = rms_step_minus - 0.1;
	}

	if (quiet_mode) histo->Fit("gaus","0Q","0",RangeLowBest, RangeUpBest);
	else 
	{
		histo->Fit("gaus","0","0",RangeLowBest, RangeUpBest);
		cout << "\n\n\nMean =  " << mean << "  Xmax = " << Xmax << "  RMS = " << rms << "  WidthAtHalfMax = " << WidthAtHalfMaximum <<  endl;
		cout << "Fit found!" << endl;
		cout << "Final fitting range used: [Mean(Xmax) - " << StepMinusBest << " rms(WHF), Mean(Xmax) + " << StepPlusBest << " rms(WHF) ] "<< endl;
		cout << "ChiSquare = " << ChiSquareBest << " NDF = " << ndfBest << " Prob =  " << PvalueBest << "\n\n" << endl;
	}	
	gausTF1 = (TF1*)	histo->GetListOfFunctions()->FindObject("gaus");

	return gausTF1;
}

void Plot_GausFit_Offset_Superimpose(double eta){

TCanvas *c = new TCanvas("c","c",1000,800);
c->SetTickx(1);
c->SetTicky(1);

TFile *f1 = new TFile("/path1/to/Step2/output_ak4puppi.root");
TFile *f2 = new TFile("/path2/to/Step2/output_ak4puppi.root");

char eta_reg[1024];
if(eta==0.0) sprintf(eta_reg,"bb");
if(eta==1.3) sprintf(eta_reg,"ei");
if(eta==2.5) sprintf(eta_reg,"eo");
if(eta==3.0) sprintf(eta_reg,"ff");

for(int mu=0; mu<=40; mu=mu+10){

char hname[1024];
sprintf(hname,"p_offresVsrefpt_%s_tnpu%d_%d",eta_reg,mu,mu);

TH2D *h1 = (TH2D*)f1->Get(hname);	
TH2D *h2 = (TH2D*)f2->Get(hname);

for(unsigned int i=1; i<=h1->GetNbinsX(); i++)
{
	cout <<"pT bin = "<<i<<" ---> "<<" Low Edge = "<<h1->GetXaxis()->GetBinLowEdge(i)<<" Upper Edge = "<<h1->GetXaxis()->GetBinUpEdge(i)<<endl;
}

c->cd();

TH1D *histo1 = h1->ProjectionY("first set",23,23);
TH1D *histo2 = h2->ProjectionY("second set",23,23);

histo1->Rebin(4);
histo2->Rebin(4);
histo1->SetStats(0);
histo2->SetStats(0);
histo1->GetXaxis()->SetRangeUser(-40,40);
histo1->GetXaxis()->SetNdivisions(1010);
char titlename[1024];
if (eta==0.0) sprintf(titlename,"#font[22]{p_{T}^{ptcl} : 45 - 57 GeV, |#eta|< 1.3 , %d #leq #mu < %d}",mu,mu+10);
if (eta==1.3) sprintf(titlename,"#font[22]{p_{T}^{ptcl} : 45 - 57 GeV, 1.3 < |#eta|< 2.5 , %d #leq #mu < %d}",mu,mu+10);
if (eta==2.5) sprintf(titlename,"#font[22]{p_{T}^{ptcl} : 45 - 57 GeV, 2.5 < |#eta|< 3.0 , %d #leq #mu < %d}",mu,mu+10);
if (eta==3.0) sprintf(titlename,"#font[22]{p_{T}^{ptcl} : 45 - 57 GeV, 3.0 < |#eta|< 5.0 , %d #leq #mu < %d}",mu,mu+10);
histo1->SetTitle(titlename);
histo1->GetXaxis()->SetTitle("Offset [GeV]");
histo1->GetYaxis()->SetTitle("A.U.");
histo1->GetYaxis()->SetTitleOffset(1.3);
histo1->SetMarkerSize(0.7);
histo1->SetMarkerColor(kBlack);
histo1->SetLineColor(kBlack);
histo1->SetLineWidth(2);
histo1->SetMarkerStyle(8);
histo2->SetMarkerSize(0.7);
histo2->SetMarkerColor(kBlue);
histo2->SetLineColor(kBlue);
histo2->SetLineWidth(2);
histo2->SetMarkerStyle(8);
histo1->Draw("hist");
histo2->Scale(histo1->Integral()/histo2->Integral());
histo2->Draw("hist sames");

TF1 *g1;
g1=FindBestGaussianCoreFit(histo1);
g1->Draw("same");

cout<<"Prob = "<<g1->GetProb()<<endl;
cout<<"Val = "<<g1->GetParameter(1)<<endl;
cout<<"Valerr = "<<g1->GetParError(1)<<endl;

TF1 *g2;
g2=FindBestGaussianCoreFit(histo2);
g2->Draw("same");

cout<<"Prob = "<<g2->GetProb()<<endl;
cout<<"Val = "<<g2->GetParameter(1)<<endl;
cout<<"Valerr = "<<g2->GetParError(1)<<endl;

//gStyle->SetOptFit(1111);
//gStyle->SetOptStat(0);


char entries[1024], mean[1024], stddev[1024], chi2ndf[1024], prob[1024], constant[1024], meanfit[1024], sigmafit[1024];
sprintf(entries,"Entries = %.0f  ",histo1->GetEntries());
sprintf(mean, "Mean  = %.2f",histo1->GetMean());
sprintf(stddev, "Std Dev   =  %.2f",histo1->GetRMS());
sprintf(chi2ndf, "#chi^{2} / ndf = %.2f / %d",g1->GetChisquare(),g1->GetNDF());
sprintf(prob, "Prob  = %lf",g1->GetProb());
sprintf(constant, "Constant = %.2f #pm %.2f ",g1->GetParameter(0),g1->GetParError(0));
sprintf(meanfit, "Mean     = %.2f #pm %.2f ",g1->GetParameter(1),g1->GetParError(1));
sprintf(sigmafit, "Sigma    = %.2f #pm %.2f ",g1->GetParameter(2),g1->GetParError(2));

TPaveStats *ptstats = new TPaveStats(0.62,0.535,0.98,0.935,"brNDC");  
ptstats->SetName("stats");
ptstats->SetBorderSize(1);
ptstats->SetFillColor(0);
ptstats->SetTextAlign(12);
ptstats->SetTextFont(42);
TText *ptstats_LaTex = ptstats->AddText("first set");
ptstats_LaTex->SetTextSize(0.04088889);
ptstats_LaTex = ptstats->AddText(entries);
ptstats_LaTex = ptstats->AddText(mean);
ptstats_LaTex = ptstats->AddText(stddev);
ptstats_LaTex = ptstats->AddText(chi2ndf);
ptstats_LaTex = ptstats->AddText(prob);
ptstats_LaTex = ptstats->AddText(constant);
ptstats_LaTex = ptstats->AddText(meanfit);
ptstats_LaTex = ptstats->AddText(sigmafit);
ptstats->SetOptStat(1111);
ptstats->SetOptFit(1111);
ptstats->Draw();


sprintf(entries,"Entries = %.0f  ",histo2->GetEntries());
sprintf(mean, "Mean  = %.2f",histo2->GetMean());
sprintf(stddev, "Std Dev   =  %.2f",histo2->GetRMS());
sprintf(chi2ndf, "#chi^{2} / ndf = %.2f / %d",g2->GetChisquare(),g2->GetNDF());
sprintf(prob, "Prob  = %lf",g2->GetProb());
sprintf(constant, "Constant = %.2f #pm %.2f ",g2->GetParameter(0),g2->GetParError(0));
sprintf(meanfit, "Mean     = %.2f #pm %.2f ",g2->GetParameter(1),g2->GetParError(1));
sprintf(sigmafit, "Sigma    = %.2f #pm %.2f ",g2->GetParameter(2),g2->GetParError(2));

TPaveStats *ptstats2 = new TPaveStats(0.62,0.1277419,0.98,0.5277419,"brNDC"); 
ptstats2->SetName("stats");
ptstats2->SetBorderSize(1);
ptstats2->SetFillColor(0);
ptstats2->SetTextAlign(12);
ptstats2->SetTextFont(42);
TText *ptstats2_LaTex = ptstats2->AddText("second set");
ptstats2_LaTex->SetTextSize(0.04088889);
ptstats2_LaTex = ptstats2->AddText(entries);
ptstats2_LaTex = ptstats2->AddText(mean);
ptstats2_LaTex = ptstats2->AddText(stddev);
ptstats2_LaTex = ptstats2->AddText(chi2ndf);
ptstats2_LaTex = ptstats2->AddText(prob);
ptstats2_LaTex = ptstats2->AddText(constant);
ptstats2_LaTex = ptstats2->AddText(meanfit);
ptstats2_LaTex = ptstats2->AddText(sigmafit);
ptstats2->SetOptStat(1111);
ptstats2->SetOptFit(1111);
ptstats2->Draw();


TLegend *l = new TLegend(0.15,0.6,0.32,0.8,"");
l->SetBorderSize(0);
l->SetTextSize(0.03);
l->AddEntry(histo1,"first set","L");
l->AddEntry(histo2,"second set","L");
l->Draw();

char canvasname[1024];
sprintf(canvasname,"L1Offset_AK4PUPPI_first_set_vs_second_set_pT45to57_%s.png",eta_reg);
c->SaveAs(canvasname);

}
}
