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

  for(Int_t kk=1;kk<=513;kk++)
  {
      sprintf(filechain,"/eos/cms/store/group/phys_jetmet/ilias/Run3MCtruthSamples/NoPtCut/AK4/Winter22/PremixedPU/QCD_Pt-15to7000_TuneCP5_Flat2018_13p6TeV_pythia8/Run3Winter22_PremixedPU/220902_080010/0000/JRA_%d.root",kk);
      tree->Add(filechain);
  }

  std::vector<float> *tnpus=0;	
  tree->SetBranchAddress("tnpus",&tnpus);

  TH1F *pileup = new TH1F("pileup","",100,0.,100.);

  cout << "Entries = " << tree->GetEntries() << endl; 

  for(int i=0; i<tree->GetEntries(); i++)
  {
	tree->GetEntry(i);
	if(i%1000000==0) cout << "Processed " << i << " / " << tree->GetEntries() << " events" << endl;
	pileup->Fill(tnpus->at(12));
  }

  TFile *fout = new TFile("MyDataMCHistos/MyMCPUHisto_Run3Winter22_Flat2018_13p6TeV_PremixedPU.root","RECREATE");
  fout->cd();
  pileup->Write();

}
