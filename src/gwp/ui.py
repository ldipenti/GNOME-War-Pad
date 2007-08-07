# UI components

import pygtk
pygtk.require('2.0')

import gtk, math

from kiwi.ui.delegates import GladeDelegate, SlaveDelegate
from kiwi.ui.gadgets import quit_if_last

from gwp.models import Game
from gwp.widgets import Starchart, PlanetDrawable, ShipDrawable, Line
from gwp.collections import PlanetCollection, ShipCollection

class Shell(GladeDelegate):
    starchart = None

    def __init__(self):
        super(Shell, self).__init__(gladefile="shell",
                                    delete_handler=self.quit_if_last)
        self.__init_starchart()
        self.__init_menu()

    def __init_menu(self):
        m = gtk.Menu()
        layers_menu = gtk.MenuItem('_Layers', True)
        layers_menu.set_submenu(m)

        for l in self.starchart.get_layer_list():
            item = gtk.CheckMenuItem(l['description'])
            item.set_active(l['enabled'])
            item.connect('toggled', self.__do_toggle_layer, l['name'])
            m.add(item)
        
        self.menubar.append(layers_menu)

    def __do_toggle_layer(self, checkmenuitem, layer):
        '''
        Callback to update layer status
        '''
        self.starchart.enable_layer(layer, checkmenuitem.active)

    def __init_starchart(self):
        game = Game()
        game.planets = PlanetCollection(game.path, game.race)
        game.ships = ShipCollection(game.path, game.race)

        # Init starchart
        self.starchart = Starchart()
        self.starchart.add_layer('planets', description='The planets')
        self.starchart.add_layer('ships', description='The ships')
        self.starchart.add_layer('constellations', description='Planet constellations')

        # Object addition
        self.starchart.add_drawables(game.planets, PlanetDrawable, layer='planets')
        self.starchart.add_drawables(game.ships, ShipDrawable, layer='ships')
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
                                            (0.4, 0.4, 0.4)), layer='constellations')
        return
    pass # End of Shell class

