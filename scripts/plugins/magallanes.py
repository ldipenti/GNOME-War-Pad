#!/usr/bin/env python

import sys
import pygtk
import gtk
import gtk.glade

sys.path.append(gwp.get_system_plugins_dir())
import vp_utils

class Magallanes(gwp.Plugin):

    name = "Magallanes"
    version = "0.2"
    author_name = "Cristian Abalos"
    author_email = "abalosc@ciudad.com.ar"
    desc_short = "Utilidad para visualizar las caracteristicas de las naves por raza"
    desc_long = ""
    license = "GPL"
    
    hulls = gwp.hullspec_get_list()
    th = gwp.get_truehull()
    es = gwp.engspec_get_list()
    bs = gwp.beamspec_get_list()
    ts = gwp.torpspec_get_list()
    
    torpedos_costo = {'MC':0,'tri':0,'dur':0,'mol':0}    
    motores_costo = {'MC':0,'tri':0,'dur':0,'mol':0}
    rayos_costo = {'MC':0,'tri':0,'dur':0,'mol':0}        
    hull_costo = {'MC':0, 'tri':0, 'dur':0, 'mol':0}
    
    # Por default quedan elegidos los tech 10
    def_motor = 9
    def_rayos = 10
    def_torps = 10
    
    def get_nro_raza(self, nombre):
        for i in range(1,12):
            if (nombre == gwp.get_race_name(i)):
                return i
            
    def get_tipo_motores(self, nombre):
        for i in range(1,10):
            if (nombre == self.es[i].get_name()):
                return i
    
    def get_tipo_rayos(self, nombre):
        for i in range(1,11):
            if (nombre == self.bs[i].get_name()):
                return i
    
    def get_tipo_torpedo(self, nombre):
        for i in range(1,11):
            if (nombre == self.ts[i].get_name()):
                return i

    def cargar_lista_razas(self):
        self.slist = []
        for i in range(1,12):
            #self.store_razas.append([i, gwp.get_race_name(i)])
            #self.lst_razas.set_item_string(i, gwp.get_race_name(i))
            self.slist.append(gwp.get_race_name(i))

        self.lst_razas.set_popdown_strings(self.slist)
            
        return gtk.TRUE 

    def cargar_lista_naves(self, nro_raza):
        if nro_raza:
            self.store_naves.clear()
            for i in self.th[nro_raza]:
                id = self.th[nro_raza][i]
                if id <> 0:
                    nombre = self.hulls[id].get_name()
                    self.store_naves.append([id, nombre])
                    
    def cargar_tipos_motores(self):
        self.slist = []
        for i in self.es:
            self.slist.append(self.es[i].get_name())

        self.cmb_tipos_motores.set_popdown_strings(self.slist)
            
        return gtk.TRUE 
        
    def cargar_tipos_rayos(self):
        self.slist = []
        for i in self.bs:
            self.slist.append(self.bs[i].get_name())

        self.cmb_tipos_rayos.set_popdown_strings(self.slist)
            
        return gtk.TRUE
        
    def cargar_tipos_torpedos(self):
        self.slist = []
        for i in self.ts:
            self.slist.append(self.ts[i].get_name())

        self.cmb_tipos_torpedos.set_popdown_strings(self.slist)
            
        return gtk.TRUE 

    def cargar_datos_nave(self, id):
        self.nave = self.hulls[id]
        self.lbl_nombre.set_markup('<big><b>'+ self.nave.get_name() + '</b></big>')
        self.lbl_tech_level.set_text(str(self.nave.get_tech_level()))
        self.lbl_func_esp.set_text(vp_utils.get_hull_function(id))
        self.lbl_masa.set_text(str(self.nave.get_mass()))
        self.lbl_trip.set_text(str(self.nave.get_crew()))
        self.lbl_rayos.set_text(str(self.nave.get_beam_weapons()))
        self.lbl_rayos_nro.set_text(str(self.nave.get_beam_weapons()))
        #tipo de arma secundario/auxiliar
        torps = self.nave.get_torp_launchers()
        bays = self.nave.get_fighter_bays()
        if (torps):
            aux = str(torps) + "T"
            self.lbl_aux_nro.set_text(str(torps))
        elif(bays):
            aux = str(bays) + "F"
            self.lbl_aux_nro.set_text("n/a")
        else:
            aux = "n/a"
            self.lbl_aux_nro.set_text("n/a")
        self.lbl_aux.set_text(aux)

        #self.lbl_cargo.set_markup("<span background='blue' foreground='white'>"+ str(self.nave.get_cargo()) +'</span>')
        self.lbl_cargo.set_text(str(self.nave.get_cargo()))
        #self.lbl_fuel.set_markup("<span background='blue' foreground='white'>"+ str(self.nave.get_fuel_tank()) +'</span>')
        self.lbl_fuel.set_text(str(self.nave.get_fuel_tank()))
        self.lbl_motores.set_text(str(self.nave.get_engines()))
        self.lbl_motores_nro.set_text(str(self.nave.get_engines()))
        self.hull_costo['MC'] = self.nave.get_cost()
        self.lbl_mc.set_text(str(self.nave.get_cost()))
        self.hull_costo['tri'] = self.nave.get_tritanium()
        self.lbl_tri.set_text(str(self.nave.get_tritanium()))
        self.hull_costo['dur'] = self.nave.get_duranium()
        self.lbl_dur.set_text(str(self.nave.get_duranium()))
        self.hull_costo['mol'] = self.nave.get_molybdenum()
        self.lbl_mol.set_text(str(self.nave.get_molybdenum()))
        #DATOS PARTES
        self.cargar_datos_motores()
        self.cargar_datos_rayos()
        self.cargar_datos_torpedos()
        self.calcular_totales()
        

    def cargar_imagen_nave(self, id):
        nave = self.hulls[id]
        file_number = nave.get_picture()
        self.image_nave.set_from_file(gwp.get_path_pic_hull(file_number))
        self.image_nave.show()

    def actualizar_posesion(self, id):
        """ Se fija en las listas de cada raza si posee o no la nave corresp a id
        y genera una lista de 11 con los valores a usar al setear los controles"""
        r = []
        for nro_raza in self.th:
            presente = 0
            for i in self.th[nro_raza]:
                if id == self.th[nro_raza][i]:
                    presente = 1
                    break
            idx = nro_raza - 1
            if presente:
                r.append(gtk.TRUE)
            else:
                r.append(gtk.FALSE)
        #seteo los botones
        self.setear_posesion(r)

    def setear_posesion(self, r):
        self.btn_raza_1.set_sensitive(r[0])
        self.btn_raza_2.set_sensitive(r[1])
        self.btn_raza_3.set_sensitive(r[2])
        self.btn_raza_4.set_sensitive(r[3])
        self.btn_raza_5.set_sensitive(r[4])
        self.btn_raza_6.set_sensitive(r[5])
        self.btn_raza_7.set_sensitive(r[6])
        self.btn_raza_8.set_sensitive(r[7])
        self.btn_raza_9.set_sensitive(r[8])
        self.btn_raza_10.set_sensitive(r[9])
        self.btn_raza_11.set_sensitive(r[10])

    def inicializar_seleccion_naves(self):
        self.treeselection_naves.select_path((0,))

    def inicializar_seleccion_razas(self):
        nro_raza = self.get_nro_raza(self.lst_razas.entry.get_text())
        self.cargar_lista_naves(nro_raza)
        self.inicializar_seleccion_naves()
        pass
    
    def inicializar_seleccion_partes(self):
        self.cmb_tipos_motores.entry.set_text(self.es[self.def_motor].get_name())
        self.cmb_tipos_rayos.entry.set_text(self.bs[self.def_rayos].get_name())
        self.cmb_tipos_torpedos.entry.set_text(self.ts[self.def_torps].get_name())
        pass
        
    def eligio_raza(self, dato, data=None):
        nro_raza = self.get_nro_raza(self.lst_razas.entry.get_text())
        self.cargar_lista_naves(nro_raza)
        self.inicializar_seleccion_naves()
    
    def eligio_nave(self, treeselection, data=None):
        (model, iter) = treeselection.get_selected()
        try:
            id = self.store_naves.get_value(iter,0)
            self.cargar_imagen_nave(id)
            self.cargar_datos_nave(id)
            self.actualizar_posesion(id)
            pass
        except TypeError:
            #print "Type Error al elegir nave" 
            pass
            
    def eligio_motores(self, dato, data=None):
        if (self.cmb_tipos_motores.entry.get_text()):
            self.cargar_datos_motores()
            self.calcular_totales()
    
    def cargar_datos_motores(self):
        tipo = self.get_tipo_motores(self.cmb_tipos_motores.entry.get_text())
        cant = self.nave.get_engines()
        self.motores_costo['MC'] = cant * self.es[tipo].get_cost()
        self.lbl_MC_motor.set_text(str(self.motores_costo['MC']))
        self.motores_costo['tri'] = cant * self.es[tipo].get_tritanium()
        self.lbl_tri_motor.set_text(str(self.motores_costo['tri']))
        self.motores_costo['dur'] = cant * self.es[tipo].get_duranium()
        self.lbl_dur_motor.set_text(str(self.motores_costo['dur']))
        self.motores_costo['mol'] = cant * self.es[tipo].get_molybdenum()
        self.lbl_mol_motor.set_text(str(self.motores_costo['mol']))
        
    def eligio_rayos(self, dato, data=None):
        if (self.cmb_tipos_rayos.entry.get_text()):
            self.cargar_datos_rayos()
            self.calcular_totales()
        
    def cargar_datos_rayos(self):
        tipo = self.get_tipo_rayos(self.cmb_tipos_rayos.entry.get_text())
        cant = self.nave.get_beam_weapons()
        self.rayos_costo['MC'] = cant * self.bs[tipo].get_cost()
        self.lbl_MC_rayos.set_text(str(self.rayos_costo['MC']))
        self.rayos_costo['tri'] = cant * self.bs[tipo].get_tritanium()
        self.lbl_tri_rayos.set_text(str(self.rayos_costo['tri']))
        self.rayos_costo['dur'] = cant * self.bs[tipo].get_duranium()
        self.lbl_dur_rayos.set_text(str(self.rayos_costo['dur']))
        self.rayos_costo['mol'] = cant * self.bs[tipo].get_molybdenum()
        self.lbl_mol_rayos.set_text(str(self.rayos_costo['mol']))
        
    def eligio_torpedos(self, dato, data=None):
        if (self.cmb_tipos_torpedos.entry.get_text()):
            self.cargar_datos_torpedos()
            self.calcular_totales()

    def cargar_datos_torpedos(self):
        cant = self.nave.get_torp_launchers()
        if cant:
            tipo = self.get_tipo_torpedo(self.cmb_tipos_torpedos.entry.get_text())
            
            self.torpedos_costo['MC'] = cant * self.ts[tipo].get_cost()
            self.lbl_MC_torps.set_text(str(self.torpedos_costo['MC']))
            self.torpedos_costo['tri'] = cant * self.ts[tipo].get_tritanium()
            self.lbl_tri_torps.set_text(str(self.torpedos_costo['tri']))
            self.torpedos_costo['dur'] = cant * self.ts[tipo].get_duranium()
            self.lbl_dur_torps.set_text(str(self.torpedos_costo['dur']))
            self.torpedos_costo['mol'] = cant * self.ts[tipo].get_molybdenum()
            self.lbl_mol_torps.set_text(str(self.torpedos_costo['mol']))
        else:
            self.lbl_MC_torps.set_text(' ')
            self.lbl_tri_torps.set_text(' ')
            self.lbl_dur_torps.set_text(' ')
            self.lbl_mol_torps.set_text(' ')
        
    def calcular_totales(self):
        self.tot_MC = self.hull_costo['MC'] +  self.motores_costo['MC'] + \
        self.rayos_costo['MC'] + self.torpedos_costo['MC']
        self.lbl_MC_total.set_text(str(self.tot_MC))
        
        self.tot_tri = self.hull_costo['tri'] +  self.motores_costo['tri'] + \
        self.rayos_costo['tri'] + self.torpedos_costo['tri']
        self.lbl_tri_total.set_text(str(self.tot_tri))
        
        self.tot_dur = self.hull_costo['dur'] +  self.motores_costo['dur'] + \
        self.rayos_costo['dur'] + self.torpedos_costo['dur']
        self.lbl_dur_total.set_text(str(self.tot_dur))
        
        self.tot_mol = self.hull_costo['mol'] +  self.motores_costo['mol'] + \
        self.rayos_costo['mol'] + self.torpedos_costo['mol']
        self.lbl_mol_total.set_text(str(self.tot_mol))
    
    def agregar_nave(self, button, data=None):
        # Store comparacion #id @raza @Nombre nave #masa#trip @XR@TP/F #cargo#fuel@mot
        # #MC #tri#dur#mol
        (model, iter) = self.treeselection_naves.get_selected()
        id = self.store_naves.get_value(iter,0)
        raza = self.lst_razas.entry.get_text()
        nombre = self.nave.get_name()
        masa = self.nave.get_mass()
        trip = self.nave.get_crew()
        rayos = str(self.nave.get_beam_weapons())
        torps = self.lbl_aux.get_text()
        cargo  = self.nave.get_cargo()
        fuel = self.nave.get_fuel_tank()
        motores = self.nave.get_engines()
        MC = self.nave.get_cost()
        tri = self.nave.get_tritanium()
        dur = self.nave.get_duranium()
        mol = self.nave.get_molybdenum()
        
        self.store_comparacion.append([id, raza, nombre, masa, trip, rayos, torps, cargo, fuel, motores,MC, tri,dur,mol])
         
    def agregar_nave_con_partes(self, button, data=None):
        # Store comparacion #id @raza @Nombre nave #masa#trip @XR@TP/F #cargo#fuel@mot
        # #MC #tri#dur#mol
        (model, iter) = self.treeselection_naves.get_selected()
        id = self.store_naves.get_value(iter,0)
        raza = self.lst_razas.entry.get_text()
        nombre = self.nave.get_name()
        masa = self.nave.get_mass() # se podria calcular una masa que incluya las partes
        trip = self.nave.get_crew()
        tech = str(self.get_tipo_rayos(self.cmb_tipos_rayos.entry.get_text()))
        rayos = str(self.nave.get_beam_weapons()) + ' (' + tech +')'
        if self.nave.get_torp_launchers():
            tech = str(self.get_tipo_torpedo(self.cmb_tipos_torpedos.entry.get_text()))
            torps = self.lbl_aux.get_text() + ' (' + tech +')'
        else:
            torps = self.lbl_aux.get_text()
        cargo  = self.nave.get_cargo()
        fuel = self.nave.get_fuel_tank()
        tech = str(self.get_tipo_motores(self.cmb_tipos_motores.entry.get_text()))
        motores = str(self.nave.get_engines()) + ' ('+ tech +')'
        MC = self.tot_MC
        tri = self.tot_tri
        dur = self.tot_dur
        mol = self.tot_mol
        
        self.store_comparacion.append([id, raza, nombre, masa, trip, rayos, torps, cargo, fuel, motores,MC, tri,dur,mol])

         
    def quitar_nave(self, button, data=None):
        (model, iter) = self.treeselection_comparacion.get_selected()
        if iter:
            if self.store_comparacion.iter_is_valid(iter):
                self.store_comparacion.remove(iter)
    

    # Hide window but not terminate plugin
    def delete_event(self, widget, event, data=None):
	self.window.hide()
        return gtk.TRUE

    # Another callback
    def destroy(self, widget, data=None):
        gtk.main_quit()

    # Constructor
    def __init__(self):
        self.ruta = gwp.get_system_plugins_dir()
        self.fname = self.ruta + '/magallanes.glade'
        self.main_window = gtk.glade.XML(self.fname)
        self.main_window.signal_autoconnect(self)
        self.__enlazar_controles()
        self.__create_gui()

    def __enlazar_controles(self):
        self.image_nave = self.main_window.get_widget('image_nave')
        self.lst_razas =  self.main_window.get_widget('cmb_razas')
        self.cmb_tipos_motores =  self.main_window.get_widget('cmb_tipos_motores')
        self.cmb_tipos_rayos =  self.main_window.get_widget('cmb_tipos_rayos')
        self.cmb_tipos_torpedos =  self.main_window.get_widget('cmb_tipos_torpedos')
        self.lst_naves =  self.main_window.get_widget('lst_naves')
        self.lst_comparacion = self.main_window.get_widget('lst_comparacion')
        #labels una nave
        self.lbl_nombre =  self.main_window.get_widget('lbl_nombre')
        self.lbl_tech_level =  self.main_window.get_widget('lbl_tech_level')
        self.lbl_func_esp =  self.main_window.get_widget('lbl_func_esp')
        self.lbl_masa =  self.main_window.get_widget('lbl_masa')
        self.lbl_trip =  self.main_window.get_widget('lbl_trip')
        self.lbl_rayos =  self.main_window.get_widget('lbl_rayos')
        self.lbl_rayos_nro =  self.main_window.get_widget('lbl_rayos_nro')
        self.lbl_aux =  self.main_window.get_widget('lbl_aux')
        self.lbl_aux_nro =  self.main_window.get_widget('lbl_aux_nro')
        self.lbl_cargo =  self.main_window.get_widget('lbl_cargo')
        self.lbl_fuel =  self.main_window.get_widget('lbl_fuel')
        self.lbl_motores =  self.main_window.get_widget('lbl_motores')
        self.lbl_motores_nro =  self.main_window.get_widget('lbl_motores_nro')
        self.lbl_mc =  self.main_window.get_widget('lbl_mc')
        self.lbl_tri =  self.main_window.get_widget('lbl_tri')
        self.lbl_dur =  self.main_window.get_widget('lbl_dur')
        self.lbl_mol =  self.main_window.get_widget('lbl_mol')
        #labels partes
        self.lbl_con_motor =  self.main_window.get_widget('lbl_con_motor')
        self.lbl_con_rayos =  self.main_window.get_widget('lbl_con_rayos')
        self.lbl_con_torps =  self.main_window.get_widget('lbl_con_torps')
        self.lbl_MC_motor =  self.main_window.get_widget('lbl_MC_motor')
        self.lbl_MC_rayos =  self.main_window.get_widget('lbl_MC_rayos')
        self.lbl_MC_torps =  self.main_window.get_widget('lbl_MC_torps')
        self.lbl_tri_motor =  self.main_window.get_widget('lbl_tri_motor')
        self.lbl_tri_rayos =  self.main_window.get_widget('lbl_tri_rayos')
        self.lbl_tri_torps =  self.main_window.get_widget('lbl_tri_torps')
        self.lbl_dur_motor =  self.main_window.get_widget('lbl_dur_motor')
        self.lbl_dur_rayos =  self.main_window.get_widget('lbl_dur_rayos')
        self.lbl_dur_torps =  self.main_window.get_widget('lbl_dur_torps')
        self.lbl_mol_motor =  self.main_window.get_widget('lbl_mol_motor')
        self.lbl_mol_rayos =  self.main_window.get_widget('lbl_mol_rayos')
        self.lbl_mol_torps =  self.main_window.get_widget('lbl_mol_torps')
        #totales
        self.lbl_MC_total =  self.main_window.get_widget('lbl_MC_total')
        self.lbl_tri_total =  self.main_window.get_widget('lbl_tri_total')
        self.lbl_dur_total =  self.main_window.get_widget('lbl_dur_total')
        self.lbl_mol_total =  self.main_window.get_widget('lbl_mol_total')
        
        #botones +/- lista comparacion
        self.btn_nave =  self.main_window.get_widget('btn_nave')
        self.btn_nave_con_partes =  self.main_window.get_widget('btn_nave_con_partes')
        self.btn_quitar =  self.main_window.get_widget('btn_quitar')
        #botones de posesion/raza
        self.btn_raza_1 = self.main_window.get_widget('btn_raza_1')
        self.btn_raza_2 = self.main_window.get_widget('btn_raza_2')
        self.btn_raza_3 = self.main_window.get_widget('btn_raza_3')
        self.btn_raza_4 = self.main_window.get_widget('btn_raza_4')
        self.btn_raza_5 = self.main_window.get_widget('btn_raza_5')
        self.btn_raza_6 = self.main_window.get_widget('btn_raza_6')
        self.btn_raza_7 = self.main_window.get_widget('btn_raza_7')
        self.btn_raza_8 = self.main_window.get_widget('btn_raza_8')
        self.btn_raza_9 = self.main_window.get_widget('btn_raza_9')
        self.btn_raza_10 = self.main_window.get_widget('btn_raza_10')
        self.btn_raza_11 = self.main_window.get_widget('btn_raza_11')

    def __create_gui(self):

	self.window = self.main_window.get_widget('window1')
        # Para el manejo de la selecion en los treeviews
        self.treeselection_naves = self.lst_naves.get_selection()
        self.treeselection_comparacion = self.lst_comparacion.get_selection()

        #ComboBoxEntry

        #self.store_razas = gtk.ListStore(int, str)
        #print dir(self.lst_razas)
        #self.lst_razas.ComboBox.set_model(self.store_razas)
        #self.lst_razas.set_text_column(1)
       
        # treeview setup
        self.store_naves = gtk.ListStore(int, str)
        # Store comparacion #id @raza @Nombre nave #masa#trip @XR@TP/F #cargo#fuel@mot
        # #MC #tri#dur#mol
        self.store_comparacion = gtk.ListStore(int, str, str, int, int, str, str, int, int, str,\
        int, int, int, int)
        renderer = gtk.CellRendererText()
        
        # Columns Lista Naves
        col_naves = gtk.TreeViewColumn('Naves', renderer, text=1)
        # Columns Comparacion
        col_raza = gtk.TreeViewColumn('Raza', renderer, text=1)
        col_hull = gtk.TreeViewColumn('Hull', renderer, text=2)
        col_masa = gtk.TreeViewColumn('Masa', renderer, text=3)
        col_trip = gtk.TreeViewColumn('Trip', renderer, text=4)
        col_rayos = gtk.TreeViewColumn('RY (tech)', renderer, text=5)
        col_torps = gtk.TreeViewColumn('T/F (tech)', renderer, text=6)
        col_cargo = gtk.TreeViewColumn('Cargo', renderer, text=7)
        col_fuel = gtk.TreeViewColumn('Fuel', renderer, text=8)
        col_motor = gtk.TreeViewColumn('Mot (wp)', renderer, text=9)
        col_MC = gtk.TreeViewColumn('MC', renderer, text=10)
        col_tri = gtk.TreeViewColumn('Tri', renderer, text=11)
        col_dur = gtk.TreeViewColumn('Dur', renderer, text=12)
        col_mol = gtk.TreeViewColumn('Mol', renderer, text=13)
        # Add columns to models
        ## Naves
        self.lst_naves.append_column(col_naves)
        self.lst_naves.set_model(self.store_naves)
        ## Comparacion
        self.lst_comparacion.append_column(col_raza)
        self.lst_comparacion.append_column(col_hull)
        self.lst_comparacion.append_column(col_masa)
        self.lst_comparacion.append_column(col_trip)
        self.lst_comparacion.append_column(col_rayos)
        self.lst_comparacion.append_column(col_torps)
        self.lst_comparacion.append_column(col_cargo)
        self.lst_comparacion.append_column(col_fuel)
        self.lst_comparacion.append_column(col_motor)
        self.lst_comparacion.append_column(col_MC)
        self.lst_comparacion.append_column(col_tri)
        self.lst_comparacion.append_column(col_dur)
        self.lst_comparacion.append_column(col_mol)
        self.lst_comparacion.set_model(self.store_comparacion)
        # Agregar Razas
        self.cargar_lista_razas()
        self.cargar_tipos_motores()
        self.cargar_tipos_rayos()
        self.cargar_tipos_torpedos()
        self.inicializar_seleccion_partes()
        
        # callbacks
        self.lst_razas.entry.connect("changed", self.eligio_raza, None)
        self.cmb_tipos_motores.entry.connect("changed", self.eligio_motores, None)
        self.cmb_tipos_rayos.entry.connect("changed", self.eligio_rayos, None)
        self.cmb_tipos_torpedos.entry.connect("changed", self.eligio_torpedos, None)
        self.treeselection_naves.connect("changed", self.eligio_nave, None)
        self.btn_nave.connect("clicked", self.agregar_nave, None)
        self.btn_nave_con_partes.connect("clicked", self.agregar_nave_con_partes, None)
        self.btn_quitar.connect("clicked", self.quitar_nave, None)
        
        #Comienzo la cascada de inicializaciones
        self.inicializar_seleccion_razas()
    
    def main_cb(self, widget, data=None):
        self.main()
        
    def main(self):
        # All PyGTK applications must have a gtk.main(). Control ends here
        # and waits for an event to occur (like a key press or mouse event).
        self.window.show_all()
        gtk.main()

    def register(self, pm):
        pm.set_hook_key(0, # No modifier
                        gtk.gdk.keyval_from_name('m'),
                        self.main)
        pm.set_hook_menu("_Magallanes",
                         self.main_cb)

    # Cleaning up
    def unregister(self, pm):
        pass

