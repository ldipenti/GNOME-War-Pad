#!/bin/sh
# Release GWP nice & easy!

PROJECT_NAME="Gnome War Pad"
VERSION=$1

# Check if this is run from the correct directory
if [ ! -f `basename $0` ]; then
	echo "ERROR: You must execute this script from project root directory."
	exit
fi
# Check for version parameter
if [ -z "$VERSION" ]; then
	echo "Usage: $0 <version_number>"
	exit
fi
# Ask for confirmation
echo -n "ATTENTION: You're about to release $PROJECT_NAME $VERSION, is this correct? (y/n)"
read ANSWER

case $ANSWER in
	y|Y)
	echo "Let's work!!!"
	;;
	*)
	echo "Release process cancelled by user. Bye!"
	exit
	;;
esac

perl -p -i -e "s/^PROJECT_NUMBER(.*)=(.*)$/PROJECT_NUMBER\1= $VERSION/"  Doxyfile
perl -p -i -e "s/AC_INIT\((.*),(.*),(.*)\)/AC_INIT(\1, $VERSION,\3)/" configure.in
perl -p -i -e "s/AM_INIT_AUTOMAKE\((.*),(.*)\)/AM_INIT_AUTOMAKE(\1, $VERSION)/" configure.in

# 
#make dist
