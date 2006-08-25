# Models.py: Model classes

from gtkmvc.model import Model

class Starchart(Model):
    '''
    This class represents the Echo Cluster, a piece of the Universe where
    lots of things happen everyday...
    '''
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

# The good old GwpObject class...reloaded!
class FloatingObject(Model):
    '''
    This class represents any object that floats in the cold and dark
    universe, and can be showed in the Starchart. This class is meant to
    be an abstract class
    '''
    id = None
    name = None
    x = 0
    y = 0
    
    def __init__(self, x, y):
        Model.__init__(self)
        self.x = x
        self.y = y
        return

    def __setattr__(self, name, value):
        '''
        Some constrains on attribute settings
        '''
        # Coordinates shouldn't be negative
        if name == 'x':
            if value < 0:
                raise ValueError
            else:
                Model.__setattr__(self, 'x', value)
        elif name == 'y':
            if value < 0:
                raise ValueError
            else:
                Model.__setattr__(self, 'y', value)
        else:
            Model.__setattr__(self, name, value)
        return
    
    pass # End of FloatingObject class


class FlyingObject(FloatingObject):
    '''
    Any object in space that moves (ships, meteors, storms, etc...)
    '''
    heading = 0 # 0 - 360 degrees
    speed = 0 # warp speed: 0 - 9
    
    def __init__(self, x, y, heading, speed):
        FloatingObject.__init__(self, x, y)
        self.heading = heading
        self.speed = speed
        return

    def __setattr__(self, name, value):
        '''
        Custom attribute constrains
        '''
        if name == 'heading':
            if value < 0 or value > 360:
                raise ValueError
            else:
                FloatingObject.__setattr__(self, 'heading', value)
        elif name == 'speed':
            if value < 0 or value > 9:
                raise ValueError
            else:
                FloatingObject.__setattr__(self, 'speed', value)
        else:
            FloatingObject.__setattr__(self, name, value)
        return

    pass # End of FlyingObject class


class Ship(FlyingObject):
    '''
    A starship object
    '''
    def __init__(self, x, y, heading, speed):
        FlyingObject.__init__(x, y, heading, speed)
        return

    pass # End of Ship class


class Planet(FloatingObject):
    '''
    A rock in the sky
    '''
    is_known = False
    ground_dur = 0
    happ_colonists = 0
    owner = -1
    natives_race = -1
    id = 0
    temperature = -1
    mined_tri = 0
    mines = 0
    fcode = 0
    ground_mol = 0
    colonists = -1
    tax_colonists = 0
    supplies = 0
    dens_mol = 0
    happ_natives = 0
    megacredits = 0
    dens_dur = 0
    ground_neu = 0
    defenses = 0
    mined_neu = 0
    mined_mol = 0
    tax_natives = 0
    factories = 0
    ground_tri = 0
    mined_dur = 0
    build_base = 0
    natives_spi = 0
    dens_neu = 0
    dens_tri = 0
    natives = 0

    def __init__(self, x, y, name, pdata=None):
        super(Planet, self).__init__(x, y)
        self.name = name
        if pdata != None:
            self.is_known = True
            # Load all other data coming from PDATAx.DAT file reader class
            attrs = ['ground_dur', 'happ_colonists', 'owner', 'natives_race',
                     'id', 'temperature', 'mined_tri', 'mines', 'fcode',
                     'ground_mol', 'colonists', 'tax_colonists', 'supplies',
                     'dens_mol', 'happ_natives', 'megacredits', 'dens_dur',
                     'ground_neu', 'defenses', 'mined_neu', 'mined_mol',
                     'tax_natives', 'factories', 'ground_tri', 'mined_dur',
                     'build_base', 'natives_spi', 'dens_neu', 'dens_tri',
                     'natives']
            for a in attrs:
                setattr(self, a, pdata[a])
        return
    pass
