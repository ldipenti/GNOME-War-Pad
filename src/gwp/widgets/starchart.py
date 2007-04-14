import pygtk
pygtk.require('2.0')
import gtk, gobject, cairo, pango
import math

from gwp.collections import PlanetCollection, ShipCollection

class Starchart(gtk.DrawingArea):
    __gsignals__ = {
        "expose-event" : "override",
        "key-press-event" : "override",
        "button-press-event" : "override",
        "motion-notify-event" : "override",
        "scroll-event" : "override",
        }

    def __init__(self):
        gtk.DrawingArea.__init__(self)

        self.set_flags(gtk.CAN_FOCUS)
        self.add_events(gtk.gdk.BUTTON_PRESS_MASK |
                        gtk.gdk.SCROLL_MASK |
                        gtk.gdk.BUTTON1_MOTION_MASK)

        # Viewport attrs
        self.x = 1900
        self.y = 1900
        self.zoom = 1.0
        self.zoom_max = 3.0
        self.zoom_min = 0.3
        self.zoom_step = 0.15

        # Objects to draw
        self.drawings = []

    def coord_c2v(self, x, y):
        '''
        Convert coordinates from Cairo system to VGAP system
        '''
        x = self.x + x / self.zoom
        y = self.y + (self.allocation.height - y) / self.zoom
        return x, y

    def coord_v2c(self, x, y):
        '''
        Convert coordinates from VGAP system to Cairo system
        '''
        x = self.zoom * (x - self.x)
        y = self.zoom * (y - self.y)
        return x, y

    # Mouse events
    def do_button_press_event(self, event):
        self.x_tmp = self.x
        self.y_tmp = self.y
        self.drag_x = event.x
        self.drag_y = event.y

    def do_motion_notify_event(self, event):
        self.x = self.x_tmp + (self.drag_x - event.x) / self.zoom
        self.y = self.y_tmp - (self.drag_y - event.y) / self.zoom
        # Force redraw
        self.queue_draw()

    def do_scroll_event(self, event):
        if event.direction == gtk.gdk.SCROLL_UP:
            self.__zoom(event.x, event.y, 1.15)
        else:
            self.__zoom(event.x, event.y, 0.85)

    # Keyboard events
    def do_key_press_event(self, event):
        k = gtk.gdk.keyval_name(event.keyval)
        if k == 'Up':
            self.__pan(0, 1)
        elif k == 'Down':
            self.__pan(0, -1)
        elif k == 'Left':
            self.__pan(-1, 0)
        elif k == 'Right':
            self.__pan(1, 0)
        elif k == 'KP_Add':
            x = self.allocation.width / 2
            y = self.allocation.height / 2
            self.__zoom(x, y, 1.15)
        elif k == 'KP_Subtract':
            x = self.allocation.width / 2
            y = self.allocation.height / 2
            self.__zoom(x, y, 0.85)
        else:
            print "Unhandled Key: '" + k + "'"

    # Handle contents redraw
    def do_expose_event(self, event):
        self.cr = self.window.cairo_create()
        self.cr.rectangle(event.area.x, event.area.y,
                          event.area.width, event.area.height)
        self.cr.clip()
        self.draw(*self.window.get_size())

    def draw(self, width, height):
        self.cr.set_source_rgb(0.0, 0.0, 0.0)
        self.cr.rectangle(0, 0, width, height)
        self.cr.fill()

        # Coordinate transformation: this mirrors the Y axis so that
        # Y=0 is below
        self.cr.scale(1.0, -1.0)
        self.cr.translate(0, -1.0 * height)

        # NOTE: Actual drawings go below this line!!!
        self.text(2500, 2500, "Hola mi amor!!! :-*", size=10, scale=True)
        self.circle(2500, 2500, 50, (1, 0, 0))

        # Drawing groups
        self.__draw_drawings()

    def __pan(self, x_factor, y_factor):
        '''
        This method moves the viewport to a new location on the map
        based on the X and Y factors
        '''
        self.x += x_factor
        self.y += y_factor
        self.queue_draw()

    def __zoom(self, x, y, factor):
        '''
        This method calculates the X and Y shifting that the viewport
        has to make so that zooming will be made based on the pointer
        position (x, y)
        '''
        # Some limits to zooming in or out
        if factor > 1 and self.zoom >= self.zoom_max: return
        if factor < 1 and self.zoom <= self.zoom_min: return

        w = self.allocation.width
        h = self.allocation.height

        x2 = self.x + w / self.zoom
        # Viewport's width in "units"
        w2 = x2 - self.x
        # Margin in X
        hx = w2 - w2 * 1 / factor
        # Delta-shifting in X
        dx = hx * x / w
        self.x += dx

        y2 = self.y + h / self.zoom
        # Viewport's height in "units"
        h2 = y2 - self.y
        # Margin in Y
        hy = h2 - h2 * 1 / factor
        # Delta-shifting in Y
        dy = hy * (1-(y / h))
        self.y += dy
        
        # Zoooom!
        self.zoom *= factor

        # Redraw
        self.queue_draw()

    def add_drawings(self, obj_list, Drawable):
        '''
        Adds a list of tuples, containing the object list and the method
        to draw those objects.
        '''
        self.drawings.append((obj_list, Drawable))

    def __draw_drawings(self):
        for obj_list, Drawable in self.drawings:
            for obj in self.__obj_in_viewport(obj_list.values()):
                self.cr.save()
                Drawable(obj).draw(self)
                self.cr.restore()
            self.cr.stroke()

    def __obj_in_viewport(self, obj_list):
        '''
        Filters obj_list returning only those objects included within
        the viewport\'s boundaries
        '''
        margin = 5
        # Viewport boundaries in "units"
        x1 = self.x - margin
        y1 = self.y - margin
        x2 = self.x + margin + self.allocation.width / self.zoom
        y2 = self.y + margin + self.allocation.height / self.zoom
        # Filter
        return [obj for obj in obj_list if self.__is_in_viewport(obj, x1, y1, x2, y2)]

    def __is_in_viewport(self, obj, x1, y1, x2, y2):
        '''
        Returns if the object is within the viewport limits, passed as params
        '''
        return obj.x >= x1 and obj.x <= x2 and obj.y >= y1 and obj.y <= y2

    #####
    # Drawing primitives
    #####

    # Line (from, to)
    def line(self, x1, y1, x2, y2, rgb=(1, 1, 1)):
        '''
        Draws a line on the starchart
        '''
        x_from, y_from = self.coord_v2c(x1, y1)
        x_to, y_to = self.coord_v2c(x2, y2)

        self.cr.save()
        self.cr.set_source_rgb(*rgb)
        self.cr.move_to(x_from, y_from)
        self.cr.line_to(x_to, y_to)
        self.cr.stroke()
        self.cr.restore()
    
    # Circle (center, radius)
    def circle(self, x, y, radius, rgb=(1, 1, 1), filled=False):
        '''
        Draws a circle based on center coords and radius
        '''
        xc, yc = self.coord_v2c(x, y)
        r = radius * self.zoom

        self.cr.save()
        self.cr.set_source_rgb(*rgb)
        self.cr.arc(xc, yc, r, 0, 2 * math.pi)
        if filled: self.cr.fill()
        self.cr.stroke()
        self.cr.restore()

    # Rectangle (1st corner, 2nd corner)
    def rectangle(self, x1, y1, x2, y2, rgb=(1, 1, 1), filled=False):
        '''
        Draws a rectangle from two points
        '''
        x, y = self.coord_v2c(x1, y1)
        width = (x2 - x1) * self.zoom
        height = (y2 - y1) * self.zoom

        self.cr.save()
        self.cr.set_source_rgb(*rgb)
        self.cr.rectangle(x, y, width, height)
        if filled: self.cr.fill()
        self.cr.stroke()
        self.cr.restore()

    # Text
    def text(self, x, y, text, rgb=(1, 1, 1), size=5, scale=False):
        '''
        Draws text strings on the starchart
        '''
        xt, yt = self.coord_v2c(x, y)
        if scale:
            text_size = int(round(size * self.zoom))
        else:
            text_size = int(round(size))

        self.cr.save()
        self.cr.set_source_rgb(*rgb)
        layout = self.cr.create_layout()
        layout.set_text(text)
        layout.set_font_description(pango.FontDescription("sans serif " + str(text_size)))
        fontw, fonth = layout.get_pixel_size()
        self.cr.move_to(xt - fontw / 2, yt + fonth / 2)
        self.cr.scale(1.0, -1.0)
        self.cr.show_layout(layout)
        self.cr.stroke()
        self.cr.restore()
        
    pass # End of Starchart class

class Drawable:
    '''
    Abstract class to represent any drawable object on the screen
    '''
    def __init__(self, obj=None):
        '''
        Initialisation
        '''
        self.obj = obj
        
    def draw(self, starchart):
        '''
        Here goes the actual cairo drawing
        '''
        pass

    pass # End of Drawable class

class PlanetDrawable(Drawable):
    '''
    How to draw a planet
    '''
    def __init__(self, obj=None):
        Drawable.__init__(self, obj)

    def draw(self, starchart):
        # Avoid planets to be shown too small on zoom out
        if starchart.zoom < 0.8:
            size = 2 / starchart.zoom
        else:
            size = 2
            
        # Draw planet
        starchart.circle(self.obj.x, self.obj.y, size,
                         rgb=(0.3, 0.3, 0.9), filled=True)

        # Show planet's name when zooming
        if starchart.zoom > 1.2:
            starchart.text(self.obj.x, self.obj.y - 8,
                           self.obj.name,
                           rgb=(0.6, 0.6, 0.6), size=8)
    pass # End of PlanetDrawable class


class ShipDrawable(Drawable):
    '''
    How to draw a ship
    '''
    def __init__(self, x, y, obj=None):
        Drawable.__init__(self, x, y, obj)

    def draw(self, context, zoom=1):
        # mini canvas size
        w, h = (5 * zoom, 5 * zoom)

        # Avoid ship being too tiny on zoom-out
        if zoom < 1: zoom = 1

        # Triangle data
        angle = -1.0 * self.obj.heading
        base = 2 * zoom
        top = base * 2

        # Create new drawing buffer
        img = cairo.ImageSurface(cairo.FORMAT_ARGB32,
                                 int(round(w * zoom)),
                                 int(round(h * zoom)))
        ctx = cairo.Context(img)

        # Matrix transformation apply from bottom to top!
        ctx.translate(w / 2, h / 2)
        ctx.rotate(angle * math.pi / 180)

        # Draw ship
        ctx.set_source_rgb(0.0, 1.0, 0.0)
        ctx.move_to(-1 * base / 2, -1 * top / 2)
        ctx.rel_line_to(base, 0)
        ctx.rel_line_to(-1 * base / 2, top)
        ctx.close_path()
        ctx.fill()
        ctx.stroke()

        # Apply buffer on starchart
        context.set_source_surface(img, self.x - w/2, self.y - h/2)
        context.paint()

    pass # End of ShipDrawable class


