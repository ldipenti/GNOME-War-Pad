#!/usr/bin/env python
import sys
sys.path.append(gwp.get_system_plugins_dir())
##import vp_utils
import pygtk
import gtk
import gtk.glade

class Quark(gwp.Plugin):
    import quark_utils
    name = "Quark"
    version = "0.15"
    author_name = "Cristian Abalos"
    author_email = "abalosc@gmail.com"
    desc_short = _("Help in the resources management")
    desc_long = ""
    license = "GPL"
    hotkey = 'q'

    FILTER_NONE = 1
    RUTA_QUARK_FILES = gwp.get_system_plugins_dir() + 'quark_files/'
    natt = ''
    prioridad_aviso = quark_utils.PRIORIDAD_AVISO_NINGUNO
    
    #--------------------------------------------------------------------------     
    def _init_lists(self):
        self.pl = []
        self.pl_otros = []
        all_pl = gwp.planet_get_list()
        for i in all_pl:
            p = all_pl[i]
            if p.is_mine():
                self.pl.append(p)
            elif p.is_known() and p.is_unowned():
                self.pl_otros.append(p)

    #--------------------------------------------------------------------------
    
# *******************************  REPORTE ************************************

    #--------------------------------------------------------------------------    
    def quark_report_generate(self, p):
        """Realiza todos los chequeos para mostrar el reporte en la ventana de
        existir algo que informar."""
        self.textbuffer = self.tv_notification.get_buffer()
        self.textbuffer.set_text(self.natt)
        
    #--------------------------------------------------------------------------
    
# ***************************  Notification Area  *****************************

    #--------------------------------------------------------------------------
    def na_report_generate(self, p):
        """Genera los avisos que van al area de notificacion."""
        self.natt = ''
        self.quark_set_icon(self.quark_utils.PRIORIDAD_AVISO_NINGUNO,
                            self.natt)        
        if p.is_mine():
            self.report_verify_happyness(p, 'c') # Colonists
            self.report_verify_happyness(p, 'n') # Natives
        self.report_verify_colonists(p)
        #self.report_verify_temperature(p) # Ve si conviene Terraformar
        
    #--------------------------------------------------------------------------
    
# *****************************************************************************
# ***************************  Funciones comunes  *****************************
# ************************  a reporte y notif area ****************************
# *****************************************************************************

    #--------------------------------------------------------------------------
    def calculate_future_happyness_natives(self, p):
        """Devuelve el valor de happyness del siguiente turno"""
        actual_change = p.get_happiness_nat_change()
        actual_happ = p.get_happiness_natives()
        return (actual_happ + actual_change)
       
    #--------------------------------------------------------------------------
    def calculate_future_happyness_colonists(self, p):
        """Devuelve el valor de happyness del siguiente turno"""
        actual_change = p.get_happiness_col_change()
        actual_happ = p.get_happiness_colonists()
        return (actual_happ + actual_change)
       
    #--------------------------------------------------------------------------
    def calculate_missing_colonists_tax_natives(self, p):
        """devuelve la cantidad de colonos que faltan para cobrar al maximo a
        los nativos."""
        if (p.get_natives_race() <> 5): # Si no son Amorphous
            tax, max_i = self.calculate_max_income_from_natives(p)
            if max_i > p.get_tax_collected_natives():
                factor_impuestos = p.get_tax_rate_natives()/100
                col_faltan = (max_i - p.get_tax_collected_natives())/factor_impuestos
                
                if col_faltan > p.get_colonists():
                    return col_faltan
        return 0
    #--------------------------------------------------------------------------    
    def calculate_max_income_from_natives(self, p):
        """ Determino el maximo que se puede cobrar (con una copia del planeta)
        devuelve (% de impuesto, cantidad de MC) """
        if p.get_natives(): # SI no hay nativos no tiene sentido esto 
            future_p = p.copy()

            #gs = gwp.get_game_state()
            #nro_raza = gs.get_race_nr()
            #future_p.set_owner(nro_raza)
            
            future_p.set_colonists(1000) # suficientemente grande para evitar problemas
            tax = 1
            while tax:
                future_p.set_tax_natives(tax)
                hap_dif = future_p.get_happiness_nat_change()
                limit = future_p.get_col_growth_limit()
                income = future_p.get_tax_collected_natives()
                if  (hap_dif >= 0) and  (limit >= income):
                    tax += 1
                else:
                    if hap_dif < 0:
                        tax -= 1
                    future_p.set_tax_natives(tax)
                    income = future_p.get_tax_collected_natives()
                    return tax, income
        return 0,0

    #--------------------------------------------------------------------------
    def calculate_missing_colonists_supplies(self, p):
        """Devuelve la cantidad de colonos que faltan para que los bovinoides
        produzcan el maximo de supplies."""
        # Supplies Bovinoids
        if (p.get_natives_race() == 2): # Bovinoids
            sup = p.get_natives() / 100
            if p.get_colonists() < sup:
                return sup
        return 0

    #--------------------------------------------------------------------------
    def is_miner_planet(self, p):
        """Determina si la cantidad de mineral que se puede obtener esta dentro
        de los parametros de *Planeta Minero*."""
        return 0

        
    #--------------------------------------------------------------------------
    def report_verify_happyness(self, p, people):
        """Verifica si van a pasar a estar desontentos o en guerra civil en caso de
        taxes con modificador negativo. Salida al area de notificacion"""
        self.natt = ""
        if people == 'c':
            people = _("Colonists ")
            future_happ = self.calculate_future_happyness_colonists(p)
        else:
            people = ("Natives ")
            future_happ = self.calculate_future_happyness_natives(p)
        if future_happ < 1: # CIVIL WAR!
            self.natt = people + "will be in CIVIL WAR the next turn"
        elif future_happ < 30: # NO PAGAN
            self.natt = people + "will not pay taxes the next turn"
        elif future_happ < 40: # en 39 empieza el quilombo
            self.natt = people + "will be RIOTING the next turn"
        elif future_happ < 70: # en 69 dejan de crecer
                self.natt = people + "will be UNHAPPY the next turn"
        if self.natt:
            self.quark_set_icon(self.quark_utils.PRIORIDAD_AVISO_ALTO, self.natt)

        
    #--------------------------------------------------------------------------
    def report_verify_colonists(self, p_orig):
        """ Verifica si existen suficiente cantidad de colonos para:
        * cobrarles el maximo posible a los nativos 
        * sacar el max posible de supplies si hay Bovinoids
        * Max de Fab y minas si no hay nativos que paguen bien # FALTA #
        """
        self.natt = ""

        p = p_orig.copy()
        if (not p.is_mine()): # Para planetas orbitados y no mios
            gs = gwp.get_game_state()
            nro_raza = gs.get_race_nr()
            p.set_owner(nro_raza)
            
        if p.get_natives(): # SI no hay nativos no tiene sentido esto  
            #Hago todos los calculos
            col_faltan_tax = self.calculate_missing_colonists_tax_natives(p)
            col_faltan_sup = self.calculate_missing_colonists_supplies(p)
            tax, max_i = self.calculate_max_income_from_natives(p)
            dif = max_i - p.get_tax_collected_natives()
            if dif < 0:
                dif = 0
            
            # REPORTA "Faltan colonos"
            if col_faltan_tax or col_faltan_sup:
                if col_faltan_tax > col_faltan_sup:
                    col_faltan = col_faltan_tax
                else:
                    col_faltan = col_faltan_sup
                self.natt = "Need "+ str(col_faltan) +" clans of colonists!"

            # REPORTA "Puedo cobrar mas"
            if dif:
                if self.natt:
                    self.natt = self.natt + "\n"
                self.natt = self.natt + "You can collect " + str(max_i) + " MC "
                self.natt = self.natt  + "(" + str(dif) +" more)"
                
                # Falta ver si pagan poco y conviene construir fab y minas

            # REPORTA "Puedo sacar mas supplies"
            if col_faltan_sup:
                if self.natt:
                    self.natt = self.natt + "\n"
                self.natt = self.natt + "You can obtain " + str(col_faltan_sup) + " supplies "
                dif = col_faltan_sup - p.get_colonists()
                self.natt = self.natt + "(" + str(dif) +" more)"

        
        chequear_construcciones = 1
        if chequear_construcciones:
            # FALTA controlar si las fab y minas estan en valores optimos.
            pass
        # Se imprime!
        if self.natt:
            self.quark_set_icon(self.quark_utils.PRIORIDAD_AVISO_MEDIO, self.natt)
            

    #--------------------------------------------------------------------------
    def report_verify_temperature(self, orig_p):
        if orig_p.get_natives(): # SI no hay nativos no tiene sentido esto  
            if (orig_p.get_temperature_f() < 15) or (orig_p.get_temperature_f() > 84):

                p = orig_p.copy()
                if not orig_p.is_mine(): # Si no es mio
                    # Lo simulo para hacer los calculos
                    print "SIMULO"
                    gs = gwp.get_game_state()
                    nro_raza = gs.get_race_nr()
                    p.set_owner(nro_raza)
                    p.set_colonists(1000)

                limit = p.get_col_growth_limit()
                tax, max_i = self.calculate_max_income_from_natives(p)
                print "ANTES: Max: " + str(max_i) + " Limite: " + str(limit)
                if (max_i < limit) or (max_i == 0):
                    # No interesa la temp, cobro poco
                    print "Cobro poco"
                    return 0
                else:
                    # La $$ cobrada es limitada por la temperatura
                    terraformado = p.copy()
                    print "ANTES : Max" + str(max_i) + " Limite: " + str(limit)
                    while max_i > limit:
                        if (terraformado.get_temperature_f() < 50):
                            terraformado.set_temperature(100 - (terraformado.get_temperature_f() + 1))
                        else:
                            terraformado.set_temperature(100 - (terraformado.get_temperature_f() - 1))
                        limit = terraformado.get_col_growth_limit()
                        tax, max_i = self.calculate_max_income_from_natives(terraformado)
                        print "Max: " + str(max_i) + " Limite: " + str(limit)
                        print "A " + str(terraformado.get_temperature_f()) + " grados"


    #--------------------------------------------------------------------------
    def conectar_planetas(self):
        """Conecta la senial planeta seleccionado para mostrar avisos en el
        area de notificacion. YA NO SE USA"""
        pass
#         self.signals_id = []
#         for planeta in self.pl:
#             cod = planeta.connect("selected", self.na_generar)
#             if self.signals_id == []:
#                 self.signals_id = { planeta.get_id() : cod }
#             else:
#                 self.signals_id [ planeta.get_id() ] = cod
#         for planeta in self.pl_otros: # Planetas orbitados sin duenio
#             cod = planeta.connect("selected", self.na_generar)
#             if self.signals_id == []:
#                 self.signals_id = { planeta.get_id() : cod }
#             else:
#                 self.signals_id [ planeta.get_id() ] = cod
            
    ###########################################################################        
    ################################## GUI ####################################
    ###########################################################################

    # Constructor
    #--------------------------------------------------------------------------
    def __init__(self):
        gwp.Plugin.__init__(self)
        self.ruta = gwp.get_system_plugins_dir()
        self.fname = self.ruta + '/quark.glade'
        self.__initglade(self.fname)
        self.quark_utils.widgets_make_link(self)
        self._init_lists()
        self.__create_gui()
        # self.conectar_planetas()
        self.inicializar_interfaces() # Notification Area
    
    #--------------------------------------------------------------------------
    def __create_gui(self):
        # Para el manejo de la selecion en los treeviews
        self.treeselection_planets = self.lst_planets.get_selection()
        # treeview setup
        self.store_planets = gtk.ListStore(int, str)
        self.store_minerals = gtk.ListStore(str, int, int, str, str)
        renderer = gtk.CellRendererText()
        
        # Columns Lista Planetas
        col_planets = gtk.TreeViewColumn(_('Planets'), renderer, text=1)
        col_minerals = gtk.TreeViewColumn(_('Mineral'), renderer, text=0)
        col_surf = gtk.TreeViewColumn(_('Surf'), renderer, text=1)
        col_core = gtk.TreeViewColumn(_('Core'), renderer, text=2)
        col_extr = gtk.TreeViewColumn(_('Extr'), renderer, text=3)
        col_extrx100 = gtk.TreeViewColumn(_('x/100'), renderer, text=4)
        # Add columns to models
        # Planetas
        self.lst_planets.append_column(col_planets)
        self.lst_planets.set_model(self.store_planets)
        # Minerales
        self.lst_minerals.append_column(col_minerals)
        self.lst_minerals.append_column(col_surf)
        self.lst_minerals.append_column(col_core)
        self.lst_minerals.append_column(col_extr)
        self.lst_minerals.append_column(col_extrx100)
        self.lst_minerals.set_model(self.store_minerals)

        # callbacks
        ## FIXME : USO DEL FILTER
        #self.cmb_filter.entry.connect("changed", self.filter_selected, None)
        self.treeselection_planets.connect("changed", self.quark_planet_selected, None)
        #Comienzo la cascada de inicializaciones
        self.filter_load_data()
        self.filter_init_selection()

    #--------------------------------------------------------------------------            
    def inicializar_interfaces(self):
        self.pm = gwp.get_plugin_mgr()
        self.na = self.pm.get_plugin('NotificationArea')
        if self.na:
            self.quark_icon = gtk.Button()
            self.quark_icon.connect("clicked", self.main_cb, None)
            self.i = gtk.Image()
            
            self.quark_icon.add(self.i) #agregado para que tenga alguna imagen (x el remove)
            self.na.add_notification(self.quark_icon)
            self.natt = ''
            self.quark_set_icon(self.quark_utils.PRIORIDAD_AVISO_NINGUNO,
                                self.quark_utils.get_regla_adquisicion()) # Un msj cheto 

    #--------------------------------------------------------------------------
    def destruir_interfaces(self):
        self.na = None

    #--------------------------------------------------------------------------
    def quark_set_icon(self, prioridad, texto=None):
        """ Devuelve una imagen con el icono del color correspondiente"""
        filename = ''

        if prioridad == self.quark_utils.PRIORIDAD_AVISO_NINGUNO:
            self.prioridad_aviso = self.quark_utils.PRIORIDAD_AVISO_NINGUNO
            filename = self.quark_utils.ICONO_TRANSPARENTE
            
        elif (prioridad > self.prioridad_aviso) \
                 and (prioridad == self.quark_utils.PRIORIDAD_AVISO_BAJO):
            self.prioridad_aviso = self.quark_utils.PRIORIDAD_AVISO_BAJO
            filename = self.quark_utils.ICONO_VERDE
            
        elif (prioridad > self.prioridad_aviso) \
                 and (prioridad == self.quark_utils.PRIORIDAD_AVISO_MEDIO):
            self.prioridad_aviso = self.quark_utils.PRIORIDAD_AVISO_MEDIO
            filename = self.quark_utils.ICONO_AMARILLO
            
        elif (prioridad > self.prioridad_aviso) \
                 and (prioridad == self.quark_utils.PRIORIDAD_AVISO_ALTO):
            self.prioridad_aviso = self.quark_utils.PRIORIDAD_AVISO_ALTO
            filename = self.quark_utils.ICONO_ROJO
        else:
            return None
        # remuevo la imagen anterior
        self.quark_icon.remove(self.i)
        # preparo la nueva imagen
        self.i.set_from_file(self.RUTA_QUARK_FILES + filename)
        self.i.show()
        # agrego la nueva imagen
        self.quark_icon.add(self.i)
        self.quark_icon.show()
        if not texto:
            texto = self.quark_utils.get_regla_adquisicion() # Un msj cheto 
        self.na.set_tooltip(self.quark_icon, texto)

    #--------------------------------------------------------------------------
    def notify(self, objeto, event):
        if (event == 'plugin-registered') and (objeto.name == 'Notification Area'):
            self.inicializar_interfaces() # Enlaza el notification area
            pass
        if (event == 'plugin-unregistered') and (objeto.name == 'Notification Area'):
            self.destruir_interfaces()
        if self.na and (event == 'planet-selected'):
            self.natt = ''
            self.quark_set_icon(self.quark_utils.PRIORIDAD_AVISO_NINGUNO,
                                self.quark_utils.get_regla_adquisicion()) # Un msj cheto 
            pid = objeto.get_id()
            for planeta in self.pl:
                if planeta.get_id() == pid:
                    self.na_report_generate(objeto)
            for planeta in self.pl_otros: # Planetas orbitados sin duenio
                if planeta.get_id() == pid:
                    self.na_report_generate(objeto)
        if self.na and (event == 'ship-selected'):
            self.na.remove_notification(self.quark_icon)

    #--------------------------------------------------------------------------            
    def filter_load_data(self):
        # Cargo el filtro con un arreglo que tiene los tipos de filtro.
        #self.cmb_filter.set_popdown_strings(self.quark_utils.filter_list)
        ## FIXME : USO DEL FILTER
        pass

    #--------------------------------------------------------------------------    
    def filter_init_selection(self):
        """ Seteo el filtro por defecto, cargo la lista con los planetas
        correspondientes y llamo al inicializador de la lista de planetas."""
        ## filter = self.get_filter(self.cmb_filter.entry.get_text())
        ## FIXME : USO DEL FILTER
        filter = None
        self.planets_load_list(filter)
        self.planets_init_selection()
        
    #--------------------------------------------------------------------------
    def get_filter(self, texto):
        ##FIXME : Falta devolver el filtro correcto.
        return self.FILTER_NONE

    #--------------------------------------------------------------------------        
    def planets_load_list(self, filter):
        """Carga la lista de planetas de acuerdo al filtro."""
        ##FIXME : Falta darle bola al filtro
        self.store_planets.clear()
        for p in self.pl:
            self.store_planets.append([p.get_id(), p.get_name()])
                
    #--------------------------------------------------------------------------
    def planets_init_selection(self):
        """ Elige el planeta seleccionado en la interface del gwp en la lista.
        Esto desencadena el evento de *planeta seleccionado* que carga los
        datos de este planeta en la interface del plugin."""
        ggs = gwp.get_game_state()
        p = ggs.get_selected_planet()
        iter_found = [] # debe ser una lista para que se devuelva en los argumentos (puntero)
        if p and p.is_mine():
            self.store_planets.foreach(self.find_planet_in_list, (p.get_id(), iter_found))
            # selecciona el planeta encontrado
            self.treeselection_planets.select_iter(iter_found[0])
        else:
            self.treeselection_planets.select_path((0,)) # El primero

    #--------------------------------------------------------------------------
    def find_planet_in_list(self, i_model, i_path, i_iter, (id_selected, iter_found)):
        """Busca el planeta seleccionado en la lista."""
        # FIXME : Cuando funcione el filtro esta busqueda hay que hacerla distinto.
        if i_model.get_value(i_iter, 0) == id_selected:
            iter_found.append(i_iter)
            # devuelve true para senialar que se encontro el planeta
            return True
        else:
            # Se debe seguir iterando
            return False
        
    #--------------------------------------------------------------------------    
    def filter_selected(self, dato, data=None):
        pass
    
    #--------------------------------------------------------------------------        
    def quark_planet_selected(self, treeselection, data=None):
        """Manejador del evento que ocurre al seleccionar un planeta en la
        ventana del plugin."""
        (model, iter) = treeselection.get_selected()
        try:
            pid = self.store_planets.get_value(iter,0)
            p = gwp.planet_get_by_id(pid)
            s = gwp.Starchart()
            s.select_nearest_planet(p.get_x_coord(), p.get_y_coord())
            s.center_around(p)
            self.planet_load_data(pid)
            pass
        except TypeError:
            #print "Type Error al elegir planeta" 
            pass

    #--------------------------------------------------------------------------    
    def planet_load_data(self, id):
        """Carga los datos del planeta en la ventana."""
        p = gwp.planet_get_by_id(id)
        txt =  '<big><b>' + p.get_name()+ ' (' + str(p.get_id())+ ')'+'</b></big>'
        self.lbl_planet_name.set_markup(txt)
        # Colonos
        self.lbl_colonists.set_text(str(p.get_colonists()))
        txt = str(p.get_happiness_colonists()) + '% (' + str(p.get_happiness_col_change()) +')'
        self.lbl_colonists_happ.set_text(txt)
        self.inc_colonists_tax.set_value(p.get_tax_colonists())
       # Nativos
        self.lbl_natives.set_text(str(p.get_natives()))
        txt = str(p.get_happiness_natives()) + '% (' + str(p.get_happiness_nat_change()) +')'
        self.lbl_natives_happ.set_text(txt)
        self.lbl_natives_type.set_text(p.get_natives_race_chars())
        self.lbl_natives_spi.set_text(p.get_natives_spi_chars())
        self.inc_natives_tax.set_value(p.get_tax_natives())
       # Planeta
        self.inc_fab.set_value(p.get_factories())
        self.inc_min.set_value(p.get_mines())
        self.inc_def.set_value(p.get_defense_posts())
        self.lbl_MC.set_text(str(p.get_megacredits()))
        self.lbl_supplies.set_text(str(p.get_supplies()))
        self.lbl_income.set_text(str(p.get_tax_collected_colonists()+p.get_tax_collected_natives()))
        self.lbl_fab_max.set_text(str(p.calculate_allowed_factories()))
        self.lbl_min_max.set_text(str(p.calculate_allowed_mines()))
        self.lbl_def_max.set_text(str(p.calculate_allowed_defenses()))
        if p.has_starbase():
            self.lbl_base.set_text(_("BASE"))
        else:
            self.lbl_base.set_text('')
        # Lista Minerales
        self.store_minerals.clear()
        factor_minado = p.get_mining_rate()/100
       
        extraccion = str(p.neutronium_extraction_rate())
        densidad = str(p.get_dens_neutronium()*factor_minado)
        fila = ["Neu", p.get_mined_neutronium(), p.get_ground_neutronium(), extraccion, densidad ]
        self.store_minerals.append(fila)

        extraccion = str(p.tritanium_extraction_rate())
        densidad = str(p.get_dens_tritanium()*factor_minado)
        fila = ["Tri", p.get_mined_tritanium(), p.get_ground_tritanium(), extraccion, densidad ]
        self.store_minerals.append(fila)

        extraccion = str(p.duranium_extraction_rate())
        densidad = str(p.get_dens_duranium()*factor_minado)        
        fila = ["Dur", p.get_mined_duranium(), p.get_ground_duranium(), extraccion, densidad ]
        self.store_minerals.append(fila)

        extraccion = str(p.molybdenum_extraction_rate())
        densidad = str(p.get_dens_molybdenum()*factor_minado)
        fila = ["Mol", p.get_mined_molybdenum(), p.get_ground_molybdenum(), extraccion, densidad ]
        self.store_minerals.append(fila)
        
        ## renderer.set_property('background','green')
        self.quark_report_generate(p)

    #--------------------------------------------------------------------------
    def main_cb(self, widget, data=None):
        """Arrancadora del plugin en modo ventana"""
        self.main()
        
    #--------------------------------------------------------------------------
    def main(self):
        """Muestra la ventana del plugin y comienza el loop de eventos"""
        self.planets_init_selection()
        self.window.show_all()
        gtk.main()

    #--------------------------------------------------------------------------
    def __initglade(self, glade_file_name):
        """Inicializa el arbol de widgets y conecta los eventos definidos en glade"""
        self.main_window = gtk.glade.XML(glade_file_name)
        self.main_window.signal_autoconnect(self)

    #--------------------------------------------------------------------------
    def delete_event(self, widget, event, data=None):
        """Hide window but not terminate plugin"""
        self.window.hide()
        return gtk.TRUE

    #--------------------------------------------------------------------------
    def register(self, pm):
        pm.set_hook_key(0, # No modifier
                        gtk.gdk.keyval_from_name(self.hotkey),
                        self.main)
        pm.set_hook_menu("_Quark",
                         self.main_cb)

    #--------------------------------------------------------------------------
    def unregister(self, pm):
        # Cleaning up
        #desconecto las senales de planeta seleccionado
        #for pid, signal in self.signals_id.iteritems():
        #    planeta = gwp.planet_get_by_id(pid)
        #    planeta.disconnect(signal)
            
        if self.na:
            self.na.remove_notification(self.quark_icon)


    
