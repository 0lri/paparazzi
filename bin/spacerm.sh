#!/bin/sh

for i in `git diff paparazzi/master -- . | grep " b/" | grep +++ | sed 's/+++//;s/b\///'`
do
	cp $i $i.tmp
        sed 's/[\t ]*$//g;' $i.tmp > $i
        rm $i.tmp
done
