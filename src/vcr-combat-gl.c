
#define USE_TEXTURES


#include "vcr-combat-gl.h"
#include <gnome.h>
#include "global.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


#ifdef USE_GTKGLEXT


#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "trackball.h"

#define DIG_2_RAD (G_PI / 180.0)
#define RAD_2_DIG (180.0 / G_PI)
#define TIMEOUT_INTERVAL 10
#define DEFAULT_ROT_COUNT 100
#define VIEW_INIT_AXIS_X 1.0
#define VIEW_INIT_AXIS_Y 0.0
#define VIEW_INIT_AXIS_Z 0.0
#define VIEW_INIT_ANGLE  20.0
#define VIEW_SCALE_MAX 12.0
#define VIEW_SCALE_MIN 0.5

enum {
   VCRCGL_TEX_ZERO,
   VCRCGL_TEX_SHIP_A,
   VCRCGL_TEX_SHIP_B,
   VCRCGL_TEX_PLANET_B,
   VCRCGL_TEX_UNIVERSE,
   VCRCGL_TEX_COUNT
};


#ifdef USE_TEXTURES
static GLuint vcrcgl_texture_names[ VCRCGL_TEX_COUNT -1 ];
#endif

static guint vcrcgl_timeout_id = 0;
static float vcrcgl_begin_x = 0.0;
static float vcrcgl_begin_y = 0.0;
static float vcrcgl_axis_x[3] = { 1.0, 0.0, 0.0 };
static float vcrcgl_axis_y[3] = { 0.0, 1.0, 0.0 };
static float vcrcgl_axis_z[3] = { 0.0, 0.0, 1.0 };
static float vcrcgl_view_quat[4] = { 0.0, 0.0, 0.0, 1.0 };
static float vcrcgl_logo_quat[4] = { 0.0, 0.0, 0.0, 1.0 };
static float vcrcgl_view_scale = 5.0;
static int vcrcgl_rot_count = DEFAULT_ROT_COUNT;
static int vcrcgl_mode = 0;
static int vcrcgl_counter = 0;

static gboolean vcrcgl_animate = FALSE;
static gboolean vcrcgl_is_initialized = FALSE;

static void vcrcgl_toggle_animation (GtkWidget *widget);
static void vcrcgl_init_logo_view   (GtkWidget *widget);



static void vcrcgl_init_view( void )
{
  float sine = sin (0.5 * VIEW_INIT_ANGLE * DIG_2_RAD);
  vcrcgl_view_quat[0] = VIEW_INIT_AXIS_X * sine;
  vcrcgl_view_quat[1] = VIEW_INIT_AXIS_Y * sine;
  vcrcgl_view_quat[2] = VIEW_INIT_AXIS_Z * sine;
  vcrcgl_view_quat[3] = cos (0.5 * VIEW_INIT_ANGLE * DIG_2_RAD);
  vcrcgl_view_scale = 1.2;
}



static void vcrcgl_init_logo_quat( void )
{
  vcrcgl_logo_quat[0] = 0.0;
  vcrcgl_logo_quat[1] = 0.0;
  vcrcgl_logo_quat[2] = 0.0;
  vcrcgl_logo_quat[3] = 1.0;
}



static void realize( GtkWidget *widget, gpointer user_data )
{
  GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

  static GLfloat light0_position[] = { 3.0, 3.0, 10.0, 0.0 };
  static GLfloat light0_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
  static GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

  static GLfloat mat_specular[]  = { 0.5, 0.5, 0.5, 0.0 };
  static GLfloat mat_shininess[] = { 10.0 };

  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
    return;


#ifdef USE_TEXTURES
  glGenTextures( (VCRCGL_TEX_COUNT -1), vcrcgl_texture_names );
  glEnable( GL_TEXTURE );
  vcrcgl_load_textures();
#endif

  glClearColor (0.8, 0.8, 0.9, 1.0);
  glClearDepth (1.0);

  glLightfv (GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv (GL_LIGHT0, GL_SPECULAR, light0_specular);

  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_DEPTH_TEST);

  glCullFace( GL_BACK );
  glEnable (GL_CULL_FACE);

  glShadeModel (GL_SMOOTH);

  glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv (GL_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv (GL_BACK, GL_SHININESS, mat_shininess);

  glPolygonMode( GL_FRONT, GL_FILL );
  glPolygonMode( GL_BACK, GL_FILL );




  vcrcgl_create_gl_callists( );

  glEnable (GL_NORMALIZE);

  /* Init logo orientation. */
  vcrcgl_init_logo_quat ();

  /* Init view. */
  vcrcgl_init_view ();

  gdk_gl_drawable_gl_end (gldrawable);
  /*** OpenGL END ***/
}



static gboolean configure_event( GtkWidget *widget,
		                         GdkEventConfigure *event,
		                         gpointer user_data )
{
  GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

  GLfloat w = widget->allocation.width;
  GLfloat h = widget->allocation.height;
  GLfloat aspect;

  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
    return FALSE;

  glViewport (0, 0, w, h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  if (w > h)
    {
      aspect = w / h;
      glFrustum (-aspect, aspect, -1.0, 1.0, 2.0, 60.0);
    }
  else
    {
      aspect = h / w;
      glFrustum (-1.0, 1.0, -aspect, aspect, 2.0, 60.0);
    }

  glMatrixMode (GL_MODELVIEW);

  gdk_gl_drawable_gl_end (gldrawable);
  /*** OpenGL END ***/

  return TRUE;
}



/* Logo rotation mode. */
typedef struct _VcrcglRotMode
{
  float *axis;
  float sign;
} VcrcglRotMode;

static VcrcglRotMode vcrcgl_rot_mode[] = {
  { vcrcgl_axis_x,  1.0 },
  { vcrcgl_axis_y,  1.0 },
  { vcrcgl_axis_x,  1.0 },
  { vcrcgl_axis_z,  1.0 },
  { vcrcgl_axis_x,  1.0 },
  { vcrcgl_axis_y, -1.0 },
  { vcrcgl_axis_x,  1.0 },
  { vcrcgl_axis_z, -1.0 },
  { NULL,    0.0 }  /* terminator */
};



static gboolean expose_event( GtkWidget *widget,
                              GdkEventExpose *event,
                              gpointer user_data )
{
  GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

  GLfloat d_quat[4];
  GLfloat m[4][4];

  /* allow to toggle constant rotation animation */
  if (vcrcgl_animate)
  {
    if (vcrcgl_counter == vcrcgl_rot_count)
    {
      if (vcrcgl_rot_mode[++vcrcgl_mode].axis == NULL)
        vcrcgl_mode = 0;
      vcrcgl_counter = 0;
    }
    axis_to_quat( vcrcgl_rot_mode[vcrcgl_mode].axis,
                  vcrcgl_rot_mode[vcrcgl_mode].sign * G_PI_2 / vcrcgl_rot_count,
                  d_quat );
    add_quats (d_quat, vcrcgl_logo_quat, vcrcgl_logo_quat);
    vcrcgl_counter++;
  }

  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
    return FALSE;

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity ();

  /* View transformation. */
  glTranslatef (0.0, 0.0, -30.0);
  glScalef (vcrcgl_view_scale, vcrcgl_view_scale, vcrcgl_view_scale);
  build_rotmatrix (m, vcrcgl_view_quat);
  glMultMatrixf (&m[0][0]);

  /* Logo model */
  glPushMatrix ();
    build_rotmatrix (m, vcrcgl_logo_quat);
    glMultMatrixf (&m[0][0]);
    glRotatef (90.0, 1.0, 0.0, 0.0);

    glCallList( VCRCGL_TEX_SHIP_A );
    glCallList( VCRCGL_TEX_PLANET_B );
    glCallList( VCRCGL_TEX_UNIVERSE );
  glPopMatrix ();

  /* Swap buffers. */
  if (gdk_gl_drawable_is_double_buffered (gldrawable))
    gdk_gl_drawable_swap_buffers (gldrawable);
  else
    glFlush ();

  gdk_gl_drawable_gl_end (gldrawable);
  /*** OpenGL END ***/

  return TRUE;
}



static gboolean button_press_event( GtkWidget *widget,
                                    GdkEventButton *event,
                                    GtkWidget *menu )
{
  vcrcgl_begin_x = event->x;
  vcrcgl_begin_y = event->y;

  return FALSE;
}



static gboolean motion_notify_event( GtkWidget *widget,
                                     GdkEventMotion *event,
                                     gpointer user_data )
{
  float w = widget->allocation.width;
  float h = widget->allocation.height;
  float x = event->x;
  float y = event->y;
  float d_quat[4];
  gboolean redraw = FALSE;

  /* Rotation. */
  if (event->state & GDK_BUTTON1_MASK)
    {
      trackball (d_quat,
		 (2.0 * vcrcgl_begin_x - w) / w,
		 (h - 2.0 * vcrcgl_begin_y) / h,
		 (2.0 * x - w) / w,
		 (h - 2.0 * y) / h);
      add_quats (d_quat, vcrcgl_view_quat, vcrcgl_view_quat);
      redraw = TRUE;
    }

  /* Scaling. */
  if (event->state & GDK_BUTTON2_MASK)
    {
      vcrcgl_view_scale = vcrcgl_view_scale * (1.0 + (y - vcrcgl_begin_y) / h);
      if (vcrcgl_view_scale > VIEW_SCALE_MAX)
	vcrcgl_view_scale = VIEW_SCALE_MAX;
      else if (vcrcgl_view_scale < VIEW_SCALE_MIN)
	vcrcgl_view_scale = VIEW_SCALE_MIN;
      redraw = TRUE;
    }

  vcrcgl_begin_x = x;
  vcrcgl_begin_y = y;

  if (redraw && !vcrcgl_animate)
    gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);

  return TRUE;
}



static gboolean key_press_event( GtkWidget *widget,
                                 GdkEventKey *event,
                                 gpointer user_data )
{
  switch (event->keyval)
    {
    case GDK_a:
      vcrcgl_toggle_animation (widget);
      break;
    case GDK_i:
      vcrcgl_init_logo_view (widget);
      break;
    case GDK_Escape:
      gtk_main_quit ();
      break;
    default:
      return TRUE;
    }

  return TRUE;
}



static gboolean timeout( GtkWidget *widget )
{
  /* Invalidate the whole window. */
  gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);

  /* Update synchronously. */
  gdk_window_process_updates (widget->window, FALSE);

  return TRUE;
}



static void timeout_add( GtkWidget *widget )
{
  if (vcrcgl_timeout_id == 0)
    {
      vcrcgl_timeout_id = g_timeout_add (TIMEOUT_INTERVAL,
                                  (GSourceFunc) timeout,
                                  widget);
    }
}



static void timeout_remove( GtkWidget *widget )
{
  if (vcrcgl_timeout_id != 0)
    {
      g_source_remove (vcrcgl_timeout_id);
      vcrcgl_timeout_id = 0;
    }
}



static gboolean map_event( GtkWidget *widget,
                           GdkEventAny *event,
                           gpointer user_data )
{
  if (vcrcgl_animate)
    timeout_add (widget);

  return TRUE;
}



static gboolean unmap_event( GtkWidget *widget,
                             GdkEventAny *event,
                             gpointer user_data )
{
  timeout_remove (widget);

  return TRUE;
}



static gboolean visibility_notify_event( GtkWidget *widget,
                                         GdkEventVisibility *event,
                                         gpointer user_data )
{
  if (vcrcgl_animate)
    {
      if (event->state == GDK_VISIBILITY_FULLY_OBSCURED)
	timeout_remove (widget);
      else
	timeout_add (widget);
    }

  return TRUE;
}



static void vcrcgl_toggle_animation( GtkWidget *widget )
{
  vcrcgl_animate = !vcrcgl_animate;

  if (vcrcgl_animate)
    {
      timeout_add (widget);
    }
  else
    {
      timeout_remove (widget);
      gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);
    }
}



static void vcrcgl_init_logo_view( GtkWidget *widget )
{
  vcrcgl_init_logo_quat ();
  vcrcgl_init_view ();
  vcrcgl_mode = 0;
  vcrcgl_counter = 0;

  if (!vcrcgl_animate)
    gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);
}


 
static gboolean button_press_event_popup_menu( GtkWidget *widget,
                                               GdkEventButton *event,
                                               gpointer user_data )
{
  if (event->button == 3)
    {
      /* Popup menu. */
      gtk_menu_popup (GTK_MENU (widget), NULL, NULL, NULL, NULL,
		      event->button, event->time);
      return TRUE;
    }

  return FALSE;
}



static GtkWidget *create_popup_menu( GtkWidget *drawing_area )
{
  GtkWidget *menu;
  GtkWidget *menu_item;

  menu = gtk_menu_new ();

  /* Toggle animation */
  menu_item = gtk_menu_item_new_with_label ("Toggle Animation");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
  g_signal_connect_swapped (G_OBJECT (menu_item), "activate",
			    G_CALLBACK (vcrcgl_toggle_animation), drawing_area);
  gtk_widget_show (menu_item);

  /* Init orientation */
  menu_item = gtk_menu_item_new_with_label ("Initialize");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
  g_signal_connect_swapped (G_OBJECT (menu_item), "activate",
			    G_CALLBACK (vcrcgl_init_logo_view), drawing_area);
  gtk_widget_show (menu_item);

  /* Quit */
  menu_item = gtk_menu_item_new_with_label ("Quit");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
  g_signal_connect (G_OBJECT (menu_item), "activate",
		    G_CALLBACK (gtk_main_quit), NULL);
  gtk_widget_show (menu_item);
	
  return menu;
}



static void print_gl_config_attrib( GdkGLConfig *glconfig,
                                    const gchar *attrib_str,
                                    int          attrib,
                                    gboolean     is_boolean )
{
  int value;

  g_print ("%s = ", attrib_str);
  if (gdk_gl_config_get_attrib (glconfig, attrib, &value))
    {
      if (is_boolean)
        g_print ("%s\n", value == TRUE ? "TRUE" : "FALSE");
      else
        g_print ("%d\n", value);
    }
  else
    g_print ("*** Cannot get %s attribute value\n", attrib_str);
}



static void examine_gl_config_attrib( GdkGLConfig *glconfig )
{
  g_print ("\nOpenGL visual configurations :\n\n");

  g_print ("gdk_gl_config_is_rgba (glconfig) = %s\n",
           gdk_gl_config_is_rgba (glconfig) ? "TRUE" : "FALSE");
  g_print ("gdk_gl_config_is_double_buffered (glconfig) = %s\n",
           gdk_gl_config_is_double_buffered (glconfig) ? "TRUE" : "FALSE");
  g_print ("gdk_gl_config_is_stereo (glconfig) = %s\n",
           gdk_gl_config_is_stereo (glconfig) ? "TRUE" : "FALSE");
  g_print ("gdk_gl_config_has_alpha (glconfig) = %s\n",
           gdk_gl_config_has_alpha (glconfig) ? "TRUE" : "FALSE");
  g_print ("gdk_gl_config_has_depth_buffer (glconfig) = %s\n",
           gdk_gl_config_has_depth_buffer (glconfig) ? "TRUE" : "FALSE");
  g_print ("gdk_gl_config_has_stencil_buffer (glconfig) = %s\n",
           gdk_gl_config_has_stencil_buffer (glconfig) ? "TRUE" : "FALSE");
  g_print ("gdk_gl_config_has_accum_buffer (glconfig) = %s\n",
           gdk_gl_config_has_accum_buffer (glconfig) ? "TRUE" : "FALSE");

  g_print ("\n");

  print_gl_config_attrib (glconfig, "GDK_GL_USE_GL",           GDK_GL_USE_GL,           TRUE);
  print_gl_config_attrib (glconfig, "GDK_GL_BUFFER_SIZE",      GDK_GL_BUFFER_SIZE,      FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_LEVEL",            GDK_GL_LEVEL,            FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_RGBA",             GDK_GL_RGBA,             TRUE);
  print_gl_config_attrib (glconfig, "GDK_GL_DOUBLEBUFFER",     GDK_GL_DOUBLEBUFFER,     TRUE);
  print_gl_config_attrib (glconfig, "GDK_GL_STEREO",           GDK_GL_STEREO,           TRUE);
  print_gl_config_attrib (glconfig, "GDK_GL_AUX_BUFFERS",      GDK_GL_AUX_BUFFERS,      FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_RED_SIZE",         GDK_GL_RED_SIZE,         FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_GREEN_SIZE",       GDK_GL_GREEN_SIZE,       FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_BLUE_SIZE",        GDK_GL_BLUE_SIZE,        FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ALPHA_SIZE",       GDK_GL_ALPHA_SIZE,       FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_DEPTH_SIZE",       GDK_GL_DEPTH_SIZE,       FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_STENCIL_SIZE",     GDK_GL_STENCIL_SIZE,     FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_RED_SIZE",   GDK_GL_ACCUM_RED_SIZE,   FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_GREEN_SIZE", GDK_GL_ACCUM_GREEN_SIZE, FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_BLUE_SIZE",  GDK_GL_ACCUM_BLUE_SIZE,  FALSE);
  print_gl_config_attrib (glconfig, "GDK_GL_ACCUM_ALPHA_SIZE", GDK_GL_ACCUM_ALPHA_SIZE, FALSE);

  g_print ("\n");
}



static void logo_draw_triangle( GLfloat *v0, GLfloat *v1, GLfloat *v2)
{
  GLfloat w0[3], w1[3];
  GLfloat n[3], m;

  w0[0] = v1[0] - v0[0];
  w0[1] = v1[1] - v0[1];
  w0[2] = v1[2] - v0[2];

  w1[0] = v2[0] - v1[0];
  w1[1] = v2[1] - v1[1];
  w1[2] = v2[2] - v1[2];

  n[0] = w0[1]*w1[2] - w0[2]*w1[1];
  n[1] = w0[2]*w1[0] - w0[0]*w1[2];
  n[2] = w0[0]*w1[1] - w0[1]*w1[0];

  m = n[0]*n[0] + n[1]*n[1] + n[2]*n[2];
  if (m > 0.0)
    {
      m = 1.0 / sqrt(m);
      n[0] *= m;
      n[1] *= m;
      n[2] *= m;
    }

  glBegin(GL_TRIANGLES);
    glNormal3fv(&n[0]);
    glVertex3fv(&v0[0]);
    glVertex3fv(&v1[0]);
    glVertex3fv(&v2[0]);
  glEnd();
}



#define TEST_SHIP_SIZE 34
static GLfloat test_ship[TEST_SHIP_SIZE][3][3] = {
  {  {  2.0000,  0.0000,  0.5000*2 }, {  0.0000, -0.5000,  0.2500*2 }, {  0.0000,  0.5000,  0.2500*2 } },
  {  {  2.0000, -1.0000,  0.5000*2 }, {  0.0000, -0.5000,  0.2500*2 }, {  2.0000,  0.0000,  0.5000*2 } },
  {  {  2.0000,  0.0000,  0.5000*2 }, {  0.0000,  0.5000,  0.2500*2 }, {  2.0000,  1.0000,  0.5000*2 } },
  {  {  4.0000, -1.0000,  0.5500*2 }, {  2.0000, -1.0000,  0.5000*2 }, {  2.0000,  0.0000,  0.5000*2 } },
  {  {  4.0000,  1.0000,  0.5500*2 }, {  2.0000,  0.0000,  0.5000*2 }, {  2.0000,  1.0000,  0.5000*2 } },
  {  {  4.0000, -1.0000,  0.5500*2 }, {  2.0000,  0.0000,  0.5000*2 }, {  4.0000,  1.0000,  0.5500*2 } },
  {  {  5.5000, -0.7500,  0.3000*2 }, {  4.0000, -1.0000,  0.5500*2 }, {  4.0000,  0.0000,  0.5500*2 } },
  {  {  5.5000,  0.7500,  0.3000*2 }, {  4.0000,  0.0000,  0.5500*2 }, {  4.0000,  1.0000,  0.5500*2 } },
  {  {  5.5000, -0.7500,  0.3000*2 }, {  4.0000,  0.0000,  0.5500*2 }, {  5.5000,  0.7500,  0.3000*2 } },

  {  {  0.0000, -0.5000, -0.1250*2 }, {  2.0000,  0.0000, -0.2000*2 }, {  0.0000,  0.5000, -0.1250*2 } },
  {  {  0.0000, -0.5000, -0.1250*2 }, {  2.0000, -1.2500, -0.2000*2 }, {  2.0000,  0.0000, -0.2000*2 } },
  {  {  0.0000,  0.5000, -0.1250*2 }, {  2.0000,  0.0000, -0.2000*2 }, {  2.0000,  1.2500, -0.2000*2 } },
  {  {  2.0000, -1.2500, -0.2000*2 }, {  4.0000, -1.2500, -0.2000*2 }, {  2.0000,  0.0000, -0.2000*2 } },
  {  {  2.0000,  0.0000, -0.2000*2 }, {  4.0000,  1.2500, -0.2000*2 }, {  2.0000,  1.2500, -0.2000*2 } },
  {  {  2.0000,  0.0000, -0.2000*2 }, {  4.0000, -1.2500, -0.2000*2 }, {  4.0000,  1.2500, -0.2000*2 } },
  {  {  4.0000, -1.2500, -0.2000*2 }, {  5.5000, -0.8500, -0.1500*2 }, {  4.0000,  0.0000, -0.2000*2 } },
  {  {  4.0000,  0.0000, -0.2000*2 }, {  5.5000,  0.8500, -0.1500*2 }, {  4.0000,  1.2500, -0.2000*2 } },
  {  {  4.0000,  0.0000, -0.2000*2 }, {  5.5000, -0.8500, -0.1500*2 }, {  5.5000,  0.8500, -0.1500*2 } },

  {  {  0.0000,  0.5000,  0.2500*2 }, {  0.0000, -0.5000,  0.2500*2 }, {  0.0000, -0.5000, -0.1250*2 } },
  {  {  0.0000,  0.5000,  0.2500*2 }, {  0.0000, -0.5000, -0.1250*2 }, {  0.0000,  0.5000, -0.1250*2 } },

  {  {  0.0000, -0.5000,  0.2500*2 }, {  2.0000, -1.0000,  0.5000*2 }, {  0.0000, -0.5000, -0.1250*2 } },
  {  {  0.0000, -0.5000, -0.1250*2 }, {  2.0000, -1.0000,  0.5000*2 }, {  2.0000, -1.2500, -0.2000*2 } },
  {  {  2.0000, -1.0000,  0.5000*2 }, {  4.0000, -1.0000,  0.5500*2 }, {  2.0000, -1.2500, -0.2000*2 } },
  {  {  4.0000, -1.2500, -0.2000*2 }, {  2.0000, -1.2500, -0.2000*2 }, {  4.0000, -1.0000,  0.5500*2 } },
  {  {  4.0000, -1.0000,  0.5500*2 }, {  5.5000, -0.7500,  0.3000*2 }, {  4.0000, -1.2500, -0.2000*2 } },
  {  {  5.5000, -0.8500, -0.1500*2 }, {  4.0000, -1.2500, -0.2000*2 }, {  5.5000, -0.7500,  0.3000*2 } },

  {  {  2.0000,  1.0000,  0.5000*2 }, {  0.0000,  0.5000,  0.2500*2 }, {  0.0000,  0.5000, -0.1250*2 } },
  {  {  2.0000,  1.0000,  0.5000*2 }, {  0.0000,  0.5000, -0.1250*2 }, {  2.0000,  1.2500, -0.2000*2 } },
  {  {  4.0000,  1.0000,  0.5500*2 }, {  2.0000,  1.0000,  0.5000*2 }, {  2.0000,  1.2500, -0.2000*2 } },
  {  {  2.0000,  1.2500, -0.2000*2 }, {  4.0000,  1.2500, -0.2000*2 }, {  4.0000,  1.0000,  0.5500*2 } },
  {  {  5.5000,  0.7500,  0.3000*2 }, {  4.0000,  1.0000,  0.5500*2 }, {  4.0000,  1.2500, -0.2000*2 } },
  {  {  4.0000,  1.2500, -0.2000*2 }, {  5.5000,  0.8500, -0.1500*2 }, {  5.5000,  0.7500,  0.3000*2 } },

  {  {  5.5000, -0.7500,  0.3000*2 }, {  5.5000,  0.7500,  0.3000*2 }, {  5.5000, -0.8500, -0.1500*2 } },
  {  {  5.5000,  0.8500, -0.1500*2 }, {  5.5000, -0.8500, -0.1500*2 }, {  5.5000,  0.7500,  0.3000*2 } }
};



void vcrcgl_draw_ship( GLfloat coord[3], GLint direction, GLfloat size )
{
  GLint i;
  GLfloat v0[3], v1[3], v2[3];

  for (i = 0; i < TEST_SHIP_SIZE; i++)
  {
    v0[0] = direction * ( test_ship[i][0][0] * size + coord[0] );
    v0[1] = direction * ( test_ship[i][0][1] * size + coord[1] );
    v0[2] = direction * ( test_ship[i][0][2] * size + coord[2] );

    v1[0] = direction * ( test_ship[i][1][0] * size + coord[0] );
    v1[1] = direction * ( test_ship[i][1][1] * size + coord[1] );
    v1[2] = direction * ( test_ship[i][1][2] * size + coord[2] );

    v2[0] = direction * ( test_ship[i][2][0] * size + coord[0] );
    v2[1] = direction * ( test_ship[i][2][1] * size + coord[1] );
    v2[2] = direction * ( test_ship[i][2][2] * size + coord[2] );

    logo_draw_triangle( &v2, &v1, &v0 );
  }
}



void vcrcgl_init( void )
{
  /* don't initialize the gtkglext a second time */
  if( vcrcgl_is_initialized )
    return;

  vcrcgl_is_initialized = TRUE;

  GdkGLConfig *glconfig;
  gint major, minor;
  GtkWidget *vbox;
  GtkWidget *drawing_area;
  GtkWidget *menu;

  gtk_init (0, NULL);

  /* Init GtkGLExt */
  gtk_gl_init (0, NULL);

  /* Query OpenGL extension version */
  gdk_gl_query_version (&major, &minor);
  g_message( "\nOpenGL extension version - %d.%d\n", major, minor );

  /* Configure OpenGL-capable visual */

  /* Try double-buffered visual */
  glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB    |
					GDK_GL_MODE_DEPTH  |
					GDK_GL_MODE_DOUBLE);
  if (glconfig == NULL)
  {
    g_message ("# Warning: Cannot find the double-buffered visual.\n");
    g_message ("#          single-buffered visual.\n");

    /* Try single-buffered visual */
    glconfig = gdk_gl_config_new_by_mode( GDK_GL_MODE_RGB   |
                                          GDK_GL_MODE_DEPTH );
    if (glconfig == NULL)
	{
	  g_message ("### ERROR: No appropriate OpenGL-capable visual found.\n");
	  g_message ("###        Try to recompile GWP without GtkGLExtension support\n");
	  exit( EXIT_FAILURE );
	}
  }

  /* TODO ... decide whether to keep it in or not */
  /* examine_gl_config_attrib (glconfig);         */


  /* Drawing area for drawing OpenGL scene.*/
  drawing_area = gtk_drawing_area_new ();

  /* Set OpenGL-capability to the widget. */
  gtk_widget_set_gl_capability (drawing_area,
				glconfig,
				NULL,
				TRUE,
				GDK_GL_RGBA_TYPE);

  gtk_widget_add_events (drawing_area,
			 GDK_BUTTON1_MOTION_MASK    |
			 GDK_BUTTON2_MOTION_MASK    |
			 GDK_BUTTON_PRESS_MASK      |
			 GDK_VISIBILITY_NOTIFY_MASK);

  g_signal_connect_after (G_OBJECT (drawing_area), "realize",
                          G_CALLBACK (realize), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "configure_event",
		    G_CALLBACK (configure_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "expose_event",
		    G_CALLBACK (expose_event), NULL);

  g_signal_connect (G_OBJECT (drawing_area), "button_press_event",
		    G_CALLBACK (button_press_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "motion_notify_event",
		    G_CALLBACK (motion_notify_event), NULL);

  g_signal_connect (G_OBJECT (drawing_area), "map_event",
		    G_CALLBACK (map_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "unmap_event",
		    G_CALLBACK (unmap_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "visibility_notify_event",
		    G_CALLBACK (visibility_notify_event), NULL);

  g_signal_connect_swapped (G_OBJECT (drawing_area), "key_press_event",
			    G_CALLBACK (key_press_event), drawing_area);

  vbox = GTK_VBOX( lookup_widget( "vcr_vbox_simulation" ) );
  gtk_box_pack_start_defaults( GTK_BOX( vbox ), drawing_area );
  gtk_widget_show( drawing_area );


  /* Popup menu */
  menu = create_popup_menu (drawing_area);

  /* Signal handler */
  g_signal_connect_swapped (G_OBJECT (drawing_area), "button_press_event",
                            G_CALLBACK (button_press_event_popup_menu), menu);

  return;
}



gint vcrcgl_check_texture_bmp( gchar *filename, gint *width, gint *height )
{
  /* declarations */
  FILE *dz;
  gchar name[256];      // filename to open
  gboolean valid;       // becomes FALSE if file header is invalid
  guint offset;         // offset to start of data
  guint tmpint;         // temporary value

  /* prepare filename with path to open */
  name[0] = '\0';
  strcat( name, GWP_VCR_TEXTURES_DIR );
  strcat( name, "/" );
  strcat( name, filename );

  /* try to get access to file */
  dz = fopen( name, "rb" );
  if( !dz )
  {
    g_message( "## ERROR: unable to open texture file '%s'", name );
    return( EXIT_FAILURE );
  }

  /* check for valid file header */
  valid = TRUE;
  /* signature */
  if( fgetc( dz ) != 0x42 ) valid = FALSE;
  if( fgetc( dz ) != 0x4d ) valid = FALSE;
  /* unreliable file size */
  fgetc( dz ); fgetc( dz ); fgetc( dz ); fgetc( dz );
  /* reserved values, must be zero */
  if( fgetc( dz ) != 0x00 ) valid = FALSE;
  if( fgetc( dz ) != 0x00 ) valid = FALSE;
  if( fgetc( dz ) != 0x00 ) valid = FALSE;
  if( fgetc( dz ) != 0x00 ) valid = FALSE;
  /* offset to start of data (normally == 54) */
  offset  = fgetc( dz );
  offset += fgetc( dz ) * 256;
  offset += fgetc( dz ) * 256 * 256;
  offset += fgetc( dz ) * 256 * 256 *256;
  /* size of BITMAPINFOHEADER structure, must be 40 */
  tmpint  = fgetc( dz );
  tmpint += fgetc( dz ) * 256;
  tmpint += fgetc( dz ) * 256 * 256;
  tmpint += fgetc( dz ) * 256 * 256 *256;
  if( tmpint != 40 ) valid = FALSE;
  /* get width of image in pixels */
  *width  = fgetc( dz );
  *width += fgetc( dz ) * 256;
  *width += fgetc( dz ) * 256 * 256;
  *width += fgetc( dz ) * 256 * 256 *256;
  /* get height of image in pixels */
  *height  = fgetc( dz );
  *height += fgetc( dz ) * 256;
  *height += fgetc( dz ) * 256 * 256;
  *height += fgetc( dz ) * 256 * 256 *256;
  /* number of planes in the image, must be 1 */
  tmpint  = fgetc( dz );
  tmpint += fgetc( dz ) * 256;
  if( tmpint != 1 ) valid = FALSE;
  /* number of bits per pixel (1, 4, 8, or 24) */
  tmpint  = fgetc( dz );
  tmpint += fgetc( dz ) * 256;
  if( tmpint != 24 ) valid = FALSE;
  /* compression type (0=none, 1=RLE-8, 2=RLE-4) */
  tmpint  = fgetc( dz );
  tmpint += fgetc( dz ) * 256;
  tmpint += fgetc( dz ) * 256 * 256;
  tmpint += fgetc( dz ) * 256 * 256 *256;
  if( tmpint != 0 ) valid = FALSE;
  /* size of image data in bytes (including padding) */
  fgetc( dz ); fgetc( dz ); fgetc( dz ); fgetc( dz );
  /* horizontal resolution in pixels per meter (unreliable) */
  fgetc( dz ); fgetc( dz ); fgetc( dz ); fgetc( dz );
  /* vertical resolution in pixels per meter (unreliable) */
  fgetc( dz ); fgetc( dz ); fgetc( dz ); fgetc( dz );
  /* number of colors in image, or zero */
  fgetc( dz ); fgetc( dz ); fgetc( dz ); fgetc( dz );
  /* number of important colors, or zero */
  fgetc( dz ); fgetc( dz ); fgetc( dz ); fgetc( dz );

  if( !valid )
  {
    g_message( "## Error: invalid or unusable file-header from '%s'", name );
    fclose( dz );
    return( EXIT_FAILURE );
  }

  /* check if file is big enough */
  fseek( dz, 0L, SEEK_END );
  if( ( (*width)*(*height)*3 + offset ) > ftell( dz ) )
  {
    g_message( "## Error: file %s seems to have size %d, but should have at least %d",
                name, ftell( dz ), (*width)*(*height)*3 + offset );
    fclose( dz );
    return( EXIT_FAILURE );
  }

  /* done */
  fclose( dz );
  return( EXIT_SUCCESS );
}



void vcrcgl_load_textures( void )
{
  gint width, height;

  /* read planet texture */
  glBindTexture( GL_TEXTURE_2D, VCRCGL_TEX_PLANET_B );
  if( vcrcgl_check_texture_bmp( "planet_earth.bmp", &width, &height ) )
    g_message( "## Error: vcrcgl_check_texture_bmp() failed for %s", "planet_earth.bmp" );
  GLubyte texture_planet[width][height][4];
  vcrcgl_read_texture_from_bmp( &texture_planet[0][0][0], "planet_earth.bmp" );
  glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D( GL_TEXTURE_2D, 0, 4, width, height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE,
                &texture_planet[0][0][0] );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );


  /* read universe texture */
  glBindTexture( GL_TEXTURE_2D, VCRCGL_TEX_UNIVERSE );
  if( vcrcgl_check_texture_bmp( "planet_universe.bmp", &width, &height ) )
    g_message( "## Error: vcrcgl_check_texture_bmp() failed for %s", "planet_universe.bmp" );
  GLubyte texture_universe[width][height][4];
  vcrcgl_read_texture_from_bmp( &texture_universe[0][0][0], "planet_universe.bmp" );
  glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D( GL_TEXTURE_2D, 0, 4, width, height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE,
                &texture_universe[0][0][0] );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
}



gint vcrcgl_read_texture_from_bmp( GLubyte *texture_pt, gchar *filename )
{
  /* declarations */
  FILE *dz;
  gchar name[256];      // filename to open
  guint offset;         // offset to start of data
  gint width, height;   // dimensions of data
  gint i, j;

  /* prepare filename with path to open */
  name[0] = '\0';
  strcat( name, GWP_VCR_TEXTURES_DIR );
  strcat( name, "/" );
  strcat( name, filename );

  /* try to get access to file */
  dz = fopen( name, "rb" );
  if( !dz )
  {
    g_message( "## ERROR: unable to open texture file '%s'", name );
    return( EXIT_FAILURE );
  }


  fseek( dz, 6L, SEEK_SET );
  /* offset to start of data (normally == 54) */
  offset  = fgetc( dz );
  offset += fgetc( dz ) * 256;
  offset += fgetc( dz ) * 256 * 256;
  offset += fgetc( dz ) * 256 * 256 *256;

  fseek( dz, 18L, SEEK_SET );  
  /* get width of image in pixels */
  width  = fgetc( dz );
  width += fgetc( dz ) * 256;
  width += fgetc( dz ) * 256 * 256;
  width += fgetc( dz ) * 256 * 256 *256;
  /* get height of image in pixels */
  height  = fgetc( dz );
  height += fgetc( dz ) * 256;
  height += fgetc( dz ) * 256 * 256;
  height += fgetc( dz ) * 256 * 256 *256;

  /* jump to start of data */
  fseek( dz, offset, SEEK_SET );

  /* read texture */
  for( i=0; i<width ; i++ )
  {
    for( j=0; j<height ; j++ )
    {
      *( texture_pt + (i*height*4) + (j*4) + 2 ) = (GLubyte) fgetc( dz );
      *( texture_pt + (i*height*4) + (j*4) + 1 ) = (GLubyte) fgetc( dz );
      *( texture_pt + (i*height*4) + (j*4) + 0 ) = (GLubyte) fgetc( dz );
      *( texture_pt + (i*height*4) + (j*4) + 3 ) = (GLubyte) 255;
    }
  }

  /* done */
  fclose( dz );
  return( EXIT_SUCCESS );
}



static GLfloat vdata[12][3] = {
	{-0.525731112119133606, 0.0, 0.850650808352039932 },
    { 0.525731112119133606, 0.0, 0.850650808352039932 },
    {-0.525731112119133606, 0.0,-0.850650808352039932 },
    { 0.525731112119133606, 0.0,-0.850650808352039932 },
	{ 0.0, 0.850650808352039932, 0.525731112119133606 },
    { 0.0, 0.850650808352039932,-0.525731112119133606 },
    { 0.0,-0.850650808352039932, 0.525731112119133606 },
    { 0.0,-0.850650808352039932,-0.525731112119133606 }, 
	{ 0.850650808352039932, 0.525731112119133606, 0.0 },
    {-0.850650808352039932, 0.525731112119133606, 0.0 },
    { 0.850650808352039932,-0.525731112119133606, 0.0 },
    {-0.850650808352039932,-0.525731112119133606, 0.0 }
}; 



static GLint tindices[20][3] = {
	{  4,0,  1 }, { 9,0,  4 }, {  5,9, 4 }, { 5, 4, 8 }, { 8,4,  1 }, 
	{ 10,8,  1 }, { 3,8, 10 }, {  3,5, 8 }, { 2, 5, 3 }, { 7,2,  3 }, 
	{ 10,7,  3 }, { 6,7, 10 }, { 11,7, 6 }, { 0,11, 6 }, { 1,0,  6 }, 
	{  1,6, 10 }, { 0,9, 11 }, { 11,9, 2 }, { 2, 9, 5 }, { 2,7, 11 }
}; 



GLfloat vcrcgl_sphere_texcoord_x( GLfloat v[3] )
{
  GLfloat tx;

  if ( v[0] != 0 )
    if ( v[0] > 0 )
      tx =( 0.5 + (atan(v[2]/v[0])+ G_PI/2) / (G_PI*2) );
    else
      tx = ((atan(v[2]/v[0])+ G_PI/2) / (G_PI*2) );
  else
    tx = ( 0.5 + v[2]/2.0 ); 

  return tx;
}



GLfloat vcrcgl_sphere_texcoord_y( GLfloat v[3] )
{	
  return ( 0.5 + asin( v[1] ) / G_PI );
}



void normalize( GLfloat v[3] )
{
  GLdouble d = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
  v[0] /= d;
  v[1] /= d;
  v[2] /= d;
}



void vcrcgl_draw_sphere( GLfloat coord[3], GLfloat diameter, GLint density )
{
  GLint i;
  for (i=0; i<20; i++ )
  polyhedron( vdata[tindices[i][0]],
              vdata[tindices[i][1]],
              vdata[tindices[i][2]], coord, diameter, density );
}



/* draws a sphere-like shape with lots of triangles
   'level' specifies how many triangles are used:
   0: 20, 1: 80, 2: 320, 3: 1280, etc ...             */
void polyhedron ( GLfloat *v1, GLfloat *v2, GLfloat *v3,
                 GLfloat coord[3], GLfloat diameter, GLint level )
{
	GLfloat v12[3], v23[3], v31[3];
	GLint i;
	
	if (level == 0 )
	{
		glBegin( GL_TRIANGLES );

			normalize( v1 );
			glNormal3fv( v1 );
			glTexCoord2f( vcrcgl_sphere_texcoord_x( v1 ), vcrcgl_sphere_texcoord_y( v1 ) );
			glVertex3f( v1[0]*diameter + coord[0],
                        v1[1]*diameter + coord[1],
                        v1[2]*diameter + coord[2] );

			normalize( v2 );
			glNormal3fv( v2 );
			glTexCoord2f( vcrcgl_sphere_texcoord_x( v2 ), vcrcgl_sphere_texcoord_y( v2 ) );
			glVertex3f( v2[0]*diameter + coord[0],
                        v2[1]*diameter + coord[1],
                        v2[2]*diameter + coord[2] );

			normalize( v3 );
			glNormal3fv( v3 );
			glTexCoord2f( vcrcgl_sphere_texcoord_x( v3 ), vcrcgl_sphere_texcoord_y( v3 ) );
			glVertex3f( v3[0]*diameter + coord[0],
                        v3[1]*diameter + coord[1],
                        v3[2]*diameter + coord[2] );

		glEnd();
        return;
	}
	
	for (i=0; i<3; i++)
	{
		v12[i] = v1[i] + v2[i];
		v23[i] = v2[i] + v3[i];
		v31[i] = v3[i] + v1[i];
	}
	
	normalize( v12 );
	normalize( v23 );
	normalize( v31 );
	
	polyhedron(  v1, v12, v31, coord, diameter, (level-1) );
	polyhedron(  v2, v23, v12, coord, diameter, (level-1) );
	polyhedron(  v3, v31, v23, coord, diameter, (level-1) );
	polyhedron( v12, v23, v31, coord, diameter, (level-1) );
}



/*
 *  creates all necessary callists
 */
void vcrcgl_create_gl_callists( void )
{
  static GLfloat mat_black[]     = { 0.0, 0.0, 0.0, 0.0 };
  static GLfloat mat_red[]       = { 1.0, 0.0, 0.0, 0.0 };
  static GLfloat mat_green[]     = { 0.0, 1.0, 0.0, 0.0 };
  static GLfloat mat_blue[]      = { 0.0, 0.0, 1.0, 0.0 };

  /* PLANET B */
  glNewList( VCRCGL_TEX_PLANET_B, GL_COMPILE );
#ifdef USE_TEXTURES
    glBindTexture( GL_TEXTURE_2D, VCRCGL_TEX_PLANET_B );
    glEnable(GL_TEXTURE_2D);
#endif
    glEnable( GL_CULL_FACE );
    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_green );

   GLfloat d[3] = {15.0, 0.0, 0.0};
    vcrcgl_draw_sphere( d, 1.5, 4 );
    glDisable (GL_CULL_FACE);
#ifdef USE_TEXTURES
    glDisable(GL_TEXTURE_2D);
#endif
  glEndList();

  /* UNIVERSE */
  glNewList( VCRCGL_TEX_UNIVERSE, GL_COMPILE );
#ifdef USE_TEXTURES
    glBindTexture( GL_TEXTURE_2D, VCRCGL_TEX_UNIVERSE );
    glEnable(GL_TEXTURE_2D);
#endif
    glCullFace( GL_FRONT );
    glEnable( GL_CULL_FACE );
    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_black );

   GLfloat e[3] = {0.0, 0.0, 0.0};
    vcrcgl_draw_sphere( e, 20.0, 4 );
    glDisable (GL_CULL_FACE);
    glCullFace( GL_BACK );
#ifdef USE_TEXTURES
    glDisable(GL_TEXTURE_2D);
#endif
  glEndList();

  /* SHIP A */
  glNewList( VCRCGL_TEX_SHIP_A, GL_COMPILE );
    glEnable( GL_CULL_FACE );
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_red);
    GLfloat c[3] = { -15.0, 0.0, 0.0 };
    glDisable (GL_CULL_FACE);
    vcrcgl_draw_ship( c, 1, 0.3 );
  glEndList ();
}


























#else

static gboolean vcrcgl_is_initialized = FALSE;

/* show a small help-text if no gtk-GL-extension is available */
void vcrcgl_init( void )
{
  /* don't initialize the gtkglext a second time */
  if( vcrcgl_is_initialized )
    return;

  vcrcgl_is_initialized = TRUE;


  GtkWidget *vbox;
  GtkTextView *view;
  GtkTextBuffer *buffer;
  GtkTextTagTable* table;

  table = gtk_text_tag_table_new();
  buffer = gtk_text_buffer_new( table );

  gtk_text_buffer_insert_at_cursor( buffer, "Welcome to the Visual Combat Simulator\n", -1 );
  gtk_text_buffer_insert_at_cursor( buffer, "\n", -1 );
  gtk_text_buffer_insert_at_cursor( buffer, "If you can read this message your GWP is not able to show\n", -1 );
  gtk_text_buffer_insert_at_cursor( buffer, "any 3D-animated combat simulations - which is quite a pity :-).\n", -1 );
  gtk_text_buffer_insert_at_cursor( buffer, "\n", -1 );
  gtk_text_buffer_insert_at_cursor( buffer, "The required gnome-extension should be available at:\n", -1 );
  gtk_text_buffer_insert_at_cursor( buffer, "http://gtkglext.sourceforge.net/\n", -1 );
  gtk_text_buffer_insert_at_cursor( buffer, "\n", -1 );
  gtk_text_buffer_insert_at_cursor( buffer, "Good luck ...\n", -1 );

  view = gtk_text_view_new_with_buffer( buffer );
  vbox = GTK_VBOX( lookup_widget( "vcr_vbox_simulation" ) );
  gtk_box_pack_start_defaults( GTK_BOX( vbox ), view );
  gtk_widget_show( view );
}

#endif
