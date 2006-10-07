# TORPSPEC.DAT file reader
# Torpedo weapons specifications

import struct
import filereaders

class TorpspecFile(filereaders.CaseInsensitiveFile):
    '''
    Torpedo weapons specs

    A torpspec record:
      +0  20 BYTEs   Name
     +20     WORD    Cost (mc for a Torpedo)
     +22     WORD    Cost (mc for a Launcher)
     +24     WORD    Tritanium needed for Launcher
     +26     WORD    Duranium needed for Launcher
     +28     WORD    Molybdenum needed for Launcher
     +30     WORD    Mass of Launcher
     +32     WORD    Tech Level
     +34     WORD    Kill Value
     +36     WORD    Damage Value
     '''
    reg_size = 38

    def __init__(self, filename):
        super(TorpspecFile, self).__init__(filename)
        return

    def read(self):
        self.seek(0)
        ret = []
        for torp_nr in range(10):
            a = struct.unpack("<20s 9H",
                              super(TorpspecFile, self).read(self.reg_size))
            torpspec = {
                'name' : a[0].strip(),
                'torp_cost' : a[1],
                'launcher_cost' : a[2],
                'tri' : a[3],
                'dur' : a[4],
                'mol' : a[5],
                'mass' : a[6],
                'tech' : a[7],
                'kill' : a[8],
                'damage' : a[9],
                }
            ret.append(torpspec)
        return ret
    pass # End of class TorpspecFile

