# KOREx.DAT file reader

import struct
from gwp.filereaders import CaseInsensitiveFile

class KoreFile(CaseInsensitiveFile):
    '''
    Additional contacts file reader
    '''
    minefield_reg_size = 8
    storm_reg_size = 12
    contact_reg_size = 34
    
    def __init__(self, filename):
        super(KoreFile, self).__init__(filename)
        return

    def read(self):
        ret = {}
        ret_minefields = {}
        ret_storms = {}
        ret_contacts = {}
        # Minefields
        self.seek(102)
        for minefield_id in range(1, 501):
            a = struct.unpack("<4h",
                              super(KoreFile, self).read(self.minefield_reg_size))
            minefield = {
                'id' : minefield_id,
                'x' : a[0],
                'y' : a[1],
                'radius' : a[2],
                'owner' : a[3],
                }
            ret_minefields[minefield['id']] = minefield
        ret['minefields'] = ret_minefields
        # Ion storms
        self.seek(4102)
        for storm_id in range(1, 51):
            a = struct.unpack("<6h",
                              super(KoreFile, self).read(self.storm_reg_size))
            storm = {
                'id' : storm_id,
                'x' : a[0],
                'y' : a[1],
                'radius' : a[2],
                'voltage' : a[3],
                'speed' : a[4],
                'heading' : a[5],
                }
            ret_storms[storm['id']] = storm
        ret['storms'] = ret_storms
        # Additional visual contacts (if there is any...)
        ret['contacts'] = {}
        self.seek(12702)
        contact_signature = struct.unpack("<4s", super(KoreFile, self).read(4))[0]
        
        # This suck, thanks to Tim
        if contact_signature == '1120':
            ret['target_extra'] = True
            return ret
        else:
            ret['target_extra'] = False
            return ret
            
        self.seek(12722)
        contacts_nr = struct.unpack("<I", super(KoreFile, self).read(4))[0]
        
        for contact in range(contacts_nr):
            a = struct.unpack("<6H 1h 20s",
                              super(KoreFile, self).read(self.contact_reg_size))
            contact = {
                'id' : a[0],
                'owner' : a[1],
                'speed' : a[2],
                'x' : a[3],
                'y' : a[4],
                'hull_type' : a[5],
                'heading' : a[6],
                'name' : self._decode_name(a[7]),
                }
            ret_contacts[contact['id']] = contact
        ret['contacts'] = ret_contacts
        return ret

    # I wonder why Tim did this...
    def _decode_name(self, name):
        ret = ''
        for i in range(len(name)):
            ret += chr(ord(name[i]) ^ 155 - i - 1)
        return ret
    pass
