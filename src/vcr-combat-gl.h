#ifndef VCR_COMBAT_GL_H
#define VCR_COMBAT_GL_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif




void vcrcgl_init( void );




#ifdef USE_GTKGLEXT

#include <gnome.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


void vcrcgl_load_textures( void );
gint vcrcgl_check_texture_bmp( gchar *filename, gint *width, gint *height );
gint vcrcgl_read_texture_from_bmp( GLubyte *texture_pt, gchar *filename );
void vcrcgl_draw_ship( GLfloat coord[3], GLint direction, GLfloat size );
void vcrcgl_draw_sphere( GLfloat coord[3], GLfloat diameter, GLint density );
GLfloat vcrcgl_sphere_texcoord_x( GLfloat v[3] );
GLfloat vcrcgl_sphere_texcoord_y( GLfloat v[3] );
void normalize( GLfloat v[3] );
void polyhedron ( GLfloat *v1, GLfloat *v2, GLfloat *v3,
                  GLfloat coord[3], GLfloat diameter, GLint level );
void vcrcgl_create_gl_callists( void );

#endif // USE_GTKGLEXT







#endif // VCR_COMBAT_GL_H
