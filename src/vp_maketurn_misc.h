/* Made by Rutger Nijlunsing (using Turbo Pascal 6.0)
     (including his ErrorH.pas)
   Translated by p2c (changing turbo pascal 5.0 *cry* )
   Changed by Kero van Gelder
   Last revision: 28 XII 1995 */

/* All kinds of miscellaneous stuff, varying from macros to
   complicated functions */

#ifndef MISC_H
#define MISC_H

#ifdef MISC_G
# define vextern
#else
# define vextern extern
#endif


/* Constanten */

#define pi              3.14159265358979324638
#define boolean         int
#define TRUE            1
#define True            1
#define true            1
#define FALSE           0
#define False           0
#define false           0

#define ReadLn();         fscanf(stdin,"%*[^\n]");fgetc(stdin);

/* Error */

vextern void SetErrorLevel (int e);
/* Sets errorlevel to e, where meanings of e are:
    0  = Ignore
    1  = Warning
    2  = Quit */

vextern void Error (char *s);
/* Depending on errorlevel, print s and quit */


/* Conversion */

vextern char *StrToUpper (char *s);
/* converts string s to uppercase */

vextern char *StrToLower (char *s);
/* converts string s to lowercase */


/* Fileoperaties : */

vextern boolean Exist (char *filename);
/* Levert TRUE als file met filenaam <f> bestaat; anders FALSE */


#undef vextern

#endif /*MISC_H */
