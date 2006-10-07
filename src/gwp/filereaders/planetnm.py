# PLANET.NM file reader

import struct
import filereaders

class PlanetNMFile(filereaders.CaseInsensitiveFile):
    '''
    Planet Names file: Handles the planet.nm file format abstraction
    '''
    
    def __init__(self, filename):
        super(PlanetNMFile, self).__init__(filename)
        return

    def read(self, planetnum=None):
        '''
        Return a planet names collection
        '''
        ret = {}
        self.seek(0)
        for id in range(1, 501):
            name = struct.unpack("20s", super(PlanetNMFile, self).read(20))[0].strip()
            ret[id] = name
        return ret
    pass
