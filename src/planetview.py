#!/usr/bin/env python

import gtk

from gwp.collections import PlanetCollection
from kiwi.ui.delegates import SlaveDelegate, Delegate
from kiwi.ui.gadgets import quit_if_last
from kiwi.ui.objectlist import Column, ObjectList


class PlanetList(SlaveDelegate):
    def __init__(self):
        planets = PlanetCollection('/home/ldipenti/VP/ARGF4/', 8)
        plist = ObjectList([Column('id', data_type=int),
                            Column('name', data_type=str),
                            Column('megacredits', data_type=int),
                            Column('supplies', data_type=int)])
        for planet in planets.values():
            plist.append(planet)
        SlaveDelegate.__init__(self, toplevel=plist)

slave = PlanetList()

class Shell(Delegate):
    my_widgets = ["name", "tri", "dur", "mol", "owner"]
    def __init__(self):
        Delegate.__init__(self, gladefile="planetview",
                          widgets=self.my_widgets,
                          delete_handler=quit_if_last)
        self.attach_slave("list_placeholder", slave)
        slave.focus_toplevel()
        self.slave = slave

app = Shell()
app.show_all()
gtk.main()
