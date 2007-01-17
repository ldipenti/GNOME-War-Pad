#!/usr/bin/python

from gwp.collections import PlanetCollection
from gwp.collections import ShipCollection
from gwp.widgets import Starchart
import gtk

p = PlanetCollection('/home/ldipenti/VP/ARGF4/', 8)
s = ShipCollection('/home/ldipenti/VP/ARGF4/', 8)
sc = Starchart(p, s)

w = gtk.Window()
w.set_title('GWP a full')
w.add(sc)
w.show_all()
gtk.main()
