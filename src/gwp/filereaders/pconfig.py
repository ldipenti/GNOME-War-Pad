# PCONFIG.SRC

from gwp.filereaders import CaseInsensitiveFile
import re

class PConfigFile(CaseInsensitiveFile):
    '''
    PConfig file: PHOST Configuration
    '''
    def __init__(self, filename):
        super(PConfigFile, self).__init__(filename)
        return

    def read(self):
        re_data = re.compile("^\s*(\w+)\s*=\s*([\w, -]+).*$")
        ret = {}

        for line in self.readlines():
            obj = re_data.search(line)
            if obj:
                value = obj.group(2)
                if ',' in value:
                    value = map(lambda x: x.strip(), value.split(','))
                ret[obj.group(1)] = value
        return ret
    pass
