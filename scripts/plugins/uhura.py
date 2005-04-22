import pygtk
import gtk

class Uhura(gwp.Plugin):

    name = "Uhura"
    version = "0.1"
    author_name = "Cristian Abalos"
    author_email = "abalosc@ciudad.com.ar"
    desc_short = _("Utility for reading messages from plugins")
    desc_long = ""
    license = "GPL"

    modelos = {}
    pl = []
    pl_otros = []

    FILTRO_TEXTO = 0
    ITEMS_ID = 0
    ITEMS_NOMBRE = 1
    ITEMS_TEXTO = 2

    #--------------------------------------------------------------------------
    def add_model(self, nombre, descripcion, modelo):
        entrada = {'nombre': nombre, 'descripcion': descripcion, 'modelo': modelo}
        self.modelos[ entrada['nombre'] ] = entrada
        #self.filtro.append_text(modelo['nombre'])
        self.filtro_model.append(modelo ['nombre'])
        
    #--------------------------------------------------------------------------
    def get_lista_modelos(self):
        return self.modelos.keys()

    #--------------------------------------------------------------------------
    def get_model(self, nombre):
        if self.modelos.has_key(nombre):
            return self.modelos [ nombre ]

    #--------------------------------------------------------------------------
    def set_model_active(self, nombre):
        modelo = self.get_model(nombre)
        
        #self.descripcion.set_text(modelo['descripcion'])
        #self.store_items = modelo ['modelo']

        #filtro_model = self.filtro.get_model()
        # No se si aparecen en el orden cargados (planetas primero)
        self.filtro.set_active(0)
        self.treeselection_items.select_path((0,)) # FALTA RECORDAR

    #--------------------------------------------------------------------------
    def load_items(self, filter_name):
        modelo = self.modelos [ filter_name ]
        self.store_items = modelo ['modelo']
    
    #--------------------------------------------------------------------------
    def load_mensaje(self, item):
        self.buf.set_text (item ['texto'])

    #--------------------------------------------------------------------------        
    def __create_gui(self):
        # Armo la ventana
        self.ventana = gtk.VBox()
        self.slot = gtk.VBox()
        self.cabecera = gtk.HBox()
        self.cuerpo = gtk.HBox()
        self.msg_mgr = gtk.HBox()
        #ventana.set_homogeneous(gtk.FALSE)

        # Widgets
        self.filtro_model = gtk.ListStore(str)
        self.filtro = gtk.ComboBox(self.filtro_model)
        cell = gtk.CellRendererText()
        self.filtro.pack_start(cell, True)
        #self.filtro.add_attribute(cell, 'text', self.FILTRO_TEXTO )
  
        self.descripcion = gtk.Label()

        self.list_scroll = gtk.ScrolledWindow()
        self.list_scroll.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        self.list_scroll.set_border_width(5)

        self.item_list = gtk.TreeView()
        self.treeselection_items = self.item_list.get_selection()
        self.item_list.set_headers_visible(gtk.FALSE)
        self.store_items = gtk.ListStore(int, str, str)
        renderer = gtk.CellRendererText()
        col_planets = gtk.TreeViewColumn(None, renderer, text=1)
        # Add columns to models
        # Planetas
        self.item_list.append_column(col_planets)
        self.item_list.set_model(self.store_items)
       
        self.list_scroll.add(self.item_list)

        self.text_scroll = gtk.ScrolledWindow()
        self.text_scroll.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        self.text_scroll.set_border_width(5)
        self.tv = gtk.TextView()
        self.buf = self.tv.get_buffer()
        self.text_scroll.add(self.tv)

        self.botonera = gtk.VButtonBox()

        # Contenedores
        self.cabecera.pack_start(self.filtro, gtk.FALSE, gtk.TRUE, 2)
        self.cabecera.pack_start(self.descripcion, gtk.TRUE, gtk.TRUE, 2)


        self.msg_mgr.pack_start(self.text_scroll, gtk.TRUE, gtk.TRUE, 2)
        self.msg_mgr.pack_start(self.botonera, gtk.FALSE, gtk.FALSE, 2)

        self.cuerpo.pack_start(self.list_scroll, gtk.TRUE, gtk.TRUE, 2)
        self.cuerpo.pack_start(self.msg_mgr, gtk.TRUE, gtk.TRUE, 2)

        self.ventana.pack_start(self.cabecera, gtk.FALSE, gtk.FALSE, 0)
        self.ventana.pack_start(self.cuerpo, gtk.TRUE, gtk.TRUE, 0)

        # Cargo datos
        #self.filtro.append_text("Planetas")
        #self.filtro.append_text("Quark_warnings")
        #self.filtro.append_text("Quark_ALERT")

        #self.descripcion.set_text("Aca iria una descripcion de lo que se lista")
        #self.buf.set_text("Hola cachito como te va?")

        self.pm = gwp.get_plugin_mgr()
        self.pm.add_plugin_slot("down", self.ventana)
        self.ventana.show_all()

        # Seteo el modelo planetas como default
        self.planets_add_model()
        
        # callbacks
        self.filtro.connect("changed", self.filter_selected, None)
        self.treeselection_items.connect("changed", self.item_selected, None)

    #--------------------------------------------------------------------------        
    def planets_add_model(self):
        """
        Carga la lista de planetas en un store y lo carga.
        """
        if not self.modelos.has_key("Planetas"): # solo evita uso de CPU
            all_pl = gwp.planet_get_list()
            for i in all_pl:
                p = all_pl[i]
                if p.is_mine():
                    self.pl.append(p)
                elif p.is_known() and p.is_unowned():
                    self.pl_otros.append(p)

            self.store_planetas = gtk.ListStore(int, str, str)
            for p in self.pl:
                self.store_planetas.append([p.get_id(), p.get_name(), "n/a"])
            self.add_model("Planetas", "Listado de planetas", self.store_planetas)
            self.set_model_active("Planetas")

    #--------------------------------------------------------------------------
    def filter_selected(self, filtro, data=None):
        filter_name = self.get_filter_active_name (filtro)
        self.load_filter_description (filter_name)
        self.load_items (filter_name)

    #--------------------------------------------------------------------------
    def get_filter_active_name(self):
        model = self.filtro.get_model()
        active = self.filtro.get_active()
        if active < 0:
            return None
        return model[active][ self.FILTRO_TEXTO ]
    
    #--------------------------------------------------------------------------    
    def load_filter_description (self, nombre):
        modelo = self.get_model(nombre)
        self.descripcion.set_text(modelo['descripcion'])
        
    #--------------------------------------------------------------------------
    def item_selected(self, treeselection, data=None):
        try:
            item = self.get_item_active()
            print "Eligio: " + item ['nombre']
            self.load_mensaje (item)
        except TypeError:
            #print "Type Error al elegir item" 
            pass
    #--------------------------------------------------------------------------
    def get_item_active(self):
        (model, iter) = treeselection.get_selected()
        try:
            ret = []
            ret['id'] = self.store_items.get_value(iter, self.ITEMS_ID)
            ret['nombre'] = self.store_items.get_value(iter, self.ITEMS_NOMBRE)
            ret['texto'] = self.store_items.get_value(iter, self.ITEMS_TEXTO)
            return ret
        except TypeError:
            #print "Type Error al pedir item" 
            pass
    #--------------------------------------------------------------------------    
    # Hide window but not terminate plugin
    def delete_event(self, widget, event, data=None):
	#self.window.hide()
        return gtk.TRUE

    # Another callback
    def destroy(self, widget, data=None):
        gtk.main_quit()

    # Constructor
    def __init__(self):
        gwp.Plugin.__init__(self)
        self.__create_gui()

    def main_cb(self, widget, data=None):
        self.main()
        
    def main(self):
        # All PyGTK applications must have a gtk.main(). Control ends here
        # and waits for an event to occur (like a key press or mouse event).
        #self.window.show_all()
        #gtk.main()
        pass

    def register(self, pm):
        pm.set_hook_key(0, # No modifier
                        gtk.gdk.keyval_from_name('u'),
                        self.main)
        pm.set_hook_menu("_Uhura",
                         self.main_cb)

    # Cleaning up
    def unregister(self, pm):

        vb = self.ventana.get_parent()
        print vb
        vp = vb.get_parent()
        vp.set_position(1000)
        print vp
        c1 = vp.get_child1()
        print c1
        c1.set_size_request(-1, 768)
        
        pm.remove_plugin_slot("down", self.ventana)
        pass

