/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.2  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

/* Author: Rutger Nijlunsing
   Changed by: Kero van Gelder
   First version beginning of September 1995
   Last revision 12 II 1996 */

/* Written for Tim Wissemans VGA-planets.
   Reads in all global stuff like ``engspec.dat''
   Puts that in data-structures given below */

#ifndef VGAPL_H
#define VGAPL_H

#ifndef MISC_H
#include "vp_maketurn_misc.h"
#endif


#ifdef VGAPL_G
# define vextern
#else
# define vextern extern
#endif

#define kutilversion "0.5b"
#define email "kero@dds.nl"

#define nop            500	/* Number of planets */
#define nocpp           20	/* Length of a planetname */
#define nor             11	/* Number of races */
#define nocprc          30	/* Length of complete racename */
#define nocprl          20	/* Length of long racename */
#define nocprs          12	/* Length of short racename */
#define noe              9	/* Number of engine types */
#define nocpe           20	/* Length of an enginetype name */
#define noh            105	/* Number of hulls */
#define nocph           30	/* Length of a hull name */
#define nob             10	/* Number of weapon types */
#define nocpb           20	/* Length of a weapontype name */
#define notp            10	/* Number of torpedo types */
#define nocptp          20	/* Length of a torpedotype name */

#define sof            204	/* size of registration part in ``fizz.bin'' */

/* The following 4 macros are made to read/write ... endian
   They assume s,l are short resp. long and buf is an unsigned char*
   Conclusion: one of the dangerous things in this program */
/* In this program I NEVER use these macros on a variable with
   `remember' in it, because they are always the beginning of some
   buffer (will de free-ed later) */
#define ReadShort(s,buf); {s=(short)(buf[0]+(buf[1]<<8));buf+=2;}
#define ReadLong(l,buf); {l=(long)(buf[0]+(buf[1]<<8)+(buf[2]<<16)+(buf[3]<<24));buf+=4;}
#define WriteShort(s,buf); {buf[0]=(s)&255;buf[1]=(s)>>8;buf+=2;}
#define WriteLong(l,buf); {buf[0]=(l)&255;buf[1]=((l)>>8)&255;buf[2]=((l)>>16)&255;buf[3]=(l)>>24;buf+=4;}

typedef struct globalplanet
{
  long x, y;			/* Coordinates of a planet */
  char name[nocpp + 1];		/* Name of a planet */
} globalplanets[nop];

typedef struct globalrace
{
  char complete[nocprc + 1];	/* Complete name of a race */
  char long_[nocprl + 1];	/* Long name of a race */
  char short_[nocprs + 1];	/* Short name of a race */
} globalraces[nor];

typedef struct globalengine
{
  char name[nocpe + 1];		/* Name of an engine */
  unsigned short mc, trit, dur, molyb, tech;
  long usage[9];
} globalengines[noe];

typedef struct globalhull
{
  char name[nocph + 1];		/* Name of the hull */
  long trit, dur, molyb, neutr, crew, engines, mass, tech, cargo, bays,
    launch, beams, mc, picture;
} globalhulls[noh];

typedef struct globalbeam
{
  char name[nocpb + 1];		/* Name of the beamweapon */
  long mc, trit, dur, molyb, mass, tech, kill, expl;
} globalbeams[nob];

typedef struct globaltorpedo
{
  char name[nocptp + 1];	/* Name of the Torpedoe(launcher) */
  long mc, trit, dur, molyb, mass, tech, kill, expl;	/* costs of launcher */
  long torpmc;			/* Costs of torpedoes (TDM&mass 1 for all torps) */
} globaltorpedoes[notp];


vextern char *planetsdir;
vextern globalplanets planets;	/* De planeten */
vextern globalengines engines;	/* De engines */
vextern globalraces races;	/* De rassen */
vextern globalhulls hulls;	/* De hullen */
vextern globalbeams beams;	/* De wapens */
vextern globaltorpedoes torpedoes;	/* De torpedo's */

extern void SetPlanetsDir (char *pdir);
extern void GlobalInit ();
extern void GlobalDone ();

#undef vextern

#endif /*VGAPL_H */
