import pygtk
pygtk.require('2.0')
import gtk
import re


class Finder(gwp.Plugin):

    def __multiple_replace(self, dict, text):

        """
        Replace in 'text' all occurences of any key in the given
        dictionary by its corresponding value.  Returns the new string.
        """
        for key,val in dict.items():
            text = re.sub(key,val,text)
        return text

    def __transform_eval(self, str):
        d = {
            '\\b[nN]\\b|\\bneu\\b' : 'ship.get_neutronium()',
            '\\b[tT]\\b|\\btri\\b' : 'ship.get_tritanium()',
            '\\b[mM]\\b|\\bmol\\b' : 'ship.get_molybdenum()',
            '\\b[dD]\\b|\\bdur\\b' : 'ship.get_duranium()',
            '\\b[wW]\\b' : 'ship.calculate_waypoint_distance()',
            '\\b[Oo]\\b|owner' : 'ship.get_owner()',
            'mine' : 'ship.is_mine()'
            }
        return self.__multiple_replace(d, str)

    # This is a callback function. The data arguments are ignored
    # in this example. More on callbacks below.
    def entry_key(self, widget, event, data=None):
        if (event.keyval == gtk.gdk.keyval_from_name('Return')):
            self.search_obj(self.btn)
      
    def search_obj(self,  widget, data=None):
        ships = gwp.ship_get_list()
        nr = self.search.get_text()
        query = self.__transform_eval(nr)
        self.store.clear()
        result = filter(lambda (k,ship): eval(query), ships.items())

        for (key,obj) in result:
            self.store.append([key, obj.get_name(), obj.get_neutronium()])

        
    def delete_event(self, widget, event, data=None):
        return gtk.FALSE

    # Another callback
    def destroy(self, widget, data=None):
        gtk.main_quit()

    # Constructor
    def __init__(self):
        gwp.Plugin.__init__(self,
                            "Ship Finder", "0.1",
                            "Lucas Di Pentima", "lucas@lunix.com.ar",
                            "A very simple plugin to search ships by several criteria",
                            "", "GPL")
        self.__create_gui()

    def __create_gui(self):
        # create a new window
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_title('Search Ship')
        self.window.set_default_size(300, 400)
    
        self.window.connect("delete_event", self.delete_event)
        self.window.connect("destroy", self.destroy)
    
        # Sets the border width of the window.
        self.window.set_border_width(1)
    
        # Widgets
        self.vbox = gtk.VBox()
        self.hbox = gtk.HBox()
        self.vbox.set_homogeneous(gtk.FALSE)
        self.search = gtk.Entry(30)
        self.list_scroll = gtk.ScrolledWindow()
        self.list_scroll.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_ALWAYS)
        self.list = gtk.TreeView()
        self.btn = gtk.Button('Search')
        # additions
        self.hbox.pack_start(self.search, gtk.TRUE, gtk.TRUE, 2)
        self.hbox.pack_start(self.btn, gtk.FALSE, gtk.FALSE, 2)
        self.vbox.pack_start(self.hbox, gtk.FALSE, gtk.FALSE, 0)
        self.vbox.pack_start(self.list_scroll, gtk.TRUE, gtk.TRUE, 0)
        self.list_scroll.add(self.list)
        self.window.add(self.vbox)
        # callbacks
        self.btn.connect("clicked", self.search_obj, None)
        self.search.connect("key_press_event", self.entry_key, None)
        # treeview setup
        self.store = gtk.ListStore(int, str, int)
        renderer = gtk.CellRendererText()
        # ID Column
        col_id = gtk.TreeViewColumn('#', renderer, text=0)
        col_id.set_sort_column_id(0)
        col_id.set_sort_indicator(gtk.TRUE)        
        # Name Column
        col_name = gtk.TreeViewColumn('Name', renderer, text=1)
        # Neu Column
        col_neu = gtk.TreeViewColumn('Neu', renderer, text=2)
        col_neu.set_sort_column_id(2)
        col_neu.set_sort_indicator(gtk.TRUE)
        # Add columns to model
        self.list.append_column(col_id)
        self.list.append_column(col_name)
        self.list.append_column(col_neu)
        self.list.set_model(self.store)

    def __main(self):
        # All PyGTK applications must have a gtk.main(). Control ends here
        # and waits for an event to occur (like a key press or mouse event).
        self.window.show_all()
        gtk.main()

    def register(self, pm):
        pm.set_hook_key('f', self.__main)


#####
# Load code
#####
if __name__ == '__main__':
    finder = Finder()
