/* Author: Kero van Gelder
   First version 16 IX 1995
   Last revision 12 XII 1995 */

/* Written for Tim Wissemans VGA-planets.
   Reads in all player-data like ``mdata??.dat'' and stores it in
   data-structures declared below */

#ifndef LOCAL_H
#define LOCAL_H

#include "vp_maketurn_misc.h"
#include "vp_maketurn_global.h"

#ifdef LOCAL_G
# define vextern
#else
# define vextern extern
#endif

typedef enum
{
  neutr, trit, dur, molyb
} Tmineral;
typedef long ntdm[4];

typedef struct oneplanet
{
  short owner, nr;
  char fc[4];			/* friendly code of planet */
  short mines, fact, defense;	/* buildings */
  ntdm mined, ground, density;	/* minerals */
  long nocol, nonat;		/* number of colonists/natives */
  long supp, mc;
  short natcivil, natsort;	/* native stats */
  short coltax, nattax;		/* taxes */
  short colhappy, nathappy;	/* happiness info */
  short temp, buildbase;	/* temperature */
} oneplanet;

typedef struct manyplanets
{
  unsigned short noplanets;
  oneplanet **planet;
} manyplanets;

typedef struct oneship
{
  short nr, owner;
  short x, y;			/* place of ship */
  short warp, dx, dy;		/* movement */
  char name[21];		/* name of ship (inluding "\0") */
  char fc[4];			/* friendly code */
  short engtype, hulltype, beamtype, torptype;	/* what is the ship built of */
  short nobeams, nobays, nolaunch, notorps;	/* and more */
  short mission, towtarget, inttarget;	/* mission and belonging targets */
  short enemy, damage, crew;	/* some other stats */
  short nocol, supp, mc;	/* cargo */
  ntdm mineral;			/* mineral cargo */
  short clanstopl, fueltopl, trittopl;	/* ship to planet transfer */
  short durtopl, molybtopl, supptopl, planettopl;	/* last item is nr. of planet */
  short clanstosh, fueltosh, trittosh;	/* ship to planet transfer */
  short durtosh, molybtosh, supptosh, shiptosh;	/* last item is nr. of ship */
} oneship;

typedef struct manyships
{
  unsigned short noships;
  oneship **ship;
} manyships;

typedef struct onebase
{
  short nr, owner;
  short defense, damage;	/* some stats */
  short engtech, hulltech, beamtech, torptech;	/* tech levels */
  short noengines[noe];		/* all engines */
  short nohulls[20];		/* 20 because no race can build more types of ships */
  short nobeams[nob];		/* all beams */
  short nolaunch[notp], notorps[notp];	/* all launchers and missiles */
  short nofighters, mission, fixrec, target;	/* some stats */
  short bhulltype, bengtype, bbeamtype, bnobeams, btorptype, bnolaunch;	/* stats of ship being Built  */
} onebase;

typedef struct manybases
{
  unsigned short nobases;
  onebase **base;
} manybases;

typedef struct onemess
{
  short messlen;		/* length of the message */
  short from, to;
  unsigned char *message;	/* char message[messlen] containing message itself */
  char type;
  boolean old;
  long nr;
} onemess;

typedef struct manymess
{
  unsigned short nomess;
  onemess **mess;
} manymess;

typedef struct allscores
{
  unsigned short total, planets, bases, capitals, freighters;
} allscores;

typedef struct gentype
{
  char timestamp[19];		/* timestamp + closing "\0" */
  allscores scores[11];
  unsigned char weirdsig[11], dissig[11], datsig[11];
  unsigned short player, turnnr, gameid;	/* gameid might be two bytes */
  long shipcs, planetcs, basecs;	/* three checksums */
  boolean changepw;		/* is there a new password? */
  char newpw[11];		/* new password and closing "\0" */
} gentype;


vextern char *natname[10];	/* names of all sorts of natives */
vextern char *civname[10];	/* names of sorts of civilization */

vextern char *player;		/* string (!) of the number of a player */
vextern char *gamedir;		/* directory where the playerfiles are */
vextern manyplanets *oldplanet, *newplanet;
vextern manyships *oldship, *newship;
vextern manybases *oldbase, *newbase;
vextern manymess *oldmess, *newmess;
vextern gentype gen;

extern void SetGameDir (char *gdir);
extern void SetPlayer (int p);
extern void PlayerioInit ();
extern void PlayerioDone ();

#undef vextern

#endif /* LOCAL_H */
