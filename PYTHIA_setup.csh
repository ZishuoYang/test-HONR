#!/bin/csh
setenv MYLOCATION  `pwd`
echo $MYLOCATION

setenv CMSSCE /home/eno/CMSSW_5_3_29/

cd $CMSSCE
cmsenv
cd $MYLOCATION

echo "done"
