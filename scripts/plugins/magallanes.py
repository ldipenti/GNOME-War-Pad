#!/usr/bin/env python

import pygtk
import gtk
import gtk.glade

class Magallanes(Plugin):

    name = "Magallanes"
    version = "0.1"
    author_name = "Cristian Abalos"
    author_email = "abalosc@ciudad.com.ar"
    desc_short = "Utilidad para visualizar las caracteristicas de las naves por raza"
    desc_long = ""
    license = "GPL"
    
    hulls = gwp.hullspec_get_list()
    th = gwp.get_truehull()
    
    def cargar_lista_razas(self):
        for i in range(1,12):
            self.store_razas.append([i, gwp.get_race_name(i)])
        return gtk.TRUE 

    def cargar_lista_naves(self, nro_raza):
        self.store_naves.clear()
        for i in self.th[nro_raza]:
            id = self.th[nro_raza][i]
            if id <> 0:
                nombre = self.hulls[id].get_name()
                self.store_naves.append([id, nombre])

    def cargar_datos_nave(self, id):
        nave = self.hulls[id]
        
        self.lbl_nombre.set_text(nave.get_name())
        self.lbl_tech_level.set_text(str(nave.get_tech_level()))
        self.lbl_func_esp.set_text("ninguna") # falta
        self.lbl_masa.set_text(str(nave.get_mass()))
        self.lbl_trip.set_text(str(nave.get_crew()))
        self.lbl_rayos.set_text(str(nave.get_beam_weapons()))
        #tipo de arma secundario/auxiliar
        torps = nave.get_torp_launchers()
        bays = nave.get_fighter_bays()
        if (torps):
            aux = str(torps) + "T"
        elif(bays):
            aux = str(bays) + "F"
        else:
            aux = "n/a"
        self.lbl_aux.set_text(aux)

        self.lbl_cargo.set_text(str(nave.get_cargo()))
        self.lbl_fuel.set_text(str(nave.get_fuel_tank()))
        self.lbl_motores.set_text(str(nave.get_engines()))
        self.lbl_mc.set_text(str(nave.get_cost()))
        self.lbl_tri.set_text(str(nave.get_tritanium()))
        self.lbl_dur.set_text(str(nave.get_duranium()))
        self.lbl_mol.set_text(str(nave.get_molybdenum()))

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
        self.treeselection_razas.select_path((0,))
    
    def eligio_raza(self, treeselection, data=None):
        (model, iter) = treeselection.get_selected()
        #paso nro de raza como param
        self.cargar_lista_naves(self.store_razas.get_value(iter, 0))
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
    

    # Hide window but not terminate plugin
    def delete_event(self, widget, event, data=None):
        self.window.hide()
        return gtk.TRUE

    # Constructor
    def __init__(self): #, fname):
        self.ruta = gwp.get_system_plugins_dir()
        self.fname = self.ruta + '/magallanes.glade'
        self.main_window = gtk.glade.XML(self.fname)
        self.main_window.signal_autoconnect(self)
        self.__enlazar_controles()
        self.__create_gui()

    def __enlazar_controles(self):
        self.window = self.main_window.get_widget('window')
        self.image_nave = self.main_window.get_widget('image_nave')
        self.lst_razas =  self.main_window.get_widget('lst_razas')
        self.lst_naves =  self.main_window.get_widget('lst_naves')
        #labels
        self.lbl_nombre =  self.main_window.get_widget('lbl_nombre')
        self.lbl_tech_level =  self.main_window.get_widget('lbl_tech_level')
        self.lbl_func_esp =  self.main_window.get_widget('lbl_func_esp')
        self.lbl_masa =  self.main_window.get_widget('lbl_masa')
        self.lbl_trip =  self.main_window.get_widget('lbl_trip')
        self.lbl_rayos =  self.main_window.get_widget('lbl_rayos')
        self.lbl_aux =  self.main_window.get_widget('lbl_aux')
        self.lbl_cargo =  self.main_window.get_widget('lbl_cargo')
        self.lbl_fuel =  self.main_window.get_widget('lbl_fuel')
        self.lbl_motores =  self.main_window.get_widget('lbl_motores')
        self.lbl_mc =  self.main_window.get_widget('lbl_mc')
        self.lbl_tri =  self.main_window.get_widget('lbl_tri')
        self.lbl_dur =  self.main_window.get_widget('lbl_dur')
        self.lbl_mol =  self.main_window.get_widget('lbl_mol')
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
        # Para el manejo de la selecion en los treeviews
        self.treeselection_razas = self.lst_razas.get_selection()
        self.treeselection_naves = self.lst_naves.get_selection()

        # callbacks
        self.treeselection_razas.connect("changed", self.eligio_raza, None)
        self.treeselection_naves.connect("changed", self.eligio_nave, None)
        # treeview setup
        self.store_razas = gtk.ListStore(int, str)
        self.store_naves = gtk.ListStore(int, str)
        renderer = gtk.CellRendererText()
        # Columns
        col_razas = gtk.TreeViewColumn('Razas', renderer, text=1)
        col_naves = gtk.TreeViewColumn('Naves', renderer, text=1)
        # Add columns to models
        self.lst_razas.append_column(col_razas)
        self.lst_naves.append_column(col_naves)
        self.lst_razas.set_model(self.store_razas)
        self.lst_naves.set_model(self.store_naves)
        self.cargar_lista_razas()
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

    
