import glob, os, ROOT
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)
from array import array
import numpy as np
from tdrstyle_JERC import *
import tdrstyle_JERC as TDR
TDR.extraText  = 'Simulation'
TDR.extraText2 = 'Preliminary'

class L1L2L3ClosureVsPt():
    def __init__(self, radius, algo, year):
        self.radius = radius
        self.algo = algo
        self.year = year
        if 'UL' in self.year:
            self.inputPath = 'Inputs/'
        if 'Run3' in self.year:
            self.inputPath = 'Inputs/'
        self.outputPath = 'Pdfs/'
        os.system('mkdir -p '+self.outputPath)
        self.filename = 'MCtruthCorrectionVsEta_AK'+self.radius+self.algo+'_default'
        self.ptbins = ['15','30','90','300','1000','3000']
        self.pts_leg = ['15', '300', '30', '1000', '90', '3000']
        self.Hists = {
            '15'  : { 'color': ROOT.kBlack,      'marker': ROOT.kFullStar,        'msize': 1.2,    'hname': 'EtaSF_0' },
            '30'  : { 'color': ROOT.kGreen+3,    'marker': ROOT.kFullSquare,      'msize': 0.8,    'hname': 'EtaSF_1' },
            '90'  : { 'color': ROOT.kOrange+1,   'marker': ROOT.kFullCircle,      'msize': 0.9,    'hname': 'EtaSF_2' },
            '300' : { 'color': ROOT.kViolet-3,   'marker': ROOT.kFullDiamond,     'msize': 1.2,    'hname': 'EtaSF_3' },
            '1000': { 'color': ROOT.kAzure+2,    'marker': ROOT.kFullCross,       'msize': 0.9,    'hname': 'EtaSF_4' },
            '3000': { 'color': ROOT.kRed+1,      'marker': ROOT.kFullTriangleUp,  'msize': 0.9,    'hname': 'EtaSF_5' },
        }


    def Plot(self):
        PlotXMin = -5.2
        PlotXMax = 5.2
        PlotYMin = 0.8
        PlotYMax = 2.5
        TDR.cms_lumi = TDR.commonScheme['legend'][self.year]
        TDR.cms_energy = '13.6'
        if 'UL' in self.year:
            TDR.cms_lumi +=' Legacy'
        TDR.extraText3 = []
        TDR.extraText3.append('AK'+self.radius+' '+self.algo.replace('CHS','PF+CHS'))
        canv = tdrCanvas('MCtruthCorrectionVsEta'+self.year, PlotXMin, PlotXMax, PlotYMin, PlotYMax, '#eta^{jet}', 'MC truth Correction', square=kSquare, isExtraSpace=True)
        leg = tdrLeg(0.40,0.71,0.93,0.90, textSize=0.033)
        leg.SetNColumns(2)

        f_ = ROOT.TFile(os.path.join(self.inputPath,self.filename+'.root').replace('default',self.year).replace('Summer20UL16nonAPV','Summer20UL16'))

        for bin in self.ptbins:
            color  = self.Hists[bin]['color']
            marker = self.Hists[bin]['marker']
            self.Hists[bin]['hist'] = f_.Get(self.Hists[bin]['hname'])
            self.Hists[bin]['hist'].SetDirectory(0)
            self.Hists[bin]['hist'].SetMarkerSize(self.Hists[bin]['msize'])
            tdrDraw(self.Hists[bin]['hist'], 'P', marker=marker, mcolor=color )

        for bin in self.pts_leg:
            leg.AddEntry(self.Hists[bin]['hist'], 'p_{T}^{jet} = ' + bin + ' GeV', 'lp')

        canv.SaveAs(os.path.join(self.outputPath, self.filename.replace('default', self.year)+'.pdf'))
        canv.Close()
        f_.Close()

def main():
    #radii = ['4', '8']
    radii = ['4']
    #algos = ['CHS', 'PUPPI']
    algos = ['PUPPI']
    #years = ['UL16APV', 'UL16nonAPV','UL17','UL18', 'Run2']
    years = ['Run3']
    for radius in radii:
        for algo in algos:
            for year in years:
                L1L2L3ClosureVsPt(radius=radius, algo=algo, year=year).Plot()

if __name__ == '__main__':
    main()
