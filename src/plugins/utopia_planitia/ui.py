# Utopia Planitia UI 

import pygtk
pygtk.require('2.0')

import gtk

from kiwi.ui.delegates import GladeDelegate
from kiwi.ui.gadgets import quit_if_last

import gwp
from gwp.models import Game
from gwp.collections import RaceList, TrueHullCollection, HullCollection, BeamCollection, TorpedoCollection, EngineCollection

class UP(GladeDelegate):
    hullwidgets = ["hull_mc", "hull_tri", "hull_dur", "hull_mol", "engine_quantity", "beam_quantity", "tube_quantity"]
    engineswidgets = ["engine_mc", "engine_tri", "engine_dur", "engine_mol"]
    beamswidgets = ["beam_mc", "beam_tri", "beam_dur", "beam_mol"]
    tubeswidgets = ["tube_mc", "tube_tri", "tube_dur", "tube_mol", "torp_mc"]

    def __init__(self):
        super(UP, self).__init__(gladefile="utopia_planitia",
                                    delete_handler=self.do_quit)
        self.__init_view()

    def do_quit(self, *args):
        '''
        Quits up
        '''
        print "Hasta la vista!"
        gtk.main_quit()
        

    def __init_view(self):
        self.game  = Game()
        
        self.hull_proxy = self.add_proxy(model=None, widgets=self.hullwidgets)
        self.engines_proxy = self.add_proxy(model=None, widgets=self.engineswidgets)
        self.beams_proxy = self.add_proxy(model=None, widgets=self.beamswidgets)
        self.tubes_proxy = self.add_proxy(model=None, widgets=self.tubeswidgets)

        self.__populate_combo( self.combo_hulls, self.game.hulls)
        self.__populate_combo( self.combo_engines, self.game.engines)
        self.__populate_combo( self.combo_beams, self.game.beams)
        self.__populate_combo( self.combo_tubes, self.game.tubes)
            

    def on_combo_hulls__content_changed(self, widget):
        id = widget.get_selected_data() - 1; # array begins in 0
        self.hull_proxy.set_model(self.game.hulls[id])

    def on_combo_engines__content_changed(self, widget):
        id = widget.get_selected_data() - 1; # array begins in 0
        self.engines_proxy.set_model(self.game.engines[id])

    def on_combo_beams__content_changed(self, widget):
        id = widget.get_selected_data() - 1; # array begins in 0
        self.beams_proxy.set_model(self.game.beams[id])

    def on_combo_tubes__content_changed(self, widget):
        id = widget.get_selected_data() - 1; # array begins in 0
        self.tubes_proxy.set_model(self.game.tubes[id])

    def __populate_combo(self, widget, list):
        i = 1
        for object in list:
            widget.append_item(object.name, i)
            i = i + 1
