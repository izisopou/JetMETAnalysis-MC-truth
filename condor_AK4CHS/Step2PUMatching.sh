#!/bin/sh --login

#BSUB -q 1nh
export DISPLAY=localhost0.0
WorkDir=$1
NoPUFile=$2
PUFile=$3
Output=$4
ID=$5

source $WorkDir/Setup_CMSSW.sh

if [[ $NoPUFile != *":"* ]]; then
   cp $NoPUFile NoPUFile.root
else
   hadd -f -k NoPUFile.root `echo $NoPUFile | tr ':' ' '`
fi

if [[ $PUFile != *":"* ]]; then
   cp $PUFile PUFile.root
else
   hadd -f -k PUFile.root `echo $PUFile | tr ':' ' '`
fi

cp $WorkDir/Files/L1_output/My*.root .
cp $WorkDir/Files/L1_output/*.txt .

echo Current directory content
ls
echo

jet_match_x \
   -basepath // \
   -samplePU PUFile.root \
   -sampleNoPU NoPUFile.root \
   -algo1 ak4pfchs \
   -algo2 ak4pfchs \
   -iftest false \
   -maxEvts 10000000 \
   -ApplyJEC false \
   -outputPath ./ \
   -npvRhoNpuBinWidth 10 \
   -NBinsNpvRhoNpu 9 \
   -MCPUReWeighting MyMCPUHisto_FlatPU.root \
   -DataPUReWeighting MyDataPUHisto.root \
   -useweight false \
   -nrefmax 3 \
   -doNotSave false

mv output_ak4pfchs.root ${Output}/Result_${ID}.root

# When you want to apply the L1 txt file to examine the corrected offset replace
#   -ApplyJEC false \
#
# with the following:
#
#   -ApplyJEC true \
#   -JECpar Winter22Run3_L1FastJet_AK4PFchs.txt \


