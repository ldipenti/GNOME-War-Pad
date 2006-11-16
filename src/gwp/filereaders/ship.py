# SHIPx.DAT file reader
# My ships data

import struct
from gwp.filereaders import CaseInsensitiveFile

class ShipFile(CaseInsensitiveFile):
    '''
    Ship data file reader
    '''
    reg_size = 107

    def __init__(self, filename):
        super(ShipFile, self).__init__(filename)
        return

    def read(self):
        self.seek(0)
        ships_nr = struct.unpack("<H",
                                 super(ShipFile, self).read(2))[0]
        ret = {}
        for ship in range(ships_nr):
            a = struct.unpack("<2H 3s 1H 2h 16H 20s 21H",
                              super(ShipFile, self).read(self.reg_size))
            ship = {
                'id' : a[0],
                'owner' : a[1],
                'fcode' : a[2],
                'speed' : a[3],
                'x_to_waypoint' : a[4],
                'y_to_waypoint' : a[5],
                'x' : a[6],
                'y' : a[7],
                'engines_type' : a[8],
                'hull_type' : a[9],
                'beams_type' : a[10],
                'beams' : a[11],
                'fighter_bays' : a[12],
                'torps_type' : a[13],
                'torps_fighters_nr' : a[14],
                'torps_launchers' : a[15],
                'mission' : a[16],
                'primary_enemy' : a[17],
                'tow_ship_id' : a[18],
                'damage' : a[19],
                'crew' : a[20],
                'colonists' : a[21],
                'name' : a[22].strip(),
                'neu' : a[23],
                'tri' : a[24],
                'dur' : a[25],
                'mol' : a[26],
                'supp' : a[27],
                'unload_neu' : a[28],
                'unload_tri' : a[29],
                'unload_dur' : a[30],
                'unload_mol' : a[31],
                'unload_col' : a[32],
                'unload_supp' : a[33],
                'unload_planet_id' : a[34],
                'transfer_neu' : a[35],
                'transfer_tri' : a[36],
                'transfer_dur' : a[37],
                'transfer_mol' : a[38],
                'transfer_col' : a[39],
                'transfer_supp' : a[40],
                'transfer_ship_id' : a[41],
                'intercept_ship_id' : a[42], # ...or second mission argument
                'megacredits' : a[43],
                }
            ret[ship['id']] = ship
        return ret
    pass
