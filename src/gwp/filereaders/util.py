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

    def read(self):
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
        # Every register have several fields, the first value is the field
        # size, the second is the field name, and the third the struct
        # string to read the data from the file.
        registers = { 0 : [[2, 'id', 'h'],               # Minefield
                           [2, 'x', 'h'],
                           [2, 'y', 'h'],
                           [2, 'owner', 'h'],
                           [4, 'mine_units', 'i'],
                           [2, 'type', 'h'],
                           [2, 'id_planet', 'h'],
                           [2, 'report_cause', 'h']],
                      1 : [[2, 'x', 'h'],                # Explosion
                           [2, 'y', 'h'],
                           [2, 'ship_id', 'h'],
                           [20, 'ship_name', '20s']],
                      2 : [[2, 'ship_id', 'h'],          # Mine hit
                           [2, 'x', 'h'],
                           [2, 'y', 'h'],
                           [2, 'damage', 'h'],
                           [20, 'ship_name', '20s']],
                      5 : [[2, 'id', 'h'],               # Planet
                           [2, 'temperature', 'h'],
                           [2, 'owner', 'h'],
                           [4, 'colonists', 'i'],
                           [2, 'starbase', 'h']],
                      10: [[2, 'id', 'h'],               # Visual Contact
                           [2, 'owner', 'h'],
                           [2, 'speed', 'h'],
                           [2, 'x', 'h'],
                           [2, 'y', 'h'],
                           [2, 'hull_type', 'h'],
                           [2, 'heading', 'h'],
                           [20, 'name', '20s']],
                      11: [[2, 'id', 'h'],               # Allied starbase
                           [2, 'owner', 'h']],
                      12: [[2, 'id', 'h'],               # Allied planet
                           [2, 'owner', 'h'],
                           [2, 'temperature', 'h'],
                           [2, 'native_gov', 'h'],
                           [4, 'natives', 'i'],
                           [4, 'mined_neu', 'i'],
                           [4, 'mined_tru', 'i'],
                           [4, 'mined_dur', 'i'],
                           [4, 'mined_mol', 'i'],
                           [4, 'colonists', 'i'],
                           [4, 'supplies', 'i'],
                           [4, 'megacredits', 'i']],
                      13: [[18, 'timestamp', '18s'],     # Control record
                           [2, 'turn_nr', 'h'],
                           [2, 'player_nr', 'h'],
                           [1, 'phost_major_version', 'c'],
                           [1, 'phost_minor_version', 'c'],
                           [4, 'digest_hullspec', 'i'],
                           [4, 'digest_engspec', 'i'],
                           [4, 'digest_beamspec', 'i'],
                           [4, 'digest_torpspec', 'i'],
                           [4, 'digest_truehull', 'i'],
                           [4, 'digest_xyplan', 'i'],
                           [4, 'digest_pconfig', 'i'],
                           [4, 'digest_racenm', 'i'],
                           [32, 'game_name', '32s'],
                           [1, 'phost_release_code', 'c']]
                      }
        ret = {}
        while record_type <> 30:
            self.seek(pointer)
            record_type, data_size = struct.unpack("<2H", super(UtilFile, self).read(4))
            pointer = pointer + 4

            if record_type in registers:
                reg_size = 0
                reg_data = {}

                for field in registers[record_type]:
                    if reg_size < data_size:

                        reg_size += field[0]
                        a = struct.unpack("<"+field[2],
                                          super(UtilFile, self).read(field[0]))
                        reg_data[field[1]] = a[0]
                        pointer += field[0]
                try:
                    ret[types[record_type]].append(reg_data)
                except KeyError:
                    ret[types[record_type]] = [reg_data]

                pointer += data_size - reg_size
            else:
                pointer += data_size            
        return ret

        
