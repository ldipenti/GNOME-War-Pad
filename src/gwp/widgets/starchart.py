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
        "selected" : (gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE,
                      (gobject.TYPE_FLOAT, gobject.TYPE_FLOAT,))
        }

    def __init__(self):
        gtk.DrawingArea.__init__(self)

        self.set_flags(gtk.CAN_FOCUS)
        self.add_events(gtk.gdk.BUTTON_PRESS_MASK |
                        gtk.gdk.SCROLL_MASK |
                        gtk.gdk.BUTTON1_MOTION_MASK)
        self.layout = None

        # Viewport attrs
        self.x = 1900
        self.y = 1900
        self.zoom = 1.0
        self.zoom_max = 3.0
        self.zoom_min = 0.3
        self.zoom_step = 0.15

        # Objects to draw
        self.drawings = []
        self.drawables = []

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
        if event.button == 3:
            x, y = self.coord_c2v(event.x, event.y)
            self.emit('selected', x, y)
        elif event.button == 1:
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

        self.cr.set_line_width(1)

        # NOTE: Actual drawings go below this line!!!

        # Drawing groups
        self.__draw_drawables()
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

    def add(self, drawing):
        self.drawings.append(drawing)

    def __draw_drawings(self):
        for drawing in self.drawings:
            self.cr.save()
            drawing.draw(self)
            self.cr.restore()
        self.cr.stroke()

    def add_drawables(self, obj_list, Drawable):
        '''
        Adds a list of tuples, containing the object list and the method
        to draw those objects.
        '''
        self.drawables.append((obj_list, Drawable))

    def __draw_drawables(self):
        for obj_list, Drawable in self.drawables:
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
        # Filter
        return [obj for obj in obj_list if self.__in_viewport(obj.x-margin, obj.y-margin, obj.x+margin, obj.y+margin)]

    def __in_viewport(self, x1, y1, x2, y2):
        '''
        Returns True if rectangle described by (x1, y1) and (x2, y2) is totally
        or partially in the viewport.
        '''
        # Viewport boundaries in "units"
        v_x1 = self.x
        v_y1 = self.y
        v_x2 = self.x + self.allocation.width / self.zoom
        v_y2 = self.y + self.allocation.height / self.zoom

        if (v_x1 < x1 and v_x1 < x2 and v_x2 < x1 and v_x2 < x2) or (v_x1 > x1 and v_x1 > x2 and v_x2 > x1 and v_x2 > x2):
            return False
        elif (v_y1 < y1 and v_y1 < y2 and v_y2 < y1 and v_y2 < y2) or (v_y1 > y1 and v_y1 > y2 and v_y2 > y1 and v_y2 > y2):
            return False
        else:
            return True

    #####
    # Drawing primitives
    #####

    # Line (from, to)
    def line(self, x1, y1, x2, y2, rgb=(1, 1, 1)):
        '''
        Draws a line on the starchart
        '''
        if self.__in_viewport(x1, y1, x2, y2):
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
        if self.__in_viewport(x-radius, y-radius, x+radius, y+radius):
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
        if self.__in_viewport(x1, y1, x2, y2):
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

        # Avoid memory leaks, one layout is enough
        if self.layout == None:
            self.layout = self.cr.create_layout()
        
        self.layout.set_text(text)
        self.layout.set_font_description(pango.FontDescription("sans serif " + str(text_size)))
        fontw, fonth = self.layout.get_pixel_size()
        
        x1 = x - fontw / self.zoom / 2
        y1 = y - fonth / self.zoom / 2
        x2 = x + fontw / self.zoom / 2
        y2 = y + fonth / self.zoom / 2

        if self.__in_viewport(x1, y1, x2, y2):
            self.cr.save()
            self.cr.set_source_rgb(*rgb)
            self.cr.move_to(xt - fontw / 2, yt + fonth / 2)
            self.cr.scale(1.0, -1.0)
            self.cr.show_layout(self.layout)
            self.cr.stroke()
            self.cr.restore()

    # Polygon defined by a list of points
    def polygon(self, points, rgb=(1, 1, 1), filled=False):
        '''
        Draws a polygon from a list of points
        '''
        if len(points) < 3:
            print "Error: Polygon needs at least 3 points"
            return

        # Check visibility
        lx = []
        ly = []
        for x, y in points:
            lx.append(x)
            ly.append(y)
        if self.__in_viewport(min(lx), min(ly), max(lx), max(ly)):
            # Initial point
            ix, iy = points[0]
            x, y = self.coord_v2c(ix, iy)
            self.cr.move_to(x, y)
            # The rest
            self.cr.save()
            self.cr.set_source_rgb(*rgb)
            for (vx, vy) in points[1:]:
                cx, cy = self.coord_v2c(vx, vy)
                self.cr.line_to(cx, cy)
            self.cr.close_path()
            if filled: self.cr.fill()
            self.cr.stroke()
            self.cr.restore()

    #####
    # Other primitives
    #####
    # Rotate the following drawings
    def rotate(self, x, y, angle):
        '''
        Rotate using (x, y) as rotation point, and angle in degrees
        '''
        rx, ry = self.coord_v2c(x, y)
        # Translate to the center, rotate, and un-translate
        self.cr.translate(rx, ry)
        self.cr.rotate(-1 * angle * math.pi / 180)
        self.cr.translate(-1.0 * rx, -1.0 * ry)
        
    pass # End of Starchart class

gobject.type_register(Starchart)

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
    def __init__(self, obj):
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
    def __init__(self, obj):
        Drawable.__init__(self, obj)

    def draw(self, starchart):
        starchart.rotate(self.obj.x, self.obj.y, self.obj.heading)
        starchart.polygon([(self.obj.x-1, self.obj.y-1),
                           (self.obj.x+1, self.obj.y-1),
                           (self.obj.x, self.obj.y+2)],
                          rgb=(0, 1, 0), filled=True)
    pass # End of ShipDrawable class

class Line:
    def __init__(self, x1, y1, x2, y2, rgb=(1, 1, 1)):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.rgb = rgb

    def draw(self, starchart):
        starchart.line(self.x1, self.y1, self.x2, self.y2, self.rgb)

    pass

class Circle:
    def __init__(self, x, y, radius, rgb=(1, 1, 1), filled=False):
        self.x = x
        self.y = y
        self.radius = radius
        self.rgb = rgb
        self.filled
    def draw(self, starchart):
        starchart.circle(self.x, self.y, self.radius, self.rgb, self.filled)

class Rectangle:
    def __init__(self, x1, y1, x2, y2, rgb=(1, 1, 1), filled=False):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.rgb = rgb
        self.filled = filled
    def draw(self, starchart):
        starchart.rectangle(self.x1, self.y1,
                            self.x2, self.y2, self.rgb, self.filled)

class Text:
    def __init__(self, x, y, text, rgb=(1, 1, 1), size=5, scale=False):
        self.x = x
        self.y = y
        self.text = text
        self.rgb = rgb
        self.size = size
        self.scale = scale
    def draw(self, starchart):
        starchart.text(self.x, self.y, self.text, self.rgb, self.size, self.scale)

class Polygon:
    def __init__(self, points, rgb=(1, 1, 1), filled=False):
        self.points = points
        self.rgb = rgb
        self.filled = filled
    def draw(self, starchart):
        starchart.polygon(self.points, self.rgb, self.filled)

