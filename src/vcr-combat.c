#include "vcr-combat.h"


void vcr_combat_start( combatdata *cdata )
{
  vcrc_print_combatants( cdata );
}

void vcrc_print_combatants( combatdata *cdata )
{
  g_message( "----------------------------"                                             );
  g_message( "             :    A  -     B"                                             );
  g_message( "is a ship    : %4d  -  %4d", cdata->g_a_is_ship  ,  cdata->g_b_is_ship    );
  g_message( "shield       : %4d  -  %4d", cdata->a_shield     ,  cdata->b_shield       );
  g_message( "hull left    : %4d  -  %4d", cdata->a_hull       ,  cdata->b_hull         );
  g_message( "crew members : %4d  -  %4d", cdata->a_crew       ,  cdata->b_crew         );
  g_message( "type of hull : %4d  -  %4d", cdata->a_typ_hull   ,  cdata->b_typ_hull     );
  g_message( "fighters     : %4d  -  %4d", cdata->a_nmb_fighter,  cdata->b_nmb_fighter  );
  g_message( "fighter bays : %4d  -  %4d", cdata->a_nmb_bays   ,  cdata->b_nmb_bays     );
  g_message( "torpedos     : %4d  -  %4d", cdata->a_nmb_torps  ,  cdata->b_nmb_torps    );
  g_message( "torpedotubes : %4d  -  %4d", cdata->a_nmb_tubes  ,  cdata->b_nmb_tubes    );
  g_message( "torpedotype  : %4d  -  %4d", cdata->a_typ_torps  ,  cdata->b_typ_torps    );
  g_message( "beams        : %4d  -  %4d", cdata->a_nmb_beams  ,  cdata->b_nmb_beams    );
  g_message( "beamtype     : %4d  -  %4d", cdata->a_typ_beams  ,  cdata->b_typ_beams    );
  g_message( "has starbase :       -  %4d",                        cdata->p_has_base     );
  g_message( "pl. beamtype :       -  %4d",                        cdata->p_typ_beams    );
  g_message( "pl. defense  :       -  %4d",                        cdata->p_nmb_pdefense );
  g_message( "bas defense  :       -  %4d",                        cdata->p_nmb_bdefense );
  g_message( "bas fighters :       -  %4d",                        cdata->p_nmb_fighter  );
  g_message( "shield bonus :     %4d"        , cdata->g_shibon                          );
  g_message( "----------------------------"                                             );
}


void vcrc_prepare_fighters( combatdata *cdata )
{
}


void vcrc_prepare_torpedos( combatdata *cdata )
{
}


void vcrc_prepare_beams( combatdata *cdata )
{
}


void vcrc_fight( combatdata *cdata )
{
}



