filter_list = ["All","High Priority", "Medium Priority", "Low Priority"]

HAPP_STATE_NONE = 0
HAPP_STATE_UNHAPPY = 1
HAPP_STATE_CIVIL_WAR = 2

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
MINERO_MIN_EXTR_NEU = 50
MINERO_MIN_EXTR_TRI = 50
MINERO_MIN_EXTR_DUR = 30
MINERO_MIN_EXTR_MOL = 30
# Cantidad de Minerales bajo tierra.
MINERO_MIN_NEU = 2000
MINERO_MIN_TRI = 2000
MINERO_MIN_DUR = 1000
MINERO_MIN_MOL = 900
# Minimo de MC para considerar a un planeta recaudador de guita en vez de minero
RECAUDADOR_MIN_MC = 500

def widgets_make_link(self):
    self.window = self.main_window.get_widget('window1')
    self.cmb_filter =  self.main_window.get_widget('cmb_filter')
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
def get_regla_adquisicion(): # FIXME AGREGAR LAS REGLAS
    return 'El Latinio lo es todo'
    

##    self.btn_raza_11 = self.main_window.get_widget('btn_raza_11')


####execfile("/home/cristian/devel/quark/01/quark.py")
