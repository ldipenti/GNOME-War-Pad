# Several collections

from gwp.filereaders import RaceNMFile
from gwp.filereaders import XYPlanFile
from gwp.filereaders import PlanetNMFile
from gwp.filereaders import PDataFile
from gwp.filereaders import HullspecFile
from gwp.filereaders import BeamspecFile
from gwp.filereaders import TorpspecFile
from gwp.filereaders import EngspecFile
from gwp.filereaders import ShipXYFile
from gwp.filereaders import ShipFile
from gwp.filereaders import TargetFile
from gwp.models import Planet
from gwp.models import Hull
from gwp.models import Beam
from gwp.models import Torpedo
from gwp.models import Engine
from gwp.models import Ship

class RaceList(list):
    '''
    This class represents the race names collection
    '''
    def __init__(self, gamedir=''):
        list.__init__(self)
        map(lambda x: self.append(x), RaceNMFile(gamedir + '/race.nm').read())
        return

    def get_long(self):
        '''
        Return a list of races long descriptions
        '''
        ret = []
        map(lambda (l,s,a): ret.append(l), self)
        return ret
    
    def get_short(self):
        '''
        Return a list of races short descriptions
        '''
        ret = []
        map(lambda (l,s,a): ret.append(s), self)
        return ret
    
    def get_adj(self):
        '''
        Return a list of races adjectives
        '''
        ret = []
        map(lambda (l,s,a): ret.append(a), self)
        return ret
    pass


class PlanetCollection(dict):
    '''
    A collection of planets
    '''
    def __init__(self, gamedir, racenum):
        super(PlanetCollection, self).__init__(self)
        # data loading
        planetnm = PlanetNMFile(gamedir + 'planet.nm')
        xyplan = XYPlanFile(gamedir + 'xyplan' + str(racenum) + '.dat')
        pdata = PDataFile(gamedir + 'pdata' + str(racenum) + '.dat')
        planet_names = planetnm.read()
        planet_coords = xyplan.read()
        planet_data = pdata.read()
        planetnm.close()
        xyplan.close()
        pdata.close()
        # planet data integration
        for xy in planet_coords.keys():
            if xy in planet_data.keys():
                # Known planet
                self[xy] = Planet(planet_coords[xy]['x'],
                                  planet_coords[xy]['y'],
                                  planet_names[xy],
                                  planet_data[xy])
            else:
                # Unknown planet
                self[xy] = Planet(planet_coords[xy]['x'],
                                  planet_coords[xy]['y'],
                                  planet_names[xy])
                self[xy].owner = -1 # Unknown owner
                self[xy].id = xy
        return
    pass

class HullCollection(list):
    '''
    The entire collection of starship hulls on the game
    '''
    def __init__(self, gamedir):
        list.__init__(self)
        # data loading
        hulls = HullspecFile(gamedir + 'hullspec.dat')
        for hulldata in hulls.read():
            hull = Hull(hulldata)
            self.append(hull)
        hulls.close()
        return
    pass # End of HullCollection class

class BeamCollection(list):
    '''
    The entire collection of starship beam weapons on the game
    '''
    def __init__(self, gamedir):
        list.__init__(self)
        # data loading
        beams = BeamspecFile(gamedir + 'beamspec.dat')
        for beamdata in beams.read():
            beam = Beam(beamdata)
            self.append(beam)
        beams.close()
        return
    pass # End of BeamCollection class

class TorpedoCollection(list):
    '''
    The entire collection of starship torpedo weapons on the game
    '''
    def __init__(self, gamedir):
        list.__init__(self)
        # data loading
        torpedos = TorpspecFile(gamedir + 'torpspec.dat')
        for torpedodata in torpedos.read():
            torpedo = Torpedo(torpedodata)
            self.append(torpedo)
        torpedos.close()
        return
    pass # End of TorpedoCollection class

class EngineCollection(list):
    '''
    The entire collection of starship engines on the game
    '''
    def __init__(self, gamedir):
        list.__init__(self)
        # data loading
        engines = EngspecFile(gamedir + 'engspec.dat')
        for enginedata in engines.read():
            engine = Engine(enginedata)
            self.append(engine)
        engines.close()
        return
    pass # End of EngineCollection class

class ShipCollection(dict):
    '''
    A collection of ships
    '''
    def __init__(self, gamedir, racenum):
        super(ShipCollection, self).__init__(self)
        # data loading (shipxy)
        shipxy = ShipXYFile(gamedir + 'shipxy' + str(racenum) + '.dat')
        ship_coords = shipxy.read()
        shipxy.close()
        # data loading (targetX)
        target_file = TargetFile("%starget%d.dat" % (gamedir, racenum))
        targets = target_file.read()
        target_file.close()
        # data loading (shipX)
        my_ships_file = ShipFile("%sship%d.dat" % (gamedir, racenum))
        my_ships = my_ships_file.read()
        my_ships_file.close()
        # data assembly (own ships)
        for (ship_id, ship_data) in my_ships.items():
            self[ship_id] = Ship(ship_data['x'],
                                 ship_data['y'],
                                 racenum,
                                 0, 0,
                                 ship_data)
        # data assembly (other ships)
        for (ship_id, ship_data) in ship_coords.items():
            # Avoid non-existing ships
            if ship_data['x'] == ship_data['y'] == 0:
                continue
            
            # Use data from SHIPXY
            if not ship_id in self.keys():
                self[ship_id] = Ship(ship_data['x'],
                                     ship_data['y'],
                                     ship_data['owner'])
                self[ship_id].mass = ship_data['mass']
                
            # Complete with data from TARGETx
            if ship_id in targets.keys():
                self[ship_id].name = targets[ship_id]['name']
                self[ship_id].speed = targets[ship_id]['speed']
                self[ship_id].hull_type = targets[ship_id]['hull_type']
        return
    pass # End of ShipCollection class