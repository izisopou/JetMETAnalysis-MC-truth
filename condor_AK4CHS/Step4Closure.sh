#!/bin/sh --login

#BSUB -q 1nh

WorkDir=$1
File=$2
Output=$3
ID=$4

source $WorkDir/Setup_CMSSW.sh

cp $WorkDir/Files/L1L2L3_output/*.txt .
cp $WorkDir/Files/L1L2L3_output/My*.root .

echo Input files are: $File

hadd -k -f Input.root `echo $File | tr ':' ' '`

jet_correction_analyzer_x \
   -inputFilename Input.root \
   -outputDir ./ \
   -path $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK4CHS/ \
   -era Winter22Run3 \
   -levels 1 2 \
   -useweight false \
   -algs ak4pfchs \
   -drmax 0.2 \
   -evtmax 0 \
   -nbinsrelrsp 60 \
   -relrspmin 0.0 \
   -relrspmax 3.0 \
   -MCPUReWeighting MyMCPUHisto_Winter22Run3_Flat2018_PremixedPU.root \
   -DataPUReWeighting MyDataPUHisto_2022.root \
   -nrefmax 3

cp Closure_ak4pfchs.root ${Output}/Closure_ak4pfchs${ID}.root

rm *.root

