import random
import gwp

filter_list = ["All","High Priority", "Medium Priority", "Low Priority"]
FILTER_NONE = 1

HAPP_STATE_NONE = 0
HAPP_STATE_UNHAPPY = 1
HAPP_STATE_CIVIL_WAR = 2

RUTA_QUARK_FILES = gwp.get_system_plugins_dir() + 'quark_files/'

ICONO_TRANSPARENTE = 'quark_transp.gif'
ICONO_VERDE = 'quark_verde.gif'
ICONO_AMARILLO = 'quark_amarillo.gif'
ICONO_ROJO = 'quark_rojo.gif'

PRIORIDAD_AVISO_ALTO = 3
PRIORIDAD_AVISO_MEDIO = 2
PRIORIDAD_AVISO_BAJO = 1
PRIORIDAD_AVISO_NINGUNO = 0

# Cantidades que definen cuando un planeta es considerado minero y se levantan las 
# estructuras al maximo.
# Cantidad de Minerales extraidos c/100 minas.
MINERO_EXTR_NEU = 50
MINERO_EXTR_TRI = 50
MINERO_EXTR_DUR = 30
MINERO_EXTR_MOL = 30
# Cantidad de Minerales bajo tierra.
MINERO_NEU = 2000
MINERO_TRI = 2000
MINERO_DUR = 1000
MINERO_MOL = 900
# Minimo de MC para considerar a un planeta recaudador de guita en vez de minero
RECAUDADOR_MIN_MC = 500

TIPO_NADA = 0
TIPO_MINERO = 1
TIPO_RECAUDADOR = 2
TIPO_COMUN = 3

planeta_quark = {'pid': 0,
                 'tipo_quark': TIPO_NADA,
                 'tipo_elegido': TIPO_NADA,
                 'minero_neu': 0,
                 'minero_tri': 0,
                 'minero_dur': 0,
                 'minero_mol': 0,
                 'terraformar': 0
                 }

reporte_planeta = {'pid': 0,
                   'temperature' : 0,
                   'clanes_nec': 0,
                   'clanes_nec_comment': '',
                   'MC': 0,
                   'supplies' : 0,
                   'fabricas': 0,
                   'minas': 0,
                   'minas_comment': '',
                   'dp': 0,
                   'dp_comment': '',
                   'costo_constr' : 0,
                   }

ID_BOVINOIDS = 2
ID_AMORFOS = 5

#--------------------------------------------------------------------------
def widgets_make_link(self):
    self.window = self.main_window.get_widget('window1')
    ## FIXME : USO DEL FILTER
    #self.cmb_filter =  self.main_window.get_widget('cmb_filter')
    self.lst_planets =  self.main_window.get_widget('lst_planets')
    self.lst_minerals =  self.main_window.get_widget('lst_minerals')
    #TextView
    self.tv_notification =  self.main_window.get_widget('tv_notification')
    #labels
    self.lbl_planet_name =  self.main_window.get_widget('lbl_planet_name')
    self.lbl_colonists =  self.main_window.get_widget('lbl_colonists')
    self.lbl_colonists_happ =  self.main_window.get_widget('lbl_colonists_happ')
    self.lbl_natives =  self.main_window.get_widget('lbl_natives')
    self.lbl_natives_happ =  self.main_window.get_widget('lbl_natives_happ')
    self.lbl_natives_type =  self.main_window.get_widget('lbl_natives_type')
    self.lbl_natives_spi =  self.main_window.get_widget('lbl_natives_spi')
    self.lbl_fab_max =  self.main_window.get_widget('lbl_fab_max')
    self.lbl_min_max =  self.main_window.get_widget('lbl_min_max')
    self.lbl_def_max =  self.main_window.get_widget('lbl_def_max')
    self.lbl_MC =  self.main_window.get_widget('lbl_MC')
    self.lbl_supplies =  self.main_window.get_widget('lbl_supplies')
    self.lbl_income =  self.main_window.get_widget('lbl_income')
    self.lbl_base =  self.main_window.get_widget('lbl_base')
    #SpinButtons
    self.inc_colonists_tax =  self.main_window.get_widget('inc_colonists_tax')
    self.inc_natives_tax =  self.main_window.get_widget('inc_natives_tax')
    self.inc_fab =  self.main_window.get_widget('inc_fab')
    self.inc_min =  self.main_window.get_widget('inc_min')
    self.inc_def =  self.main_window.get_widget('inc_def')

#--------------------------------------------------------------------------
def get_tip(self): 
    return random.choice(self.tips)

#--------------------------------------------------------------------------
def init_tips(self):
    self.tips = []
    f=open(self.quark_utils.RUTA_QUARK_FILES + 'quark_tips.txt', 'r')
    for line in f:
        if not line[0:1] == '#': # Si no es un comentario
            if line[-1:] == "\n": # si el ultimo caracter es un "enter"
                line = line[:-2] # caso el "enter"
            self.tips.append(line)
   
    f.close()



