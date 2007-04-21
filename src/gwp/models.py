# models.py: Model classes

import math

# The good old GwpObject class...reloaded!
class FloatingObject(object):
    '''
    This class represents any object that floats in the cold and dark void
    called Universe, and can be showed in the Starchart. This class is meant
    to be an abstract class.
    '''
    id = None
    name = None
    x = 0
    y = 0
    
    def __init__(self, x, y):
        self.x = x
        self.y = y
        return

    def __setattr__(self, name, value):
        '''
        Some constrains on attribute settings
        '''
        # Coordinates: from 1000,1000 to 3000,3000 with a 50 LY margin
        # coordinates shouldn't be negative
        if name == 'x':
            if value < 0 or value > 3050:
                raise ValueError
            else:
                super(FloatingObject, self).__setattr__('x', value)
        elif name == 'y':
            if value < 0 or value > 3050:
                raise ValueError
            else:
                super(FloatingObject, self).__setattr__('y', value)
        else:
            super(FloatingObject, self).__setattr__(name, value)
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
            if value < -1 or value > 360:
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
    beams = 0
    beams_type = 0
    colonists = 0
    crew = 0
    damage = 0
    dur = 0
    engines_type = 0
    fcode = 0
    fighter_bays = 0
    hull_type = 0
    id = 0
    intercept_ship_id = 0
    megacredits = 0
    mission = 0
    mol = 0
    name = 0
    neu = 0
    owner = 0
    primary_enemy = 0
    speed = 0
    supp = 0
    torps_fighters_nr = 0
    torps_launchers = 0
    torps_type = 0
    tow_ship_id = 0
    transfer_col = 0
    transfer_dur = 0
    transfer_mol = 0
    transfer_neu = 0
    transfer_ship_id = 0
    transfer_supp = 0
    transfer_tri = 0
    tri = 0
    unload_col = 0
    unload_dur = 0
    unload_mol = 0
    unload_neu = 0
    unload_planet_id = 0
    unload_supp = 0
    unload_tri = 0
    x = 0
    x_to_waypoint = 0
    y = 0
    y_to_waypoint = 0
    
    def __init__(self, x, y, owner, heading=0, speed=0, sdata=None):
        super(Ship, self).__init__(x, y, heading, speed)
        self.owner = owner
        if sdata != None:
            attrs = ['beams', 'beams_type', 'colonists', 'crew', 'damage',
                     'dur', 'engines_type', 'fcode', 'fighter_bays',
                     'hull_type', 'id', 'intercept_ship_id', 'megacredits',
                     'mission', 'mol', 'name', 'neu', 'owner', 'primary_enemy',
                     'speed', 'supp', 'torps_fighters_nr', 'torps_launchers',
                     'torps_type', 'tow_ship_id', 'transfer_col',
                     'transfer_dur', 'transfer_mol', 'transfer_neu',
                     'transfer_ship_id', 'transfer_supp', 'transfer_tri',
                     'tri', 'unload_col', 'unload_dur', 'unload_mol',
                     'unload_neu', 'unload_planet_id', 'unload_supp',
                     'unload_tri', 'x', 'x_to_waypoint', 'y', 'y_to_waypoint']
            for a in attrs:
                setattr(self, a, sdata[a])
            self.update_heading()
        return

    def update_heading(self):
        # Calculate heading from waypoint coords
        dx = self.x_to_waypoint
        dy = self.y_to_waypoint
        if dx == 0 and dy == 0:
            self.heading = -1 # Ship not moving
        else:
            hyp = math.hypot(dx, dy)
            if hyp != 0:
                heading = math.asin(dy/hyp)
                h = heading * (360 / (2 * math.pi))
                if dx >= 0:
                    h = 90 + (h * -1)
                else:
                    h += 270
            else:
                h = 0
            self.heading = int(round(h))
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
    selected = False # delete this

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

class Hull:
    '''
    A starship hull
    '''
    def __init__(self, hullspec):
        # Load all hullspec data from file reader class
        attrs = ['name', 'pic_nr', 'tri', 'dur', 'mol', 'fuel', 'crew',
                 'engines', 'mass', 'tech', 'cargo', 'fighter_bays',
                 'torp_launchers', 'beam_weapons', 'cost']
        for a in attrs:
            setattr(self, a, hullspec[a])
        return
    pass # End of Hull class

class Beam:
    '''
    A starship beam weapon
    '''
    def __init__(self, beamspec):
        # Load all beamspec data from file reader class
        attrs = ['name', 'cost', 'tri', 'dur', 'mol', 'mass', 'tech',
                 'kill', 'damage']
        for a in attrs:
            setattr(self, a, beamspec[a])
        return
    pass # End of Beam class

class Engine:
    '''
    A starship engine
    '''
    def __init__(self, engspec):
        # Load all engspec data from file reader class
        attrs = ['name', 'cost', 'tri', 'dur', 'mol', 'tech', 'fuel_use']
        for a in attrs:
            setattr(self, a, engspec[a])
        return
    pass # End of Engine class

class Torpedo:
    '''
    A starship torpedo launcher weapon
    '''
    def __init__(self, torpspec):
        # Load all torpspec data from file reader class
        attrs = ['name', 'torp_cost', 'launcher_cost', 'tri', 'dur', 'mol',
                 'mass', 'tech', 'kill', 'damage']
        for a in attrs:
            setattr(self, a, torpspec[a])
        return
    pass # End of Torpedo class

class Minefield:
    '''
    A mine field on space
    '''
    def __init__(self, x, y, radius, owner):
        self.x = x
        self.y = y
        self.radius = radius
        self.owner = owner
        return
    pass # End of Torpedo class
