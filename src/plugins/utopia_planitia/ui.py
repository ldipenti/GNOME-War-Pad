# Utopia Planitia UI 

import pygtk
pygtk.require('2.0')

import gtk

from kiwi.ui.delegates import GladeDelegate
from kiwi.ui.gadgets import quit_if_last

import gwp
from gwp.models import Game
from models import ShipProyect
from gwp.collections import RaceList, TrueHullCollection, HullCollection, BeamCollection, TorpedoCollection, EngineCollection

class UP(GladeDelegate):
    ship_widgets = ["total_mc","total_tri","total_dur","total_mol", "hull_mc", "hull_tri", "hull_dur", "hull_mol", "engine_quantity", "spin_beam_quantity", "spin_tube_quantity", "engine_mc", "engine_tri", "engine_dur", "engine_mol", "beam_mc", "beam_tri", "beam_dur", "beam_mol", "tube_mc", "tube_tri", "tube_dur", "tube_mol", "torp_mc", "mass", "crew", "cargo", "fuel"]

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
        self.game = Game()
        self.ship_proxy = self.add_proxy(model=None, widgets=self.ship_widgets)

        self.__populate_combo( self.combo_hulls, self.game.hulls)
        self.__populate_combo( self.combo_engines, self.game.engines)
        self.__populate_combo( self.combo_beams, self.game.beams)
        self.__populate_combo( self.combo_tubes, self.game.tubes)
        
        self.ship_proyect = None;

    def on_combo_hulls__content_changed(self, widget):
        id = widget.get_selected_data() - 1; # array begins in 0

        if self.ship_proyect == None:
            self.ship_proyect = ShipProyect(id)
            self.ship_proxy.set_model(self.ship_proyect)
            # Activate the comboboxes
            self.combo_engines.set_sensitive(True)
            self.combo_beams.set_sensitive(True)
            self.combo_tubes.set_sensitive(True)
            self.btn_add.set_sensitive(True)
        else:
            self.ship_proyect.set_hull(id)
            # Update BEAM Combo
            if self.ship_proyect.beam_quantity:
                self.combo_beams.set_sensitive(True)
            else:
                self.combo_beams.set_sensitive(False)
            # Update TORP Combo
            if self.ship_proyect.tube_quantity:
                self.combo_tubes.set_sensitive(True)
            else:
                self.combo_tubes.set_sensitive(False)

        if self.combo_engines.get_selected_data() == None:
            self.combo_engines.select_item_by_data(9) # Fix: use last

        self.ship_image.set_from_file('/usr/local/games/gwp/ships/vpl' + str(self.ship_proyect.picture_nr) + '.jpg')
        self.ship_image.show()


    def on_combo_engines__content_changed(self, widget):
        id = widget.get_selected_data() - 1 # array begins in 0
        self.ship_proyect.set_engine(id)

    def on_combo_beams__content_changed(self, widget):
        id = widget.get_selected_data() - 1 # array begins in 0
        self.ship_proyect.set_beam(id)

    def on_combo_tubes__content_changed(self, widget):
        id = widget.get_selected_data() - 1 # array begins in 0
        self.ship_proyect.set_tube(id)

    def on_spin_beam_quantity__value_changed(self, widget):
        self.ship_proyect.set_beam_quantity( widget.get_value_as_int() )

    def on_spin_tube_quantity__value_changed(self, widget):
        self.ship_proyect.set_tube_quantity( widget.get_value_as_int() )

    def on_btn_reset__clicked(self,widget):
        self.ship_proyect = None
        self.combo_engines.set_sensitive(False)
        self.combo_beams.set_sensitive(False)
        self.combo_tubes.set_sensitive(False)
        self.btn_add.set_sensitive(False)

    def on_btn_use_favorite__clicked(self,widget):
        print self.spin_beam_quantity.get_value_as_int()

        pass

# Validations ----------------------------------------------------------------------------------
    def on_spin_beam_quantity__validate(self, widget, data):
        return self.ship_proyect.beam_quantity_validate(data)

    def on_spin_tube_quantity__validate(self, widget, data):
        return self.ship_proyect.tube_quantity_validate(data)

# Private methods ------------------------------------------------------------------------------
    def __populate_combo(self, widget, list):
        i = 1
        for object in list:
            widget.append_item(object.name, i)
            i = i + 1

