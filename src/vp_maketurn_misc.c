/* Made by Rutger Nijlunsing (using Turbo Pascal 6.0)
   Translated by p2c (changing turbo pascal 5.0 *cry* )
   Changed by Kero van Gelder
   Last revision: 28 XII 1995 */

/* Implements misc.h */

#define MISC_G

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "vp_maketurn_misc.h"


/* Error */

static int errorlevel = 2;	/* Standaard errorlevel: BREAK on error */

void
Error (s)
     char *s;
{
  switch (errorlevel)
    {
    case 1:
      fprintf (stderr, "%s\n", s);
      break;
    case 2:
      fprintf (stderr, "Fatal error: %s\n", s);
      fprintf (stderr, "Program aborted.\n");
      exit (1);
    default:
      /* ignore */
    }
}

void
SetErrorLevel (e)
     int e;
{
  errorlevel = e;
}


/* Conversion */

char *
StrToUpper (s)
/* Converts string s to uppercase */
     char *s;
{
  unsigned int i;
  for (i = 0; i < strlen (s); i++)
    s[i] = toupper (s[i]);
  return s;
}

char *
StrToLower (s)
/* Converts string s to lowercase */
     char *s;
{
  unsigned int i;
  for (i = 0; i < strlen (s); i++)
    s[i] = tolower (s[i]);
  return s;
}


/* Fileoperaties */

boolean
Exist (filename)
     char *filename;
{
  /* Levert TRUE als file <filename> bestaat, anders FALSE */
  FILE *f;

  f = fopen (filename, "r");
  if (f != NULL)
    {
      fclose (f);
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}
