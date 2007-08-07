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


    def __init_starchart(self):
        game = Game()
        game.planets = PlanetCollection(game.path, game.race)
        game.ships = ShipCollection(game.path, game.race)
        # Init starchart
        self.starchart = Starchart()
        self.starchart.add_drawables(game.planets, PlanetDrawable)
        self.starchart.add_drawables(game.ships, ShipDrawable)
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
                                            (0.4, 0.4, 0.4)))
        return
    pass # End of Shell class

