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

#define VCRCGL_TextImaX 1024
#define VCRCGL_TextImaY 512
GLubyte VCRCGL_TextIma[VCRCGL_TextImaX][VCRCGL_TextImaY][4];

void vcrcgl_read_texture( void );

void vcrcgl_draw_ship( GLfloat coord[3], GLint direction, GLfloat size );
void vcrcgl_draw_sphere( GLfloat coord[3], GLfloat diameter, GLint density );
float Tx( float v[3], float size );
float Ty( float v[3], float size );
void normalize( float v[3] );
void polyhedron ( float *v1, float *v2, float *v3,
                  GLfloat coord[3], GLfloat diameter, GLint level );

#endif // USE_GTKGLEXT







#endif // VCR_COMBAT_GL_H
