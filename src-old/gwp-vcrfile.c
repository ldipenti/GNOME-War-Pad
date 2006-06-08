/*
 *  Gnome War Pad: A VGA Planets Client for Gnome
 *  Copyright (C) 2002-2004 Lucas Di Pentima <lucas@lunix.com.ar>
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

/** \file
    $Source$ 
    $Revision$
    
    $Log$
    Revision 1.3  2005/05/31 13:17:39  ldipenti
    Feature: Added CVS metadata on source files

*/

#include <string.h>

#include "global.h"
#include "gwp-vcrfile.h"
#include "gwp-game-state.h"

/*
 * Private members.
 */
struct _GwpVCRFilePrivate {
  gboolean dispose_has_run;
  gint x_coord;
  gint y_coord;
  gint id;
  GString *name;
  FILE *vcrfile;
  
  gboolean fileread;

  gint currentRecord;
  /* parameters for every vcr record */
  gint nmbOfRecords;
  gint typeOfCombat;

  gint     randomSeed;
  gint     lMass    , rMass;
  gchar   *lName    , *rName;
  gint     lDamage  , rDamage;
  gint     lCrew    , rCrew;
  gint     lID      , rID;
  gint     lOwner   , rOwner;
  gint     lTypBeams, rTypBeams;
  gint     lNmbBeams, rNmbBeams;
  gint     lNmbBays , rNmbBays;
  gint     lTypTorp , rTypTorp;
  gint     lNmbTorp , rNmbTorp;
  gint     lNmbFight, rNmbFight;
  gint     lNmbTubes, rNmbTubes;
  gint     lShield  , rShield;
};

/*
 * forward definitions.
 */
static void gwp_vcrfile_init (GTypeInstance *instance, gpointer g_class);
static void gwp_vcrfile_class_init (GwpVCRFileClass *klass);

GType gwp_vcrfile_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GwpVCRFileClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) gwp_vcrfile_class_init, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (GwpVCRFile),
      0, /* n_preallocs */
      (GInstanceInitFunc) gwp_vcrfile_init /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
				   "GwpVCR",
				   &info, 0);
  }
  return type;
}

/* Instance constructor */
static void gwp_vcrfile_init (GTypeInstance *instance,
			     gpointer       g_class)
{
  GwpVCRFile *self = (GwpVCRFile *)instance;
  self->priv = g_new0 (GwpVCRFilePrivate, 1);
  self->priv->dispose_has_run = FALSE;
  self->pub = g_new0 (GwpVCRFilePublic, 1);

  /* Private members init */
  self->priv->x_coord = 0;
  self->priv->y_coord = 0;
  self->priv->id = 0;
  self->priv->name = g_string_new("");
  self->priv->fileread = FALSE;
  self->priv->lName = (gchar *)malloc( ( VCRFILE_MAX_SHIPNAME_LENGTH + 1 ) * sizeof( gchar ) );
  self->priv->rName = (gchar *)malloc( ( VCRFILE_MAX_SHIPNAME_LENGTH + 1 ) * sizeof( gchar ) );
}

static void gwp_vcrfile_dispose (GwpVCRFile *self)
{
  if(self->priv->dispose_has_run) {
    return;
  }
  /* Make sure dispose does not run twice. */
  self->priv->dispose_has_run = TRUE;

  /*
   * Here I have to unref all members on which I own a reference.
   */
  g_string_free (self->priv->name, TRUE);
}

static void gwp_vcrfile_finalize (GwpVCRFile *self)
{
  /*
   * Here, complete object destruction.
   */
  g_free (self->priv);
}

static void gwp_vcrfile_class_init (GwpVCRFileClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* g_message("GwpVCRFileClass init"); */
  /* Register destructor methods. */
  gobject_class->dispose = (void *)gwp_vcrfile_dispose;
  gobject_class->finalize = (void *)gwp_vcrfile_finalize;
}

/* 
 * Public method implementations.
 */
GwpVCRFile * gwp_vcrfile_new (void)
{
  return g_object_new (gwp_vcrfile_get_type (), NULL);
}

/**********************/
/* High-level methods */
/**********************/

/**
 * Check if the given objects has valid coordinates
 *
 * @param self a GwpVCRFile
 * @return TRUE if the current objects has valid coordinates, FALSE
 * otherwise.
 */
gboolean gwp_vcrfile_valid_coords (GwpVCRFile *self) 
{
  g_assert(GWP_IS_VCRFILE(self));

  if (gwp_vcrfile_get_x_coord(self) <= STARCHART_X_MAX && 
      gwp_vcrfile_get_x_coord(self) >= STARCHART_X_MIN &&
      gwp_vcrfile_get_y_coord(self) <= STARCHART_Y_MAX && 
      gwp_vcrfile_get_y_coord(self) >= STARCHART_Y_MIN) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*******************/
/* Get-Set methods */
/*******************/

gint gwp_vcrfile_get_x_coord (GwpVCRFile *self)
{
  g_assert (GWP_IS_VCRFILE(self));
  return self->priv->x_coord;
}

void gwp_vcrfile_set_x_coord (GwpVCRFile *self, gint x)
{
  g_assert (GWP_IS_VCRFILE(self));
  if (x >= 0 && x <= 4000) {
    self->priv->x_coord = x;
  } else {
    self->priv->x_coord = 0;
  }
}

gint gwp_vcrfile_get_y_coord (GwpVCRFile *self)
{
  g_assert (GWP_IS_VCRFILE(self));
  return self->priv->y_coord;
}

void gwp_vcrfile_set_y_coord (GwpVCRFile *self, gint y)
{
  g_assert (GWP_IS_VCRFILE(self));
  if (y >= 0 && y <= 4000) {
    self->priv->y_coord = y;
  } else {
    self->priv->y_coord = 0;
  }
}

gint gwp_vcrfile_get_id (GwpVCRFile *self)
{
  g_assert(GWP_IS_VCRFILE(self));
  return self->priv->id;
}

void gwp_vcrfile_set_id (GwpVCRFile *self, gint id)
{
  g_assert(GWP_IS_VCRFILE(self));
  self->priv->id = id;
}

GString * gwp_vcrfile_get_name (GwpVCRFile *self)
{
  g_assert (GWP_IS_VCRFILE(self));
  /* CP437 (DOS format) to UTF-8 conversion is done */
  return g_string_new (g_convert(self->priv->name->str, 
				 strlen(self->priv->name->str), 
				 "UTF-8", "CP437", NULL, NULL, NULL));
}

void gwp_vcrfile_set_name (GwpVCRFile *self, GString *name)
{
  g_assert (GWP_IS_VCRFILE(self));
  g_assert (name != NULL);
  g_string_free (self->priv->name, TRUE);
  self->priv->name = g_string_new(name->str);
}






gint gwp_vcrfile_read( GwpVCRFile *self )
{
  /* declarations */
  GString *filename;

  /* create the correct filename to the vcr-data */
  filename = g_string_new( (const gchar *)"VCR" );
  switch( gwp_game_state_get_race(game_state) )
  {
    case  1: g_string_append_c( filename, (const gchar)'1' ); break;
    case  2: g_string_append_c( filename, (const gchar)'2' ); break;
    case  3: g_string_append_c( filename, (const gchar)'3' ); break;
    case  4: g_string_append_c( filename, (const gchar)'4' ); break;
    case  5: g_string_append_c( filename, (const gchar)'5' ); break;
    case  6: g_string_append_c( filename, (const gchar)'6' ); break;
    case  7: g_string_append_c( filename, (const gchar)'7' ); break;
    case  8: g_string_append_c( filename, (const gchar)'8' ); break;
    case  9: g_string_append_c( filename, (const gchar)'9' ); break;
    case 10: g_string_append_c( filename, (const gchar)'A' ); break;
    case 11: g_string_append_c( filename, (const gchar)'B' ); break;
    default: g_string_append_c( filename, (const gchar)'0' ); break;
  }
  g_string_append( filename, (const gchar *)".DAT" );

  /* try to open this file (upper case) */
  self->priv->vcrfile = fopen( gwp_game_state_get_full_path( game_state, filename->str ), "rb" );
  g_message( "vcrfile: trying to open '%s'\n", gwp_game_state_get_full_path( game_state, filename->str ) );

  /* in case of failure, try again with lowercase */
  if( !self->priv->vcrfile )
  {
    GString *lc = g_string_ascii_down( filename );
    self->priv->vcrfile = fopen( gwp_game_state_get_full_path( game_state, filename->str ), "rb" );
    g_message( "vcrfile: trying to open '%s'\n", gwp_game_state_get_full_path( game_state, filename->str ) );
    g_string_free(lc, FALSE);
  }

  /* check if file was opened successfully and quit otherwise */
  if( !self->priv->vcrfile )
  {
    g_string_free( filename, FALSE );
    return( EXIT_FAILURE );
  }

  /* file OPENED, life is good */
  self->priv->nmbOfRecords = gwp_vcrfile_get_word( self->priv->vcrfile );

  self->priv->fileread = TRUE;
  self->priv->currentRecord = 0;

  /* done */
//  g_string_free( filename, FALSE );
//  if( vcrfile ) fclose( vcrfile );

  return( EXIT_SUCCESS );
}



gint gwp_vcrfile_get_number_of_combats( GwpVCRFile *self )
{
  if( !self->priv->fileread )
    gwp_vcrfile_read( self );

  return( self->priv->nmbOfRecords );
}



void gwp_vcrfile_set_current_combat( GwpVCRFile *self, gint n )
{
  if( !self->priv->fileread )
    gwp_vcrfile_read( self );

  self->priv->currentRecord = n;
  if( self->priv->currentRecord > self->priv->nmbOfRecords )
    self->priv->currentRecord = self->priv->nmbOfRecords;
  if( self->priv->currentRecord < 0 )
    self->priv->currentRecord = 0;

  gwp_vcrfile_read_combat_record( self, self->priv->currentRecord );
}



gint gwp_vcrfile_read_combat_record( GwpVCRFile *self, gint n )
{
  if( !self->priv->fileread )
    gwp_vcrfile_read( self );

  gint tmp;
  gint signature1;
  gint temperature;
  gint lHost1, rHost1;
  gint lHost2, rHost2;
  gint lPic, rPic;

  /* set the current record */
  self->priv->currentRecord = n;
  if( self->priv->currentRecord > self->priv->nmbOfRecords )
    self->priv->currentRecord = self->priv->nmbOfRecords;
  if( self->priv->currentRecord < 0 )
    self->priv->currentRecord = 0;

  /* record == 0 means no record at all */
  if( self->priv->currentRecord == 0 )
  {
    /* TODO - set default values */
    return( EXIT_FAILURE );
  }

  /* jump to the right place */
  fseek( self->priv->vcrfile, 2 + 100*(self->priv->currentRecord - 1), SEEK_SET );

  /* read this record */
  self->priv->randomSeed = gwp_vcrfile_get_word( self->priv->vcrfile );
  signature1 = gwp_vcrfile_get_word( self->priv->vcrfile );
  temperature = gwp_vcrfile_get_word( self->priv->vcrfile ); /* temperature code */
  self->priv->typeOfCombat = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lMass = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rMass = gwp_vcrfile_get_word( self->priv->vcrfile );
  /* left side */
  gwp_vcrfile_get_gchars( self->priv->vcrfile, self->priv->lName, VCRFILE_MAX_SHIPNAME_LENGTH );
  self->priv->lDamage = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lCrew   = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lID     = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lOwner  = gwp_vcrfile_get_byte( self->priv->vcrfile );
  lHost1 = gwp_vcrfile_get_byte( self->priv->vcrfile );
  lPic   = gwp_vcrfile_get_byte( self->priv->vcrfile );
  lHost2 = gwp_vcrfile_get_byte( self->priv->vcrfile );
  self->priv->lTypBeams = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lNmbBeams = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lNmbBays  = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lTypTorp  = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lNmbTorp  = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->lNmbTubes = gwp_vcrfile_get_word( self->priv->vcrfile );
  /* right side */
  gwp_vcrfile_get_gchars( self->priv->vcrfile, self->priv->rName, VCRFILE_MAX_SHIPNAME_LENGTH );
  self->priv->rDamage = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rCrew   = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rID     = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rOwner  = gwp_vcrfile_get_byte( self->priv->vcrfile );
  rHost1 = gwp_vcrfile_get_byte( self->priv->vcrfile );
  rPic   = gwp_vcrfile_get_byte( self->priv->vcrfile );
  rHost2 = gwp_vcrfile_get_byte( self->priv->vcrfile );
  self->priv->rTypBeams = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rNmbBeams = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rNmbBays  = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rTypTorp  = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rNmbTorp  = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rNmbTubes = gwp_vcrfile_get_word( self->priv->vcrfile );
  /* why the shield values are here ... who cares */
  self->priv->lShield = gwp_vcrfile_get_word( self->priv->vcrfile );
  self->priv->rShield = gwp_vcrfile_get_word( self->priv->vcrfile );

  /* check if ammunition is fighter or torpedo type */
  if( self->priv->lNmbBays > 0 ) {
    self->priv->lNmbFight = self->priv->lNmbTorp;
    self->priv->lNmbTorp = 0; }
  else {
    self->priv->lNmbFight = 0; }

  if( self->priv->rNmbBays > 0 ) {
    self->priv->rNmbFight = self->priv->rNmbTorp;
    self->priv->rNmbTorp = 0; }
  else {
    self->priv->rNmbFight = 0; }

  /* do some checks */
  if( signature1 != 0 ) g_message(
    "## Warning: vcrfile, record %d has invalid signature 1 (thost) = %d",
    self->priv->currentRecord, signature1 );
  if( lHost1 != 0 ) g_message(
    "## Warning: vcrfile, record %d has invalid left Host 1 (thost) = %d",
    self->priv->currentRecord, lHost1 );
  if( lHost1 != 0 ) g_message(
    "## Warning: vcrfile, record %d has invalid left Host 2 (thost) = %d",
    self->priv->currentRecord, lHost2 );

  /* done */
  return( EXIT_SUCCESS );
}



gint gwp_vcrfile_get_random_seed( GwpVCRFile *self )
{
  return( self->priv->randomSeed );
}
gboolean gwp_vcrfile_2nd_side_is_planet( GwpVCRFile *self )
{
  if( self->priv->typeOfCombat == 0 )
    return( FALSE );
  else
    return( TRUE );
}



gint gwp_vcrfile_get_mass( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lMass );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rMass );
      break;
    default:
      break;
  }
  return( 0 );
}



gchar* gwp_vcrfile_get_shipname( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lName );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rName );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_damage( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lDamage );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rDamage );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_shields( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lShield );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rShield );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_crew( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lCrew );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rCrew );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_shipid( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lID );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rID );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_owner( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lOwner );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rOwner );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_type_of_beams( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lTypBeams );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rTypBeams );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_number_of_beams( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lNmbBeams );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rNmbBeams );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_number_of_bays( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lNmbBays );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rNmbBays );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_type_of_torpedos( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lTypTorp );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rTypTorp );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_number_of_torpedos( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lNmbTorp );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rNmbTorp );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_number_of_fighters( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lNmbFight );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rNmbFight );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_number_of_tubes( GwpVCRFile *self, gint side )
{
  switch( side )
  {
    case VCRC_SIDE_A:
      return( self->priv->lNmbTubes );
      break;
    case VCRC_SIDE_B:
      return( self->priv->rNmbTubes );
      break;
    default:
      break;
  }
  return( 0 );
}



gint gwp_vcrfile_get_word( FILE *from )
{
  gint tmp;

  if( from == NULL )
    return( -1 );

  tmp = fgetc( from );
  tmp += 256 * fgetc( from );

  return( tmp );
}



gint gwp_vcrfile_get_byte( FILE *from )
{
  if( from == NULL )
    return( -1 );
  return( fgetc( from ) );
}



gint gwp_vcrfile_get_gchars( FILE *from, gchar *to, gint len )
{
  /* check for consistency */
  if( from == NULL )
    return( EXIT_FAILURE );

  gint i;

  /* read from file to tmpstr and store it in GString */
  fread( to, len, 1, from );
  i = len;
  while( to[i-1] == ' ' )
  {
    to[i-1] = '\0';
    i--;
  }

  /* done */
  return( EXIT_SUCCESS );
}





