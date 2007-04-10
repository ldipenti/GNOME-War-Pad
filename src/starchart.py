#! /usr/bin/env python

import pygtk
pygtk.require('2.0')
import gtk, gobject, cairo, pango
import math

from gwp.widgets import Starchart, PlanetDrawable, ShipDrawable
from gwp.collections import PlanetCollection, ShipCollection


def run(Widget):
    window = gtk.Window()
    window.connect("delete-event", gtk.main_quit)
    planets = PlanetCollection('/home/ldipenti/VP/ARGF4/', 8)
    ships = ShipCollection('/home/ldipenti/VP/ARGF4/', 8)
    screen = Widget()
    screen.add_drawings(planets, PlanetDrawable)
    screen.add_drawings(ships, ShipDrawable)
    screen.show()
    window.add(screen)
    window.present()
    gtk.main()

if __name__ == "__main__":
    run(Starchart)
