#!/bin/sh

source $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK8PUPPI/Setup_FileLocation.sh

hadd -k -f $Step2Output/output_ak8puppi.root $Step2Output/Result_*.root

# We do not derive L1 corrections for PUPPI so the following lines are commented out (but can be used to derive as a test)

# jet_synchfit_x \
#   -inputDir  $Step2Output/ \
#   -outputDir `pwd`/Files/L1_output/ \
#   -algo1 ak8puppi \
#   -algo2 ak8puppi \
#   -highPU false \
#   -useNPU false \
#   -functionType ak8 \
#   -era Winter22Run3



