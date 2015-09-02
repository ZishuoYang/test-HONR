#!/bin/csh
setenv MYLOCATION  `pwd`
echo $MYLOCATION


setenv MYROOT /data/users/eno/root/
setenv MYROOT2 /data/users/eno/root/bin

cd $MYROOT2
pwd
source ./thisroot.csh
cd $MYLOCATION
echo "done"
