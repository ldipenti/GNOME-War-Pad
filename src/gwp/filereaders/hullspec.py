# HULLSPEC.DAT file reader
# Ship hulls specifications

import struct
from gwp.filereaders import CaseInsensitiveFile

class HullspecFile(CaseInsensitiveFile):
    '''
    Ship hulls specs

    A hullspec record:
     +0  30 BYTEs   Name
    +30     WORD    Number of picture in RESOURCE.PLN
    +32     WORD    =1. In VPCPLAY.BAS this field is identified as "image of a
                    heavily damaged ship", though it seems to be unused.
    +34     WORD    Tritanium needed
    +36     WORD    Duranium needed
    +38     WORD    Molybdenum needed
    +40     WORD    Fuel tank size
    +42     WORD    Crew size
    +44     WORD    Number of engines
    +46     WORD    Hull mass (empty)
    +48     WORD    Tech Level
    +50     WORD    Cargo room
    +52     WORD    Number of fighter bays
    +54     WORD    max. Number of torpedo launchers
    +56     WORD    max. Number of beam weapons
    +58     WORD    Cost (mc)
    '''
    reg_size = 60

    def __init__(self, filename):
        super(HullspecFile, self).__init__(filename)
        return

    def read(self):
        self.seek(0)
        ret = []
        for hull_nr in range(105):
            a = struct.unpack("<30s 15H",
                              super(HullspecFile, self).read(self.reg_size))
            hullspec = {
                'name' : a[0].strip(),
                'pic_nr': a[1], # a[2] ignored - garbage
                'tri' : a[3],
                'dur' : a[4],
                'mol' : a[5],
                'fuel' : a[6],
                'crew' : a[7],
                'engines' : a[8],
                'mass' : a[9],
                'tech' : a[10],
                'cargo' : a[11],
                'fighter_bays' : a[12],
                'torp_launchers' : a[13],
                'beam_weapons' : a[14],
                'cost' : a[15],
                }
            ret.append(hullspec)
        return ret
    pass # End of class HullspecFile

