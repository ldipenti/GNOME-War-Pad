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

#########
#### Version modification in several control files
#########

###
# Doxygen
perl -p -i -e "s/^PROJECT_NUMBER(.*)=(.*)$/PROJECT_NUMBER\1= $VERSION/"  Doxyfile

###
# configure.in
perl -p -i -e "s/AC_INIT\((.*),(.*),(.*)\)/AC_INIT(\1, $VERSION,\3)/" configure.in
#perl -p -i -e "s/AM_INIT_AUTOMAKE\((.*),(.*)\)/AM_INIT_AUTOMAKE(\1, $VERSION)/" configure.in

###
# SPEC files
perl -p -i -e "s/%define version(.*)$/%define version $VERSION/" package/gwp-mdk.spec
perl -p -i -e "s/%define version(.*)$/%define version $VERSION/" package/gwp-fedora.spec

###
# debian changelog
TMPFILE=/tmp/gwp.tmp
rm -f $TMPFILE
echo "gwp ($VERSION-1) unstable; urgency=low" >> $TMPFILE
echo                                          >> $TMPFILE
echo "  * Release $VERSION"                   >> $TMPFILE
echo                                          >> $TMPFILE
echo " -- Lucas Di Pentima <lucas@lunix.com.ar>  `date +'%a, %d %b %Y %T %z'`" >> $TMPFILE
echo                                          >> $TMPFILE
cat $TMPFILE debian/changelog > debian/changelog.tmp
mv debian/changelog.tmp debian/changelog
rm $TMPFILE

###
# ChangeLog version & date header
mv ChangeLog ChangeLog.bak
echo -e "Version $VERSION (released `date +%m-%d-%Y`):\n" > ChangeLog.header
cat ChangeLog.header ChangeLog.bak > ChangeLog
rm -f ChangeLog.header ChangeLog.bak

###
# VERSION file - to direct use by the website
echo $VERSION > VERSION

#########################################

###  CVS commiting & tagging
cvs ci -m "Release $VERSION commit, yeah!"
cvs -q tag Release-`echo $VERSION | tr . _`
###

#### Packages making
# TGZ
autoconf && automake && make clean && make dist
# API
rm -rf docs/api/html/* ; doxygen Doxyfile ; cd docs/api/ ; tar -cvzf ../../gwp-$VERSION-api.tar.gz html/ ; cd -
# DEB
fakeroot dpkg-buildpackage
####

### Package uploading
echo "Uploading packages..."
scp gwp-$VERSION.tar.gz $URL_SITE"/releases"
scp gwp-$VERSION-api.tar.gz $URL_SITE"/releases/documentation"
scp ../gwp_"$VERSION"-1_i386.deb $URL_SITE"/releases/packages"
scp -r docs/api $URL_SITE"/docs"
###
