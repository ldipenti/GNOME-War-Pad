#!/usr/bin/env python

import pygtk
pygtk.require('2.0')

import gtk, gobject, cairo, pango
import math

from gwp.collections import PlanetCollection, ShipCollection
from gwp.widgets import Starchart, PlanetDrawable, ShipDrawable

from kiwi.ui.delegates import SlaveDelegate, Delegate
from kiwi.ui.gadgets import quit_if_last
from kiwi.ui.objectlist import Column, ObjectList


import os.path

class Shell(Delegate):
    my_widgets = ["entry_dir", "button_open"]
    planets = None
    ships = None
    planetslave = None
    starchart = None
    
    def __init__(self):
        Delegate.__init__(self, gladefile="starchartview",
                          widgets=self.my_widgets,
                          delete_handler=quit_if_last)

        self.planetslave = PlanetData()
        self.attach_slave("eventbox2", self.planetslave)

        # object list
        self.objlist = ObjectList([Column('id', data_type=int, sorted=True),
                                   Column('name', data_type=str),
                                   ])
        slave = SlaveDelegate(toplevel=self.objlist)
        self.attach_slave("eventbox3", slave)


    def on_button_open__clicked(self, widget):
        path = self.entry_dir.get_text()
        
        if path != "" and os.path.isdir(path):
            path += '/'
            self.planets = PlanetCollection(path, 7)
            self.ships = ShipCollection(path, 7)
            self.starchart = Starchart()
            self.starchart.add_drawables(self.planets, PlanetDrawable)
            self.starchart.add_drawables(self.ships, ShipDrawable)
            self.starchart.connect("selected", self.on_starchart_selected)
            self.starchart.show()
            
            slave = SlaveDelegate(toplevel=self.starchart)
            self.attach_slave("eventbox1", slave)
            slave.focus_toplevel()
            self.slave = slave

    def on_starchart_selected(self, widget, x, y, data=None):
        min_dist = 99999999
        ret = None
        objlist = []
        objects = self.planets.values() + self.ships.values()
        for obj in objects:
            distance =  abs(math.hypot(obj.x - x,
                                       obj.y - y))
            if distance < min_dist:
                min_dist = distance
                objlist = [ obj ]
                ret = obj
            elif distance == min_dist:
                objlist.append(obj)

        self.starchart.move(ret.x - x, ret.y - y)

        # Reset model to none so it wont complain of different models assignments
        #self.planetslave.proxy.set_model(None)
        #self.planetslave.proxy.set_model(ret)
        
        self.objlist.clear()
        self.objlist.extend(objlist)


class PlanetData(SlaveDelegate):
    planetwidgets = ["name", "owner", "id"]
    proxy = None
    
    def __init__(self):
        SlaveDelegate.__init__(self, gladefile="planetdata",
                               toplevel_name="window1",
                               widgets=self.planetwidgets)

        self.proxy = self.add_proxy(model=None, widgets=self.planetwidgets)
        self.owner.prefill([
            ("desconocido", -1),
            ("Feds", 1),
            ("Lizard", 2),
            ("Birdmen", 3),
            ("Fascists", 4),
            ("Privateers", 5),
            ("Borg", 6),
            ("Crystal People", 7),
            ("Evils", 8),
            ("Robots", 9),
            ("Rebels", 10),
            ("Colonies of Man", 11),
            ])



app = Shell()
app.show_all()
gtk.main()
