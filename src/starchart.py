#!/usr/bin/python2.4

import pygtk
pygtk.require('2.0')

import gobject
import pango
import gtk
import math
import time
from gtk import gdk

try:
    import cairo
except ImportError:
    pass

if gtk.pygtk_version < (2,7,99):
    print "PyGtk 2.7.99 or later required"
    raise SystemExit

TEXT = 'cairo'
BORDER_WIDTH = 10

import gwp.collections
import random

class StarchartFloatingObject(object):
    '''
    A drawable object in the starchart
    '''
    def __init__(self, obj):
        super(StarchartFloatingObject, self).__init__()
        self.obj = obj
        return

    def __getattr__(self, attr):
        if attr == 'x':
            return self.getX()
        elif attr == 'y':
            return self.getY()
        else:
            return self.obj.__getattribute__(attr)
        return

    def getX(self):
        return self.obj.x - 1000

    def getY(self):
        return (self.obj.y - 3000) * -1
    pass # End of class

class Point:
    def __init__(self,x,y):
        self.x = x
        self.y = y

    def __repr__(self):
        return str((self.x, self.y))

planetas = gwp.collections.PlanetCollection('/home/ldipenti/VP/ARGF4/', 8).values()
planetas = map(lambda x: StarchartFloatingObject(x), planetas)

viewport = [Point(850.0,850.0),Point(1150.0,1150.0)]
viewport_prev = [Point(850.0,850.0),Point(1150.0,1150.0)]

class PyGtkWidget(gtk.DrawingArea):

    ## no se como usar las gsignals en este caso...
    #__gsignals__ = { 'realize': 'override',
    #                 'expose-event' : 'override',
    #                 'size-allocate': 'override',
    #                 'size-request': 'override',}

    def __init__(self):
        gtk.DrawingArea.__init__(self)

        self.start = Point(0,0)

        self.add_events(gtk.gdk.BUTTON_PRESS_MASK |
                        gtk.gdk.BUTTON_RELEASE_MASK |
                        gtk.gdk.BUTTON1_MOTION_MASK |
                        gtk.gdk.SCROLL_MASK
                        )
        
        self.connect("expose_event", self.do_expose_event)
        self.connect("button_press_event", self.on_button_press_event)
        self.connect("button_release_event", self.on_button_release_event)
        self.connect("motion_notify_event", self.pan_move)
        self.connect("scroll_event", self.on_zoom_event)
        
        self.draw_gc = None
        self.layout = self.create_pango_layout(TEXT)
        self.layout.set_font_description(pango.FontDescription("sans serif 8"))
        self.names = map(lambda p: self.create_pango_layout(p.name), planetas)

    def pan_move(self,w, e):
        delta_x = (e.x - self.start.x) * (viewport[1].x - viewport[0].x) / float(w.allocation.width )
        delta_y = (e.y - self.start.y) *  (viewport[1].y - viewport[0].y) / float(w.allocation.height )
        viewport[0].x = viewport_prev[0].x - delta_x
        viewport[0].y = viewport_prev[0].y - delta_y
        viewport[1].x = viewport_prev[1].x - delta_x
        viewport[1].y = viewport_prev[1].y - delta_y
        self.draw()
        #Redibujamos el widget
        self.queue_draw()

    def pan_stop(self):
        viewport_prev[0].x = viewport[0].x
        viewport_prev[0].y = viewport[0].y
        viewport_prev[1].x  = viewport[1].x
        viewport_prev[1].y  = viewport[1].y
        self.draw()
        #Redibujamos el widget
        self.queue_draw()


    def on_zoom_event(self, w, e):
        if e.direction == gtk.gdk.SCROLL_UP:
            self.zoom(w, e.x, e.y, 0.85)
        else:
            self.zoom(w, e.x, e.y, 1.15)


    def zoom(self, w, x, y, relative_factor):
        another_x, another_y, w, h = w.allocation
        v_width = viewport[1].x - viewport[0].x
        v_height = viewport[1].y - viewport[0].y

        new_width = (v_width * relative_factor)
        new_height = (v_height * relative_factor)

        if (new_width > 100 and new_height > 100) and (new_width < 2000 and new_height < 2000):

            a_x = new_width * (x / w)
            viewport[0].x = viewport[0].x + (x / w) * v_width - a_x
            viewport[1].x = viewport[0].x + new_width  
            
            a_y = new_height * (y / h)
            viewport[0].y = viewport[0].y + (y / h) * v_height - a_y
            viewport[1].y = viewport[0].y + new_height

        self.pan_stop()
        self.draw()


    def on_button_release_event(self, w,e):
        self.pan_stop()

    def on_button_press_event(self, w,e):
        ## panning's starting point 
        self.start.x = e.x
        self.start.y = e.y

        #detect the planet.
        #(x, y) = convertCoords(viewport, w, e.x, e.y)
        pid = find_closest_planet(e.x,e.y)
        print pid
        planetas[pid].selected = not planetas[pid].selected
        self.draw()
        #Redibujamos el widget
        self.queue_draw()

    def refresh(self):
        x, y, w, h = self.allocation
        self.window.invalidate_rect((0,0,w,h),False)
        self.do_realize()

    def do_realize(self):
        self.set_flags(self.flags() | gtk.REALIZED)
        self.window = gdk.Window(self.get_parent_window(),
                                 width=self.allocation.width,
                                 height=self.allocation.height,
                                 window_type=gdk.WINDOW_CHILD,
                                 wclass=gdk.INPUT_OUTPUT,
                                 event_mask=self.get_events() | gdk.EXPOSURE_MASK)
        if not hasattr(self.window, "cairo_create"):
            self.draw_gc = gdk.GC(self.window,
                                  line_width=5,
                                  line_style=gdk.SOLID,
                                  join_style=gdk.JOIN_ROUND)

	self.window.set_user_data(self)
        self.style.attach(self.window)
        self.style.set_background(self.window, gtk.STATE_NORMAL)
        self.window.move_resize(*self.allocation)

    def do_size_request(self, requisition):
        # FIXME: no se esta ejecutando...
	width, height = self.layout.get_size()
	requisition.width = (width // pango.SCALE + BORDER_WIDTH*4)* 1.45
	requisition.height = (3 * height // pango.SCALE + BORDER_WIDTH*4) * 1.2

    def do_size_allocate(self, allocation):
        # FIXME: no se esta ejecutando...
        self.allocation = allocation
        if self.flags() & gtk.REALIZED:
            self.window.move_resize(*allocation)

    def _expose_gdk(self, event):
        x, y, w, h = self.allocation
        self.layout = self.create_pango_layout('no cairo')
        fontw, fonth = self.layout.get_pixel_size()
        self.style.paint_layout(self.window, self.state, False,
                                event.area, self, "label",
                                (w - fontw) / 2, (h - fonth) / 2,
                                self.layout)


    def _draw_a_planet(self,cr,p,radius):
        # FIXME: my_x and my_y  las debe devolver convertCoords()
        x, y, w, h = self.allocation
        viewport_width = viewport[1].x - viewport[0].x
        viewport_height = viewport[1].y - viewport[0].y
        my_x = (p.x  - viewport[0].x) / viewport_width * w
        my_y = (p.y  - viewport[0].y) / viewport_height * h

        if p.selected:
            cr.set_line_width (1)
            cr.set_source_rgb(1, 1, 0.7)
            cr.rectangle (my_x-(radius+2), my_y-(radius+2), (radius +2)*2, (radius +2)*2)
            cr.stroke()
            cr.set_source_rgba(1, 0.7, 0.1, 1)
        else:
            cr.set_source_rgba(1, 1, 0.7, 0.9) 

        cr.arc (my_x, my_y, math.ceil(radius), 0, 2 * math.pi)
        cr.fill ()

        if (viewport[1].x - viewport[0].x) < 400:
            cr.rectangle (my_x+10, my_y-30, 25, 32)
            cr.set_source_rgb(0.1, 0.1, 0.1) 
            cr.fill()
            cr.rectangle (my_x+10, my_y-30, 25, 32)
            cr.set_source_rgb(0.6, 0.8, 0.8) 
            cr.set_line_width (1)
            cr.stroke()
            #neu
            cr.set_source_rgba(1, 0.5, 0.5, 0.7) 
            cr.set_line_width (5)
            cr.move_to(my_x+15,my_y)
            h = p.ground_neu * (30.0 / 20000.0)
            cr.line_to(my_x+15,my_y - h)
            cr.stroke()
            #tri
            cr.set_source_rgba(0.5, 1, 0.5, 0.7) 
            cr.set_line_width (5)
            cr.move_to(my_x+20,my_y)
            h = p.ground_tri * (30.0 / 20000.0)
            cr.line_to(my_x+20,my_y - h)
            cr.stroke()
            #dur
            cr.set_source_rgba(0.5, 0.5, 1, 0.7) 
            cr.set_line_width (5)
            cr.move_to(my_x+25,my_y)
            h = p.ground_dur * (30.0 / 20000.0)
            cr.line_to(my_x+25,my_y - h)
            cr.stroke()
            #mol
            cr.set_source_rgba(1, 1, 1, 0.7) 
            cr.set_line_width (5)
            cr.move_to(my_x+30,my_y)
            h = p.ground_mol * (30.0 / 20000.0)
            cr.line_to(my_x+30,my_y - h)
            cr.stroke()

        
    def _draw_minimap(self,cr, w_mm, h_mm):
        x, y, w, h = self.allocation
        cr.set_source_rgb(0.2, 0.2, 0.2) 
        cr.rectangle (w-w_mm,h-h_mm,w_mm,h_mm)        
        cr.fill ()
        cr.stroke()

        cr.set_source_rgba(0.7, 0.7, 0.7, 0.5)
        x1 = (viewport[0].x / 2000.0) * w_mm + w-w_mm
        y1 = (viewport[0].y / 2000.0) * h_mm + h-h_mm
        x2 = ((viewport[1].x - viewport[0].x) / 2000.0) * w_mm 
        y2 = ((viewport[1].y - viewport[0].y) / 2000.0) * h_mm 

        cr.rectangle (x1,y1,x2,y2)   
        cr.fill ()
        cr.stroke()
        
    def _draw_lines(self,cr):
        return
        
    def _draw_planets(self,cr):
        x, y, w, h = self.allocation
        viewport_width = viewport[1].x - viewport[0].x
        viewport_height = viewport[1].y - viewport[0].y
        if viewport_width < 1000 and viewport_height < 1000:
            show_names = True
        else:
            show_names = False

        show_lines=True
        show_minimap=True

        for i in range(0,len(planetas)-1):
            p = planetas[i]
            # FIXME: my_x and my_y  las debe devolver convertCoords()
            my_x = (p.x  - viewport[0].x) / viewport_width * w
            my_y = (p.y  - viewport[0].y) / viewport_height * h
            if p.x > viewport[0].x and p.x < viewport[1].x and p.y > viewport[0].y and p.y < viewport[1].y:
                v_width = viewport[1].x - viewport[0].x
                #FIXME: draw_a_planet deberia estar completa aca
                self._draw_a_planet(cr,p,2000.0/v_width)

    
                if show_names:
                    cr.set_source_rgba(0.7, 1, 0.7, 0.5) 
                    cr.move_to(my_x - 30, my_y + 8)
                    cr.update_layout(self.names[i])
                    cr.show_layout(self.names[i])
                    cr.stroke()

        if show_lines:
            self._draw_lines(cr)

        if show_minimap:
            self._draw_minimap(cr,w/10.0,h/10.0)

    def draw(self):
        # background
        x, y, w, h = self.allocation
        try:
            self.context.set_source_rgb(0, 0, 0) 
            self.context.rectangle (0,0,w,h)
            self.context.fill ()
            self.context.stroke()
            
            self._draw_planets(self.context)
            fontw, fonth = self.layout.get_pixel_size()
            self.context.move_to((w - fontw - 4), (h - fonth ))
            self.context.update_layout(self.layout)
            self.context.show_layout(self.layout)
        except cairo.Error:
            # FIXME: says "cairo.Error: the target surface has been finished"
            pass

    def _expose_cairo(self, event):

        self.context.rectangle(event.area.x, event.area.y,
                     event.area.width, event.area.height)
        self.context.clip()
	
        self.draw()


    def do_expose_event(self,w, event):
        #self.chain(event)
        try:
            self.context = self.window.cairo_create()
        except AttributeError:
            return self._expose_gdk(event)
        return self._expose_cairo(event)



win = gtk.Window()
win.set_title('starchart')
win.connect('delete-event', gtk.main_quit)


def convertCoords(viewport, win, x, y):
    viewport_width = viewport[1].x - viewport[0].x
    viewport_height = viewport[1].y - viewport[0].y
    a_x, a_y, w, h = win.allocation
    delta_x = (float(x) / float(w)) * viewport_width
    delta_y = (float(y) / float(h)) * viewport_height

    return(viewport[0].x + delta_x, viewport[0].y + delta_y)

def find_closest_planet(x,y):
    closest=0
    dist=999999999999
    for a in planetas:
        if a.x > viewport[0].x and a.x < viewport[1].x and a.y > viewport[0].y and a.y < viewport[1].y:
            actual_dist = math.hypot(a.x - x, a.y - y)
            if actual_dist < dist:
                closest = a.id
                dist=actual_dist
    return closest

w = PyGtkWidget()
vb = gtk.VBox()
#b = gtk.Button("OK..")
#vb.add(b)
vb.add(w)
win.add(vb)

win.show_all()

gtk.main()

