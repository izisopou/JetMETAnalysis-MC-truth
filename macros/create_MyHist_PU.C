#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
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

void create_MyHist_PU(){

  TChain *tree = new TChain("ak4puppi/t");
  Char_t filechain[1024];

  for(Int_t kk=1;kk<=216;kk++)
  {
      sprintf(filechain,"/eos/cms/store/group/phys_jetmet/ilias/Run3MCtruthSamples/NoRawPtCut/Run3Summer23BPix/QCD_PT-15to7000_TuneCP5_13p6TeV_pythia8/PremixedPU/231127_094724/0000/JRA_%d.root",kk);
      tree->Add(filechain);
  }

  std::vector<float> *tnpus=0;	
  std::vector<float> *AllGenJetsPt=0;
  tree->SetBranchAddress("tnpus",&tnpus);
  tree->SetBranchAddress("AllGenJetsPt",&AllGenJetsPt);

  const int nBins = 42;

  double Boundaries[nBins+1] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 20, 23, 27, 30, 35, 40, 45, 57, 72, 90, 120, 150, 200, 300, 400, 550, 750, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 6800};

  TH1F *pileup = new TH1F("pileup","",100,0.,100.);
  TH1F *gen_pt = new TH1F("gen_pt","",nBins,Boundaries);
  TH1F *gen_pt_3leading = new TH1F("gen_pt_3leading","",nBins,Boundaries);

  cout << "Entries = " << tree->GetEntries() << endl; 

  for(int i=0; i<tree->GetEntries(); i++)
  {
	tree->GetEntry(i);
	if(i%1000000==0) cout << "Processed " << i << " / " << tree->GetEntries() << " events" << endl;
	pileup->Fill(tnpus->at(12));
	
	for(int ijet=0; ijet<AllGenJetsPt->size(); ijet++)
	{
		gen_pt->Fill(AllGenJetsPt->at(ijet));

		if(ijet<=2)
		{
			gen_pt_3leading->Fill(AllGenJetsPt->at(ijet));
		}
	}
  }

  TFile *fout = new TFile("MyMCPUHisto_Run3Summer23BPix_FlatPU0to70.root","RECREATE");
  //TFile *fout = new TFile("pT_spectra/Gen_pT_spectrum_Run3Summer23BPix_PremixedPU.root","RECREATE");
  fout->cd();
  pileup->Write();
  //gen_pt->Write();
  //gen_pt_3leading->Write();

}
