/* Author: Kero van Gelder
   First version 16 IX 1995
   Last revision 15 XII 1995 */

/* Implements local.h */

#define LOCAL_G

#define sos            107	/* size of a ship */
#define sop             85	/* size of a planet */
#define sob            156	/* size of a base */
#define sot             34	/* size of a target */
#define sog            157	/* size of ``gen.dat'' */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vp_maketurn_misc.h"
#include "vp_maketurn_global.h"
#include "vp_maketurn_playerio.h"

void PlayerioInit (void);
void PlayerioDone (void);

char *natname[10] = {
  "NONE", "Humanoids", "Bovinoids", "Reptilians", "Avians", "Amorphous",
  "Insectoids", "Amphibians", "Ghipsoldals", "Siliconoids"
};

char *civname[10] = {
  "", "Anarchy", "Pre-Tribal", "Early Tribal", "Tribal", "Feudal",
  "Monarchy", "Representative", "Participatory", "Unity"
};

char *gamedir;

static FILE *ctrl;
static unsigned char *ctrlbuf, *ctrlremember;

void
SetGameDir (gdir)
     char *gdir;
/* sets the directory where the player files should be found */
{
  if (*gdir != '\0')
    {
      if (gdir[0] == '/')
	{
	  gamedir = malloc (strlen (gdir) + 1);
	  strcpy (gamedir, gdir);
	}
      else
	{
	  gamedir = malloc (strlen (planetsdir) + strlen (gdir) + 1);
	  sprintf (gamedir, "%s%s", planetsdir, gdir);
	}
    }
  else
    {
      gamedir = malloc (strlen (planetsdir) + 1);
      strcpy (gamedir, planetsdir);
    }
  /* check for init.tmp and fizz.bin, may be other files (control.dat?) */
  if (gamedir[strlen (gamedir) - 1] != '/')
    {
      gamedir = realloc (gamedir, strlen (gamedir) + 2);
      strcat (gamedir, "/");
    }
#ifdef test
  fprintf (stderr, "%s\n", gamedir);
#endif
}				/* SetGameDir */


void
SetPlayer (p)
     int p;
/* Sets the string player to the number p */
{
  char *gen;

  gen = malloc (strlen (gamedir) + 3 + p % 9 + 1 + 4 + 1);
  sprintf (gen, "%sgen%d.dat", gamedir, p);
  if (!Exist (gen))
    {
      /* instead, check init.tmp */
      /* then check ALL playerfiles */
      fprintf (stderr, "player %d does not play in specified game %s\n", p,
	       gamedir);
      exit (-1);
    }
  else
    {
      player = malloc (p % 9 + 2);
      sprintf (player, "%d", p);
    }
}				/* SetPlayer */


static FILE *
ResetPlayerFile (prefix, suffix)
     char *prefix, *suffix;
/* opens the player file gamedir-prefix-player-suffix */
{
  char *filename;

  filename = malloc (strlen (gamedir) + strlen (prefix) +
		     strlen (player) + strlen (suffix) + 2);
  sprintf (filename, "%s%s%s.%s", gamedir, prefix, player, suffix);
  if (!Exist (filename))
    {
      fprintf (stderr, "Could not find `%s'\n", filename);
      exit (-1);
    }
#ifdef test
  fprintf (stderr, "Opened %s for you.\n", filename);
#endif
  return fopen (filename, "rb");
}				/* ResetPlayerFile */

static FILE *
RewritePlayerFile (prefix, suffix)
     char *prefix, *suffix;
/* creates the player file gamedir-prefix-player-suffix */
{
  FILE *f;
  char *filename;

  filename = malloc (strlen (gamedir) + strlen (prefix) +
		     strlen (player) + strlen (suffix) + 2);
  sprintf (filename, "%s%s%s.%s", gamedir, prefix, player, suffix);
  f = fopen (filename, "wb");
  if (f == NULL)
    {
      fprintf (stderr, "Could not create `%s'\n", filename);
      exit (-1);
    }
#ifdef test
  fprintf (stderr, "Opened %s for you.\n", filename);
#endif
  return f;
}				/* RewritePlayerFile */


static manyplanets *
ReadPlanets (suffix)
     char *suffix;
/* Reads in the file "pdata"-player-"."-suffix */
{
  FILE *f;
  unsigned char *buf, *remember;
  manyplanets *newplanet;
  long i;
  short dump;

  newplanet = malloc (sizeof (manyplanets));
  f = ResetPlayerFile ("pdata", suffix);
  remember = malloc (2);
  fread (remember, 2, 1, f);
  buf = remember;
  ReadShort (newplanet->noplanets, buf);
  newplanet->planet = malloc (4 * newplanet->noplanets);
  remember = realloc (remember, sop * newplanet->noplanets);
  fread (remember, sop, newplanet->noplanets, f);
  buf = remember;
  for (i = 0; i < newplanet->noplanets; i++)
    {
      newplanet->planet[i] = malloc (sizeof (oneplanet));
#ifdef test
      fprintf (stderr, "<");
#endif
      ReadShort (newplanet->planet[i]->owner, buf);
      ReadShort (newplanet->planet[i]->nr, buf);
      memcpy (newplanet->planet[i]->fc, buf, 3);
      buf += 3;
      newplanet->planet[i]->fc[3] = (char) 0;
      ReadShort (newplanet->planet[i]->mines, buf);
      ReadShort (newplanet->planet[i]->fact, buf);
      ReadShort (newplanet->planet[i]->defense, buf);
      ReadLong (newplanet->planet[i]->mined[neutr], buf);
      ReadLong (newplanet->planet[i]->mined[trit], buf);
      ReadLong (newplanet->planet[i]->mined[dur], buf);
      ReadLong (newplanet->planet[i]->mined[molyb], buf);
      ReadLong (newplanet->planet[i]->nocol, buf);
      ReadLong (newplanet->planet[i]->supp, buf);
      ReadLong (newplanet->planet[i]->mc, buf);
      ReadLong (newplanet->planet[i]->ground[neutr], buf);
      ReadLong (newplanet->planet[i]->ground[trit], buf);
      ReadLong (newplanet->planet[i]->ground[dur], buf);
      ReadLong (newplanet->planet[i]->ground[molyb], buf);
      ReadShort (newplanet->planet[i]->density[neutr], buf);
      ReadShort (newplanet->planet[i]->density[trit], buf);
      ReadShort (newplanet->planet[i]->density[dur], buf);
      ReadShort (newplanet->planet[i]->density[molyb], buf);
      ReadShort (newplanet->planet[i]->coltax, buf);
      ReadShort (newplanet->planet[i]->nattax, buf);
      ReadShort (newplanet->planet[i]->colhappy, buf);
      ReadShort (newplanet->planet[i]->nathappy, buf);
      ReadShort (newplanet->planet[i]->natcivil, buf);
      ReadLong (newplanet->planet[i]->nonat, buf);
      ReadShort (newplanet->planet[i]->natsort, buf);
      ReadShort (dump, buf);	/* for temp */
      newplanet->planet[i]->temp = 100 - dump;
      ReadShort (newplanet->planet[i]->buildbase, buf);
#ifdef test
      fprintf (stderr, "%ld>", i);
#endif
    }
#ifdef test
  fprintf (stderr, "\n");
#endif
  /* No reason to read the DAT-signature */
  fclose (f);
  free (remember);
  return newplanet;
}				/* ReadPlanets */

static void
WriteNewPlanets ()
/* Writes newplanets to "pdata"-player-".dat"
   On the fly, some checksums are computed */
{
  FILE *f;
  unsigned long i, j, cs;
  unsigned char *buf, *remember;

  remember = malloc (2 + newplanet->noplanets * sop + 10);
  buf = remember;
  WriteShort (newplanet->noplanets, buf);
  gen.planetcs = (newplanet->noplanets >> 8) + (newplanet->noplanets & 255);
  for (i = 0; i < newplanet->noplanets; i++)
    {
#ifdef test
      fprintf (stderr, "<");
#endif
      WriteShort (newplanet->planet[i]->owner, buf);
      WriteShort (newplanet->planet[i]->nr, buf);
      memcpy (buf, newplanet->planet[i]->fc, 3);
      buf += 3;
      WriteShort (newplanet->planet[i]->mines, buf);
      WriteShort (newplanet->planet[i]->fact, buf);
      WriteShort (newplanet->planet[i]->defense, buf);
      WriteLong (newplanet->planet[i]->mined[neutr], buf);
      WriteLong (newplanet->planet[i]->mined[trit], buf);
      WriteLong (newplanet->planet[i]->mined[dur], buf);
      WriteLong (newplanet->planet[i]->mined[molyb], buf);
      WriteLong (newplanet->planet[i]->nocol, buf);
      WriteLong (newplanet->planet[i]->supp, buf);
      WriteLong (newplanet->planet[i]->mc, buf);
      WriteLong (newplanet->planet[i]->ground[neutr], buf);
      WriteLong (newplanet->planet[i]->ground[trit], buf);
      WriteLong (newplanet->planet[i]->ground[dur], buf);
      WriteLong (newplanet->planet[i]->ground[molyb], buf);
      WriteShort (newplanet->planet[i]->density[neutr], buf);
      WriteShort (newplanet->planet[i]->density[trit], buf);
      WriteShort (newplanet->planet[i]->density[dur], buf);
      WriteShort (newplanet->planet[i]->density[molyb], buf);
      WriteShort (newplanet->planet[i]->coltax, buf);
      WriteShort (newplanet->planet[i]->nattax, buf);
      WriteShort (newplanet->planet[i]->colhappy, buf);
      WriteShort (newplanet->planet[i]->nathappy, buf);
      WriteShort (newplanet->planet[i]->natcivil, buf);
      WriteLong (newplanet->planet[i]->nonat, buf);
      WriteShort (newplanet->planet[i]->natsort, buf);
      WriteShort (100 - newplanet->planet[i]->temp, buf);	/* not funny */
      WriteShort (0, buf);	/* unknown */
#ifdef test
      fprintf (stderr, "%ld>", i);
#endif
      cs = 0;
      for (j = 0; j < sop; j++)
	cs += buf[-1 - j];
      gen.planetcs += cs;
      ctrlbuf = ctrlremember + 2000 + 4 * (newplanet->planet[i]->nr - 1);	/* this sucks */
      WriteLong (cs, ctrlbuf);
    }
  gen.planetcs *= 2;
  for (i = 0; i < 10; i++)
    gen.planetcs += (gen.datsig[i] + gen.dissig[i]);
#ifdef test
  fprintf (stderr, "Planet CS= %lXd", gen.planetcs);
#endif
  memcpy (buf, gen.datsig, 10);
  /* no need for adjusting buf, since we're at the end of the buffer */
  f = RewritePlayerFile ("pdata", "dat");
  fwrite (remember, 2 + newplanet->noplanets * sop + 10, 1, f);
  fclose (f);
  free (remember);
}				/* WriteNewPlanets */


static manyships *
ReadShips (suffix)
     char *suffix;
/* Reads in all ships from "ship"-player-"."-suffix */
{
  FILE *f;
  manyships *newship;
  unsigned char *buf, *remember;
  long i;

  f = ResetPlayerFile ("ship", suffix);
  newship = malloc (sizeof (manyships));
  remember = malloc (2);
  fread (remember, 2, 1, f);
  buf = remember;
  ReadShort (newship->noships, buf);
  newship->ship = malloc (4 * newship->noships);
  remember = realloc (remember, newship->noships * sos);
  fread (remember, sos, newship->noships, f);
  buf = remember;
  for (i = 0; i < newship->noships; i++)
    {
#ifdef test
      fprintf (stderr, "<%ld", i);
#endif
      newship->ship[i] = malloc (sizeof (oneship));
      ReadShort (newship->ship[i]->nr, buf);
      ReadShort (newship->ship[i]->owner, buf);
      memcpy (newship->ship[i]->fc, buf, 3);
      buf += 3;
      newship->ship[i]->fc[3] = 0;
      ReadShort (newship->ship[i]->warp, buf);
      ReadShort (newship->ship[i]->dx, buf);
      ReadShort (newship->ship[i]->dy, buf);
      ReadShort (newship->ship[i]->x, buf);
      ReadShort (newship->ship[i]->y, buf);
      ReadShort (newship->ship[i]->engtype, buf);
      ReadShort (newship->ship[i]->hulltype, buf);
      ReadShort (newship->ship[i]->beamtype, buf);
      ReadShort (newship->ship[i]->nobeams, buf);
      ReadShort (newship->ship[i]->nobays, buf);
      ReadShort (newship->ship[i]->torptype, buf);
      ReadShort (newship->ship[i]->notorps, buf);
      ReadShort (newship->ship[i]->nolaunch, buf);
      ReadShort (newship->ship[i]->mission, buf);
      ReadShort (newship->ship[i]->enemy, buf);
      ReadShort (newship->ship[i]->towtarget, buf);
      ReadShort (newship->ship[i]->damage, buf);
      ReadShort (newship->ship[i]->crew, buf);
      ReadShort (newship->ship[i]->nocol, buf);
      memcpy (newship->ship[i]->name, buf, 20);
      buf += 20;
      newship->ship[i]->name[20] = '\0';
      ReadShort (newship->ship[i]->mineral[neutr], buf);
      ReadShort (newship->ship[i]->mineral[trit], buf);
      ReadShort (newship->ship[i]->mineral[dur], buf);
      ReadShort (newship->ship[i]->mineral[molyb], buf);
      ReadShort (newship->ship[i]->supp, buf);
      ReadShort (newship->ship[i]->fueltopl, buf);
      ReadShort (newship->ship[i]->trittopl, buf);
      ReadShort (newship->ship[i]->durtopl, buf);
      ReadShort (newship->ship[i]->molybtopl, buf);
      ReadShort (newship->ship[i]->clanstopl, buf);
      ReadShort (newship->ship[i]->supptopl, buf);
      ReadShort (newship->ship[i]->planettopl, buf);
      ReadShort (newship->ship[i]->fueltosh, buf);
      ReadShort (newship->ship[i]->trittosh, buf);
      ReadShort (newship->ship[i]->durtosh, buf);
      ReadShort (newship->ship[i]->molybtosh, buf);
      ReadShort (newship->ship[i]->clanstosh, buf);
      ReadShort (newship->ship[i]->supptosh, buf);
      ReadShort (newship->ship[i]->shiptosh, buf);
      ReadShort (newship->ship[i]->inttarget, buf);
      ReadShort (newship->ship[i]->mc, buf);
#ifdef test
      fprintf (stderr, ">");
#endif
    }
  /* No reason to read the DAT-signature */
  fclose (f);
  free (remember);
  return newship;
}				/* ReadShips */

static void
WriteNewShips ()
/* Writes newship to the file "ship"-player-".dat"
   On the fly, some checksums are computed */
{
  FILE *f;
  unsigned long i, j, cs;
  unsigned char *buf, *remember;

  remember = malloc (2 + sos * newship->noships + 10);
  gen.shipcs = (newship->noships >> 8) + (newship->noships & 255);
  buf = remember;
  WriteShort (newship->noships, buf);
  for (i = 0; i < newship->noships; i++)
    {
#ifdef test
      fprintf (stderr, "<%ld", i);
#endif
      WriteShort (newship->ship[i]->nr, buf);
      WriteShort (newship->ship[i]->owner, buf);
      memcpy (buf, newship->ship[i]->fc, 3);
      buf += 3;
      WriteShort (newship->ship[i]->warp, buf);
      WriteShort (newship->ship[i]->dx, buf);
      WriteShort (newship->ship[i]->dy, buf);
      WriteShort (newship->ship[i]->x, buf);
      WriteShort (newship->ship[i]->y, buf);
      WriteShort (newship->ship[i]->engtype, buf);
      WriteShort (newship->ship[i]->hulltype, buf);
      WriteShort (newship->ship[i]->beamtype, buf);
      WriteShort (newship->ship[i]->nobeams, buf);
      WriteShort (newship->ship[i]->nobays, buf);
      WriteShort (newship->ship[i]->torptype, buf);
      WriteShort (newship->ship[i]->notorps, buf);
      WriteShort (newship->ship[i]->nolaunch, buf);
      WriteShort (newship->ship[i]->mission, buf);
      WriteShort (newship->ship[i]->enemy, buf);
      WriteShort (newship->ship[i]->towtarget, buf);
      WriteShort (newship->ship[i]->damage, buf);
      WriteShort (newship->ship[i]->crew, buf);
      WriteShort (newship->ship[i]->nocol, buf);
      memcpy (buf, newship->ship[i]->name, 20);
      buf += 20;
      WriteShort (newship->ship[i]->mineral[neutr], buf);
      WriteShort (newship->ship[i]->mineral[trit], buf);
      WriteShort (newship->ship[i]->mineral[dur], buf);
      WriteShort (newship->ship[i]->mineral[molyb], buf);
      WriteShort (newship->ship[i]->supp, buf);
      WriteShort (newship->ship[i]->fueltopl, buf);
      WriteShort (newship->ship[i]->trittopl, buf);
      WriteShort (newship->ship[i]->durtopl, buf);
      WriteShort (newship->ship[i]->molybtopl, buf);
      WriteShort (newship->ship[i]->clanstopl, buf);
      WriteShort (newship->ship[i]->supptopl, buf);
      WriteShort (newship->ship[i]->planettopl, buf);
      WriteShort (newship->ship[i]->fueltosh, buf);
      WriteShort (newship->ship[i]->trittosh, buf);
      WriteShort (newship->ship[i]->durtosh, buf);
      WriteShort (newship->ship[i]->molybtosh, buf);
      WriteShort (newship->ship[i]->clanstosh, buf);
      WriteShort (newship->ship[i]->supptosh, buf);
      WriteShort (newship->ship[i]->shiptosh, buf);
      WriteShort (newship->ship[i]->inttarget, buf);
      WriteShort (newship->ship[i]->mc, buf);
#ifdef test
      fprintf (stderr, ">");
#endif
      cs = 0;
      for (j = 0; j < sos; j++)
	cs += buf[-1 - j];
      gen.shipcs += cs;
      ctrlbuf = ctrlremember + 4 * (newship->ship[i]->nr - 1);	/* this sucks */
      WriteLong (cs, ctrlbuf);
    }
  gen.shipcs *= 2;
  for (i = 0; i < 10; i++)
    gen.shipcs += (gen.datsig[i] + gen.dissig[i]);
#ifdef test
  fprintf (stderr, "Ship CS= %lXd", gen.shipcs);
#endif
  memcpy (buf, gen.datsig, 10);
  /* no need for adjusting buf, since we're at the end of the buffer */
  f = RewritePlayerFile ("ship", "dat");
  fwrite (remember, 2 + sos * newship->noships + 10, 1, f);
  fclose (f);
  free (remember);
}				/* WriteNewShips */


static manybases *
ReadBases (suffix)
     char *suffix;
/* Reads in the file "bdata"-player-"."-suffix */
{
  FILE *f;
  manybases *newbase;
  unsigned char *buf, *remember;
  long i, j;
  short dump;

  f = ResetPlayerFile ("bdata", suffix);
  newbase = malloc (sizeof (manybases));
  remember = malloc (2);
  fread (remember, 2, 1, f);
  buf = remember;
  ReadShort (newbase->nobases, buf);
  newbase->base = malloc (4 * newbase->nobases);
  remember = realloc (remember, newbase->nobases * 156);
  fread (remember, 156, newbase->nobases, f);
  buf = remember;
  for (i = 0; i < newbase->nobases; i++)
    {
#ifdef test
      fprintf (stderr, "<");
#endif
      newbase->base[i] = malloc (sizeof (onebase));
      ReadShort (newbase->base[i]->nr, buf);
#ifdef test
      fprintf (stderr, "%ld,%d", i, newbase->base[i]->nr);
#endif
      ReadShort (newbase->base[i]->owner, buf);
      ReadShort (newbase->base[i]->defense, buf);
      ReadShort (newbase->base[i]->damage, buf);
      ReadShort (newbase->base[i]->engtech, buf);
      ReadShort (newbase->base[i]->hulltech, buf);
      ReadShort (newbase->base[i]->beamtech, buf);
      ReadShort (newbase->base[i]->torptech, buf);
      for (j = 0; j < noe; j++)
	{
	  ReadShort (newbase->base[i]->noengines[j], buf);
	}
      for (j = 0; j < 20; j++)
	{
	  ReadShort (newbase->base[i]->nohulls[j], buf);
	}
      for (j = 0; j < nob; j++)
	{
	  ReadShort (newbase->base[i]->nobeams[j], buf);
	}
      for (j = 0; j < notp; j++)
	{
	  ReadShort (newbase->base[i]->nolaunch[j], buf);
	}
      for (j = 0; j < notp; j++)
	{
	  ReadShort (newbase->base[i]->notorps[j], buf);
	}
      ReadShort (newbase->base[i]->nofighters, buf);
      ReadShort (newbase->base[i]->target, buf);
      ReadShort (newbase->base[i]->fixrec, buf);
      ReadShort (newbase->base[i]->mission, buf);
      ReadShort (newbase->base[i]->bhulltype, buf);
      ReadShort (newbase->base[i]->bengtype, buf);
      ReadShort (newbase->base[i]->bbeamtype, buf);
      ReadShort (newbase->base[i]->bnobeams, buf);
      ReadShort (newbase->base[i]->btorptype, buf);
      ReadShort (newbase->base[i]->bnolaunch, buf);
      ReadShort (dump, buf);
#ifdef test
      fprintf (stderr, ">");
#endif
    }
  /* No reason to read the DAT-signature */
  fclose (f);
  free (remember);
  return newbase;
}				/* ReadBases */

static void
WriteNewBases ()
/* Writes newbase to the file "bdata"-player-".dat" */
{
  FILE *f;
  unsigned long i, j, cs;
  unsigned char *buf, *remember;

  remember = malloc (2 + sob * newbase->nobases + 10);
  gen.basecs = (newbase->nobases >> 8) + (newbase->nobases & 255);
#ifdef test
  fprintf (stderr, "bcs:1:%lX, ", gen.basecs);
#endif
  buf = remember;
  WriteShort (newbase->nobases, buf);
  for (i = 0; i < newbase->nobases; i++)
    {
#ifdef test
      fprintf (stderr, "<%ld", i);
#endif
      WriteShort (newbase->base[i]->nr, buf);
      WriteShort (newbase->base[i]->owner, buf);
      WriteShort (newbase->base[i]->defense, buf);
      WriteShort (newbase->base[i]->damage, buf);
      WriteShort (newbase->base[i]->engtech, buf);
      WriteShort (newbase->base[i]->hulltech, buf);
      WriteShort (newbase->base[i]->beamtech, buf);
      WriteShort (newbase->base[i]->torptech, buf);
      for (j = 0; j < noe; j++)
	{
	  WriteShort (newbase->base[i]->noengines[j], buf);
	}
      for (j = 0; j < 20; j++)
	{
	  WriteShort (newbase->base[i]->nohulls[j], buf);
	}
      for (j = 0; j < nob; j++)
	{
	  WriteShort (newbase->base[i]->nobeams[j], buf);
	}
      for (j = 0; j < notp; j++)
	{
	  WriteShort (newbase->base[i]->nolaunch[j], buf);
	}
      for (j = 0; j < notp; j++)
	{
	  WriteShort (newbase->base[i]->notorps[j], buf);
	}
      WriteShort (newbase->base[i]->nofighters, buf);
      WriteShort (newbase->base[i]->target, buf);
      WriteShort (newbase->base[i]->fixrec, buf);
      WriteShort (newbase->base[i]->mission, buf);
      WriteShort (newbase->base[i]->bhulltype, buf);
      WriteShort (newbase->base[i]->bengtype, buf);
      WriteShort (newbase->base[i]->bbeamtype, buf);
      WriteShort (newbase->base[i]->bnobeams, buf);
      WriteShort (newbase->base[i]->btorptype, buf);
      WriteShort (newbase->base[i]->bnolaunch, buf);
      WriteShort (0, buf);
#ifdef test
      fprintf (stderr, ">");
#endif
      cs = 0;
      for (j = 0; j < sob; j++)
	cs += buf[-1 - j];
      gen.basecs += cs;
#ifdef test
      fprintf (stderr, "bcs:2:%lX, ", gen.basecs);
#endif
      ctrlbuf = ctrlremember + 4000 + 4 * (newbase->base[i]->nr - 1);	/* this sucks */
      WriteLong (cs, ctrlbuf);
    }
  gen.basecs *= 2;
#ifdef test
  fprintf (stderr, "bcs:3:%lX, ", gen.basecs);
#endif
  for (i = 0; i < 10; i++)
    gen.basecs += (gen.datsig[i] + gen.dissig[i]);
#ifdef test
  fprintf (stderr, "Base CS= %lX ", gen.basecs);
#endif
  memcpy (buf, gen.datsig, 10);
  /* no need for adjusting buf, since we're at the end of the buffer */
  f = RewritePlayerFile ("bdata", "dat");
  fwrite (remember, 2 + sob * newbase->nobases + 10, 1, f);
  fclose (f);
  free (remember);
}				/* WriteNewBases */


static manymess *
ReadMess (prefix)
     char *prefix;
/* Reads in all messages from the file prefix-player-".dat"
   The place of the message is forgotten */
{
  FILE *f;
  manymess *message;
  unsigned char *buf, *remember;
  long dump, i, j, size;

  f = ResetPlayerFile (prefix, "dat");
  message = malloc (sizeof (manymess));
  remember = malloc (2);
  fread (remember, 2, 1, f);
  buf = remember;
  ReadShort (message->nomess, buf);
  message->mess = malloc (4 * message->nomess);
#ifdef test
  fprintf (stderr, "Reading %u messages ", message->nomess);
#endif
  remember = realloc (remember, 6 * message->nomess);
  fread (remember, 6, message->nomess, f);
  buf = remember;
  size = 0;
  for (i = 0; i < message->nomess; i++)
    {
      message->mess[i] = malloc (sizeof (onemess));
      ReadLong (dump, buf);	/* place of message in MDATAx.DAT irrelevant */
      ReadShort (message->mess[i]->messlen, buf);
      size += message->mess[i]->messlen;
#ifdef test
      fprintf (stderr, "[%d]", message->mess[i]->messlen);
#endif
    }
  remember = realloc (remember, size);
#ifdef test
  fprintf (stderr, "\n Reading messages (local) from %ld in file\n",
	   ftell (f));
#endif
  fread (remember, size, 1, f);
  buf = remember;
  for (i = 0; i < message->nomess; i++)
    {
      message->mess[i]->message = malloc (message->mess[i]->messlen + 1);
      strncpy (message->mess[i]->message, buf, message->mess[i]->messlen);
      message->mess[i]->message[message->mess[i]->messlen] = 0;
      for (j = 0; j < message->mess[i]->messlen; j++)
	message->mess[i]->message[j] -= 13;
#ifdef test
      fprintf (stderr, "%c%c%c", buf[1], buf[2], buf[3]);
#endif
      buf += message->mess[i]->messlen;
#ifdef test
      fprintf (stderr, "(%ld)", i);
#endif
    }
#ifdef test
  fprintf (stderr, " done!\n");
#endif
  fclose (f);
  free (remember);
  return message;
}				/* ReadMess */

static manymess *
ReadNewMess (prefix)
     char *prefix;
/* Reads in all messages from the file prefix-player-".dat"
   The place of the message is forgotten */
{
  FILE *f;
  manymess *message;
  unsigned char *buf, *remember;
  long *place;
  long i, j, size;

  f = ResetPlayerFile (prefix, "dat");
  fseek (f, 0, SEEK_END);
  size = ftell (f);
  fseek (f, 0, SEEK_SET);
  remember = malloc (size);
  fread (remember, size, 1, f);
  message = malloc (sizeof (manymess));
  buf = remember;
  ReadShort (message->nomess, buf);
  message->mess = malloc (4 * message->nomess);
#ifdef test
  fprintf (stderr, "Reading %u messages ", message->nomess);
#endif
  place = calloc (message->nomess, 4);
  for (i = 0; i < message->nomess; i++)
    {
      message->mess[i] = malloc (sizeof (onemess));
      ReadLong (place[i], buf);	/* unfortunately we need to know */
      ReadShort (message->mess[i]->messlen, buf);
      ReadShort (message->mess[i]->from, buf);
      ReadShort (message->mess[i]->to, buf);
#ifdef test
      fprintf (stderr, "[%d]", message->mess[i]->messlen);
#endif
    }
#ifdef test
  fprintf (stderr, "\n Reading messages (local) from %ld in file\n",
	   ftell (f));
#endif
  for (i = 0; i < message->nomess; i++)
    {
      buf = remember + place[i] - 1;
      message->mess[i]->message = malloc (message->mess[i]->messlen + 1);
      strncpy (message->mess[i]->message, buf, message->mess[i]->messlen);
      message->mess[i]->message[message->mess[i]->messlen] = 0;
      for (j = 0; j < message->mess[i]->messlen; j++)
	message->mess[i]->message[j] -= 13;
      message->mess[i]->nr = i + 1;
#ifdef test
      fprintf (stderr, "%c%c", buf[1], buf[2]);
      fprintf (stderr, "%ld ", i);
#endif
    }
#ifdef test
  fprintf (stderr, " done!\n");
#endif
  fclose (f);
  free (place);
  free (remember);
  return message;
}				/* ReadMess */


static void
WriteNewMess ()
/* Writes all new messages to "mess"-player-".dat" */
{
  FILE *f;
  unsigned char *buf, *remember;
  long i, j, total = 0;

  for (i = 0; i < newmess->nomess; i++)
    total += newmess->mess[i]->messlen;
  remember = malloc (2 + 10 * newmess->nomess + total);
  buf = remember;
  WriteShort (newmess->nomess, buf);
  total = 0;
  for (i = 0; i < newmess->nomess; i++)
    {
      WriteLong (2 + 10 * newmess->nomess + total, buf);
      WriteShort (newmess->mess[i]->messlen, buf);
      WriteShort (newmess->mess[i]->from, buf);
      WriteShort (newmess->mess[i]->to, buf);
      total += newmess->mess[i]->messlen;
    }
  for (i = 0; i < newmess->nomess; i++)
    {
      memcpy (buf, newmess->mess[i]->message, newmess->mess[i]->messlen);
      for (j = 0; j < newmess->mess[i]->messlen; j++)
	buf[j] += 13;
      buf += newmess->mess[i]->messlen;
    }
  f = RewritePlayerFile ("mess", "dat");
  fwrite (remember, 2 + 10 * newmess->nomess + total, 1, f);
  fclose (f);
  free (remember);
}				/* WriteNewMess */

static void
ReadGen ()
/* Reads in the file "gen"-player-".dat"
   which contains scores, sig's and some other stuff */
{
  FILE *f;
  unsigned char *buf, *remember;
  long i;

  f = ResetPlayerFile ("gen", "dat");
  remember = malloc (157);
  fread (remember, 157, 1, f);
  buf = remember;
  memcpy (gen.timestamp, buf, 18);
  buf += 18;
  gen.timestamp[18] = 0;
  for (i = 0; i < 11; i++)
    {
      ReadShort (gen.scores[i].planets, buf);
      ReadShort (gen.scores[i].bases, buf);
      ReadShort (gen.scores[i].capitals, buf);
      ReadShort (gen.scores[i].freighters, buf);
      gen.scores[i].total = 10 * gen.scores[i].planets +
	120 * gen.scores[i].bases +
	10 * gen.scores[i].capitals + gen.scores[i].freighters;
    }
  ReadShort (gen.player, buf);
  memcpy (gen.weirdsig, buf, 10);
  buf += 10;
  gen.weirdsig[10] = 0;
  memcpy (gen.dissig, buf, 10);
  buf += 11;
  gen.dissig[10] = 0;
  gen.datsig[10] = 0;
  for (i = 0; i < 10; i++)
    gen.datsig[i] = gen.dissig[i] + i + 1;
  ReadLong (gen.shipcs, buf);
  ReadLong (gen.planetcs, buf);
  ReadLong (gen.basecs, buf);
  ReadShort (gen.changepw, buf);
  memcpy (gen.newpw, buf, 10);
  buf += 10;
  gen.newpw[10] = 0;
  ReadShort (gen.turnnr, buf);
  ReadShort (gen.gameid, buf);
  fclose (f);
  free (remember);
}				/* ReadGen */

static void
WriteGen ()
/* Writes some nasty information to "gen"-player-".dat" */
{
  FILE *f;
  unsigned char *buf, *remember;
  long i;

  remember = malloc (157);
  buf = remember;
  memcpy (buf, gen.timestamp, 18);
  buf += 18;
  for (i = 0; i < 11; i++)
    {
      WriteShort (gen.scores[i].planets, buf);
      WriteShort (gen.scores[i].bases, buf);
      WriteShort (gen.scores[i].capitals, buf);
      WriteShort (gen.scores[i].freighters, buf);
    }
  WriteShort (gen.player, buf);
  memcpy (buf, gen.weirdsig, 10);
  buf += 10;
  memcpy (buf, gen.dissig, 11);	/* Watch this one; I MEAN 11 (one dummy byte) */
  buf += 11;
  WriteLong (gen.shipcs, buf);
  WriteLong (gen.planetcs, buf);
  WriteLong (gen.basecs, buf);
  /* Write new password and 2 other bytes (HELP!) */
  WriteLong (0, buf);
  WriteLong (0, buf);
  WriteLong (0, buf);
  WriteShort (gen.turnnr, buf);
  WriteShort (gen.gameid, buf);

  f = RewritePlayerFile ("gen", "dat");
  fwrite (remember, 157, 1, f);
  fclose (f);
  free (remember);
}				/* WriteGen */

void
PlayerioInit ()
/* Reads in all player data */
{
  newplanet = ReadPlanets ("dat");
  oldplanet = ReadPlanets ("dis");
  newship = ReadShips ("dat");
  oldship = ReadShips ("dis");
  newbase = ReadBases ("dat");
  oldbase = ReadBases ("dis");
  newmess = ReadNewMess ("mess35");
  oldmess = ReadMess ("mdata");
  ReadGen ();
}				/* PlayerioInit */

void
PlayerioDone ()
/* Writes all player data */
{
  char *ctrlname;
  long i;

  ctrlremember = malloc (6002);
  for (i = 0; i < 6002; i++)
    ctrlremember[i] = 'K';
  WriteNewPlanets ();		/* determines gen.planetcs, writes in ctrlremember */
  WriteNewShips ();		/* determines gen.shipcs, writes in ctrlremember */
  WriteNewBases ();		/* determines gen.basecs, writes in ctrlremember */
  WriteNewMess ();
  WriteGen ();
  ctrlname = malloc (strlen (gamedir) + strlen ("control.dat") + 1);
  sprintf (ctrlname, "%s%s", gamedir, "control.dat");
  ctrl = fopen (ctrlname, "wb");
  fwrite (ctrlremember, 6002, 1, ctrl);
  fclose (ctrl);
  free (ctrlname);
  free (ctrlremember);
/* free(newplanet);
  free(oldplanet);     What
  free(newship);       about
  free(oldship);       all
  free(newbase);       sub-pointers
  free(oldbase);       ?!?
  free(newmess);
  free(oldmess); */
}				/* PlayerioDone */
