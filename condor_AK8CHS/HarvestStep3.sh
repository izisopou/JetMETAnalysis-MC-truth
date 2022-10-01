#!/bin/sh

source $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK8CHS/Setup_FileLocation.sh

hadd -k -f $Step3Output/Merged.root $Step3Output/JRA_*root

jet_l2_correction_x \
   -input $Step3Output/Merged.root \
   -algs ak8pfchsl1 \
   -era Winter22Run3 \
   -output l2.root \
   -outputDir Files/L1L2L3_output \
   -makeCanvasVariable AbsCorVsJetPt:JetEta \
   -l2l3 true \
   -batch true \
   -histMet median \
   -delphes false \
   -maxFitIter 30 \
   -l2calofit DynamicMin \
   -l2pffit standard+Gaussian \
   -ptclipfit true \

mv Files/L1L2L3_output/Winter22Run3_L2Relative_AK8PFchsl1.txt Files/L1L2L3_output/Winter22Run3_L2Relative_AK8PFchs.txt
 
