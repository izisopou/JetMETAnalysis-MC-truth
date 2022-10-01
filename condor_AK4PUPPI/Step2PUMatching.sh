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

cp $WorkDir/Files/L2L3_output/My*.root .
cp $WorkDir/Files/L2L3_output/*.txt .

echo Current directory content
ls
echo

jet_match_x \
   -basepath // \
   -samplePU PUFile.root \
   -sampleNoPU NoPUFile.root \
   -algo1 ak4puppi \
   -algo2 ak4puppi \
   -iftest false \
   -maxEvts 20000000 \
   -ApplyJEC false \
   -outputPath ./ \
   -npvRhoNpuBinWidth 10 \
   -NBinsNpvRhoNpu 9 \
   -MCPUReWeighting MyMCPUHisto_Winter22Run3_Flat2018_FlatPU.root \
   -DataPUReWeighting MyDataPUHisto_2022.root \
   -useweight false \
   -nrefmax 3 \
   -doNotSave false

mv output_ak4puppi.root ${Output}/Result_${ID}.root

# We do not derive L1 corrections for PUPPI but if you want as a test
# to create an L1 txt file and apply it to examine the corrected offset replace
#
#   -ApplyJEC false \
#
# with the following:
#
#   -ApplyJEC true \
#   -JECpar Winter22Run3_L1FastJet_AK4PUPPI.txt \


