/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.3  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

/* File: kmkturn.c
 *
 * K-MakeTurn is a newer and faster version for Tim Wisseman's VGA-Planets.
 * Distillates a ``PLAYER??.TRN'' from *.DAT and *.DIS
 *
 * Author: Kero van Gelder
 * First version: 3 XII 1995
 * Last revision: 1 VI 1998
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vp_maketurn_global.h"
#include "vp_maketurn_playerio.h"
#include "vp_maketurn_kmkturn.h"

#define version "1.3a"
/* Size of winplan trailer */
#define sowp 316

unsigned short inornot[11];	/* Player X in or not? (init.tmp) */
unsigned char *trnbuf, *trnremember[11], *fizzremember;
unsigned long size[11], cs[11];

int MakeTurn (short p);
void WriteTurns (int race, char *trn_dir);
FILE *ResetPlayerFile (char *prefix, char *nr, char *suffix);
long PerformCommands (short p);

static void encode_regstring(char* out, int index_in);
static const unsigned long magic_numbers[] = {
    1585242373,
    458484639, 1702713875, 2131768570, 943874411, 1531045611,
    622829488, 660770929, 473301358, 1868910709, 439267666, 1259778247,
    187160419, 205520992, 1162432602, 2048525217, 663275107, 1945076761,
    1912495862, 372583676, 2110506768, 972564220, 1627953855, 1696231547,
    1825551059, 690525357, 1425805634, 1273009202, 1643106825, 1033503714,
    1773067018, 1444056607, 841306782, 1311137219, 472310692, 1658228604,
    214806212, 1638334074, 870981249, 1438230436, 1722981495, 383237037,
    1014208183, 1950729749, 1381216466, 1149684732, 1475271197, 990158844,
    659846975, 131158828, 1269952134, 1929873739, 149943298, 94038386,
    1639179540, 519578396, 649680371, 2139806121, 48126387, 1820750093,
    2002158429, 834011058, 127330762, 1341047341, 45011247, 1210785240,
    102394054, 1033444233, 1452787209, 1636216880, 2001004855, 196571844,
    768753436, 1715639759, 9036553, 550413001, 1195957868, 566073290,
    1386247611, 725117880, 637842515, 782679024, 614960412, 1259473924,
    710893647, 137748852, 808495109, 1174108532, 2141228605, 1298353301,
    1989952843, 607318838, 1868217839, 2046567417, 1297732528, 886928938,
    533473933, 667670866, 1241783877, 1634258231, 1529167548, 1048674755,
    108553737, 442206379, 1427828321, 178793040, 57025576, 1886069810,
    1452681265, 392872129, 1749094387, 1931946557, 610131601, 497923660,
    800378618, 833787008, 1047995126, 867114247, 108316439, 1889137816,
    1566927898, 1606954817, 2129997452, 176508207, 1504084876, 781656333,
    1575411145, 952282888, 1920012969, 725392878, 442033280, 2055008888,
    125996860, 648896510, 1271579722, 734745843, 457213090, 101154514,
    1253209494, 649313503, 665663012, 1284757233, 526008074, 1128559135,
    708376521, 1888247159, 637430572, 1297014774, 84473586, 1938406737,
    278055502, 2082329430, 784004382, 886858342, 487519681, 979889529,
    2118032563, 376523135, 2037399162, 494383465, 1744352698, 533745717,
    752066469, 1518627158, 347571084, 1270232880, 460005993, 1754379254,
    1431354806, 103810045, 676346171, 948969734, 1270441550, 562587328,
    305781542, 48494333, 263492952, 1020466270, 190108896, 1009887493,
    1263640424, 2136294797, 951195719, 1154885409, 533815976, 707619918,
    1293089160, 1565561820, 1424862457, 2024541688, 1849356050, 804648133,
    1041775421, 1752468846, 2051572786, 749910457, 1708669854, 1592915884,
    1123095599, 1460717743, 1948843781, 1082061162, 1152635918,
    1881839283, 760734026, 1910315568, 1258782923, 2051380841, 1725205147,
    585278536, 1106219491, 444629203, 1099824661, 734821072, 2025557656,
    657473172, 255537853, 291983710, 286553905, 42517818, 670349676,
    870581336, 1127381655, 1839475352, 632654867, 547547534, 1471914002,
    1512583684, 890892484, 1857789058, 1587065657, 709203658, 1447182906,
    950862839, 1854232374, 1589606089, 18301536, 700074959, 415606342,
    1405416566, 1289157530, 1227135268, 340764183, 419122630, 1884968096,
    326246210, 540566661, 853062096, 1975701318, 1492562570, 1963382636,
    1075710563, 758982437, 2060895641, 1152739182, 1371354866, 800770398,
    1598945131, 79563287, 694771023, 1704620086, 248109047, 95128540,
    1062172273, 810095152, 2013227291, 1998220334, 1498632230, 1836447618,
    217773428, 986641406, 603013591, 1230144401, 1075426659, 1746848829,
    817629711, 186988432, 1484074762, 843442591, 776096924, 1024866700,
    2027642148, 1049701698, 247896996, 387855251, 857506062, 165410039,
    1748384075, 1958279260, 1593211160, 1998805368, 1633675306,
    2048559498, 1569149953, 1404385053, 784606841, 1589733669, 373455454,
    909199500, 1312922206, 408034973, 997233876, 963117498, 742951874,
    10752697, 574771227, 794412355, 92609016, 392712605, 964282276,
    1732686549
};

static void 
encode_regstring(char* out, int index_in)
{
  int i;
  long d;
  unsigned char *f;
  char c, y;

  f = fizzremember + index_in;
  for (i = 1; i <= 25; ++i) {
    ReadLong(d, f);
    c = d / (13 * i);
    y = 13 * i;  /* anything does */
    out[0] = c ^ y;
    out[25] = y;
    out += 1;
    index_in += 4;
  }
}

FILE *
ResetPlayerFile (prefix, nr, suffix)
     char *prefix, *nr, *suffix;
{
  char *filename;
  FILE *f;

  filename =
    malloc (strlen (gamedir) + strlen (prefix) + strlen (nr) + 1 +
	    strlen (suffix) + 1);
  sprintf (filename, "%s%s%s.%s", gamedir, prefix, nr, suffix);
  f = fopen (filename, "rb");
  if (f == NULL)
    {
/* #ifdef test */
/*       fprintf (stderr, "No file %s, trying capital version...\n", filename); */
/* #endif */
/*       StrToUpper (prefix); */
/*       StrToUpper (suffix); */
/*       sprintf (filename, "%s%s%s.%s", gamedir, prefix, nr, suffix); */
/*       f = fopen (filename, "rb"); */
/*       if (f == NULL) */
/* 	{ */
	  fprintf (stderr, "No file %s available!\n\n", filename);
	  exit (-1);
/* 	} */
    }
#ifdef test
  fprintf (stderr, "Opened file %s\n", filename);
#endif
  return f;
}

#define NewCommand(sizeofcommand,whatcommand) { \
  commptr=realloc(commptr,sizeof(long)*(nocommands+1));\
  commptr[nocommands]=commsize;\
  nocommands++;\
  commremember=realloc(commremember,commsize+sizeofcommand);\
  commbuf=commremember;\
  commbuf+=commsize;\
  WriteShort(whatcommand,commbuf);\
  commsize+=sizeofcommand;\
}

long
PerformCommands (p)
     short p;
{
  long nocommands = 0, commsize = 0, replacement;
  unsigned long *commptr = NULL;
  unsigned char *commremember = NULL, *commbuf, *trnbuf;
  long i, j;
  oneship *olds, *news;
  oneplanet *oldp, *newp;
  onebase *oldb, *newb;
  boolean build;

  /* commands for all ships */
  fprintf (stdout, "%3d ships found\n", newship->noships);
  for (i = 0; i < oldship->noships; i++)
    {
      olds = oldship->ship[i];
      news = newship->ship[i];
#ifdef test
      fprintf (stderr, "%ld", i % 10);
#endif
      if (strncmp (olds->fc, news->fc, 3))
	{
	  NewCommand (7, 1);
	  WriteShort (news->nr, commbuf);
	  memcpy (commbuf, news->fc, 3);
	  commbuf += 3;
	}
      if (olds->warp != news->warp)
	{
	  NewCommand (6, 2);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->warp, commbuf);
	}
      if ((olds->dx != news->dx) || (olds->dy != news->dy))
	{
	  NewCommand (8, 3);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->dx, commbuf);
	  WriteShort (news->dy, commbuf);
	}
      if (olds->mission != news->mission)
	{
	  NewCommand (6, 4);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->mission, commbuf);
	}
      if (olds->enemy != news->enemy)
	{
	  NewCommand (6, 5);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->enemy, commbuf);
	}
      if (olds->towtarget != news->towtarget)
	{
	  NewCommand (6, 6);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->towtarget, commbuf);
	}
      if (olds->inttarget != news->inttarget)
	{
	  NewCommand (6, 10);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->inttarget, commbuf);
	}
      if (strncmp (olds->name, news->name, 20))
	{
	  NewCommand (24, 7);
	  WriteShort (news->nr, commbuf);
	  memcpy (commbuf, news->name, 20);
	  commbuf += 20;
	}
      if ((olds->planettopl != news->planettopl) ||
	  (olds->fueltopl != news->fueltopl)
	  || (olds->trittopl != news->trittopl)
	  || (olds->durtopl != news->durtopl)
	  || (olds->molybtopl != news->molybtopl)
	  || (olds->clanstopl != news->clanstopl)
	  || (olds->supptopl != news->supptopl))
	{
	  NewCommand (18, 8);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->fueltopl, commbuf);
	  WriteShort (news->trittopl, commbuf);
	  WriteShort (news->durtopl, commbuf);
	  WriteShort (news->molybtopl, commbuf);
	  WriteShort (news->clanstopl, commbuf);
	  WriteShort (news->supptopl, commbuf);
	  WriteShort (news->planettopl, commbuf);
	}
      if ((olds->shiptosh != news->shiptosh) ||
	  (olds->fueltosh != news->fueltosh)
	  || (olds->trittosh != news->trittosh)
	  || (olds->durtosh != news->durtosh)
	  || (olds->molybtosh != news->molybtosh)
	  || (olds->clanstosh != news->clanstosh)
	  || (olds->supptosh != news->supptosh))
	{
	  NewCommand (18, 9);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->fueltosh, commbuf);
	  WriteShort (news->trittosh, commbuf);
	  WriteShort (news->durtosh, commbuf);
	  WriteShort (news->molybtosh, commbuf);
	  WriteShort (news->clanstosh, commbuf);
	  WriteShort (news->supptosh, commbuf);
	  WriteShort (news->shiptosh, commbuf);
	}
      if (olds->mineral[neutr] != news->mineral[neutr])
	{
	  NewCommand (6, 11);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->mineral[neutr], commbuf);
	}
      if (olds->mineral[trit] != news->mineral[trit])
	{
	  NewCommand (6, 12);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->mineral[trit], commbuf);
	}
      if (olds->mineral[dur] != news->mineral[dur])
	{
	  NewCommand (6, 13);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->mineral[dur], commbuf);
	}
      if (olds->mineral[molyb] != news->mineral[molyb])
	{
	  NewCommand (6, 14);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->mineral[molyb], commbuf);
	}
      if (olds->supp != news->supp)
	{
	  NewCommand (6, 15);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->supp, commbuf);
	}
      if (olds->nocol != news->nocol)
	{
	  NewCommand (6, 16);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->nocol, commbuf);
	}
      if (olds->notorps != news->notorps)
	{
	  NewCommand (6, 17);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->notorps, commbuf);
	}
      if (olds->mc != news->mc)
	{
	  NewCommand (6, 18);
	  WriteShort (news->nr, commbuf);
	  WriteShort (news->mc, commbuf);
	}
    }

  /* commands for all planets */
  fprintf (stdout, "%3d planets found\n", newplanet->noplanets);
  for (i = 0; i < newplanet->noplanets; i++)
    {
      oldp = oldplanet->planet[i];
      newp = newplanet->planet[i];
#ifdef test
      fprintf (stderr, "%ld", i % 10);
#endif
      if (strncmp (oldp->fc, newp->fc, 3))
	{
	  NewCommand (7, 21);
	  WriteShort (newp->nr, commbuf);
	  memcpy (commbuf, newp->fc, 3);
	  commbuf += 3;
	}
      if (oldp->mines != newp->mines)
	{
	  NewCommand (6, 22);
	  WriteShort (newp->nr, commbuf);
	  WriteShort (newp->mines, commbuf);
	}
      if (oldp->fact != newp->fact)
	{
	  NewCommand (6, 23);
	  WriteShort (newp->nr, commbuf);
	  WriteShort (newp->fact, commbuf);
	}
      if (oldp->defense != newp->defense)
	{
	  NewCommand (6, 24);
	  WriteShort (newp->nr, commbuf);
	  WriteShort (newp->defense, commbuf);
	}
      if (oldp->mined[neutr] != newp->mined[neutr])
	{
	  NewCommand (8, 25);
	  WriteShort (newp->nr, commbuf);
	  WriteLong (newp->mined[neutr], commbuf);
	}
      if (oldp->mined[trit] != newp->mined[trit])
	{
	  NewCommand (8, 26);
	  WriteShort (newp->nr, commbuf);
	  WriteLong (newp->mined[trit], commbuf);
	}
      if (oldp->mined[dur] != newp->mined[dur])
	{
	  NewCommand (8, 27);
	  WriteShort (newp->nr, commbuf);
	  WriteLong (newp->mined[dur], commbuf);
	}
      if (oldp->mined[molyb] != newp->mined[molyb])
	{
	  NewCommand (8, 28);
	  WriteShort (newp->nr, commbuf);
	  WriteLong (newp->mined[molyb], commbuf);
	}
      if (oldp->nocol != newp->nocol)
	{
	  NewCommand (8, 29);
	  WriteShort (newp->nr, commbuf);
	  WriteLong (newp->nocol, commbuf);
	}
      if (oldp->supp != newp->supp)
	{
	  NewCommand (8, 30);
	  WriteShort (newp->nr, commbuf);
	  WriteLong (newp->supp, commbuf);
	}
      if (oldp->mc != newp->mc)
	{
	  NewCommand (8, 31);
	  WriteShort (newp->nr, commbuf);
	  WriteLong (newp->mc, commbuf);
	}
      if (oldp->coltax != newp->coltax)
	{
	  NewCommand (6, 32);
	  WriteShort (newp->nr, commbuf);
	  WriteShort (newp->coltax, commbuf);
	}
      if (oldp->nattax != newp->nattax)
	{
	  NewCommand (6, 33);
	  WriteShort (newp->nr, commbuf);
	  WriteShort (newp->nattax, commbuf);
	}
      if (newp->buildbase)
	{
	  NewCommand (4, 34);
	  WriteShort (newp->nr, commbuf);
	}
    }

  /* commands for all bases */
  fprintf (stdout, "%3d bases found\n", newbase->nobases);
  for (i = 0; i < newbase->nobases; i++)
    {
      oldb = oldbase->base[i];
      newb = newbase->base[i];
#ifdef test
      fprintf (stderr, "%ld", i % 10);
#endif
      if (oldb->defense != newb->defense)
	{
	  NewCommand (6, 40);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->defense, commbuf);
	}
      if (oldb->engtech != newb->engtech)
	{
	  NewCommand (6, 41);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->engtech, commbuf);
	}
      if (oldb->hulltech != newb->hulltech)
	{
	  NewCommand (6, 42);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->hulltech, commbuf);
	}
      if (oldb->beamtech != newb->beamtech)
	{
	  NewCommand (6, 43);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->beamtech, commbuf);
	}
      build = false;
      for (j = 0; j < noe; j++)
	build += (oldb->noengines[j] != newb->noengines[j]);
      if (build)
	{
	  NewCommand (22, 44);
	  WriteShort (newb->nr, commbuf);
	  for (j = 0; j < noe; j++)
	    {
	      WriteShort (newb->noengines[j], commbuf);
	    }
	}
      build = false;
      for (j = 0; j < 20; j++)
	build += (oldb->nohulls[j] != newb->nohulls[j]);
      if (build)
	{
	  NewCommand (44, 45);
	  WriteShort (newb->nr, commbuf);
	  for (j = 0; j < 20; j++)
	    {
	      WriteShort (newb->nohulls[j], commbuf);
	    }
	}
      build = false;
      for (j = 0; j < nob; j++)
	build += (oldb->nobeams[j] != newb->nobeams[j]);
      if (build)
	{
	  NewCommand (24, 46);
	  WriteShort (newb->nr, commbuf);
	  for (j = 0; j < nob; j++)
	    {
	      WriteShort (newb->nobeams[j], commbuf);
	    }
	}
      build = false;
      for (j = 0; j < notp; j++)
	build += (oldb->nolaunch[j] != newb->nolaunch[j]);
      if (build)
	{
	  NewCommand (24, 47);
	  WriteShort (newb->nr, commbuf);
	  for (j = 0; j < notp; j++)
	    {
	      WriteShort (newb->nolaunch[j], commbuf);
	    }
	}
      build = false;
      for (j = 0; j < notp; j++)
	build += (oldb->notorps[j] != newb->notorps[j]);
      if (build)
	{
	  NewCommand (24, 48);
	  WriteShort (newb->nr, commbuf);
	  for (j = 0; j < notp; j++)
	    {
	      WriteShort (newb->notorps[j], commbuf);
	    }
	}
      if (oldb->nofighters != newb->nofighters)
	{
	  NewCommand (6, 49);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->nofighters, commbuf);
	}
      if (oldb->target != newb->target)
	{
	  NewCommand (6, 50);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->target, commbuf);
	}
      if (oldb->fixrec != newb->fixrec)
	{
	  NewCommand (6, 51);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->fixrec, commbuf);
	}
      if (oldb->mission != newb->mission)
	{
	  NewCommand (6, 52);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->mission, commbuf);
	}
      if (((newb->bhulltype != 0) && (newb->bengtype != 0)) &&
	  ((oldb->bhulltype != newb->bhulltype)
	   || (oldb->bengtype != newb->bengtype)))
	{
	  NewCommand (18, 53);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->bhulltype, commbuf);
	  WriteShort (newb->bengtype, commbuf);
	  WriteShort (newb->bbeamtype, commbuf);
	  WriteShort (newb->bnobeams, commbuf);
	  WriteShort (newb->btorptype, commbuf);
	  WriteShort (newb->bnolaunch, commbuf);
	  WriteShort (0, commbuf);	/* What's this? Not fighterbays */
	}
      if (oldb->torptech != newb->torptech)
	{
	  NewCommand (6, 54);
	  WriteShort (newb->nr, commbuf);
	  WriteShort (newb->torptech, commbuf);
	}
    }

  /* other commands */
  fprintf (stdout, "%3d messages found\n", newmess->nomess);
  for (i = 0; i < newmess->nomess; i++)
    {
      NewCommand (newmess->mess[i]->messlen + 8, 60);
      WriteShort (newmess->mess[i]->messlen, commbuf);
      WriteShort (p, commbuf);	/* from who could a message be? */
      WriteShort (newmess->mess[i]->to, commbuf);
      memcpy (commbuf, newmess->mess[i]->message, newmess->mess[i]->messlen);
      for (j = 0; j < newmess->mess[i]->messlen; j++)
	commbuf[j] += 13;
      commbuf += newmess->mess[i]->messlen;
    };
  if (gen.changepw)
    {
      fprintf (stdout, "New password found\n");
      NewCommand (14, 61);
      WriteShort (0, commbuf);
      memcpy (commbuf, gen.newpw, 10);
      commbuf += 10;
    }

  if (nocommands != 0)
    {
      trnremember[p - 1] =
	realloc (trnremember[p - 1],
		 size[p - 1] + 4 * nocommands + commsize + 1);
      replacement = size[p - 1] + 4 * nocommands + 1 + 1;	/* this sucks and is foolish */
      trnbuf = trnremember[p - 1] + size[p - 1];
      trnbuf[0] = 0;		/* Why inserting one useless byte */
      trnbuf++;			/* when there are commands? Tim?  */
      for (i = 0; i < nocommands; i++)
	{
	  commptr[i] += replacement;
	  WriteLong (commptr[i], trnbuf);
	}
      memcpy (trnbuf, commremember, commsize);
      size[p - 1] += 1 + 4 * nocommands + commsize;
      free (commptr);
      free (commremember);
    }
  return nocommands;
}

#undef newCommand

int
MakeTurn (p)
     short p;
{
  long nocommands = 0;
  unsigned int i;
  char buffer[100];

  fprintf (stdout, "Making turn %d for player %d in game %s...\n", gen.turnnr,
	   p, gamedir);
  trnremember[p - 1] = malloc (28);	/* playernr, #commands, timestamp, 00, gameid */
  trnbuf = trnremember[p - 1];
  WriteShort (p, trnbuf);
  WriteLong (nocommands, trnbuf);
  memcpy (trnbuf, gen.timestamp, 18);
  trnbuf += 18;
  WriteShort (0, trnbuf);	/* two bytes, sometimes 0, seem meaningless */
  WriteShort (gen.gameid, trnbuf);
  size[p - 1] = 28;             /* Header */
  nocommands = PerformCommands (p);
  fprintf (stdout, "%3ld commands\n\n", nocommands);
  trnbuf = trnremember[p - 1] + 2;
  WriteLong (nocommands, trnbuf); /* Is this necessary? */
  size[p - 1] += sowp; /* + Winplan trailer size */
  /* More mem, please */
  trnremember[p - 1] =
    realloc (trnremember[p - 1], size[p - 1] + 4 + 4 + sof + 44);
  trnbuf = trnremember[p - 1] + size[p - 1] - sowp;

  /******** Start WinPlan trailer section ******/
  memcpy (trnbuf, "VER3.501", 8);
  trnbuf += 8;
  /* VPH Values */
  WriteLong (magic_numbers[gen.turnnr % ((sizeof magic_numbers) / (sizeof magic_numbers[0]))], trnbuf);
  WriteLong (0, trnbuf); 
  /* Reg String */
  encode_regstring(buffer, 0);
  encode_regstring(buffer + 50, 100);
  memcpy (trnbuf, buffer, 100);
  trnbuf += 100;
  /* User data */
  memcpy (trnbuf, "Client: Gnome War Pad -- The coolest VGAP client! ", 50);
  trnbuf += 50;
  memcpy (trnbuf, "http://gwp.lunix.com.ar                           ", 50);
  trnbuf += 50;
  /* Rubbish padding */
  memset (buffer, 0, sizeof(buffer));
  memcpy (trnbuf, buffer, sizeof(buffer));
  trnbuf += 100;
  
  /******** Start the DOS trailer section ******/
  /* Calculate checksum */
  cs[p - 1] = 13;		/* 13 added to total checksum */
  for (i = 0; i < size[p - 1]; i++)
    cs[p - 1] += trnremember[p - 1][i];
  for (i = 6; i < 24; i++)
    cs[p - 1] += (3 * trnremember[p - 1][i]);	/* timestamp 4x in checksum; Why, Tim? */
  WriteLong (cs[p - 1], trnbuf); /* Checksum 'X' from Stefan's filefmt.txt */
  memcpy (trnbuf, "GWPs", 4);	/* GWP's signature */
  trnbuf += 4;
  memcpy (trnbuf, fizzremember, sof);
  trnbuf += sof;
  size[p - 1] += 4 + 4 + sof;	/* checksum, "Kero" and fizz */
  free (player);
  fprintf (stdout, "Done!\n\n");

  return nocommands;
}

void
WriteTurns (int race, char *trn_dir)
{
  FILE *trn = NULL;
  char *trnname = NULL;
  int i, j;

  i = race - 1;
  /* 11 checksums (ALL races) for checking same-directory (host!) */
  trnbuf = trnremember[i];
  trnbuf += size[i];
  for (j = 0; j < 11; j++) {
    WriteLong (cs[j], trnbuf);
  }
  size[i] += 4 * 11;
  trnname = malloc (strlen (gamedir) + 6 + 2 + 4 + 1);
  sprintf (trnname, "%s/player%d.trn", trn_dir, i + 1);
  trn = fopen (trnname, "wb");
  fwrite (trnremember[i], size[i], 1, trn);
  fclose (trn);
  free (trnname);
}

int
kmkturn_main (char *game_dir, int race, char *trn_dir)
{
  FILE *fizz;
  int commands_nr;

  if (!game_dir) {
    fprintf (stderr, "Usage: kmkturn <gamedir>\n\n");
    return (-1);
  }
  SetPlanetsDir (game_dir);
  SetGameDir (game_dir);
  GlobalInit ();
  fizz = ResetPlayerFile ("fizz", "", "bin");
  fizzremember = malloc (sof);
  fseek (fizz, 136, SEEK_SET);	/* The place where the registration part starts */
  fread (fizzremember, sof, 1, fizz);
  fclose (fizz);

  SetPlayer (race);
  PlayerioInit();
  commands_nr = MakeTurn (race);

  WriteTurns (race, trn_dir);
  free (fizzremember);
#ifdef test
  fprintf (stderr, "Really done now.\n");
#endif
  return commands_nr;
}
