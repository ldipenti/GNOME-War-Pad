#!/usr/bin/env python
ruta='/u/home/cristian/devel/quark/01'
import sys
##sys.path.append(gwp.get_system_plugins_dir())
sys.path.append(ruta)
##import vp_utils
import pygtk
import gtk
import gtk.glade

class Quark(gwp.Plugin):
    import quark_utils
    name = "Quark"
    version = "0.1"
    author_name = "Cristian Abalos"
    author_email = "abalosc@gmail.com"
    desc_short = "Inform deficiences in the resourses management"
    desc_long = ""
    license = "GPL"
    
    FILTER_NONE = 1
    
    # Cantidades que definen cuando un planeta es considerado minero y se levantan las 
    # estructuras al maximo. La unidad de medida es la densidad.
    MINERO_MIN_TRI = 30
    MINERO_MIN_DUR = 30
    MINERO_MIN_MOL = 30
    # Minimo de MC para considerar a un planeta recaudador de guita en vez de minero
    RECAUDADOR_MIN_MC = 500
    
    #--------------------------------------------------------------------------     
    def init_lists(self):
        self.pl = []
        all_pl = gwp.planet_get_list()
        for i in all_pl:
            p = all_pl[i]
            if p.is_mine():
                self.pl.append(p)

    #--------------------------------------------------------------------------    
    def filter_selected(self, dato, data=None):
        pass
    
    #--------------------------------------------------------------------------        
    def planet_selected(self, treeselection, data=None):
        (model, iter) = treeselection.get_selected()
        try:
            id = self.store_planets.get_value(iter,0)
            self.planet_load_data(id)
            pass
        except TypeError:
            #print "Type Error al elegir planeta" 
            pass

    #--------------------------------------------------------------------------    
    def planet_load_data(self, id):
        p = gwp.planet_get_by_id(id)
        txt =  '<big><b>' + p.get_name()+ ' (' + str(p.get_id())+ ')'+'</b></big>'
        self.lbl_planet_name.set_markup(txt)
        #Colonos
        self.lbl_colonists.set_text(str(p.get_colonists()))
        txt = str(p.get_happiness_colonists()) + '% (' + str(p.get_happiness_col_change()) +')'
        self.lbl_colonists_happ.set_text(txt)
        self.inc_colonists_tax.set_value(p.get_tax_colonists())
       #Nativos
        self.lbl_natives.set_text(str(p.get_natives()))
        txt = str(p.get_happiness_natives()) + '% (' + str(p.get_happiness_nat_change()) +')'
        self.lbl_natives_happ.set_text(txt)
        self.lbl_natives_type.set_text(p.get_natives_race_chars())
        self.lbl_natives_spi.set_text(p.get_natives_spi_chars())
        self.inc_natives_tax.set_value(p.get_tax_natives())
       #Planeta
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
            self.lbl_base.set_text("BASE")
        else:
            self.lbl_base.set_text('')
        # Lista Minerales
        self.store_minerals.clear()
        extraccion = str(p.neutronium_extraction_rate())# + "/0"
        fila = ["Neu", p.get_mined_neutronium(), p.get_ground_neutronium(), extraccion ]
        self.store_minerals.append(fila)
        extraccion = str(p.tritanium_extraction_rate())# + "/0"
        fila = ["Tri", p.get_mined_tritanium(), p.get_ground_tritanium(), extraccion ]
        self.store_minerals.append(fila)
        extraccion = str(p.duranium_extraction_rate())# + "/0"
        fila = ["Dur", p.get_mined_duranium(), p.get_ground_duranium(), extraccion ]
        self.store_minerals.append(fila)
        extraccion = str(p.molybdenum_extraction_rate())# + "/0"
        fila = ["Mol", p.get_mined_molybdenum(), p.get_ground_molybdenum(), extraccion ]
        self.store_minerals.append(fila)
        
        ##renderer.set_property('background','green')
        self.report_load(p)

    #--------------------------------------------------------------------------    
    def report_load(self, p):
        self.textbuffer = self.tv_notification.get_buffer()
        self.report_verify_happyness(p)
        #self.is_miner_planet(p)
        
        self.report_verify_colonists(p)
        
        
    #--------------------------------------------------------------------------
    def report_verify_happyness(self, p):
        """Verifica si van a pasar a estar desontentos o en guerra civil en caso de
        taxes con modificador negativo"""
        
        actual_income = p.get_tax_collected_natives()
        actual_tax = p.get_tax_natives()
        actual_change = p.get_happiness_nat_change()
        txt = ""
        if (actual_change < 0):
            actual_happ = p.get_happiness_natives()
            if (actual_happ + actual_change) < 31: # en 30 empieza la guerra civil
                txt = "Natives will be in CIVIL WAR the next turn\n\n"
            else:
                if (actual_happ + actual_change) < 71: # en 70 los nativos dejan de pagar (Descontentos)
                    txt = "Natives will be UNHAPPY the next turn\n\n"
        self.textbuffer.set_text(txt)
    
    #--------------------------------------------------------------------------
    def report_verify_colonists(self, p):
        """ Verifica si existen suficiente cantidad de colonos para:
       * cobrarles el maximo posible a los nativos 
       * sacar el max posible de supplies si hay Bovinoids
       * Max de Fab y minas si no hay nativos que paguen bien # FALTA #
       """
        txt = ""
        if p.get_natives(): # SI no hay nativos no tiene sentido esto
            if (p.get_natives_race() <> 5): #Amorphous
                tax, max = self.calculate_max_income_from_natives(p)
                if max > p.get_tax_collected_natives():
                    col_faltan = max - p.get_tax_collected_natives()
                    if p.get_natives_race() == 6: #Insectoids
                        col_faltan = col_faltan / 2
                    if p.get_owner() == 1: # Feds
                        #FIXME deberia tomar el valor de la configuracion del host (Lucas 1ro)
                        col_faltan = col_faltan / 2
                    txt = "Need "+ str(col_faltan) +"clans of colonists!\nYou can to collect " + str(max) + " MC "
                    dif = str(max - p.get_tax_collected_natives())
                    txt = txt  + "(" + dif +" more)\n"
                
                # Falta ver si pagan poco y conviene construir fab y minas

                # Supplies Bovinoids
                if (p.get_natives_race() == 2): #Bovinoid
                    sup = p.get_natives() / 100
                    if p.get_colonists() < sup:
                        if txt:
                            txt = txt + "You can to obtain " + str(sup) + " supplies "
                            dif = str(sup - p.get_colonists())
                            txt = txt + "(" + dif +" more)\n"
                        else:
                            txt = "Need colonists!\n" + txt
        
        chequear_construcciones = 1
        if chequear_construcciones:
            #FALTA controlar si las fab y minas estan en valores optimos.
            pass
        #Se imprime!
        if txt:
            self.textbuffer.set_text(txt + "\n")

    #--------------------------------------------------------------------------
    def calculate_max_income_from_natives(self, p):
        """ Determino el maximo que se puede cobrar (con una copia del planeta)
        devuelve (impuesto, cantidad_MC) """
        future_p = p.copy()
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
                if limit >= income:
                    tax -= 1
                future_p.set_tax_natives(tax)
                income = future_p.get_tax_collected_natives()
                return tax, income

    #--------------------------------------------------------------------------
    def is_miner_planet(self, p):
        return 0

    #--------------------------------------------------------------------------
    def calculate_happ_state_natives(self, p):
        actual_income = p.get_tax_collected_natives()
        actual_tax = p.get_tax_natives()
        actual_change = p.get_happiness_nat_change()
        if (actual_change < 0):
            actual_happ = p.get_happiness_natives()
            if (actual_happ + actual_change) < 31: # en 30 empieza la guerra civil
                return self.quark_utils.HAPP_STATE_UNHAPPY
            else:
                if (actual_happ + actual_change) < 71: # en 70 dejan de pagar (Descontentos)
                return self.quark_utils.HAPP_STATE_CIVIL_WAR
        return self.quark_utils.HAPP_STATE_NONE

            
    ###########################################################################        
    ################################## GUI ####################################
    ###########################################################################

    # Constructor
    #--------------------------------------------------------------------------
    def __init__(self):
        self.ruta = ruta ##gwp.get_system_plugins_dir()
        self.fname = self.ruta + '/quark.glade'
        self.__initglade(self.fname)
        self.quark_utils.widgets_make_link(self)
        self.init_lists()
        self.__create_gui()    
    
    #--------------------------------------------------------------------------
    def __create_gui(self):
        # Para el manejo de la selecion en los treeviews
        self.treeselection_planets = self.lst_planets.get_selection()
        # treeview setup
        self.store_planets = gtk.ListStore(int, str)
        self.store_minerals = gtk.ListStore(str, int, int, str)
        renderer = gtk.CellRendererText()
        
        # Columns Lista Planetas
        col_planets = gtk.TreeViewColumn('Planets', renderer, text=1)
        col_minerals = gtk.TreeViewColumn('Mineral', renderer, text=0)
        col_surf = gtk.TreeViewColumn('Surf', renderer, text=1)
        col_core = gtk.TreeViewColumn('Core', renderer, text=2)
        col_extr = gtk.TreeViewColumn('Extr', renderer, text=3)
        # Add columns to models
        # Planetas
        self.lst_planets.append_column(col_planets)
        self.lst_planets.set_model(self.store_planets)
        # Minerales
        self.lst_minerals.append_column(col_minerals)
        self.lst_minerals.append_column(col_surf)
        self.lst_minerals.append_column(col_core)
        self.lst_minerals.append_column(col_extr)
        self.lst_minerals.set_model(self.store_minerals)

        # callbacks
        self.cmb_filter.entry.connect("changed", self.filter_selected, None)
        self.treeselection_planets.connect("changed", self.planet_selected, None)
        ##self.btn_nave.connect("clicked", self.agregar_nave, None)
        #Comienzo la cascada de inicializaciones
        self.filter_load_data()
        self.filter_init_selection()

    #--------------------------------------------------------------------------            
    def filter_load_data(self):
        self.cmb_filter.set_popdown_strings(self.quark_utils.filter_list)

    #--------------------------------------------------------------------------    
    def filter_init_selection(self):
        filter = self.get_filter(self.cmb_filter.entry.get_text())
        self.planets_load_list(filter)
        self.planets_init_selection()
        
    #--------------------------------------------------------------------------
    def get_filter(self, texto):
        ##FIXME : Falta devolver el filtro correcto
        return self.FILTER_NONE

    #--------------------------------------------------------------------------        
    def planets_load_list(self, filter):
        ##FIXME : Falta darle bola al filtro
        self.store_planets.clear()
        for p in self.pl:
            self.store_planets.append([p.get_id(), p.get_name()])
                
    #--------------------------------------------------------------------------
    def planets_init_selection(self):
        self.treeselection_planets.select_path((0,))

    #--------------------------------------------------------------------------
    def main_cb(self, widget, data=None):
        self.main()
        
    #--------------------------------------------------------------------------
    def main(self):
        # All PyGTK applications must have a gtk.main(). Control ends here
        # and waits for an event to occur (like a key press or mouse event).
        #self.main_window.window1.show_all()
        gtk.main()

    ###########################################################################
    ########## Todas estas funciones podrian ir en la clase Plugin ############
    ###########################################################################
    #Inicializa el arbol de widgets y conecta los eventos definidos en glade
    def __initglade(self, glade_file_name):
        self.main_window = gtk.glade.XML(glade_file_name)
        self.main_window.signal_autoconnect(self)

    # Hide window but not terminate plugin
    def delete_event(self, widget, event, data=None):
        self.window.hide()
        return gtk.TRUE

    # Terminate App
    def destroy(self, widget, data=None):
        gtk.main_quit()

    # Terminate App
    def gtk_main_quit(self, *args):
        gtk.main_quit()
    
    #Toma el valor self.hotkey del plugin
    def register(self, pm):
        pm.set_hook_key(0, # No modifier
                        gtk.gdk.keyval_from_name(self.hotkey), # self.hotkey se define al pcipio junto con los datos del plugin
                        self.__main)

    # Cleaning up
    def unregister(self, pm):
        pass
##########################################################################

#####
# Load code
#####
if __name__ == '__main__':
    # para modo pruebas lo arranco directo
    quark = Quark()
    quark.main()
    
