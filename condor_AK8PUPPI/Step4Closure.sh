#!/bin/sh --login

#BSUB -q 1nh

WorkDir=$1
File=$2
Output=$3
ID=$4

source $WorkDir/Setup_CMSSW.sh

cp $WorkDir/Files/L2L3_output/*.txt .
cp $WorkDir/Files/L2L3_output/My*.root .

echo Input files are: $File

hadd -k -f Input.root `echo $File | tr ':' ' '`

# -levels 1 2 if you use both L1 and L2L3 txt files

jet_correction_analyzer_x \
   -inputFilename Input.root \
   -outputDir ./ \
   -path $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK8PUPPI/ \
   -era Winter22Run3 \
   -levels 2 \
   -useweight false \
   -algs ak8puppi \
   -drmax 0.4 \
   -evtmax 0 \
   -nbinsrelrsp 60 \
   -relrspmin 0.0 \
   -relrspmax 3.0 \
   -MCPUReWeighting MyMCPUHisto_Winter22Run3_Flat2018_PremixedPU.root \
   -DataPUReWeighting MyDataPUHisto_2022.root \
   -nrefmax 3

cp Closure_ak8puppi.root ${Output}/Closure_ak8puppi${ID}.root

rm *.root
