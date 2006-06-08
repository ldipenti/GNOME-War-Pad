# Planet data class

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
        planets = struct.unpack("H", super(PDataFile, self).read(2))[0]
        for reg in range(planets):
            a = struct.unpack("H H 3s H H H 71s",
                              super(PDataFile, self).read(self.pdata_size))
            pdata = {'owner' : a[0],
                     'id' : a[1],
                     'fcode' : a[2],
                     'mines' : a[3],
                     'factories' : a[4],
                     'defenses' : a[5],
                     #'' : a[],
                     }
            print "Register #%d - Owner: %d - Planet ID: %d - FC: %s" % (reg, pdata['owner'], pdata['id'], pdata['fcode'])
    pass
