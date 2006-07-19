# XYPLAN.DAT file reader

import struct
import gnomevfs

class XYPlanFile(gnomevfs.Handle):
    '''
    Planets coordinates file reader
    '''
    reg_size = 6
    def __init__(self, filename):
        super(XYPlanFile, self).__init__(gnomevfs.URI(filename))
        return

    def read(self):
        self.seek(0)
        ret = {}
        for planet_id in range(1, 501):
            a = struct.unpack("<3H",
                              super(XYPlanFile, self).read(self.reg_size))
            planet_coord = {'id' : planet_id,
                            'x' : a[0],
                            'y' : a[1],
                            'owner' : a[2],
                            }
            ret[planet_id] = planet_coord
        return ret
    pass
