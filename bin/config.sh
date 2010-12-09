#!/bin/sh

[ "$1" = "" ] && printf "Usage: $0 <HB>\n\n" && exit 1

cd conf

rm -f conf.xml control_panel.xml

ln -s conf.xml.$1 conf.xml
ln -s control_panel.xml.$1 control_panel.xml
