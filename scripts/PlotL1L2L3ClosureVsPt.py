import glob, os, ROOT
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)
from array import array
import numpy as np
from tdrstyle_JERC import *
import tdrstyle_JERC as TDR
TDR.extraText  = "Simulation"
TDR.extraText2  = "Preliminary"

class L1L2L3ClosureVsPt():
    def __init__(self, isDefault = False):
        self.inputPath = "condor_AK4CHS/Files/Run3Winter22_Flat2018QCD/L1L2L3_Closure/test/"
        self.outputPath = "condor_AK4CHS/Files/Run3Winter22_Flat2018QCD/L1L2L3_Closure/test/"
        self.fname  = self.inputPath+"ClosureVsRefPt.root"
	#self.fname  = self.inputPath+"L1L2L3ClosureVsPt_AK8CHS_default.root"
        self.years = [""]
        self.etabins = ["1.3","2.5","3.0","5.0"]
        if isDefault:
            self.Hists = {
                "1.3": {"legend": "0.0 < |#eta| < 1.3",
                        "color":  ROOT.kBlack,
                        "marker": ROOT.kFullCircle,
                        "msize":  1.0,
                        "hname":  "ak4puppi/ClosureVsRefPt_JetEta0to1.3",
                      },
                "2.5": {"legend": "1.3 < |#eta| < 2.5",
                        "color":  ROOT.kBlue,
                        "marker": ROOT.kOpenCircle,
                        "msize":  1.0,
                        "hname":  "ak4puppi/ClosureVsRefPt_JetEta1.3to2.5",
                },
                "3.0": {"legend": "2.5 < |#eta| < 3.0",
                        "color":  ROOT.kRed,
                        "marker": ROOT.kFullTriangleUp,
                        "msize":  1.0,
                        "hname":  "ak4puppi/ClosureVsRefPt_JetEta2.5to3",
                },
                "5.0": {"legend": "3.0 < |#eta| < 5.0",
                        "color":  ROOT.kViolet,
                        "marker": ROOT.kOpenTriangleUp,
                        "msize":  1.0,
                        "hname":  "ak4puppi/ClosureVsRefPt_JetEta3to5",
                },
            }
        else:
            self.Hists = {
                "1.3": {"legend": "0.0 < |#eta| < 1.3",
                        "color":  ROOT.kGreen+3,
                        "marker": ROOT.kFullCircle,
                        "msize":  1.0,
                        "hname":  "ak4pfchs/ClosureVsRefPt_JetEta0to1.3",
                      },
                "2.5": {"legend": "1.3 < |#eta| < 2.5",
                        "color":  ROOT.kBlue-4,
                        "marker": ROOT.kFullStar,
                        "msize":  1.3,
                        "hname":  "ak4pfchs/ClosureVsRefPt_JetEta1.3to2.5",
                },
                "3.0": {"legend": "2.5 < |#eta| < 3.0",
                        "color":  ROOT.kRed+1,
                        "marker": ROOT.kFullTriangleUp,
                        "msize":  1.0,
                        "hname":  "ak4pfchs/ClosureVsRefPt_JetEta2.5to3",
                },
                "5.0": {"legend": "3.0 < |#eta| < 5.0",
                        "color":  ROOT.kOrange+1,
                        "marker": ROOT.kFullTriangleDown,
                        "msize":  1.0,
                        "hname":  "ak4pfchs/ClosureVsRefPt_JetEta3to5",
                },
            }

    def Plot(self):
        #TDR.cms_lumi_TeV = "QCD multijet "
	#TDR.cms_lumi_TeV = TDR.commonScheme["legend"][year]+" Legacy"
	#TDR.cms_lumi_TeV = "Run2 Legacy "
        #extraText3.append("#bf{anti-k_{T} (R = 0.4)}")
        #extraText3.append("#bf{PF+PUPPI}")
        #TDR.extraText3.append("#bf{Anti-k_{T} (R = 0.4), PF+CHS}")
	#TDR.extraText3.append("AK4, PF+CHS")
        PlotXMin = 11
        PlotXMax = 5500
        PlotYMin = 0.96
        PlotYMax = 1.04
        for year in self.years:
	    #TDR.cms_lumi_TeV = "QCD multijet "
	    #TDR.cms_lumi_TeV = TDR.commonScheme["legend"][year]+" Legacy"
            TDR.cms_lumi_TeV = "Run3Winter22 "
            #extraText3.append("#bf{anti-k_{T} (R = 0.4)}")
            #extraText3.append("#bf{PF+PUPPI}")
            #TDR.extraText3.append("#bf{Anti-k_{T} (R = 0.4), PF+CHS}")
            TDR.extraText3.append("AK4, PF+CHS")

            #f_ = ROOT.TFile(self.fname.replace("default",year))
            f_ = ROOT.TFile(self.fname)
            canv = tdrCanvas("L1L2L3ClosureVsPt"+year, PlotXMin, PlotXMax, PlotYMin, PlotYMax, "p_{T}^{ptcl}[GeV]", "Response", square=kSquare, isExtraSpace=True)
            canv.SetLogx(True)
            leg = tdrLeg(0.60,0.70,0.89,0.89, textSize=0.04)
            latex = rt.TLatex()
            latex.SetTextFont(42)
            latex.SetTextSize(0.05)
            latex.DrawLatex(25,PlotYMin-0.06667*(PlotYMax-PlotYMin),"30")
            latex.DrawLatex(75,PlotYMin-0.06667*(PlotYMax-PlotYMin),"100")
            latex.DrawLatex(225,PlotYMin-0.06667*(PlotYMax-PlotYMin),"300")
            latex.DrawLatex(680,PlotYMin-0.06667*(PlotYMax-PlotYMin),"1000")
            latex.DrawLatex(2050,PlotYMin-0.06667*(PlotYMax-PlotYMin),"3000")	
            lines = {}
            #for shift in [+0.01, 0.00, -0.01]:
            for shift in [+0.01, +0.001, 0.00, -0.001, -0.01]:
                lines[shift] = ROOT.TLine(PlotXMin, 1+shift, PlotXMax, 1+shift)
                lines[shift].SetLineWidth(1)
                lines[shift].SetLineStyle(ROOT.kDotted if shift != 0 else ROOT.kDashed)
                lines[shift].SetLineColor(ROOT.kBlack)
                lines[shift].Draw("same")
            for bin in self.etabins:
                color  = self.Hists[bin]["color"]
                marker = self.Hists[bin]["marker"]
                self.Hists[bin]["hist"] = f_.Get(self.Hists[bin]["hname"])
                self.Hists[bin]["hist"].SetDirectory(0)
                self.Hists[bin]["hist"].SetMarkerSize(self.Hists[bin]["msize"])
                #Temp fix: Need to improve closure at high pt due to stat
                for x in range(1,self.Hists[bin]["hist"].GetNbinsX()+1):
                    if self.Hists[bin]["hist"].GetBinCenter(x)<15 : self.Hists[bin]["hist"].SetBinContent(x,0)
                    #if self.Hists[bin]["hist"].GetBinError(x)>0.018: self.Hists[bin]["hist"].SetBinContent(x,0)
		    #if self.Hists[bin]["hist"].GetBinCenter(x)>400 : self.Hists[bin]["hist"].SetBinContent(x,0)
		    #if self.Hists[bin]["hist"].GetBinCenter(x)>400 and self.Hists[bin]["hist"].GetBinContent(x)>1.01: self.Hists[bin]["hist"].SetBinContent(x,0) 
                tdrDraw(self.Hists[bin]["hist"], "P", marker=marker, mcolor=color )
                leg.AddEntry(self.Hists[bin]["hist"], self.Hists[bin]["legend"], "lp")

            f_.Close()
            canv.SaveAs(self.outputPath+"L1L2L3ClosureVsPt_Run3Winter22_AK4CHS.pdf")
            canv.SaveAs(self.outputPath+"L1L2L3ClosureVsPt_Run3Winter22_AK4CHS.png")
            del TDR.extraText3[:]

def main():
    L1L2L3ClosureVsPt().Plot()

if __name__ == '__main__':
    main()
