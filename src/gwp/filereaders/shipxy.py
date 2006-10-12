# SHIPXYx.DAT file reader
# Ship coordinates

import struct
from gwp.filereaders import CaseInsensitiveFile

class ShipXYFile(CaseInsensitiveFile):
    '''
    Ship coordinates file reader
    
    A ship record:
     +0     WORD    X position
     +2     WORD    Y position
     +4     WORD    Owner
     +6     WORD    Mass in kt    
    '''
    reg_size = 8
    ship_nr = 0

    def __init__(self, filename):
        super(ShipXYFile, self).__init__(filename)
        
        if self.size == 4010:
            self.ship_nr = 500
        elif self.size == 8002:
            self.ship_nr = 999
        else:
            raise "Wrong file size reading file '%s'" % filename
        return

    def read(self):
        self.seek(0)
        ret = {}
        for ship_id in range(1, self.ship_nr + 1):
            a = struct.unpack("<4H",
                              super(ShipXYFile, self).read(self.reg_size))
            ship_coord = {'id' : ship_id,
                          'x' : a[0],
                          'y' : a[1],
                          'owner' : a[2],
                          'mass' : a[3],
                }
            ret[ship_id] = ship_coord
        return ret
    pass
