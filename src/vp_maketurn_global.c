/* Author: Rutger Nijlunsing
   Changed by: Kero van Gelder
   First version beginning of September 1995
   Last revision 28 XII 1995 */

/* Implements vgapl.h */

#define VGAPL_G

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"vp_maketurn_misc.h"
#include"vp_maketurn_global.h"

static void
ReadFile (fname, buf, count)
     char *fname;
     void *buf;
     unsigned short count;
/* Leest file met naam <fname> in variabele <buf> voor <count> bytes */
{
  FILE *f;
  char *thefilename;

  thefilename = malloc (strlen (planetsdir) + strlen (fname) + 1);
  sprintf (thefilename, "%s%s", planetsdir, fname);
#ifdef test
  fprintf (stderr, "Opening file `%s`: ", thefilename);
#endif
  if (!Exist (thefilename))
    {
      fprintf (stderr, "File '%s' not found\n", thefilename);
      exit (-1);
    }
  f = fopen (thefilename, "rb");
  fseek (f, 0, SEEK_END);
  if (ftell (f) != count)
    {
      if (ftell (f) > count)
	{
#ifdef test
	  fprintf (stderr, "file '%s' has invalid length (%ld>%d)\n",
		   thefilename, ftell (f), count);
#endif
	}
      else
	{
	  fprintf (stderr, "file '%s' has invalid length (%ld<%d)\n",
		   thefilename, ftell (f), count);
	  exit (-1);
	}
    }
  else
    {
#ifdef test
      fprintf (stderr, "file '%s' has correct length (%ld=%d)\n",
	       thefilename, ftell (f), count);
#endif
    }
  fseek (f, 0, SEEK_SET);
  fread (buf, count, 1, f);
  fclose (f);
  free (thefilename);
}


void
SetPlanetsDir (pdir_)
     char *pdir_;
/* Sets the directory where all global data can be found */
{
  char *pdir;

  pdir = malloc (strlen (pdir_) + 1);
  strcpy (pdir, pdir_);
  if (*pdir == '\0')
    {
      pdir = realloc (pdir, 2);
      strcpy (pdir, ".");
    }
  /* Now: pdir != "" */
  if (pdir[strlen (pdir) - 1] != '/')
    {
      pdir = realloc (pdir, strlen (pdir) + 2);
      strcat (pdir, "/");
    }
  /* Test for all files needed !!! */
  planetsdir = pdir;
#ifdef test
  fprintf (stdout, "Working form directory '%s'.\n", planetsdir);
#endif
}


typedef struct oneplanetnm
{
  char name[nocpp];		/* Name of a planet */
} manyplanetnm[nop];

static void
ReadPlanets ()
/* Reads coordinates and name of all planets */
{
  long i;			/* Index */
  unsigned char *xyplan, *xypl;	/* contents of file ``xyplan.dat'' */
  manyplanetnm planetnm;	/* contents of file ``planet.nm'' */
  unsigned short dump, size = 6;

  xyplan = malloc (nop * size);
  ReadFile ("xyplan.dat", xyplan, nop * size);
  xypl = xyplan;
  ReadFile ("planet.nm", &planetnm, nop * nocpp);
  /* Combining info */
  for (i = 0; i < nop; i++)
    {
      ReadShort (planets[i].x, xypl);
      ReadShort (planets[i].y, xypl);
      ReadShort (dump, xypl);
      sprintf (planets[i].name, "%.*s", nocpp, planetnm[i].name);
    }
  free (xyplan);
}


typedef struct racenm
{
  char complete[nor][nocprc];
  char long_[nor][nocprl];
  char short_[nor][nocprs];
} racenm;

static void
ReadRaces ()
/* Reads in all 11 race names in complete, medium and short form */
{
  long i;
  racenm racenm;		/* contents of file ``race.nm'' */

  ReadFile ("race.nm", &racenm, sizeof (racenm));
  for (i = 0; i < nor; i++)
    {
      sprintf (races[i].complete, "%.*s", nocprc, racenm.complete[i]);
      sprintf (races[i].long_, "%.*s", nocprl, racenm.long_[i]);
      sprintf (races[i].short_, "%.*s", nocprs, racenm.short_[i]);
    }
}


static void
ReadEngines ()
/* Reads in all types of engines (costs and efficiency) */
{
  long i, j;
  unsigned char *engspec, *eng;	/* contents of file ``engspec.dat'' */
  unsigned short size = 66;

  engspec = malloc (noe * size);
  eng = engspec;
  ReadFile ("engspec.dat", engspec, noe * size);
  for (i = 0; i < noe; i++)
    {
      strncpy (engines[i].name, eng, nocpe);
      eng += nocpe;
      ReadShort (engines[i].mc, eng);
      ReadShort (engines[i].trit, eng);
      ReadShort (engines[i].dur, eng);
      ReadShort (engines[i].molyb, eng);
      ReadShort (engines[i].tech, eng);
      for (j = 0; j < 9; j++)
	{
	  ReadLong (engines[i].usage[j], eng);
	}
    }
  free (engspec);
}

static void
ReadHulls ()
/* Reads in all hulls (costs, name) */
{
  long i;
  unsigned char *hullspec, *hull;	/* contents of file ``hullspec.dat'' */
  unsigned short dump, size = 60;

  hullspec = malloc (noh * size);
  ReadFile ("hullspec.dat", hullspec, noh * size);
  hull = hullspec;
  for (i = 0; i < noh; i++)
    {
      strncpy (hulls[i].name, hull, nocph);
      hull += nocph;
      ReadShort (hulls[i].trit, hull);
      ReadShort (hulls[i].dur, hull);
      ReadShort (hulls[i].molyb, hull);
      ReadShort (hulls[i].neutr, hull);
      ReadShort (hulls[i].crew, hull);
      ReadShort (hulls[i].engines, hull);
      ReadShort (hulls[i].mass, hull);
      ReadShort (hulls[i].tech, hull);
      ReadShort (hulls[i].cargo, hull);
      ReadShort (hulls[i].bays, hull);
      ReadShort (hulls[i].launch, hull);
      ReadShort (hulls[i].beams, hull);
      ReadShort (hulls[i].mc, hull);
      ReadShort (hulls[i].picture, hull);
      ReadShort (dump, hull);	/* nobody knows... */
    }
  free (hullspec);
}

static void
ReadBeams ()
/* Reads in all beams (costs and power) */
{
  long i;
  unsigned char *beamspec, *beam;	/* contents of file ``beamspec.dat'' */
  unsigned short size = 36;

  beamspec = malloc (nob * size);
  beam = beamspec;
  ReadFile ("beamspec.dat", beamspec, nob * size);
  for (i = 0; i < nob; i++)
    {
      strncpy (beams[i].name, beam, nocpb);
      beam += nocpb;
      ReadShort (beams[i].mc, beam);
      ReadShort (beams[i].trit, beam);
      ReadShort (beams[i].dur, beam);
      ReadShort (beams[i].molyb, beam);
      ReadShort (beams[i].mass, beam);
      ReadShort (beams[i].tech, beam);
      ReadShort (beams[i].kill, beam);
      ReadShort (beams[i].expl, beam);
    }
  free (beamspec);
}

static void
ReadTorpedoes ()
/* Reads in all torps (costs of launcher & MC/power of missile) */
{
  long i;
  unsigned char *torpspec, *torp;	/* contents of file ``torpspec.dat'' */
  unsigned short size = 38;

  torpspec = malloc (notp * size);
  torp = torpspec;
  ReadFile ("torpspec.dat", torpspec, notp * size);
  for (i = 0; i < notp; i++)
    {
      strncpy (torpedoes[i].name, torp, nocptp);
      torp += nocptp;
      ReadShort (torpedoes[i].mc, torp);
      ReadShort (torpedoes[i].trit, torp);
      ReadShort (torpedoes[i].dur, torp);
      ReadShort (torpedoes[i].molyb, torp);
      ReadShort (torpedoes[i].mass, torp);
      ReadShort (torpedoes[i].tech, torp);
      ReadShort (torpedoes[i].kill, torp);
      ReadShort (torpedoes[i].expl, torp);
      ReadShort (torpedoes[i].torpmc, torp);
    }
  free (torpspec);
}


void
GlobalInit ()
/* Reads in all global data, using functions above */
{
  ReadPlanets ();
  ReadRaces ();
  ReadEngines ();
  ReadHulls ();
  ReadBeams ();
  ReadTorpedoes ();
}				/* GlobalInit */

void
GlobalDone ()
/* Finishes global data */
{
  /* think of something, or don't */
}				/* GlobalDone */
