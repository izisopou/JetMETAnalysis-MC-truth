#!/bin/sh

source $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK4CHS/Setup_FileLocation.sh

hadd -k -f $Step4Output/Merged.root $Step4Output/Closure_*.root

jet_draw_closure_x \
   -doPt true \
   -doEta true \
   -path $Step4Output/ \
   -filename Merged \
   -histMet median \
   -outputDir Files/L1L2L3_Closure/ \
   -outputFormat .png .pdf \
   -draw_guidelines true \
   -doRatioPt false \
   -doRatioEta false


