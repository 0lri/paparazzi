#!/bin/sh
#
# $Id$
#
# HB_SAS Busca_Razor_40cm Busca_Razor_80cm TWOG_CHNI Lerche MJ5 Busca2
for i in HB_TINY_RAZOR HB_MINI_FIXEDWING MJ5
do
	echo "###################### $i #######################"
	(
		echo make -f Makefile.ac AIRCRAFT=$i clean_ac ap.compile > /dev/tty
		make -f Makefile.ac AIRCRAFT=$i clean_ac ap.compile
		echo make -f Makefile.ac AIRCRAFT=$i clean_ac sim.compile > /dev/tty
		make -f Makefile.ac AIRCRAFT=$i clean_ac sim.compile
	) 2>&1 | egrep Total\|Error\|Fehler
done

#for i in 1 2 3 4 # defect 5
#do
#	echo "###################### demo$i #######################"
#	(
#		echo make -f Makefile.ac AIRCRAFT=DEMO clean_ac demo$i.compile > /dev/tty
#		make -f Makefile.ac AIRCRAFT=DEMO clean_ac demo$i.compile
#	) 2>&1 | egrep Total\|Error\|Fehler
#done
