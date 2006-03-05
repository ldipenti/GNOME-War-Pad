# Models.py: Model classes

from gtkmvc.model import Model

class Starchart(Model):
    __properties__ = {
        }
    # Coordinate bounds
    min_x = 0
    min_y = 0
    max_x = 0
    max_y = 0
    # Contents
    planets = []
    ships = []
    
    def __init__(self, min_x, min_y, max_x, max_y):
        Model.__init__(self)
        self.min_x = min_x
        self.min_y = min_y
        self.max_x = max_x
        self.max_y = max_y
        return

    def add_planet(self, planet):
        '''
        Adds a planet to the collection
        '''
        self.planets.append(planet)
        return

    def remove_planet(self, planet):
        '''
        Removes a planet from the collection
        '''
        if planet in self.planets:
            self.planets.remove(planet)
        return

    pass # End of Starchart class
