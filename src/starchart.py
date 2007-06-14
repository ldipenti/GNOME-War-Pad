#! /usr/bin/env python

import pygtk
pygtk.require('2.0')
import gtk, gobject, cairo, pango
import math
#import profile

from gwp.widgets import Starchart, PlanetDrawable, ShipDrawable, Line, MinefieldDrawable
from gwp.collections import PlanetCollection, ShipCollection, MinefieldCollection

def run(Widget):
    window = gtk.Window()
    window.connect("delete-event", gtk.main_quit)
    planets = PlanetCollection('/home/ldipenti/VP/ARGF4/', 8)
    ships = ShipCollection('/home/ldipenti/VP/ARGF4/', 8)
    minefields = MinefieldCollection('/home/ldipenti/VP/ARGF4/', 8)
    screen = Widget()
    screen.add_drawables(minefields, MinefieldDrawable)
    screen.add_drawables(planets, PlanetDrawable)
    screen.add_drawables(ships, ShipDrawable)

    # Draw constellations
    p = planets.values()
    while len(p) > 1:
        planet_a = p.pop()
        for planet_b in p:
            distance =  abs(math.hypot(planet_b.x - planet_a.x,
                                       planet_b.y - planet_a.y))
            if distance <= 84:
                screen.add(Line(planet_a.x, planet_a.y, planet_b.x, planet_b.y,
                                (0.4, 0.4, 0.4)))

    screen.connect("selected", myCallback)
    screen.show()
    window.add(screen)
    window.present()
    gtk.main()

def myCallback(obj, x, y, data=None):
    print x, y

if __name__ == "__main__":
    run(Starchart)
    #profile.run('run(Starchart)')

