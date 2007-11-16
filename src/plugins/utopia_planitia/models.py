# models.py: Model classes for Utopia Planitia plugin

from kiwi.model import Model
from kiwi.datatypes import ValidationError
from gwp.models import Game

class ShipProyect(Model):
    '''
    A starship Proyect to be constructed.
    '''
    hull = None
    engine = None
    beam = None
    tube = None

    # Spec
    engine_quantity = 0
    beam_quantity = 0
    tube_quantity = 0
    torp_quantity = 0
    bay_quantity = 0
    
    mass = 0
    crew = 0
    cargo = 0
    fuel = 0
    picture_nr = 0

    # Costs
    hull_cost = 0
    hull_tri = 0
    hull_dur = 0
    hull_mol = 0
    engines_cost = 0
    engines_tri = 0
    engines_dur = 0
    engines_mol = 0
    beams_cost = 0
    beams_tri = 0
    beams_dur = 0
    beams_mol = 0
    tubes_cost = 0
    tubes_tri = 0
    tubes_dur = 0
    tubes_mol = 0
    
    total_cost = 0
    total_tri = 0
    total_dur = 0
    total_mol = 0

    def __init__(self, hull_id):
        self.game = Game()
        self.set_hull(hull_id)
        return

    # Hull
    def set_hull(self, id):
        self.hull = self.game.hulls[id]
        # Spec
        self.engine_quantity = self.hull.engines
        self.beam_quantity = self.hull.beam_weapons
        self.tube_quantity = self.hull.torp_launchers
        self.bay_quantity = self.hull.fighter_bays

        self.mass = self.hull.mass
        self.crew = self.hull.crew
        self.cargo = self.hull.cargo
        self.fuel = self.hull.fuel
        self.picture_nr = self.hull.pic_nr

        # Costs
        self.hull_cost = self.hull.cost
        self.hull_tri = self.hull.tri
        self.hull_dur = self.hull.dur
        self.hull_mol = self.hull.mol

        if self.engine:
            self.update_engine_costs()
        if self.beam:
            self.update_beams_costs()
        if self.tube:
            self.update_tubes_costs()

        self.update_cost()

    # Engines
    def set_engine(self, id):
        self.engine = self.game.engines[id]
        self.update_engine_costs()

    def update_engine_costs(self):
        self.engines_cost = self.engine.cost * self.engine_quantity
        self.engines_tri = self.engine.tri * self.engine_quantity
        self.engines_dur = self.engine.dur * self.engine_quantity
        self.engines_mol = self.engine.mol * self.engine_quantity
        self.update_cost()

    # Beams
    def set_beam(self, id):
        self.beam = self.game.beams[id]
        self.update_beams_costs()

    def set_beam_quantity(self, value):
        self.beam_quantity = value
        self.update_beams_costs()

    def update_beams_costs(self):
        try:
            self.beams_cost = self.beam.cost * self.beam_quantity
            self.beams_tri = self.beam.tri * self.beam_quantity
            self.beams_dur = self.beam.dur * self.beam_quantity
            self.beams_mol = self.beam.mol * self.beam_quantity
            self.update_cost()
        except AttributeError:
            # There is no selected a beam type
            pass

    # Tubes
    def set_tube(self, id):
        self.tube = self.game.tubes[id]
        self.update_tubes_costs()

    def set_tube_quantity(self, value):
        self.tube_quantity = value
        self.update_tubes_costs()

    def update_tubes_costs(self):
        try:
            self.tubes_cost = self.tube.launcher_cost * self.tube_quantity
            self.tubes_tri = self.tube.tri * self.tube_quantity
            self.tubes_dur = self.tube.dur * self.tube_quantity
            self.tubes_mol = self.tube.mol * self.tube_quantity
            self.update_cost()
        except AttributeError:
            # There is no selected a beam type
            pass

    # Totals
    def update_cost(self):
        self.update_totals()
        pass

    def update_totals(self):
        self.total_cost = self.hull_cost + self.engines_cost + self.beams_cost + self.tubes_cost
        self.total_tri = self.hull_tri + self.engines_tri + self.beams_tri + self.tubes_tri
        self.total_dur = self.hull_dur + self.engines_dur + self.beams_dur + self.tubes_dur
        self.total_mol = self.hull_mol + self.engines_mol + self.beams_mol + self.tubes_mol
        # TODO Count torps


    pass # End of ShipProyect class

# Validations ----------------------------------------------------------------------------------

    def beam_quantity_validate(self, data):
        if data < 0 or data > self.hull.beam_weapons:
            return ValidationError("The data is out of range")

    def tube_quantity_validate(self, data):
        if data < 0 or data > self.hull.torp_launchers:
            return ValidationError("The data is out of range")
        
