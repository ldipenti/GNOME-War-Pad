# Several collections

from FileReaders import RaceNMFile
from FileReaders import XYPlanFile
from FileReaders import PlanetNMFile
from FileReaders import PDataFile
from Models import Planet

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
        dict.__init__(self)
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
