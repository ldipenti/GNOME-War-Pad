#!/usr/bin/env python

import gtk

from gwp.collections import PlanetCollection

from kiwi.ui.delegates import SlaveDelegate, Delegate
from kiwi.ui.gadgets import quit_if_last
from kiwi.ui.objectlist import Column, ObjectList

class Shell(Delegate):
    my_widgets = ["name", "tri", "dur", "mol", "owner"]
    def __init__(self):
        Delegate.__init__(self, gladefile="planetview",
                          widgets=self.my_widgets,
                          delete_handler=quit_if_last)
        # Inside list
        plist = ObjectList([Column('id', data_type=int, sorted=True),
                            Column('name', data_type=str),
                            Column('megacredits', data_type=int),
                            Column('supplies', data_type=int)])
        planets = PlanetCollection('/home/ldipenti/VP/ARGF4/', 8)
        plist.extend(planets.values())
        plist.connect('row-activated', self.slave_row_activated)
        slave = SlaveDelegate(toplevel=plist)
        self.attach_slave("list_placeholder", slave)
        slave.focus_toplevel()
        self.slave = slave

    def slave_row_activated(self, list, planet):
        self.name.set_text("<b>#%d - %s</b>" % (planet.id, planet.name))
        self.tri.set_text(str(planet.mined_tri))
        self.dur.set_text(str(planet.mined_dur))
        self.mol.set_text(str(planet.mined_mol))
        self.owner.set_text(str(planet.owner))

app = Shell()
app.show_all()
gtk.main()
