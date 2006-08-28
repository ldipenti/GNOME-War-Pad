# KOREx.DAT file reader

import struct
import FileReaders

class KoreFile(FileReaders.CaseInsensitiveFile):
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
        # Additional visual contacts
        self.seek(12706)
        contacts_nr = struct.unpack("<H", super(KoreFile, self).read(2))[0]
        for contact in range(contacts_nr):
            a = struct.unpack("<7h 20s",
                              super(KoreFile, self).read(self.contact_reg_size))
            contact = {
                'id' : a[0],
                'owner' : a[1],
                'speed' : a[2],
                'x' : a[3],
                'y' : a[4],
                'hull_type' : a[5],
                'heading' : a[6],
                'name' : a[7],
                }
            ret_contacts[contact['id']] = contact
        ret['contacts'] = ret_contacts
        return ret
    pass
