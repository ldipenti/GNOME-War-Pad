# BEAMSPEC.DAT file reader
# Beam weapons specifications

import struct
import filereaders

class BeamspecFile(filereaders.CaseInsensitiveFile):
    '''
    Beam weapons specs
    
    A beamspec record:
     +0  20 BYTEs   Name
     +20     WORD    Cost (mc)
     +22     WORD    Tritanium needed
     +24     WORD    Duranium needed
     +26     WORD    Molybdenum needed
     +28     WORD    Mass
     +30     WORD    Tech Level
     +32     WORD    Kill value
     +34     WORD    Damage value
     '''
    reg_size = 36

    def __init__(self, filename):
        super(BeamspecFile, self).__init__(filename)
        return

    def read(self):
        self.seek(0)
        ret = []
        for beam_nr in range (10):
            a = struct.unpack("<20s 8H",
                              super(BeamspecFile, self).read(self.reg_size))
            beamspec = {
                'name' : a[0].strip(),
                'cost' : a[1],
                'tri' : a[2],
                'dur' : a[3],
                'mol' : a[4],
                'mass' : a[5],
                'tech' : a[6],
                'kill' : a[7],
                'damage' : a[8]
                }
            ret.append(beamspec)
        return ret
    pass # End of class BeamspecFile
