# XYPLAN.DAT file reader

import struct
import filereaders

class XYPlanFile(filereaders.CaseInsensitiveFile):
    '''
    Planets coordinates file reader
    '''
    reg_size = 6
    def __init__(self, filename):
        super(XYPlanFile, self).__init__(filename)
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
            # Let us check if this planet should be loaded...
            # either or both coordinates must be in range 1..8999
            if planet_coord['x'] > 0 and planet_coord['x'] <= 9000:
                ret[planet_id] = planet_coord
            elif planet_coord['y'] > 0 and planet_coord['y'] <= 9000:
                ret[planet_id] = planet_coord
            else:
                continue
        return ret
    pass
