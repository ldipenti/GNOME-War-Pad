# UTILx.DAT file reader
# Aditional PHOST data

import struct
from gwp.filereaders import CaseInsensitiveFile

class UtilFile(CaseInsensitiveFile):
    '''
    Phost Aditional Data file reader
    '''
    contact_reg_size = 34
    
    def __init__(self, filename):
        super(UtilFile, self).__init__(filename)
        return

    def read(self, type_req):
        pointer = 0
        record_type = 0
        data_size = 0

        types = {
             0 : "Mine field",
             1 : "Explosion",
             2 : "Mine hit",
             3 : "Dark Sense",
             4 : "Super Spy",
             5 : "Planet",
             6 : "Sensors",
             7 : "Battle result",
             8 : "Meteor",
             9 : "Meteorite Shower",
             10 : "Visual Contact",
             11 : "allied starbase",
             12 : "allied planet",
             13 : "Control record - File Header",
             14 : "Wormhole",
             15 : "Wormhole Travel",
             16 : "Ship recycled",
             17 : "Ion storm [PHost 1.3+]",
             18 : "Colonize Mission [PHost 1.3+]",
             19 : "Ship surrendered [PHost 1.3+]",
             20 : "Ship built [PHost 1.4+]",
             21 : "Ship given away, 'gsN' friendly code [PHost 1.3c+]",
             22 : "Alliance [PHost 1.4b+]",
             23 : "Bioscan [PHost 2.6+]",
             24 : "Glory Device exploded [PHost 2.6+]",
             25 : "damaged by Glory Device [PHost 2.6+]",
             26 : "Ship boarded [PHost 2.6+]",
             27 : "PCONFIG.SRC [PHost 2.6 to 2.9]",
             28 : "Ground combat [PHost 2.6+]",
             29 : "Minefields explode [PHost 2.6d+]",
             30 : "End of PHost info [PHost 2.7a+]",
             31 : "Mines scooped 'msc' [PHost 2.9d+]",
             32 : "Pillage Mission [PHost 2.9d+]",
             33 : "General Object [PHost 2.10+]",
             34 : "File [PHost 2.9d+]",
             35 : "Cloak failure [PHost 2.10b+]",
             36 : "Cloaked ship detected [PHost 2.11g+]",
             37 : "Remote-controlled ships [PHost 3.0+]",
             38 : "Activities [PHost 3.0+]",
             39 : "Build Queue [PHost 3.0+]",
             40 : "Web Drain Complete [PHost 3.0+]",
             41 : "RGA [PHost 3.3c+]",
             42 : "General Object Destruction [PHost 3.3c+]",
             43 : "Minefield Status [PHost 3.3c+]",
             44 : "Failure Notice [PHost 3.4+]",
             45 : "Planet Trade [PHost 3.4b+]",
             46 : "Mine field [PHost 3.4b+]",
             47 : "Nonexistent Planets [PHost 3.4c+]",
             48 : "PAL Summary [PHost 3.4c+]",
             49 : "Ship Score [PHost 3.4d / 4.0+]",
             50 : "Planet Score [PHost 3.4d / 4.0+]",
             51 : "Player Score [PHost 3.4d / 4.0+]",
             52 : "Ship Abilities [PHost 4.0a+]",
             53 : "Minefield Exploding [PHost 4.0b+]",
             54 : "Enemy Report [PHost 4.0h+]",
             55 : "Production Report [PHost 4.0i+]",
             56 : "Repair Report [PHost 4.0i+]",
             57 : "Special Function Definition [PHost 4.0i+]",
            }
        
        ret = []
        while record_type <> 30:
            self.seek(pointer)
            record_type, data_size = struct.unpack("<2H", super(UtilFile, self).read(4))
            pointer = pointer + 4 + data_size
            if type_req == record_type:
                print "TYPE: %s (%d) - SIZE: %d" %  (types[record_type], record_type, data_size)
                if record_type == 5:
                    a = struct.unpack("<3h 1i 1h",
                                      super(UtilFile, self).read(data_size))
                    planet = {
                        'id': a[0],
                        'temperature': a[1],
                        'owner': a[2],
                        'colonists': a[3] / 100,
                        'starbase': a[4],
                        }
                    ret.append(planet)
                elif record_type == 10:
                    a = struct.unpack("<7h 20s",
                                      super(UtilFile, self).read(self.contact_reg_size))
                    contact = {
                        'id' : a[0],
                        'owner' : a[1],
                        'speed' : a[2],
                        'x' : a[3],
                        'y' : a[4],
                        'hull_type' : a[5],
                        'heading' : a[6],
                        'name' : a[7].strip(),
                        }
                    ret.append(contact)
                elif record_type == 13:
                    a = struct.unpack("<18s 2h 2B 8I 32s 1c",
                                      super(UtilFile, self).read(data_size))
                    control = {
                        'timestamp': a[0],
                        'turn': a[1],
                        'player': a[2],
                        'major_version': a[3],
                        'minor_version': a[4],
                        'game_name': a[13].replace('\x00',''),
                        'release_code': a[14],
                        }
                    ret.append(control)
                    return ret
                else:
                    return None
            return None
        pass
        
