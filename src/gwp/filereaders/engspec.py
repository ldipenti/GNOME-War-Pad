# ENGSPEC.DAT file reader
# Engines specifications

import struct
import filereaders

class EngspecFile(filereaders.CaseInsensitiveFile):
    '''
    Engines specs
    
    A engspec record:
    +0  20 BYTEs   Name
    +20     WORD    Cost (mc)
    +22     WORD    Tritanium needed
    +24     WORD    Duranium needed
    +26     WORD    Molybdenum needed
    +28     WORD    Tech Level
    +30   9 DWORDs  Fuel used to travel 1 month at the given speed, for each
                    warp factor, for a 100000 kt ship
     '''
    reg_size = 66

    def __init__(self, filename):
        super(EngspecFile, self).__init__(filename)
        return

    def read(self):
        self.seek(0)
        ret = []
        for beam_nr in range (9):
            a = struct.unpack("<20s 5H 9L",
                              super(EngspecFile, self).read(self.reg_size))
            engspec = {
                'name' : a[0].strip(),
                'cost' : a[1],
                'tri' : a[2],
                'dur' : a[3],
                'mol' : a[4],
                'tech' : a[5],
                'fuel_use' : [a[6], a[7], a[8],
                              a[9], a[10], a[11],
                              a[12], a[13], a[14]]
                }
            ret.append(engspec)
        return ret
    pass # End of class EngspecFile
