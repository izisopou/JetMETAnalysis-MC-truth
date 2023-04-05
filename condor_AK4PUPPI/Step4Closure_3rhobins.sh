#!/bin/sh --login

#BSUB -q 1nh

WorkDir=$1
File=$2
Output=$3
ID=$4

source $WorkDir/Setup_CMSSW.sh

cp $WorkDir/Files/Winter22/JECs_withL2L3vsRho/L2L3_output/rho0to22/Winter22Run3*.txt .
cp $WorkDir/Files/Winter22/JECs_withL2L3vsRho/L2L3_output/rho22to30/Winter22Run3*.txt .
cp $WorkDir/Files/Winter22/JECs_withL2L3vsRho/L2L3_output/rho30toinf/Winter22Run3*.txt .
cp $WorkDir/Files/Winter22/JECs_withL2L3vsRho/L2L3_output/rho0to22/My*.root .

echo Input files are: $File

hadd -k -f Input.root `echo $File | tr ':' ' '`

jet_correction_analyzer_x \
   -inputFilename Input.root \
   -outputDir ./ \
   -path $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK4PUPPI/ \
   -era_rhoLow Winter22Run3_rho0to22 \
   -era_rhoMiddle Winter22Run3_rho22to30 \
   -era_rhoHigh Winter22Run3_rho30toinf \
   -levels 2 \
   -useweight false \
   -algs ak4puppi \
   -drmax 0.2 \
   -evtmax 0 \
   -nbinsrelrsp 60 \
   -relrspmin 0.0 \
   -relrspmax 3.0 \
   -MCPUReWeighting MyMCPUHisto_Winter22Run3_Flat2018_PremixedPU.root \
   -DataPUReWeighting MyDataPUHisto_2022_erasBCDEFG.root \
   -nrefmax 3 \
   -doDZcut true \
   -doNMcut true 

cp Closure_ak4puppi.root ${Output}/Closure_ak4puppi${ID}.root

rm *.root
