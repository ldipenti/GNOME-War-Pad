# Make sure we use pygtk for gtk 2.0
import pygtk
pygtk.require("2.0")

# Import the rest of the needed modules
import gtk
import gwp

# Plugin manager class
class PluginManager:
    __module__ = 'gwp'

    # Private attributes
    __key_hooks = {}
    __plugins_registered = []
    __plugins_available = []
    
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


# Plugin abstract class
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

##############
# Main code execute at load
##############
if __name__ == "__main__":
    # Register clases on 'gwp' module
    gwp.__dict__["PluginManager"] = PluginManager
    gwp.__dict__["Plugin"] = Plugin
    # Initialize a PluginManager and pass it to GameState in C
    gwp.set_plugin_mgr (gwp.PluginManager ())

