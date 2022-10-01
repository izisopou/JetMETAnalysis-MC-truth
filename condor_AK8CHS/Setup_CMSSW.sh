export SCRAM_ARCH=slc7_amd64_gcc10
cd $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK8CHS/
eval `scramv1 runtime -sh`
cd - > /dev/null

