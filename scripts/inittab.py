# Make sure we use pygtk for gtk 2.0
import pygtk
pygtk.require("2.0")

# Import the rest of the needed modules
import os
import gtk
import gwp

#######
# Plugin manager class
#######
# To-Do:
# -----
# * Check for user' plugin directory
class PluginManager:
    __module__ = 'gwp'

    # Private attributes
    __key_hooks = {}
    __plugins_registered = []
    __plugins_available = []
    
    def __init__(self):
        plugins_dir = gwp.plugins_get_dir()
        for plugin in os.listdir(plugins_dir + '/'):
            execfile (plugins_dir + '/' + plugin)
        # Check the plugins and add them to the available plugins list
        for obj in dir():
            try:
                if (isinstance(eval(obj), gwp.Plugin)):
                    self.__plugins_available.append(obj)
            except AttributeError:
                # Ignore if 'obj' is not an instance
                pass

    def manage_event_key (self, event):
        if (event["type"] == gtk.gdk.KEY_PRESS):
            self.__key_hooks[event["string"]]()

    def set_hook_key (self, key, action):
        self.__key_hooks[key] = action

    def register_plugin (self, plugin):
        try:
            plugin.register(self)
        except NotImplementedError:
            pass
        else:
            self.__plugins_registered.append (plugin)
            
    def unregister_plugin (self, plugin):
        # Try removing the plugin from registered list
        try:
            self.__plugins_registered.remove(plugin)
        except ValueError:
            pass
        else:
            # Try calling plugin's unregister() method
            try:
                plugin.unregister(self)
            except NotImplementedError:
                pass

#######
# Plugin abstract class
#######
class Plugin:
    """
    Plugin class, all plugins will need to use this class to register
    its functions on the plugin manager.
    """
    __module__ = 'gwp'

    # Custom attributes
    plugin_name = ''
    plugin_version = 0
    plugin_author_name = ''
    plugin_author_email = ''
    plugin_desc_short = ''
    plugin_desc_long = ''
    plugin_license = ''

    # Constructor
    def __init__ (self, name, version, author_name,
                  author_email, desc_s, desc_l, license):
        self.plugin_name = name
        self.plugin_version = version
        self.plugin_author_name = author_name
        self.plugin_author_email = author_email
        self.plugin_desc_short = desc_s
        self.plugin_desc_long = desc_l
        self.plugin_license = license

    # Executed at registration time
    def register (self):
        raise NotImplementedError

    # Executed at elimination time
    def unregister (self):
        raise NotImplementedError

########
# 
########


##############
# Main code execute at load
##############
if __name__ == "__main__":
    # Register clases on 'gwp' module
    gwp.__dict__["PluginManager"] = PluginManager
    gwp.__dict__["Plugin"] = Plugin
    # Initialize a PluginManager and pass it to GameState in C
    gwp.set_plugin_mgr (gwp.PluginManager ())

