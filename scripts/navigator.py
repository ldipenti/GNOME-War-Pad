import pygtk
pygtk.require('2.0')
import gtk
import gobject

class PluginNavigator(gwp.Plugin):

    # Plugin Manager reference
    __pm = None
    
    # Hide window but not terminate plugin
    def delete_event(self, widget, event, data=None):
        self.window.hide()
        return gtk.TRUE

    # Another callback
    def destroy(self, widget, data=None):
        gtk.main_quit()

    # Constructor
    def __init__(self):
        gwp.Plugin.__init__(self,
                            "Plugin Navigator", "0.1",
                            "Lucas Di Pentima", "lucas@lunix.com.ar",
                            "The plugin manager frontend.",
                            "", "GPL")
        self.__pm = gwp.get_plugin_mgr()
        self.__create_gui()

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
        self.reload_btn = gtk.Button("_Reload")
        # additions
        self.vbox.pack_start(self.list_scroll, gtk.TRUE, gtk.TRUE, 0)
        self.vbox.pack_start(self.reload_btn, gtk.FALSE, gtk.TRUE, 0)
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
        self.reload_btn.connect("clicked", self.reload, None)
        check_render.connect("toggled", self.toggle_active)

    # Reload list callback
    def reload(self, widget=None, data=None):
        self.store.clear()
        for plugin in self.__pm.get_plugins_available():
            self.store.append([plugin.registered, plugin.name,
                               plugin.desc_short, plugin])

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
        gtk.main()

    def register(self, pm):
        pm.set_hook_key('.', self.__main)


#####
# Register plugin on manager
#####
if __name__ == '__main__':
    pm = gwp.get_plugin_mgr()
    navigator = PluginNavigator()
    pm.register_plugin(navigator)
