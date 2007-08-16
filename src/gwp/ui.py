# UI components

import pygtk
pygtk.require('2.0')

import gtk, math

from kiwi.ui.delegates import GladeDelegate, SlaveDelegate
from kiwi.ui.gadgets import quit_if_last

import gwp
from gwp.models import Game
from gwp.widgets import Starchart, PlanetDrawable, ShipDrawable, Line, Rectangle
from gwp.collections import PlanetCollection, ShipCollection
from gwp.widgets import pycons

class Shell(GladeDelegate):
    def __init__(self):
        super(Shell, self).__init__(gladefile="shell",
                                    delete_handler=self.do_quit)
        self.console = None
        self.starchart = None
        
        self.__init_starchart()
        self.__init_menu()

    def __init_menu(self):
        m = gtk.Menu()
        layers_menu = gtk.MenuItem('_Layers', True)
        layers_menu.set_submenu(m)

        for l in self.starchart.get_layer_list('shell'):
            item = gtk.CheckMenuItem(l['description'])
            item.set_active(l['enabled'])
            item.connect('toggled', self.__do_toggle_layer, l['name'])
            m.add(item)
        
        self.menubar.append(layers_menu)

    def do_quit(self, *args):
        '''
        Quits GWP
        '''
        print "Bye bye!"
        gtk.main_quit()
        
    def do_show_console(self, action):
        '''
        Sets up a python console with useful live objects within its scope
        to do debugging.
        '''
        if self.console == None:
            self.console = pycons.ConsoleWindow({'__builtins__': __builtins__,
                                                 'starchart': self.starchart,
                                                 'game': Game(),
                                                 'gwp': gwp,
                                                 '__doc__': None},
                                                title = 'GWP Debugging Console')
            self.console.win.connect('delete-event', self.__do_remove_console)
        
    def __do_remove_console(self, w, data):
        self.console = None
        
    def __do_toggle_layer(self, checkmenuitem, layer):
        '''
        Callback to update layer status
        '''
        self.starchart.enable_layer(layer, 'shell', checkmenuitem.active)

    def __init_starchart(self):
        game = Game()
        game.planets = PlanetCollection(game.path, game.race)
        game.ships = ShipCollection(game.path, game.race)

        # Init starchart
        self.starchart = Starchart()
        self.starchart.add_layer('planets', group='shell',
                                 description='The planets')
        self.starchart.add_layer('ships', group='shell',
                                 description='The ships')
        self.starchart.add_layer('constellations', group='shell',
                                 description='Planet constellations')
        # FIXME: This layer shouldn't be in the "layers" menu...maybe we
        # should implement layer groups?
        self.starchart.add_layer('selection', group='system',
                                 description='Selection area')

        # Signals
        self.starchart.connect('selected', self._do_starchart_selected)
        self.starchart.connect('selected-area', self._do_starchart_selected_area)
        self.starchart.connect('selecting-area', self._do_starchart_selecting_area)
        
        # Object addition
        self.starchart.add_drawables(game.planets, PlanetDrawable,
                                     layer='planets', group='shell')
        self.starchart.add_drawables(game.ships, ShipDrawable,
                                     layer='ships', group='shell')
        self.starchart.show()

        # Locate starchart in UI
        slave = SlaveDelegate(toplevel=self.starchart)
        self.attach_slave("eventbox_starchart", slave)
        slave.focus_toplevel()

        # Init constellations
        p = game.planets.values()
        while len(p) > 1:
            planet_a = p.pop()
            for planet_b in p:
                distance =  abs(math.hypot(planet_b.x - planet_a.x,
                                           planet_b.y - planet_a.y))
                if distance <= 84:
                    self.starchart.add(Line(planet_a.x, planet_a.y, planet_b.x, planet_b.y,
                                            (0.4, 0.4, 0.4)), layer='constellations', group='shell')

        # Selection area
        self.selection = Rectangle(0, 0, 0, 0,
                                   rgba=(0.1, 0.1, 1, 0.3),
                                   filled=True)
        self.starchart.add(self.selection, layer='selection', group='system')
        return

    def _do_starchart_selected(self, w, x, y):
        print "Selected Point: (%d, %d)" % (x, y)

    def _do_starchart_selecting_area(self, w, x1, y1, x2, y2):
        print "Selecting Area: (%d, %d) - (%d, %d)" % (x1, y1, x2, y2)
        self.selection.x1 = x1
        self.selection.y1 = y1
        self.selection.x2 = x2
        self.selection.y2 = y2

    def _do_starchart_selected_area(self, w, x1, y1, x2, y2):
        print "Selected Area: (%d, %d) - (%d, %d)" % (x1, y1, x2, y2)
        self.selection.x1 = 0
        self.selection.y1 = 0
        self.selection.x2 = 0
        self.selection.y2 = 0

    pass # End of Shell class

