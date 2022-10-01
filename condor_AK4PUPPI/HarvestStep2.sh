#!/bin/sh

source $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK4PUPPI/Setup_FileLocation.sh

hadd -k -f $Step2Output/output_ak4puppi.root $Step2Output/Result_*.root

# We do not derive L1 corrections for PUPPI so the following lines are commented out (but can be used to derive as a test)

# jet_synchfit_x \
#   -inputDir  $Step2Output/ \
#   -outputDir `pwd`/Files/L1_output/ \
#   -algo1 ak4puppi \
#   -algo2 ak4puppi \
#   -highPU false \
#   -useNPU false \
#   -functionType ak4 \
#   -era Winter22Run3



