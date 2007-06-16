#!/usr/bin/env python

import pygtk
pygtk.require('2.0')

import gtk, gobject, cairo, pango
import math

from gwp.collections import PlanetCollection, ShipCollection, RaceList
from gwp.widgets import Starchart, PlanetDrawable, ShipDrawable, Line

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

    def get_race_name_adj(self):
        # TODO: get from player data
        return "Simios"
        
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
    planet_slave = None
    ship_slave = None
    objlist = None
    
    def __init__(self):
        Delegate.__init__(self, gladefile="starchart_view",
                          widgets=self.my_widgets,
                          delete_handler=quit_if_last)
     
        # object list
        self.objlist = ObjectList([Column('id', data_type=int, sorted=True),
                                   Column('name', data_type=str),
                                   ])
        slave = SlaveDelegate(toplevel=self.objlist)
        self.attach_slave("eventbox_ship_list", slave)
	self.objlist.connect("selection-changed", self.on_objlist_selected)
            

    def on_objlist_selected(self, widget, obj):
        try:
            if obj.is_planet():
                # PLANET            
                self.planet_slave.proxy.set_model(None)
                self.planet_slave.proxy.set_model(obj)
            else:
                # SHIP
                self.ship_slave.proxy.set_model(None)
                self.ship_slave.proxy.set_model(obj)

            self.planet_slave.get_widget("frame_planet").hide()
            self.ship_slave.get_widget("frame_ship").show()
        except AttributeError:
            # Sometimes objlist_selected signal is raised without reason
            pass

    def on_button_open__clicked(self, widget):
        path = self.entry_dir.get_text()
        
        if path != "" and os.path.isdir(path):
            gd = GameData()
            gd.set_path(path)
            # Read user data
            self.planets = PlanetCollection( gd.get_path(), gd.get_race_num() )
            self.ships = ShipCollection( gd.get_path(), gd.get_race_num() )
            # Prepare the starchart
            self.starchart = Starchart()
            self.starchart.add_drawables(self.planets, PlanetDrawable)
            self.starchart.add_drawables(self.ships, ShipDrawable)
            self.starchart.connect("selected", self.on_starchart_selected)
            self.starchart.show()
            # Put the startchart in place
            slave = SlaveDelegate(toplevel=self.starchart)
            self.attach_slave("eventbox_startchart", slave)
            slave.focus_toplevel()
            self.slave = slave

            # Show game data
            self.race_name.set_text( "We are <b>" + gd.get_race_name_adj() + "</b>" )
            self.turn_number.set_text( "Turn " +  str(gd.get_turn_number()) )

            # Attach planet frame
            self.planet_slave = PlanetData()
            self.attach_slave("eventbox_planet", self.planet_slave)

            # Attach ship frame
            self.ship_slave = ShipData()
            self.attach_slave("eventbox_ship", self.ship_slave)
    
            # Draw constellations
            p = self.planets.values()
            while len(p) > 1:
                planet_a = p.pop()
                for planet_b in p:
                    distance =  abs(math.hypot(planet_b.x - planet_a.x,
                                               planet_b.y - planet_a.y))
                    if distance <= 84:
                        self.starchart.add(Line(planet_a.x, planet_a.y, planet_b.x, planet_b.y,
                                                (0.4, 0.4, 0.4)))
            # Hide empty frames
            self.planet_slave.get_widget("frame_planet").hide()
            self.ship_slave.get_widget("frame_ship").hide()

    def on_starchart_selected(self, widget, x, y, data=None):
        # Find the nearest object and construct a list of ships in that point if any
        min_dist = 99999
        ret = None
        objlist = []
        objects = self.planets.values() + self.ships.values()
        for obj in objects:
            distance =  abs(math.hypot(obj.x - x,
                                       obj.y - y))
            if distance < min_dist:
                min_dist = distance
                objlist = []
                ret = obj
            elif distance == min_dist and obj.is_ship():
                objlist.append(obj)

        self.starchart.move(ret.x - x, ret.y - y)

        # Hide/show ships frame
        if objlist == []:
            self.frame_ships.hide()
        else:
            self.frame_ships.show()
    
        # Hide/show Planet frame
        if ret.is_planet():
            # PLANET
            # Reset model to none so it wont complain of different models assignments
            self.planet_slave.proxy.set_model(None)
            self.planet_slave.proxy.set_model(ret)

            self.ship_slave.get_widget("frame_ship").hide()
            self.planet_slave.get_widget("frame_planet").show()

            # Hide/show natives frame
            if ret.natives == 0:
                self.planet_slave.get_widget("frame_natives").hide()
            else:
                self.planet_slave.get_widget("frame_natives").show()
                    
            # Decorate the Planet name
            wname = self.planet_slave.get_widget("name")
            wname.set_text("<b><big>" + wname.get_text() + "</big></b>")

        else:
            # SHIP
            objlist.append(ret)
             # Reset model to none so it wont complain of different models assignments
            self.ship_slave.proxy.set_model(None)
            self.ship_slave.proxy.set_model(ret)

            self.planet_slave.get_widget("frame_planet").hide()
            self.ship_slave.get_widget("frame_ship").show()           


        self.objlist.clear()
        self.objlist.extend(objlist)

    pass


class PlanetData(SlaveDelegate):
    planetwidgets = ["name", "owner", "id", "temperature", "colonists", "happ_colonists",
                     "tax_colonists", "natives", "happ_natives", "tax_natives",
                     "natives_race", "natives_spi", "factories", "mines", "defenses"]
    proxy = None
    
    def __init__(self):
        gd = GameData()
        SlaveDelegate.__init__(self, gladefile="planet_data",
                               toplevel_name="planet_data",
                               widgets=self.planetwidgets)

        self.proxy = self.add_proxy(model=None, widgets=self.planetwidgets)
#        races = []
#         if gd.is_valid():
#             racelist = gd.get_race_list()
#             races = racelist.get_short_and_number()
#             races.append ( ("desconocido", -1) )
#             self.owner.prefill( races )

    pass

class ShipData(SlaveDelegate):
    planetwidgets = ["name", "owner", "id", "hull_type"]

    proxy = None
    
    def __init__(self):
        gd = GameData()
        SlaveDelegate.__init__(self, gladefile="ship_data",
                               toplevel_name="ship_data",
                               widgets=self.planetwidgets)

        self.proxy = self.add_proxy(model=None, widgets=self.planetwidgets)
    pass

app = Shell()
app.show_all()
gtk.main()