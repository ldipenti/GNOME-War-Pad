# Race name classes

import struct

class RaceNMFile(file):
    '''
    Race Names file: Handles the race.nm file format abstraction
    '''
    
    def __init__(self, filename):
        file.__init__(self, filename, 'r')
        return

    def read(self, racenum=None):
        '''
        Return a tuple or a list of tuples (if racenum nor specified) with the
        races data
        '''
        self.seek(0)
        long_form = map(lambda x: x.strip(), struct.unpack("30s 30s 30s 30s 30s 30s 30s 30s 30s 30s 30s", super(RaceNMFile, self).read(330)))
        short_form = map(lambda x: x.strip(), struct.unpack("20s 20s 20s 20s 20s 20s 20s 20s 20s 20s 20s", super(RaceNMFile, self).read(220)))
        adjective = map(lambda x: x.strip(), struct.unpack("12s 12s 12s 12s 12s 12s 12s 12s 12s 12s 12s", file.read(self, 132)))

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

class RaceList(list):
    '''
    This class represents the race names collection
    '''
    racenm = None # race.nm file object

    def __init__(self, gamedir=''):
        list.__init__(self)
        map(lambda x: self.append(x), RaceNMFile(gamedir + '/race.nm').read())
        return

    def get_long(self):
        '''
        Return a list of races long descriptions
        '''
        ret = []
        map(lambda (l,s,a): ret.append(l), self)
        return ret
    
    def get_short(self):
        '''
        Return a list of races short descriptions
        '''
        ret = []
        map(lambda (l,s,a): ret.append(s), self)
        return ret
    
    def get_adj(self):
        '''
        Return a list of races adjectives
        '''
        ret = []
        map(lambda (l,s,a): ret.append(a), self)
        return ret
    pass
