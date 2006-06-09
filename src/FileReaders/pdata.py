# PDATAx.DAT/DIS file reader

import struct

class PDataFile(file):
    '''
    Planets data file: Handles the pdata.dis/dat file format abstraction
    '''
    pdata_size = 85 # Planet register size
    
    def __init__(self, filename):
        file.__init__(self, filename, 'r')
        return

    def read(self):
        self.seek(0)
        ret = {}
        planets = struct.unpack("H", super(PDataFile, self).read(2))[0]
        for reg in range(planets):
            # Format beginning with "<" as little-endian (Intel-based systems)
            # http://docs.python.org/lib/module-struct.html
            a = struct.unpack("<2H 3s 3H 11L 9H L 3H",
                              super(PDataFile, self).read(self.pdata_size))
            pdata = {'owner' : a[0],
                     'id' : a[1],
                     'fcode' : a[2],
                     'mines' : a[3],
                     'factories' : a[4],
                     'defenses' : a[5],
                     'mined_neu' : a[6],
                     'mined_tri' : a[7],
                     'mined_dur' : a[8],
                     'mined_mol' : a[9],
                     'colonists' : a[10],
                     'supplies' : a[11],
                     'megacredits' : a[12],
                     'ground_neu' : a[13],
                     'ground_tri' : a[14],
                     'ground_dur' : a[15],
                     'ground_mol' : a[16],
                     'dens_neu' : a[17],
                     'dens_tri' : a[18],
                     'dens_dur' : a[19],
                     'dens_mol' : a[20],
                     'tax_colonists' : a[21],
                     'tax_natives' : a[22],
                     'happ_colonists' : a[23],
                     'happ_natives' : a[24],
                     'natives_spi' : a[25],
                     'natives' : a[26],
                     'natives_race' : a[27],
                     'temperature' : 100 - a[28], # Tim Rocks...
                     'build_base' : a[29],
                     }
            ret[pdata['id']] = pdata
        return ret
    pass
