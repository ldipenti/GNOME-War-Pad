# TARGETx.DAT file reader
# Enemy contacts data

import struct
import filereaders

class TargetFile(filereaders.CaseInsensitiveFile):
    '''
    Enemy ships file reader
    '''
    reg_size = 34

    def __init__(self, filename):
        super(TargetFile, self).__init__(filename)
        return

    def read(self):
        self.seek(0)
        target_nr = struct.unpack("<H",
                                 super(TargetFile, self).read(2))[0]
        ret = {}
        for target in range(target_nr):
            a = struct.unpack("<7h 20s",
                              super(TargetFile, self).read(self.reg_size))
            target = {
                'id' : a[0],
                'owner' : a[1],
                'speed' : a[2],
                'x' : a[3],
                'y' : a[4],
                'hull_type' : a[5],
                'heading' : a[6],
                'name' : a[7].strip(),
              }
            ret[target['id']] = target
        return ret
    pass
