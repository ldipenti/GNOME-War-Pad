#!/bin/sh
# This script generates the Python mapping file src/gwp-py-mappins.c

# Check if this is run from the correct directory
if [ ! -f `basename $0` ]; then
	echo "ERROR: You must execute this script from project root directory."
	exit
fi

echo -n "Starting to work..."

H_FILES="src/gwp-object.h src/gwp-flying-object.h src/gwp-planet.h src/gwp-ship.h src/gwp-ion-storm.h src/gwp-engspec.h src/gwp-torpspec.h src/gwp-beamspec.h src/gwp-hullspec.h src/gwp-starbase.h src/gwp-location.h src/gwp-minefield.h src/gwp-py-functions.h src/gwp-race.h src/gwp-starchart.h src/gwp-game-state.h"
CODEGENDIR=`pkg-config --variable=codegendir pygtk-2.0`
DEFSDIR=`pkg-config --variable=defsdir pygtk-2.0`
DEFSFILE="src/gwp-py-mappings.defs"


# Generate definitions
python $CODEGENDIR/h2def.py $H_FILES > $DEFSFILE

# Generate C code from definitions
pygtk-codegen-2.0 --prefix gwp			\
	--override src/gwp-py-mappings.override	\
	--register $DEFSDIR/gdk-types.defs	\
	--register $DEFSDIR/gtk-types.defs	\
	$DEFSFILE > src/gwp-py-mappings.c

echo "done!"
