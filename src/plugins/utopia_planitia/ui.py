# Utopia Planitia UI 

import pygtk
pygtk.require('2.0')

import gtk
import copy

from kiwi.ui.delegates import GladeDelegate
from kiwi.ui.gadgets import quit_if_last
from kiwi.ui.objectlist import Column, ObjectList

import gwp
from gwp.models import Game
from models import ShipProyect, UP_Engines
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
        self.combo_hulls.do_grab_focus(self.combo_hulls)
        self.queue_list = ObjectList([
                Column('hull_name', title="Name", data_type=str),
                Column('total_cost', title="Cost", data_type=int),
                Column('total_tri', title="Tri", data_type=int),
                Column('total_dur', title="Dur", data_type=int),
                Column('total_mol', title="Mol", data_type=int),
                ])
        self.frame_queue.add(self.queue_list)
        self.queue_list.show()
        self.queue_list.grab_focus()
#        self.engines_fuel_usage = UP_Engines(self.game.engines) # Test line

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

        # Fix Path
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

    def on_btn_add__clicked(self,widget):
        self.queue_list.append( copy.copy(self.ship_proyect) )


    def on_btn_remove__clicked(self,widget):
        selected = self.queue_list.get_selected()
        if selected:
            self.queue_list.remove(selected, select=True)

    def on_btn_use_favorite__clicked(self,widget):
        pass

    def on_combo_engines__changed(self, widget):
        self.__populate_spec(self.game.engines)

    def on_combo_beams__changed(self, widget):
        self.__populate_spec(self.game.beams)

    def on_combo_tubes__changed(self, widget):
        self.__populate_spec(self.game.tubes)

    def on_combo_engines__focus(self, widget, direction):
        self.frame_components.remove(self.spec_list)

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

    def __populate_spec(self, components):
        self.frame_components.remove(self.spec_list)
        if isinstance(components[0], gwp.models.Engine):
            # Engine
            self.spec_list = ObjectList([
                    Column('name', data_type=str),
                    Column('cost', data_type=int),
                    Column('tri', data_type=int),
                    Column('dur', data_type=int),
                    Column('mol', data_type=int),
                    Column('tech', data_type=int),
                    Column('fuel_use', data_type=int),
                    # TODO add calculated data
                    ])
            # Beam
        else: 
            if isinstance(components[0], gwp.models.Beam):
                self.spec_list = ObjectList([
                        Column('name', data_type=str),
                        Column('kill', data_type=int),
                        Column('damage', data_type=int),
                        Column('cost', data_type=int),
                        Column('tri', data_type=int),
                        Column('dur', data_type=int),
                        Column('mol', data_type=int),
                        Column('mass', data_type=int),
                        Column('tech', data_type=int),
                        # TODO add calculated data
                        ])
            # Tube
            else: 
                if isinstance(components[0], gwp.models.Torpedo):
                    self.spec_list = ObjectList([
                            Column('name', data_type=str),
                            Column('kill', data_type=int),
                            Column('damage', data_type=int),
                            Column('launcher_cost', data_type=int),
                            Column('torp_cost', data_type=int),
                            Column('tri', data_type=int),
                            Column('dur', data_type=int),
                            Column('mol', data_type=int),
                            Column('mass', data_type=int),
                            Column('tech', data_type=int),
                            # TODO add calculated data
                            ])
                    
        for row in components:
            self.spec_list.append( row )
        self.frame_components.add(self.spec_list)
        self.show_all()



