To fix the compilation errors:

------------

Open the JetMETAnalysis/JetAnalyzers/BuildFile.xml code and in line 20 replace "SimDataFormats/JetMatching" with "DataFormats/JetMatching"

Open the codes JetMETAnalysis/JetAnalyzers/interface/JetResponseAnalyzer.hh and JetMETAnalysis/JetAnalyzers/interface/JetResponseAnalyzerProducer.hh and replace "SimDataFormats/JetMatching" with "DataFormats/JetMatching" in lines 45 and 43 respectively.

The above step is necessary because in CMSSW_12_2_X they moved the JetMatching/ folder from SimDataFormats to DataFormats

------------

cp /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/include/c++/9.3.0/bits/stl_tree.h JetMETAnalysis/JetUtilities/interface/

Open the JetMETAnalysis/JetUtilities/interface/stl_tree.h code and comment out lines 778-781 which are responsible for giving the error "static assertion failed: comparison object must be invocable as const"

Open the JetMETAnalysis/JetAnalyzers/bin/jet_match_x.cc and JetMETAnalysis/JetAnalyzers/bin/jet_synchtest_x.cc codes and add *before any other include* the following:
#include "JetMETAnalysis/JetUtilities/interface/stl_tree.h"

Then, open the JEC_Run3MCsamples/CMSSW_12_2_1/tmp/slc7_amd64_gcc900/src/JetMETAnalysis/JetUtilities/src/JetMETAnalysisJetUtilities/a/JetMETAnalysisJetUtilities_xr.cc code and do the same -> add *before any other include* the following:
#include "JetMETAnalysis/JetUtilities/interface/stl_tree.h" 

You need to write the above include before any other so that it takes into account our modified stl_tree.h instead of the one inside /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/gcc/9.3.0/include/c++/9.3.0/bits/
  
-----------  

Move the SynchFittingProcedure.hh code from JetMETAnalysis/JetUtilities/src/ to the JetMETAnalysis/JetUtilities/interface/ folder and then open the JetMETAnalysis/JetAnalyzers/bin/jet_synchplot_x.cc code and in line 35 replace src/ with inteface/ (to provide the new correct path).


-----------

Take the addAlgorithm.py and customizePuppiTune_cff_V15.py codes from the directory /afs/cern.ch/work/i/izisopou/public/JEC_MCsamples/CMSSW_12_2_1/src/python_scripts_forRun3samples/ and put them inside JEC_Run3MCsamples/CMSSW_12_2_1/src/JetMETAnalysis/JetAnalyzers/python/

Also, take the run_JRA_cfg_MCtruth.py from the directory /afs/cern.ch/work/i/izisopou/public/JEC_MCsamples/CMSSW_12_2_1/src/python_scripts_forRun3samples/ and put it inside JEC_Run3MCsamples/CMSSW_12_2_1/src/JetMETAnalysis/JetAnalyzers/test/

These new .py files are modified so as to not give errors with python3: 
1)4 spaces instead of a tab
2)algsizetype.items() instead of algsizetype.iteritems()
3)add parentheses in print commands
4)list(genJetsDict.keys()).index(alg_size_type) instead of genJetsDict.keys().index(alg_size_type) 


-----------

Finally, compile again in src/:
scram b -j 4

There should be no errors now.


Go to JEC_Run3MCsamples/CMSSW_12_2_1/src/JetMETAnalysis/JetAnalyzers/test and run a test:

cmsenv
voms-proxy-init -voms cms
cmsRun run_JRA_cfg_MCtruth.py
