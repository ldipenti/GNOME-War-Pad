# BDATAx.DAT/DIS file reader

import struct

class BDataFile(file):
    '''
    Starbase data file: Handles the bdata.dis/dat file format abstraction
    '''
    bdata_size = 156 # Starbase register size
    
    def __init__(self, filename):
        file.__init__(self, filename, 'r')
        return

    def read(self):
        self.seek(0)
        ret = {}
        starbases = struct.unpack("H", super(BDataFile, self).read(2))[0]
        for reg in range(starbases):
            # Format beginning with "<" as little-endian (Intel-based systems)
            # http://docs.python.org/lib/module-struct.html
            a = struct.unpack("<78H",
                              super(BDataFile, self).read(self.bdata_size))
            bdata = {'id' : a[0],
                     'owner' : a[1],
                     'defense' : a[2],
                     'damage' : a[3],
                     'engine_level' : a[4],
                     'hull_level' : a[5],
                     'beam_level' : a[6],
                     'torp_level' : a[7],
                     'engine_storage' : a[8],
                     'hull_storage' : a[9],
                     'beam_storage' : a[10],
                     'launcher_storage' : a[11],
                     'torp_storage' : a[12],
                     'fighters' : a[13],
                     'ship_id' : a[14],
                     'ship_to_do' : a[15],
                     'ship_to_build' : a[16],
                     'engine_type' : a[17],
                     'beam_type' : a[18],
                     'beam_count' : a[19],
                     'torpedo_type' : a[20],
                     'torpedo_count' : a[21],
                     'zero' : a[22],
                     }
            ret[bdata['id']] = bdata
        return ret
    pass
