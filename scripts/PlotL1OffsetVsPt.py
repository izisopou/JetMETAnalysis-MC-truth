import glob, os, ROOT
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)
from array import array
import numpy as np
from tdrstyle_JERC_forL1 import *
import tdrstyle_JERC_forL1 as TDR
TDR.extraText  = "Simulation"
TDR.extraText2  = "Preliminary"

class L1OffsetVsPt():
    def __init__(self, eta):
        self.inputPath = "condor_AK4CHS/Files/Run3Winter22_Flat2018QCD/MeanOffsetOverPt/BeforeL1/"
        self.outputPath = "condor_AK4CHS/Files/Run3Winter22_Flat2018QCD/MeanOffsetOverPt/BeforeL1/"
        self.fname  = self.inputPath+"canvases_synchplot_ak4pfchs.root"
        #self.fname  = self.inputPath+"L1ClosureVsPt_AK4CHS_UL16nonAPV.root"
        #self.years = ["UL16APV", "UL16nonAPV", "UL17", "UL18"]
	#self.years = ["UL16APV", "UL16nonAPV"]
        self.mubins = ["0","10","20","30", "40", "50"]
        self.Hists = {
                "0": {"legend": "0 #leq #mu < 10",   #"0 #leq #mu < 10"
                        "color":  634, #634
                        "marker": ROOT.kFullCircle,
                        "msize":  1.0,
                        "hname":  "histograms/OffMeantnpuRef_" + eta + "_0",
                      },
                "10": {"legend": "10 #leq #mu < 20", #"10 #leq #mu < 20"
                        "color":  802, #802
                        "marker": ROOT.kFullCircle,
                        "msize":  1.0,
                        "hname":  "histograms/OffMeantnpuRef_" + eta + "_1",
                      },
                "20": {"legend": "20 #leq #mu < 30",
                        "color":  402,
                        "marker": ROOT.kFullCircle,
                        "msize":  1.0,
                        "hname":  "histograms/OffMeantnpuRef_" + eta + "_2",
                      },
                "30": {"legend": "30 #leq #mu < 40",
                        "color":  822,
                        "marker": ROOT.kFullCircle,
                        "msize":  1.0,
                        "hname":  "histograms/OffMeantnpuRef_" + eta + "_3",
                      },
		"40": {"legend": "40 #leq #mu < 50",
                        "color":  418,
                        "marker": ROOT.kFullCircle,
                        "msize":  1.0,
                        "hname":  "histograms/OffMeantnpuRef_" + eta + "_4",
                      },
		"50": {"legend": "50 #leq #mu < 60",
                        "color":  842,
                        "marker": ROOT.kFullCircle,
                        "msize":  1.0,
                        "hname":  "histograms/OffMeantnpuRef_" + eta + "_5",
                      },
            }
        
    def Plot(self, eta):
        PlotXMin = 11
        PlotXMax = 5500
        PlotYMin = -0.1
        PlotYMax = 1.5
	#TDR.cms_lumi_TeV = TDR.commonScheme["legend"][year]+" Legacy"
        TDR.cms_lumi_TeV = "Run3Winter22 "
        TDR.extraText3.append("AK4, PF+CHS")
        TDR.extraText3.append("")

        if eta=="BB": 
            TDR.extraText3.append("0.0<|#eta|<1.3")
        elif eta=="EI":
            TDR.extraText3.append("1.3<|#eta|<2.5")
        elif eta=="EO":
            TDR.extraText3.append("2.5<|#eta|<3.0")
        elif eta=="FF":
            TDR.extraText3.append("3.0<|#eta|<5.0")
			
        #f_ = ROOT.TFile(self.fname.replace("default",year))
        f_ = ROOT.TFile(self.fname)
        canv = tdrCanvas("L1OffsetVsPt", PlotXMin, PlotXMax, PlotYMin, PlotYMax, "p_{T}^{ptcl}[GeV]", "<Offset> / <p_{T}^{ptcl}>", square=kSquare, isExtraSpace=True)
        #canv = tdrCanvas("L1OffsetVsPt", PlotXMin, PlotXMax, PlotYMin, PlotYMax, "p_{T}^{ptcl}[GeV]", "<offset> [GeV]", square=kSquare, isExtraSpace=True)
        canv.SetLogx(True)
        leg = tdrLeg(0.60,0.60,0.89,0.89, textSize=0.04) #0.60,0.70,0.89,0.89
        #leg = tdrLeg(0.60,0.70,0.89,0.89, textSize=0.04) #0.60,0.70,0.89,0.89
        #leg = tdrLeg(0.50,0.60,0.79,0.89, textSize=0.035)	

        latex = rt.TLatex()
        latex.SetTextFont(42)
        latex.SetTextSize(0.05)
        latex.DrawLatex(25,PlotYMin-0.06667*(PlotYMax-PlotYMin),"30")
        latex.DrawLatex(75,PlotYMin-0.06667*(PlotYMax-PlotYMin),"100")
        latex.DrawLatex(225,PlotYMin-0.06667*(PlotYMax-PlotYMin),"300")
        latex.DrawLatex(680,PlotYMin-0.06667*(PlotYMax-PlotYMin),"1000")
        latex.DrawLatex(2050,PlotYMin-0.06667*(PlotYMax-PlotYMin),"3000")

        lines = {}
        for shift in [0.00]:
	#for shift in [0.00, -0.01, 0.01]:
                lines[shift] = ROOT.TLine(PlotXMin, shift, PlotXMax, shift)
                lines[shift].SetLineWidth(1)
                lines[shift].SetLineStyle(ROOT.kDotted if shift != 0 else ROOT.kDashed)
                lines[shift].SetLineColor(ROOT.kBlack)
                lines[shift].Draw("same")

        for bin in self.mubins:

                #if (bin=="40" or bin=="50"): continue
                if (bin=="50"): continue
                #if(bin=="20" or bin=="30" or bin=="40" or bin=="50"): continue

                color  = self.Hists[bin]["color"]
                marker = self.Hists[bin]["marker"]
                self.Hists[bin]["hist"] = f_.Get(self.Hists[bin]["hname"])
                self.Hists[bin]["hist"].SetDirectory(0)
                self.Hists[bin]["hist"].SetMarkerSize(self.Hists[bin]["msize"])
 
                for x in range(1,self.Hists[bin]["hist"].GetNbinsX()+1):
                    	if self.Hists[bin]["hist"].GetBinCenter(x)<15: self.Hists[bin]["hist"].SetBinContent(x,-999) 
                    	#if self.Hists[bin]["hist"].GetBinCenter(x)>4000: self.Hists[bin]["hist"].SetBinContent(x,-999)
                    	#if self.Hists[bin]["hist"].GetBinError(x)>2: self.Hists[bin]["hist"].SetBinContent(x,-999)
                        #if (eta=="FF" and self.Hists[bin]["hist"].GetBinContent(x)>10): self.Hists[bin]["hist"].SetBinContent(x,-999)

                tdrDraw(self.Hists[bin]["hist"], "P", marker=marker, mcolor=color )
                leg.AddEntry(self.Hists[bin]["hist"], self.Hists[bin]["legend"], "lp")

        f_.Close()
        canv.SaveAs(self.outputPath+"L1OffsetOverPtVsPt_Run3Winter22_AK4CHS_"+eta+".png")
        canv.SaveAs(self.outputPath+"L1OffsetOverPtVsPt_Run3Winter22_AK4CHS_"+eta+".pdf")
        canv.Close()
        del TDR.extraText3[:]

def main():
    etabins = ["BB", "EI", "EO", "FF"]
    for eta in etabins:
         L1OffsetVsPt(eta).Plot(eta)

if __name__ == '__main__':
    main()
