#!/usr/bin/env python

import pygtk
pygtk.require('2.0')

import gtk, gobject, cairo, pango
import math

from gwp.collections import PlanetCollection, ShipCollection, RaceList
from gwp.widgets import Starchart, PlanetDrawable, ShipDrawable

from kiwi.ui.delegates import SlaveDelegate, Delegate
from kiwi.ui.gadgets import quit_if_last
from kiwi.ui.objectlist import Column, ObjectList

import os.path

class Singleton(object):
        def __new__(cls, *args, **kwds):
            it = cls.__dict__.get("__it__")
            if it is not None:
                return it
            cls.__it__ = it = object.__new__(cls)
            it.init(*args, **kwds)
            return it
        def init(self, *args, **kwds):
            pass


class GameData (Singleton):
    path = None
    racenum = None
    race_list = None
    state = False
    
    def __init__(self):
        pass

    def is_valid(self):
        return self.state

    def set_path(self, path):
        if path != "" and os.path.isdir(path):
            # TODO : verify path
            path += '/'
            self.path = path

            # Set gral data
            self.state = True
            self.race_list = RaceList( self.get_path() )

    def get_path(self):
        return self.path

    def get_race_num(self):
        # TODO: get from player data
        return 7

    def get_race_name(self):
        # TODO: get from player data
        return "Los Simios"
        
    def get_turn_number(self):
        # TODO: get from player data
        return 38

    def get_race_list(self):
        return self.race_list
    pass

class Shell(Delegate):
    my_widgets = ["entry_dir", "button_open", "race_name", "turn_number"]
    planets = None
    ships = None
    starchart = None
    planetslave = None
    objlist = None
    
    def __init__(self):
        Delegate.__init__(self, gladefile="starchartview",
                          widgets=self.my_widgets,
                          delete_handler=quit_if_last)
     
        # object list
        self.objlist = ObjectList([Column('id', data_type=int, sorted=True),
                                   Column('name', data_type=str),
                                   ])
        slave = SlaveDelegate(toplevel=self.objlist)
        self.attach_slave("eventbox3", slave)
            

    def on_button_open__clicked(self, widget):
        path = self.entry_dir.get_text()
        
        if path != "" and os.path.isdir(path):
            gd = GameData()
            gd.set_path(path)
            self.planets = PlanetCollection( gd.get_path(), gd.get_race_num() )
            self.ships = ShipCollection( gd.get_path(), gd.get_race_num() )
            self.starchart = Starchart()
            self.starchart.add_drawables(self.planets, PlanetDrawable)
            self.starchart.add_drawables(self.ships, ShipDrawable)
            self.starchart.connect("selected", self.on_starchart_selected)
            self.starchart.show()
            
            slave = SlaveDelegate(toplevel=self.starchart)
            self.attach_slave("eventbox1", slave)
            slave.focus_toplevel()
            self.slave = slave

            # Game data
            self.race_name.set_text( gd.get_race_name() )
            self.turn_number.set_text( "Turn " +  str(gd.get_turn_number()) )

            # object data
            self.planetslave = PlanetData()
            self.attach_slave("eventbox2", self.planetslave)


    def on_starchart_selected(self, widget, x, y, data=None):
        min_dist = 99999
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
        self.planetslave.proxy.set_model(None)
        self.planetslave.proxy.set_model(ret)
        
        self.objlist.clear()
        self.objlist.extend(objlist)
    pass

class PlanetData(SlaveDelegate):
    planetwidgets = ["name", "owner", "id"]
    proxy = None
    
    def __init__(self):
        gd = GameData()
        SlaveDelegate.__init__(self, gladefile="planetdata",
                               toplevel_name="window1",
                               widgets=self.planetwidgets)

        self.proxy = self.add_proxy(model=None, widgets=self.planetwidgets)
        races = []

        if gd.is_valid():
            racelist = gd.get_race_list()
            races = racelist.get_short_and_number()
            races.append ( ("desconocido", -1) )
        self.owner.prefill( races )
    pass



app = Shell()
app.show_all()
gtk.main()
