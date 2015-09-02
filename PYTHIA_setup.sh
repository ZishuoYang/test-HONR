#!/bin/csh
set MYLOCATION = `pwd`
echo $MYLOCATION


set MYROOT = /data/users/eno/root/
set MYROOT2 = /data/users/eno/root/bin

cd $MYROOT2
pwd
source ./thisroot.csh
cd $MYLOCATION
echo "done"
