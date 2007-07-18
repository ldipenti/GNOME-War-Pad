# GENx.DAT file reader

import struct
from gwp.filereaders import CaseInsensitiveFile

class GenFile(CaseInsensitiveFile):
    '''
    Misc data file
    '''
    gen_size = 157 # The entire file
    
    def __init__(self, filename):
        super(GenFile, self).__init__(filename)
        return

    def read(self):
        self.seek(0)
        ret = {}
        # NOOP for now... FIXME, TODO
        return ret
    pass
