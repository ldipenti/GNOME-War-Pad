/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002,2003 Lucas Di Pentima <lucas@lunix.com.ar>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
 * NOTICE: This code has been adapted from Kero van Gelder's work at
 * "kunpack" utility, you can check out his work at
 * http://members.chello.nl/~k.vangelder/vga/
 */

/* Author: Kero van Gelder
   First version: 4 XI 1995
   Last revision: 12 II 1996 */

/* Program to unpack PLAYER??.RST from VGA-planets
   Leaves PLAYER??.RST unharmed (does not alter/delete it) */

#ifdef DOS
#define dirdelimiter '\\'
#else
#define dirdelimiter '/'
#endif

#define kunpackversion "1.5d"
#define email "kero@dds.nl"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gnome.h>

#include "vp_unpack.h"

/*
 * HEADERS (private functions)
 */
FILE *OpenPlayerFile(char *prefix, char *nr, char *postfix);
void UnpackShip(char *player);
void UnpackTarget(char *player);
void UnpackPData(char *player);
void UnpackBData(char *player);
void UnpackMess(char *player);
void UnpackShipXY(char *player);
void UnpackGenPart1(void);
void UnpackGenPart2(char *player);
void UnpackVcr(char *player);
void DoUnpack(FILE *rst, char *player, int nr);
gint main_unpack(gchar *game_dir, gint race);
void UnpackWinplan(char *player);

/* 
 * The following 4 macros are made to read/write ... endian
 * They assume s,l are short resp. long and buf is an unsigned char*
 * Conclusion: one of the dangerous things in this program 
 */

/* 
 * In this program I NEVER use these macros on a variable with
 * `remember' in it, because they are always the beginning of some
 * buffer (will de free-ed later)
 */
#define ReadShort(s,buf); {s=(short)(buf[0]+(buf[1]<<8));buf+=2;}
#define ReadLong(l,buf); {l=(long)(buf[0]+(buf[1]<<8)+(buf[2]<<16)+(buf[3]<<24));buf+=4;}
#define WriteShort(s,buf); {buf[0]=(s)&255;buf[1]=(s)>>8;buf+=2;}
#define WriteLong(l,buf); {buf[0]=(l)&255;buf[1]=((l)>>8)&255;buf[2]=((l)>>16)&255;buf[3]=(l)>>24;buf+=4;}

char *gamedir,*dissig,*datsig;
unsigned char *rstremember,*ctrlbuf,*ctrlremember,*genremember;
unsigned long shipcs=0,planetcs=0,basecs=0,rstsize;
short gameid,turnnr;

FILE *OpenPlayerFile(char *prefix, char *nr, char *postfix)
/* 
 * Creates the file "prefix"nr."postfix" in the game-directory (erases
 * what exists!).  If the file cannot be created (disk full or so),
 * program terminates.  This can result in a half-unpacked turn
 */
{
  char *filename;
  FILE *f;

  filename=malloc(strlen(gamedir)+strlen(prefix)+strlen(nr)+strlen(postfix)+2);
  sprintf(filename,"%s%s%s%c%s",gamedir,prefix,nr,'.',postfix);
#ifdef test
  fprintf(stderr,"Opening file %s now\n",filename);
#endif
  f=fopen(filename,"wb");
  if (f==NULL) {
    fprintf(stderr,"OpenPlayerFile: Cannot open file %s!\nDisk might be full!\n",filename);
    exit(-1);
  }
  free(filename);
  return f;
} /* OpenPlayerFile */

void UnpackShip(char *player)
/* 
 * Takes all ships out of the results and puts them in ``ship??.dat''
 * and ``ship??.dis'' On the fly, some checksums are computed (for
 * ``control.dat'' and ``gen??.dat'')
 */
{
  FILE *ship;
  unsigned long place=0,cs;
  int i,j,size=107;
  unsigned short noships,shipnr;
  unsigned char *buf;

  buf=rstremember+place;
  ReadLong(place,buf);
  place--; /* this sucks */
  buf=rstremember+place;
  ReadShort(noships,buf);
  fprintf(stdout,"%3d own ships found\n",noships);
  shipcs=(noships>>8)+(noships&255);
  for (i=0;i<noships;i++) {
#ifdef test
    fprintf(stderr,"%i",i%10);
#endif
    cs=0;
    for (j=0;j<size;j++) cs+=buf[j];
    ReadShort(shipnr,buf);
    shipnr--; /* this sucks */
    ctrlbuf=ctrlremember+4*shipnr;
    WriteLong(cs,ctrlbuf);
    shipcs+=cs;
    buf+=size-2;
  }
  shipcs*=2;
  for (j=0;j<10;j++) shipcs+=(dissig[j]+datsig[j]);
#ifdef test
  fprintf(stderr,"checksum for ships: 0x%lX\n",shipcs);
#endif
  
  ship=OpenPlayerFile("ship",player,"dis");
  fwrite(rstremember+place,2+size*noships,1,ship);
  fwrite(dissig,10,1,ship);
  fclose(ship);

  ship=OpenPlayerFile("ship",player,"dat");
  fwrite(rstremember+place,2+size*noships,1,ship);
  fwrite(datsig,10,1,ship);
  fclose(ship);
} /* UnpackShip */

void UnpackTarget(char *player)
/* 
 * Takes all targets out of a result and puts them in the file
 * ``target??.dat''
 */
{
  FILE *target;
  unsigned long place=4;
  int size=34;
  unsigned short notargets;
  unsigned char *buf;

  buf=rstremember+place;
  ReadLong(place,buf);
  place--; /* this sucks */
  buf=rstremember+place;

  ReadShort(notargets,buf);
  fprintf(stdout,"%3d targets found\n",notargets);

  /* If there're more that 50 targets, lets create targetx.ext file */
  if (notargets <= 50) {
    target = OpenPlayerFile("target", player, "dat");
    fwrite(rstremember + place, 2 + size * notargets, 1, target);
    fwrite(datsig, 10, 1, target);
    fclose(target);
  } else {
    /* TARGETx.DAT */
    target = OpenPlayerFile("target", player, "dat");
    fwrite(rstremember + place, 2 + size * 50, 1, target);
    fwrite(datsig, 10, 1, target);
    fclose(target);

    /* 
     * TARGETx.EXT -> When RST has the AllowBigTargets ON, this have nothing 
     * to do with Winplan data, see below. 
     */
    target = OpenPlayerFile("target", player, "ext");
    fwrite(rstremember + place + 50, 2 + size * (notargets - 50), 1, target);
    fwrite(datsig, 10, 1, target);
    fclose(target);
  }
} /* UnpackTarget */

void UnpackPData(char *player)
/* 
 * Takes all planets out of the results and puts them in
 * ``pdata??.dat'' and ``pdata??.dis'' On the fly, some checksums are
 * computed (for ``control.dat'' and ``gen??.dat'')
 */
{
  FILE *pdata;
  unsigned long place=8,cs=0;
  int i,j,size=85;
  unsigned short noplanets,planetnr;
  unsigned char *buf;

  buf=rstremember+place;
  ReadLong(place,buf);
  place--; /* this sucks */
  buf=rstremember+place;
  ReadShort(noplanets,buf);
  fprintf(stdout,"%3d own planets found\n",noplanets);
  planetcs=(noplanets>>8)+(noplanets&255);
  for (i=0;i<noplanets;i++) {
#ifdef test
    fprintf(stderr,"%i",i%10);
#endif
    cs=0;
    for (j=0;j<size;j++) cs+=buf[j];
    buf+=2;
    ReadShort(planetnr,buf);
    planetnr--; /* this sucks */
    ctrlbuf=ctrlremember+2000+4*planetnr;
    WriteLong(cs,ctrlbuf);
    planetcs+=cs;
    buf+=(size-4);
  }
  planetcs*=2;
  for (j=0;j<10;j++) planetcs+=(dissig[j]+datsig[j]);
#ifdef test
  fprintf(stderr,"checksum for planets: 0x%lX\n",planetcs);
#endif

  pdata=OpenPlayerFile("pdata",player,"dis");
  fwrite(rstremember+place,2+size*noplanets,1,pdata);
  fwrite(dissig,10,1,pdata);
  fclose(pdata);

  pdata=OpenPlayerFile("pdata",player,"dat");
  fwrite(rstremember+place,2+size*noplanets,1,pdata);
  fwrite(datsig,10,1,pdata);
  fclose(pdata);
} /* UnpackPData */

void UnpackBData(char *player)
/* 
 * Takes all bases out of the results and puts them in ``bdata??.dat''
 * and ``bdata??.dis'' On the fly, some checksums are computed (for
 * ``control.dat'' and ``gen??.dat'')
 */
{
  FILE *bdata;
  unsigned long place=12,cs;
  int i,j,size=156;
  unsigned short nobases,basenr;
  unsigned char *buf;

  buf=rstremember+place;
  ReadLong(place,buf);
  place--; /* this sucks */
  buf=rstremember+place;
  ReadShort(nobases,buf);
  fprintf(stdout,"%3d own bases found\n",nobases);
  basecs=(nobases>>8)+(nobases&255);
  for (i=0;i<nobases;i++) {
#ifdef test
    fprintf(stderr,"%i",i%10);
#endif
    cs=0;
    for (j=0;j<size;j++) cs+=buf[j];
    ReadShort(basenr,buf);
    basenr--; /* this sucks */
    ctrlbuf=ctrlremember+4000+4*basenr;
    WriteLong(cs,ctrlbuf);
    basecs+=cs;
    buf+=(size-2);
  }
  basecs*=2;
  for (j=0;j<10;j++) basecs+=(dissig[j]+datsig[j]);
#ifdef test
  fprintf(stderr,"checksum for bases: 0x%lX\n",basecs);
#endif

  bdata=OpenPlayerFile("bdata",player,"dis");
  fwrite(rstremember+place,2+size*nobases,1,bdata);
  fwrite(dissig,10,1,bdata);
  fclose(bdata);

  bdata=OpenPlayerFile("bdata",player,"dat");
  fwrite(rstremember+place,2+size*nobases,1,bdata);
  fwrite(datsig,10,1,bdata);
  fclose(bdata);
} /* UnpackBData */

void UnpackMess(char *player)
/* 
 * Takes all messages from a result and puts them in ``mdata??.dat''.
 * Since messages are of unpredictable length, the place and size of
 * all messages are given at the beginning of the file. In the result,
 * however places (of course?) differ. So the messages are
 * "moved". Also, a file ``mess??.dat'' with 0 outgoing messages is
 * created.
 */
{
  FILE *mess;
  unsigned long place=16,dump;
  unsigned short nomess;
  unsigned char *buf;
  int i,total=0,size;

  buf=rstremember+place;
  ReadLong(place,buf);
  place--; /* this sucks */
  buf=rstremember+place;
  ReadShort(nomess,buf);
  fprintf(stdout,"%3d messages found\n",nomess);

  ReadLong(place,buf); /* place where first message starts */
  buf-=4;
  place--; /* this sucks */
  for (i=0;i<nomess;i++) {
#ifdef test
    fprintf(stderr,"%i",i%10);
#endif
    ReadLong(dump,buf);
    buf-=4; /* only disadvantage of my own macro */
    dump-=(place-(2+6*nomess)); /* ``move'' message */
    WriteLong(dump,buf);
    ReadShort(size,buf);
    total+=size;
  }

  mess=OpenPlayerFile("mdata",player,"dat");
  fwrite(buf-(2+6*nomess),2+6*nomess,1,mess);
  fwrite(rstremember+place,total,1,mess);
  /* datsig not needed */
  fclose(mess);

  mess=OpenPlayerFile("mess",player,"dat");
  i=0;
  fwrite(&i,2,1,mess);
  fclose(mess);
} /* UnpackMess */

void UnpackWinplan(char *player)
{
  FILE *kore;
  unsigned long place = 40;
  unsigned char *buf;
  unsigned short nocontacts = 0;
  gpointer junk = g_malloc0(90);

  buf=rstremember+place;
  ReadLong(place,buf);
  place--; /* this sucks */
  buf=rstremember+place;
  
  kore = OpenPlayerFile("kore", player, "dat");

  fwrite(&turnnr, 2, 1, kore); /* Turn number */
  fwrite(junk, 7, 1, kore); /* Junk */
  fwrite(datsig, 10, 1, kore);  /* Signature 2 */
  fwrite(junk, 83, 1, kore); /* More junk */

  fwrite(buf, 8, 500, kore); /* Minefields */

  buf += 4000;
  fwrite(buf, 12, 50, kore); /* Ion Storms */

  buf += 600;
  fwrite(buf, 4, 50, kore); /* Explosions */

  buf += 200;
  buf += 682; /* skip race.nm contents */
  fwrite(buf, 78, 100, kore); /* UFO.HST contents */

  buf += 7800;
  fwrite(buf, 4, 1, kore); /* Signature "1121" or "1120" */

  buf += 4;
  ReadLong(nocontacts, buf);
  buf -= 4;
  fwrite(buf, 4, 1, kore); /* Nr of contacts */
  if (nocontacts > 0) {
    buf += 4;
    fwrite(buf, 34, nocontacts, kore); /* contacts */
  }

  fclose(kore);
} /* UnpackWinplan */

void UnpackShipXY(char *player)
/* 
 * Takes all visual ships from the result and stores them in
 * ``shipxy??.dat''
 */
{
  FILE *shipxy;
  unsigned long place=20;
  int size=8;
  unsigned short noshipxys=500;
  unsigned char *buf;

  buf=rstremember+place;
  ReadLong(place,buf);
  place--; /* this sucks */
  buf=rstremember+place;

  shipxy=OpenPlayerFile("shipxy",player,"dat");
  fwrite(buf,size,noshipxys,shipxy);
  fwrite(datsig,10,1,shipxy);
  fclose(shipxy);
} /* UnpackShipXY */

void UnpackGenPart1(void)
/* 
 * Reads in large parts of ``gen??.dat'' from the result. Determines
 * dissig and datsig. Moves turnnr and some other short.
 */
{
  unsigned long place = 24;
  unsigned char *buf;
  int i;

  buf = rstremember + place;
  ReadLong(place, buf);
  place--; /* this sucks */
  /* check length; */
  if ((place + 157 - 13 + 2) > rstsize) { /* place + sizeof(gen)-
					     MissingPartOf(gen) + 
					     noVcrs (1 short zero) */
    fprintf(stderr, "This is not a (complete) result! (gen part 1)\n");
    exit(-1);
  }
  genremember = rstremember + place;

  /* for some odd reason, these two words must be replaced */
  buf = genremember + 140;
  ReadShort(turnnr, buf);
  ReadShort(gameid, buf);
  fprintf(stdout, "turn %d\n", turnnr);

  buf = genremember + 118; /* position of DIS-signature */
  dissig = malloc(11);     /* ---+   */
  memcpy(dissig, buf, 10); /* \|/  */
  strcat(dissig, "\0");   /* This fills one empty byte in ``gen??.dat''*/
#ifdef test
  fprintf(stderr,"DIS-Signature is %s\n",dissig);
#endif
  datsig=malloc(11);
  memcpy(datsig,dissig,11);
  for (i=0;i<10;i++) datsig[i]=datsig[i]+i+1;
#ifdef test
  fprintf(stderr,"DAT-Signature is %s\n",datsig);
#endif
} /* UnpackGenPart1 */

void UnpackGenPart2(char *player)
/* Writes ``gen??.dat'', after filling in the checksums */
{
  FILE *gen;
  unsigned char *buf;
  int size=157;
  
  buf=genremember+129;
  WriteLong(shipcs,buf);
  WriteLong(planetcs,buf);
  WriteLong(basecs,buf);
  WriteLong(0,buf);
  WriteLong(0,buf);
  WriteLong(0,buf); /* 12 empty bytes; a new password is put here */
  WriteShort(turnnr,buf);
  WriteShort(gameid,buf);
  gen=OpenPlayerFile("gen",player,"dat");
  fwrite(genremember,size,1,gen);
  fclose(gen);
} /* UnpackGenPart2 */

void UnpackVcr(char *player)
/* Takes all vcr's from the result and puts them in ``vcr??.dat'' */
{
  FILE *vcr;
  unsigned long place=28;
  int size=100;
  unsigned short novcrs;
  unsigned char *buf;

  buf=rstremember+place;
  ReadLong(place,buf);
  place--; /* this sucks */
  /* check length; */
  if ((place+2)>rstsize) {
    fprintf(stderr,"This is not a (complete) result! (vcr)\n");
    exit(-1);
  }
  buf=rstremember+place;
  ReadShort(novcrs,buf);
  /* final length-test */
  if ((place+2+size*novcrs)!=rstsize) {
    if ((place+2+size*novcrs)<rstsize) {
      fprintf(stderr,"Result is bigger than expected, this might not be a result!\n");
    } else {
      fprintf(stderr,"Result is SHORTER than expected, may be your result has been chopped off!\n");
      exit(-1);
    }
  }
  fprintf(stdout,"%3d VCR's found\n",novcrs);

  vcr=OpenPlayerFile("vcr",player,"dat");
  fwrite(rstremember+place,2+size*novcrs,1,vcr);
  fwrite(datsig,10,1,vcr);
  fclose(vcr);
} /* UnpackVcr */

FILE *rst;
short inittmp[11]={0,0,0,0,0,0,0,0,0,0,0};
int found=0;

void DoUnpack(FILE *rst, char *player, int nr)
{
  inittmp[nr - 1] = 1;
  found = 1;
  fprintf(stdout, "Unpacking player %s in game %s ", player, gamedir);
  fseek(rst, 0, SEEK_END);
  rstsize = ftell(rst);
#ifdef test
  fprintf(stderr, "Size of the result-file: %ld\n", rstsize);
#endif
  rstremember = malloc(rstsize + 13); /* rst misses 13 chars of 
					 ``gen??.dat'' */
  fseek(rst, 0, SEEK_SET);
  fread(rstremember, rstsize, 1, rst);
  /* do the unpacking */
  UnpackGenPart1();       /* reads only (inclusive dis- & datsig) */
  UnpackVcr(player);      /* includes length-check, so asap after 
			     reading datsig&dissig */
  UnpackShip(player);     /* inclusive part 1 of ctrlbuf */
  UnpackPData(player);    /* inclusive part 2 of ctrlbuf */
  UnpackBData(player);    /* inclusive part 3 of ctrlbuf */
  UnpackTarget(player);
  UnpackShipXY(player);
  UnpackMess(player);
  UnpackWinplan(player);
  UnpackGenPart2(player); /* OVERWRITES INTERNAL buf DATA!!!   Run last?
			     (to be ran after Unpack-Ship,PData,BData) */
  fprintf(stdout, "Done!\n\n");
  free(dissig);
  free(datsig);
  free(rstremember);
  fclose(rst);
} /* DoUnpack */

gint main_unpack(gchar *game_dir, gint race)
{
  gint argc = 2;
  gchar *argv[2];

  FILE *init, *ctrl;
  gchar *rstname, *player;
  gint i;

  argv[1] = game_dir;

  if (argc == 2) {
    gamedir = malloc(strlen(argv[1]) + 1 + 1); /* trailing '/' and '\0' */
    if (argv[1][strlen(argv[1]) - 1] != '/') {
      sprintf(gamedir, "%s%c", argv[1], '/');
    } else {
      sprintf(gamedir, "%s", argv[1]);
    }
#ifdef test
    fprintf(stderr, "Game directory is %s\n", gamedir);
#endif
    ctrlremember = malloc(6002);
    for (i = 0; i < 6002; i++) ctrlremember[i] = 'K';

    i = race;
    player = malloc(3); /* max 2 digits + '\0' */
    sprintf(player, "%d", i);
#ifdef test
    fprintf(stderr, "Player number is %s\n", player);
#endif
    rstname = malloc(strlen(gamedir) + strlen(player) + 11);
    sprintf(rstname, "%splayer%s.rst", gamedir, player);
#ifdef test
    fprintf(stderr, "%s\n", rstname);
#endif
    rst = fopen(rstname, "rb");
    if (rst != NULL) {
      DoUnpack(rst, player, i);
    } else {
      sprintf(rstname, "%sPLAYER%s.RST", gamedir, player);
#ifdef test
      fprintf(stderr, "%s\n", rstname);
#endif
      rst = fopen(rstname, "rb");
      if (rst != NULL) {
	DoUnpack(rst, player, i);
      } else {
#ifdef test
	fprintf(stderr, "No player %s in game %s\n", player, gamedir);
#endif
      }
    }
    free(rstname);
    free(player);

    if (found) {
      init = OpenPlayerFile("init", "", "tmp");
      fwrite(&inittmp, 2, 11, init);
      fclose(init);
      ctrl = OpenPlayerFile("control", "", "dat");
      fwrite(ctrlremember, 6002, 1, ctrl);
      fclose(ctrl);
    } else {
      fprintf(stderr, "Nothing to unpack!\n\n");
    }
    free(gamedir);
    free(ctrlremember);
  } else {
    fprintf(stderr, "Usage: kunpack <gamedir> \n\n");
    return(1);
  }
#ifdef test
  fprintf(stderr, "Really done now.\n");
#endif
  return(0);
} /* main */

/*
 * Proxy function to main_unpack ... the old main()
 * Minimum effort...always :-)
 */
gboolean vp_unpack(const gchar *game_dir, gint race_num)
{
  gchar *dir;
  g_assert(game_dir != NULL);

  dir = g_strdup(game_dir);

  if(main_unpack(dir, race_num) == 0) {
    g_free(dir);
    return TRUE;
  } else {
    /* Some problem went on! alert! */
    g_free(dir);
    return FALSE;
  }
}
