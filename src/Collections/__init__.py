# Several collections

from FileReaders import RaceNMFile

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
