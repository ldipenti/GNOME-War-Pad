# TRUEHULL.DAT file reader
# Race -> Hulls assignments

import struct
from gwp.filereaders import CaseInsensitiveFile

class TruehullFile(CaseInsensitiveFile):
    '''
    Race -> Starship hulls assignments

    For each player (11) an array with 20 WORDs. Each WORD contains the
    number of a hull that the player can build (Index into HULLSPEC.DAT).
    These 20 "hull slots" correspond to the appropriate field in
    the starbase record.
    '''
    reg_size = 40

    def __init__(self, filename):
        super(TruehullFile, self).__init__(filename)
        return

    def read(self):
        self.seek(0)
        ret = []
        for player in range(11):
            a = struct.unpack("<20H",
                              super(TruehullFile, self).read(self.reg_size))
            ret.append(a)
        return ret
    pass # End of class TruehullFile
