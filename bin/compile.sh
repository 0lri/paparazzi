#!/bin/sh
#
# $Id:$ olri
#

[ $# = 1 ] || { echo "Usage: $0 <AirframeName>"; exit 5; }

make -k -f Makefile.ac AIRCRAFT="$1" ap.compile
