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
sfd = {CLOAK:"Cloak",\
ADVANCED_CLOAK:"Advanced Cloak",\
ANTICLOAK:"Anti-Cloak",\
BIOSCAN:"BioScan",\
ENFRIADORA:"Enfria hasta 50 grados",\
CALENTADORA:"Calienta Hasta 50 grados",\
RECALENTADORA:"Calienta Hasta 100 grados",\
GLORY_HD:"Glory Device High Damage",\
GLORY_LD:"Glory Device Low Damage",\
CASINO:"Casino",\
GRAVITRONIC:"Cloak y Gravitronic Acelerators",\
CHUNNEL:"Chunnel",\
HYP:"Hyperdrive",\
I_ASSAULT:"Imperial Assault",\
RAMSCOOP:"Ramscoop, Bioscanner",\
REFINERIA:"Genera combustible",\
REFINERIA_A:"Genera combustible",\
ALQUIMIA:"Genera minerales",\
NINGUNA:"Ninguna"
}

def get_hull_function(id):
    if (special_func.has_key(id)):
        return get_hull_function_description(special_func[id])
    else:
        return get_hull_function_description(NINGUNA)
    
def get_hull_function_description(hf):
    return sfd[hf]
        
