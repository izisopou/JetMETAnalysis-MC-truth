import glob, os, ROOT
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)
from array import array
import numpy as np
from tdrstyle_JERC_MCtruth import *
import tdrstyle_JERC_MCtruth as TDR
TDR.extraText  = 'Simulation'
TDR.extraText2  = 'Preliminary'

class L1OffsetVsPt():
    def __init__(self, radius, algo, prefix):
        self.doCleaning = True
        self.radius = radius
        self.algo = algo
        self.inputPath = '../../Summer20default/L1FastJet/'
        self.outputPath = 'Pdfs/'
        os.system('mkdir -p '+self.outputPath)
        self.filename = 'Offset'+prefix+'L1VsPt_AK'+self.radius+self.algo+'_default'
        self.years = ['UL16APV', 'UL16nonAPV', 'UL17', 'UL18', 'Run2']
        self.etabins = ['BB', 'EI', 'EO', 'FF']
        self.mubins = ['0','10','20','30', '40', '50']
        self.Hists = {
            '0': {'legend': '  0 #leq #mu < 10',
                  'color':  ROOT.kRed+1,
                  'marker': ROOT.kFullStar,
                  'msize':  1.3,
                  'hname':  'histograms/OffMeantnpuRef_default_0',
                  },
            '10': {'legend': '10 #leq #mu < 20',
                   'color':  ROOT.kOrange+1,
                   'marker': ROOT.kFullSquare,
                   'msize':  1.0,
                   'hname':  'histograms/OffMeantnpuRef_default_1',
                   },
            '20': {'legend': '20 #leq #mu < 30',
                   'color':  ROOT.kSpring+2,
                   'marker': ROOT.kFullTriangleDown,
                   'msize':  1.0,
                   'hname':  'histograms/OffMeantnpuRef_default_2',
                   },
            '30': {'legend': '30 #leq #mu < 40',
                   'color':  ROOT.kGreen+2,
                   'marker': ROOT.kFullCircle,
                   'msize':  1.0,
                   'hname':  'histograms/OffMeantnpuRef_default_3',
                   },
            '40': {'legend': '40 #leq #mu < 50',
                   'color':  ROOT.kAzure+2,
                   'marker': ROOT.kFullTriangleUp,
                   'msize':  1.0,
                   'hname':  'histograms/OffMeantnpuRef_default_4',
                   },
            '50': {'legend': '50 #leq #mu < 60',
                   'color':  ROOT.kViolet, 
                   'marker': ROOT.kFullCrossX,
                   'msize':  1.0,
                   'hname':  'histograms/OffMeantnpuRef_default_5',
                      },
            }
    def Plot(self):
        PlotXMin = 11
        PlotXMax = 5500
        for year in self.years:
            f_ = ROOT.TFile(os.path.join(self.inputPath,self.filename+'.root').replace('default',year).replace('Summer20UL16nonAPV','Summer20UL16'))
            for eta in self.etabins:
                TDR.cms_lumi_TeV = TDR.commonScheme['legend'][year]+' Legacy'
                TDR.extraText3 = []
                TDR.extraText3.append('AK'+self.radius+', PF+'+self.algo+'')
                TDR.extraText3.append('')
                if eta=='BB':   TDR.extraText3.append('0.0 < |#eta| < 1.3')
                elif eta=='EI': TDR.extraText3.append('1.3 < |#eta| < 2.5')
                elif eta=='EO': TDR.extraText3.append('2.5 < |#eta| < 3.0')
                elif eta=='FF': TDR.extraText3.append('3.0 < |#eta| < 5.0')

                PlotYMin = -4
                if eta=='BB':   PlotYMax =  60 if self.radius=='4' else 100
                elif eta=='EI': PlotYMax =  60 if self.radius=='4' else 100
                elif eta=='EO': PlotYMax = 100 if self.radius=='4' else 100
                elif eta=='FF': PlotYMax = 100 if self.radius=='4' else 100
                if 'After' in self.filename:
                    PlotYMax = 5
                if 'Without' in self.filename:
                    PlotYMin = -10
                    PlotYMax = 20
                canv = tdrCanvas('L1OffsetVsPt', PlotXMin, PlotXMax, PlotYMin, PlotYMax, 'p_{T}^{ptcl}[GeV]', 'Average Offset / p_{T}^{ptcl} [%]', square=kSquare, isExtraSpace=True)
                canv.SetLogx(True)
                leg = tdrLeg(0.60,0.62,0.89,0.91, textSize=0.04)

                latex = rt.TLatex()
                latex.SetTextFont(42)
                latex.SetTextSize(0.05)
                latex.DrawLatex(25,PlotYMin-0.06667*(PlotYMax-PlotYMin),"30")
                latex.DrawLatex(75,PlotYMin-0.06667*(PlotYMax-PlotYMin),"100")
                latex.DrawLatex(225,PlotYMin-0.06667*(PlotYMax-PlotYMin),"300")
                latex.DrawLatex(680,PlotYMin-0.06667*(PlotYMax-PlotYMin),"1000")
                latex.DrawLatex(2050,PlotYMin-0.06667*(PlotYMax-PlotYMin),"3000")

                lines = {}
                for shift in [0.00, -1, 1]:
                    lines[shift] = ROOT.TLine(PlotXMin, shift, PlotXMax, shift)
                    lines[shift].SetLineWidth(1)
                    lines[shift].SetLineStyle(ROOT.kDotted if shift != 0 else ROOT.kDashed)
                    lines[shift].SetLineColor(ROOT.kBlack)
                    lines[shift].Draw('same')

                for bin in self.mubins:
                    #for UL16 show bins of mu up to 40 (no events in data with mu>40)
                    if ((bin=='40' or bin=='50') and (year=='UL16APV' or year=='UL16nonAPV')): continue
                    if (bin=='50'): continue #this bin only for Run3
                    color  = self.Hists[bin]['color']
                    marker = self.Hists[bin]['marker']
                    self.Hists[bin]['hist'] = f_.Get(self.Hists[bin]['hname'].replace('default',eta))
                    self.Hists[bin]['hist'].SetDirectory(0)
                    self.Hists[bin]['hist'].SetMarkerSize(self.Hists[bin]['msize'])
                    self.Hists[bin]['hist'].Scale(100)
                    if self.doCleaning:
                        # print ('FIXME: Is cleaning really needed?')
                        for x in range(1,self.Hists[bin]['hist'].GetNbinsX()+1):
                            bin_center = self.Hists[bin]['hist'].GetBinCenter(x)
                            bin_width = self.Hists[bin]['hist'].GetBinWidth(x)
                            if (bin_center-bin_width/2)<20: self.Hists[bin]['hist'].SetBinContent(x,-999)
                            if self.radius=='8':
                                if bin_center<30: self.Hists[bin]['hist'].SetBinContent(x,-999)
                    tdrDraw(self.Hists[bin]['hist'], 'P', marker=marker, mcolor=color )
                    leg.AddEntry(self.Hists[bin]['hist'], self.Hists[bin]['legend'], 'lp')

                canv.SaveAs(os.path.join(self.outputPath, self.filename.replace('default', year+'_'+eta)+'.pdf'))
                canv.Close()
            f_.Close()

def main():
    prefixes =['Before', 'After']
    radii = ['4', '8']
    algos = ['CHS', 'PUPPI']
    for radius in radii:
        for algo in algos:
            for prefix in prefixes:
                if algo=='PUPPI' and prefix=='Before': continue
                if algo=='PUPPI' and prefix=='After': prefix='Without'
                L1OffsetVsPt(radius=radius, algo=algo, prefix=prefix).Plot()

if __name__ == '__main__':
    main()
