import pygtk
pygtk.require('2.0')
import gtk
import gobject

class PluginNavigator(gwp.Plugin):

    # Plugin Manager reference
    __pm = None

    # Show details?
    __details = False
    
    # Hide window but not terminate plugin
    def delete_event(self, widget, event, data=None):
        self.window.hide()
        return gtk.TRUE

    # Another callback
    def destroy(self, widget, data=None):
        gtk.main_quit()

    # Show details callback
    def toggle_show_details(self, data=None):
        if not self.__details:
            self.details_frame.show()
            self.__details = True
            self.details_btn.set_label("<< _Hide details")
        else:
            self.details_frame.hide()
            self.__details = False
            self.details_btn.set_label("_Show details >>")
    
    # Constructor
    def __init__(self):
        gwp.Plugin.__init__(self,
                            "Plugin Navigator", "0.1",
                            "Lucas Di Pentima", "lucas@lunix.com.ar",
                            "The plugin manager frontend.",
                            "", "GPL")
        self.__pm = gwp.get_plugin_mgr()
        self.__create_gui()

    def __create_details_table(self):
        table = gtk.Table (4, 2, gtk.FALSE)
        ## Attach labels
        # Plugin Name
        table.attach (gtk.Label("Name:"),
                      0,1, # right-left attach
                      0,1) # top-bottom attach
        table.attach (self.details_name_lbl,
                      1,2,
                      0,1)
        # Author Name
        table.attach (gtk.Label("Author:"),
                      0,1,
                      1,2)
        table.attach (self.details_author_lbl,
                      1,2,
                      1,2)
        # License
        table.attach (gtk.Label("License:"),
                      0,1,
                      2,3)
        table.attach (self.details_license_lbl,
                      1,2,
                      2,3)
        # Description
        table.attach (gtk.Label("Description:"),
                      0,1,
                      3,4)
        table.attach (self.details_desc_lbl,
                      1,2,
                      3,4)
        # Return the widget!
        return table

    # Builds the GUI
    def __create_gui(self):
        # create a new window
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_title('Plugin Navigator')
        self.window.set_default_size(500, 300)
    
        self.window.connect("delete_event", self.delete_event)
        self.window.connect("destroy", self.destroy)
    
        # Sets the border width of the window.
        self.window.set_border_width(1)
    
        # Widgets
        self.vbox = gtk.VBox()
        self.vbox.set_homogeneous(gtk.FALSE)
        self.list_scroll = gtk.ScrolledWindow()
        self.list_scroll.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        self.list = gtk.TreeView()
        self.details_btn = gtk.Button("_Show details >>")
        self.details_frame = gtk.Frame("Plugin details")
        self.details_frame.set_property("visible", self.__details)
        
        ## Details widgets
        self.details_name_lbl = gtk.Label("n/a")
        self.details_author_lbl = gtk.Label("n/a")
        self.details_license_lbl = gtk.Label("n/a")
        self.details_desc_lbl = gtk.Label("n/a")
        self.details_desc_lbl.set_line_wrap(gtk.TRUE)

        self.details_table = self.__create_details_table()
        # additions
        self.vbox.pack_start(self.list_scroll, gtk.TRUE, gtk.TRUE, 0)
        self.vbox.pack_start(self.details_btn, gtk.FALSE, gtk.TRUE, 0)
        self.vbox.pack_start(self.details_frame, gtk.FALSE, gtk.TRUE, 0)
        self.details_frame.add(self.details_table)
        self.list_scroll.add(self.list)
        self.window.add(self.vbox)
        # treeview setup
        self.store = gtk.ListStore(gobject.TYPE_BOOLEAN, str, str,
                                   gobject.TYPE_PYOBJECT)
        renderer = gtk.CellRendererText()
        check_render = gtk.CellRendererToggle()
        # Columns
        self.col_active = gtk.TreeViewColumn('Active', check_render)
        self.col_active.set_attributes(check_render, active=0)
        self.col_name = gtk.TreeViewColumn('Name', renderer, text=1)
        self.col_author = gtk.TreeViewColumn('Description', renderer, text=2)
        # Add columns to model
        self.list.append_column(self.col_active)
        self.list.append_column(self.col_name)
        self.list.append_column(self.col_author)
        self.list.set_model(self.store)
        # callbacks connections
        self.details_btn.connect("clicked", self.toggle_show_details)
        check_render.connect("toggled", self.toggle_active)
        self.list.connect("cursor-changed", self.update_details)

    # Reload list callback
    def reload(self, widget=None, data=None):
        self.store.clear()
        for plugin in self.__pm.get_plugins_available():
            self.store.append([plugin.registered, plugin.name,
                               plugin.desc_short, plugin])

    # Update details callback
    def update_details(self, data=None):
        model, iter = self.list.get_selection().get_selected()
        try:
            plugin = model.get_value(iter, 3)
        except TypeError:
            pass
        else:
            self.details_name_lbl.set_label(plugin.name + ' ' +
                                            str(plugin.version))
            self.details_author_lbl.set_label(plugin.author_name + ' <' +
                                              plugin.author_email + '>')
            self.details_license_lbl.set_label(plugin.license)
            self.details_desc_lbl.set_label(plugin.desc_long)

    # Activate/deactivate plugin callback
    def toggle_active(self, renderer, path):
        model, iter = self.list.get_selection().get_selected()
        try:
            plugin = model.get_value(iter, 3)
        except TypeError:
            pass
        else:
            # If plugin is active...
            if (renderer.get_active()):
                try:
                    self.__pm.unregister_plugin(plugin)
                except NotImplementedError:
                    # FIXME: show a dialog stating that the plugin
                    # is incomplete
                    pass
                else:
                    model.set(iter, 0, plugin.registered)
            # If plugin is inactive...
            else:
                try:
                    self.__pm.register_plugin(plugin)
                except NotImplementedError:
                    # FIXME: show a dialog stating that the plugin
                    # is incomplete
                    pass
                else:
                    model.set(iter, 0, plugin.registered)
            
    
    def __main(self):
        # All PyGTK applications must have a gtk.main(). Control ends here
        # and waits for an event to occur (like a key press or mouse event).
        self.reload()
        self.window.show_all()
        self.details_frame.set_property("visible", self.__details)
        gtk.main()

    def register(self, pm):
        pm.set_hook_key(gtk.gdk.CONTROL_MASK,
                        gtk.gdk.keyval_from_name('p'),
                        self.__main)


#####
# Register plugin on manager
#####
if __name__ == '__main__':
    pm = gwp.get_plugin_mgr()
    navigator = PluginNavigator()
    pm.register_plugin(navigator)
