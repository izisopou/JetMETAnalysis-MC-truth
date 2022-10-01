#!/bin/sh

source $CMSSW_BASE/src/JetMETAnalysisMCtruth/condor_AK8CHS/Setup_FileLocation.sh

cat $Step1Output/*/*txt | ./RunMatchFiles > Files/MatchedFiles




