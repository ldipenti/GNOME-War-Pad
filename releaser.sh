#!/bin/sh
# Release GWP nice & easy!

###############
# Set-up vars #
###############
VERSION="$1"
PRJ_SHORT_NAME="gwp"
PRJ_NAME="Gnome War Pad"
# Packages file names
PKG_TGZ="$PRJ_SHORT_NAME"-"$VERSION".tar.gz
PKG_APIDOC="$PRJ_SHORT_NAME"-"$VERSION"-api.tar.gz
PKG_RPM_MDK="$PRJ_SHORT_NAME"-"$VERSION"-1mdk.i586.rpm
PKG_DEB="$PRJ_SHORT_NAME"_"$VERSION"-1_i386.deb
# Various paths
PATH_WEB="../gwp-web"
PATH_RELEASES="$PATH_WEB/releases"
PATH_PACKAGES="$PATH_RELEASES/packages"
PATH_DOCS="$PATH_RELEASES/documentation"
#
URL_SITE="ldipenti@debian1.lunix.com.ar:~/public_html/gwp"
URL_RELEASES="$URL_SITE/releases"
URL_PACKAGES="$URL_RELEASES/packages"
URL_DOCS="$URL_RELEASES/documentation"

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
echo -n "ATTENTION: You're about to release $PRJ_NAME $VERSION, is this correct? (y/n)"
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

#### Version modification in several control files
perl -p -i -e "s/^PROJECT_NUMBER(.*)=(.*)$/PROJECT_NUMBER\1= $VERSION/"  Doxyfile
perl -p -i -e "s/AC_INIT\((.*),(.*),(.*)\)/AC_INIT(\1, $VERSION,\3)/" configure.in
perl -p -i -e "s/AM_INIT_AUTOMAKE\((.*),(.*)\)/AM_INIT_AUTOMAKE(\1, $VERSION)/" configure.in
####

#### Packages making
autoconf && automake && make clean && make dist
rm -rf docs/api/html/* ; doxygen Doxyfile ; cd docs/api/ ; tar -cvzf ../../gwp-$VERSION-api.tar.gz html/ ; cd -
####
