# RACE.NM file reader

import struct
import gnomevfs

class RaceNMFile(gnomevfs.Handle):
    '''
    Race Names file: Handles the race.nm file format abstraction
    '''
    
    def __init__(self, filename):
        super(RaceNMFile, self).__init__(gnomevfs.URI(filename))
        return

    def read(self, racenum=None):
        '''
        Return a tuple or a list of tuples (if racenum nor specified) with the
        races data
        '''
        self.seek(0)
        long_form = map(lambda x: x.strip(), struct.unpack("30s 30s 30s 30s 30s 30s 30s 30s 30s 30s 30s", super(RaceNMFile, self).read(330)))
        short_form = map(lambda x: x.strip(), struct.unpack("20s 20s 20s 20s 20s 20s 20s 20s 20s 20s 20s", super(RaceNMFile, self).read(220)))
        adjective = map(lambda x: x.strip(), struct.unpack("12s 12s 12s 12s 12s 12s 12s 12s 12s 12s 12s", super(RaceNMFile, self).read(132)))

        if racenum >= 1 and racenum <= 11:
            return (long_form[racenum-1], short_form[racenum-1], adjective[racenum-1])
        elif racenum == None:
            racelist = []
            for n in range(11):
                racelist.append((long_form[n], short_form[n], adjective[n]))
            return racelist
        else:
            return None
    pass
