import sys
import gwp
# I don't understand why gwp_config.py has to exist even if I don't import it
sys.path.append(gwp.get_system_plugins_dir())
import gettext
_ = gettext.gettext

#Tipos de funciones especiales
CLOAK = 1
CALENTADORA = 2
ENFRIADORA = 3
BIOSCAN = 4
ANTICLOAK = 5
CASINO = 6
GLORY_HD = 7
GLORY_LD = 8
GRAVITRONIC = 9
HYP = 10
CHUNNEL = 11
RECALENTADORA = 12
I_ASSAULT = 13
RAMSCOOP = 14
ALQUIMIA = 15
REFINERIA = 16
REFINERIA_A = 17
ADVANCED_CLOAK = 18
NINGUNA = 19

# Funciones especiales por id de hull (Nros fijos gracias a Tim)    
special_func = {3:CALENTADORA,\
                7:ANTICLOAK,\
                8:ENFRIADORA,\
                9:BIOSCAN,\
                21:CLOAK,\
                22:CLOAK,\
                25:CLOAK,\
                26:CLOAK,\
                27:CLOAK,\
                28:CLOAK,\
                29:ADVANCED_CLOAK,\
                31:ADVANCED_CLOAK,\
                32:CLOAK,\
                33:CLOAK,\
                38:CLOAK,\
                39:GLORY_LD,\
                41:GLORY_HD,\
                42:CASINO,\
                43:CLOAK,\
                44:GRAVITRONIC,\
                45:GRAVITRONIC,\
                46:GRAVITRONIC,\
                47:CLOAK,\
                51:HYP,\
                56:CHUNNEL,\
                64:RECALENTADORA,\
                69:I_ASSAULT,\
                77:HYP,\
                84:BIOSCAN,\
                87:HYP,\
                96:RAMSCOOP,\
                97:REFINERIA_A,\
                104:REFINERIA,\
                105:ALQUIMIA}

#Special Function description 
sfd = {CLOAK:_("Cloak"),\
       ADVANCED_CLOAK:_("Advanced Cloak"),\
       ANTICLOAK:_("Anti-Cloak"),\
       BIOSCAN:_("BioScan"),\
       ENFRIADORA:_("Cools down to 50 degrees"),\
       CALENTADORA:_("Warms up to 50 degrees"),\
       RECALENTADORA:_("Warms up to 100 degrees"),\
       GLORY_HD:_("Glory Device High Damage"),\
       GLORY_LD:_("Glory Device Low Damage"),\
       CASINO:_("Generate MCs"),\
       GRAVITRONIC:_("Cloak and Gravitronic Acelerators"),\
       CHUNNEL:_("Chunnel"),\
       HYP:_("Hyperdrive"),\
       I_ASSAULT:_("Imperial Assault"),\
       RAMSCOOP:_("Ramscoop, Bioscanner"),\
       REFINERIA:_("Fuel Alchemy"),\
       REFINERIA_A:_("Fuel Alchemy"),\
       ALQUIMIA:_("Minerals Alchemy"),\
       NINGUNA:_("None")
       }

def get_hull_function(id):
    if (special_func.has_key(id)):
        return get_hull_function_description(special_func[id])
    else:
        return get_hull_function_description(NINGUNA)
    
def get_hull_function_description(hf):
    return sfd[hf]
        
