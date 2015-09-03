#!/bin/csh
setenv MYLOCATION  `pwd`
echo $MYLOCATION

setenv SCRAM_ARCH slc6_amd64_gcc491
setenv CMSSCE /home/eno/CMSSW_7_4_0/

cd $CMSSCE
cmsenv
cd $MYLOCATION

setenv MYROOT /data/users/eno/root-6.04.02/
setenv MYROOT2 /data/users/eno/root-6.04.02/config/

cd $MYROOT2
pwd
source ./thisroot.csh
cd $MYLOCATION
echo "done"
