/*

Copyright (C) 2001 Javier Loureiro

Copyright (C) 2004 Alex de Landgraaf <alextreme@xs4all.nl>
(adaptions for usage with GTK2)


This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  
*/


#include "gtksdl.h"

static void gtk_sdl_class_init		(GtkSDLClass	*klass);
static void gtk_sdl_init		(GtkSDL		*sdl);
static void gtk_sdl_realize		(GtkWidget	*widget);
static void gtk_sdl_size_allocate	(GtkWidget	*widget,
					GtkAllocation	*allocation);

static void gtk_sdl_send_configure	(GtkSDL *sdl);
static void gtk_sdl_surface_attach	(GtkSDL *sdl);
static gint gtk_sdl_expose (GtkWidget *widget, GdkEventExpose *event);

static void gtk_sdl_display_update (GtkSDL *sdl);


static GtkWidgetClass *parent_class = NULL;

GtkType gtk_sdl_get_type (void)
{
  static GtkType sdl_type = 0;

	if (!sdl_type)
	{
		static const GtkTypeInfo sdl_info =
		{
			"GtkSDL",
			sizeof (GtkSDL),
			sizeof (GtkSDLClass),
			(GtkClassInitFunc) gtk_sdl_class_init,
			(GtkObjectInitFunc) gtk_sdl_init,
			/* reserved_1 */ NULL,
			/* reserved_2 */ NULL,
			(GtkClassInitFunc) NULL,
		};
		sdl_type = gtk_type_unique (GTK_TYPE_WIDGET, &sdl_info);
	}

	return sdl_type;
}

static void gtk_sdl_class_init (GtkSDLClass *class)
{
  GtkObjectClass *object_class;
  GtkWidgetClass *widget_class;

	puts ("before class init");

	widget_class = GTK_WIDGET_CLASS (class);
	widget_class->realize = gtk_sdl_realize;
	widget_class->size_allocate = gtk_sdl_size_allocate;

	widget_class->expose_event = gtk_sdl_expose;

	parent_class = gtk_type_class (gtk_widget_get_type ());

	object_class = GTK_OBJECT_CLASS (class);
/*
	object_class->destroy = gtk_dial_destroy;
*/

/*
  widget_class->size_request = gtk_dial_size_request;
  widget_class->size_allocate = gtk_dial_size_allocate;
*/

	puts ("after class init");
}

static void gtk_sdl_init (GtkSDL *sdl)
{
	puts ("before sdl init");

	GTK_WIDGET_SET_FLAGS (sdl, GTK_CAN_FOCUS);
	if ( GTK_WIDGET_CAN_FOCUS(sdl) )
	{
		gtk_widget_grab_focus ( GTK_WIDGET (sdl) );
	}
	gtk_widget_set_events ( GTK_WIDGET (sdl), GDK_KEY_PRESS_MASK );

	puts ("after sdl init");
}

/**
 * Public function
 * Makes a new GtkSDL object and sets its initial size and colors using
 * the parameters supplied.
 * You may cast the returned GtkWidget to a GtkSDL object using GTK_SDL()
 */

GtkWidget *gtk_sdl_new (gint width, gint height, gint bpp, Uint32 flags)
{
  GtkSDL *sdl;

	puts ("before sdl new");

	sdl = gtk_type_new (gtk_sdl_get_type ());

	sdl->width = width;
	sdl->height = height;
	sdl->bpp = bpp;
	sdl->flags = flags;

	gtk_sdl_size ( GTK_SDL (sdl), width, height);

/*
	timeout_id = gtk_timeout_add ( (33*10)/10 , cbDrawAreaUpdate, (gpointer )darea);
	gtk_object_set_data ( GTK_OBJECT (sdl), "timeout_id", (gpointer )timeout_id );
*/
	puts ("after sdl new");

	return GTK_WIDGET (sdl);
}

/**
 * Public function
 * changes the size of a GtkSDL object
 */

void gtk_sdl_size (GtkSDL *sdl, gint width, gint height)
{
	puts ("before sdl size");

	g_return_if_fail (GTK_IS_SDL (sdl));

	GTK_WIDGET (sdl)->requisition.width = width;
	GTK_WIDGET (sdl)->requisition.height = height;

	gtk_widget_queue_resize (GTK_WIDGET (sdl));

	puts ("after sdl size");
}

static void gtk_sdl_realize (GtkWidget *widget)
{
  GtkSDL *sdl;
  GdkWindowAttr attributes;
  gint attributes_mask;

	puts ("before sdl realize");

	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_SDL (widget));

	sdl = GTK_SDL (widget);
	GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);

	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.x = widget->allocation.x;
	attributes.y = widget->allocation.y;
	attributes.width = widget->allocation.width;
	attributes.height = widget->allocation.height;
	attributes.wclass = GDK_INPUT_OUTPUT;
	attributes.visual = gtk_widget_get_visual (widget);
	attributes.colormap = gtk_widget_get_colormap (widget);
	attributes.event_mask = gtk_widget_get_events (widget) | GDK_EXPOSURE_MASK;

	attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;

	widget->window = gdk_window_new (gtk_widget_get_parent_window (widget), &attributes, attributes_mask);
	gdk_window_set_user_data (widget->window, sdl);

	widget->style = gtk_style_attach (widget->style, widget->window);
	gtk_style_set_background (widget->style, widget->window, GTK_STATE_NORMAL);

	gtk_sdl_send_configure (GTK_SDL (widget));

	puts ("after sdl realize");
}

static void gtk_sdl_size_allocate (GtkWidget *widget, GtkAllocation *allocation)
{
	puts ("before sdl size allocate");

	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_SDL (widget));
	g_return_if_fail (allocation != NULL);

	widget->allocation = *allocation;
	/* FIXME, TODO-1.3: back out the MAX() statements */
	widget->allocation.width = MAX (1, widget->allocation.width);
	widget->allocation.height = MAX (1, widget->allocation.height);

	if (GTK_WIDGET_REALIZED (widget))
	{
		gdk_window_move_resize (widget->window,
					allocation->x, allocation->y,
					allocation->width, allocation->height);

		gtk_sdl_send_configure (GTK_SDL (widget));
	}

	puts ("after sdl size allocate");
}

static void gtk_sdl_send_configure (GtkSDL *sdl)
{
  GtkWidget *widget;
  GdkEventConfigure event;

	puts ("before sdl send configure");

	widget = GTK_WIDGET (sdl);

	event.type = GDK_CONFIGURE;
	event.window = widget->window;
	event.send_event = TRUE;
	event.x = widget->allocation.x;
	event.y = widget->allocation.y;
	event.width = widget->allocation.width;
	event.height = widget->allocation.height;

	gtk_widget_event (widget, (GdkEvent*) &event);

	puts ("after sdl send configure");
}

static void gtk_sdl_surface_attach (GtkSDL *sdl)
{
  gchar SDL_windowhack[32];

	puts ("before sdl surface attach");

		/* Attach the SDL_Surface */

		puts ("attaching the surface");

		sprintf (SDL_windowhack, "SDL_WINDOWID=%ld",
			GDK_WINDOW_XWINDOW ( GTK_WIDGET(sdl)->window ) );
		puts (SDL_windowhack);
		putenv (SDL_windowhack);

		SDL_QuitSubSystem (SDL_INIT_VIDEO);
		puts ("before creating new surface");
		if ( SDL_InitSubSystem ( SDL_INIT_VIDEO ) < 0)
		{
			fprintf (stderr, "unable to init SDL: %s", SDL_GetError() );
			return;
		}
		puts ("after creating new surface");

		if (sdl->flags &= (SDL_OPENGLBLIT | SDL_DOUBLEBUF))
		{
			SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
		}

		if (sdl->surface)
		{
			puts ("TODO: deallocate previus surface");
		}

		sdl->surface = SDL_SetVideoMode( sdl->width, sdl->height, sdl->bpp, sdl->flags);
		if (!sdl->surface)
		{
			fprintf (stderr, "Unable to set the video mode: %s", SDL_GetError() );
			return;
		}

	puts ("after sdl surface attach");
}

static gint gtk_sdl_expose (GtkWidget *widget, GdkEventExpose *event)
{
  SDL_Surface *surface;
  SDL_Rect dest;

	puts ("before sdl expose");

	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_SDL (widget), FALSE);
	g_return_val_if_fail (event != NULL, FALSE);

	if (event->count > 0) return FALSE;

	surface = SDL_GetVideoSurface ();

	if (!surface)
	{
		gtk_sdl_surface_attach (GTK_SDL (widget));
	}

	gtk_sdl_display_update ( GTK_SDL(widget) );

/* 	if (surface) */
/* 	{ */

/* 		puts ("update rects from expose"); */
	
/* 		dest.x = event->area.x; */
/* 		dest.y = event->area.y; */
/* 		dest.w = event->area.width; */
/* 		dest.h = event->area.height; */

		/* ADDED NOW! */
/* 		SDL_UpdateRect (surface, 0, 0, 0, 0); */

/* LATER OFF */
/* 		SDL_UpdateRects (surface, 1, &dest); */

/* 	} */
/* 	else */
/* 	{ */
/* 		gtk_sdl_surface_attach (GTK_SDL (widget)); */
/* 	} */

	puts ("after sdl expose");

	surface = SDL_GetVideoSurface ();
	printf ("surface is : %p\n", surface);
/* 	SDL_UpdateRect (surface, 0, 0, 0, 0); */
/* 	puts ("rectangle updated"); */

	return FALSE;
}

static void gtk_sdl_display_update (GtkSDL *sdl)
{

  SDL_Surface *surface;

	puts ("before sdl display update");

	g_return_if_fail (sdl != NULL);
	g_return_if_fail (GTK_IS_SDL (sdl));
	g_return_if_fail (sdl->surface);

	if ( (sdl->flags &=SDL_OPENGL) || (sdl->flags &= SDL_OPENGLBLIT) )
	{
		/*
		if (dkActiveUpdaterGL) (*dkActiveUpdaterGL)();
		*/
		SDL_GL_SwapBuffers ();
	}
	else
	{
		/*
		if (dkActiveUpdater) (*dkActiveUpdater)();
		*/
		puts ("get video surface");
		surface = SDL_GetVideoSurface ();
		puts ("flip video surface");
		SDL_Flip (surface);
	}

	puts ("before update rect");

	SDL_UpdateRect (surface, 0, 0, 0, 0);

	puts ("after update rect");

	puts ("after display update");
}
