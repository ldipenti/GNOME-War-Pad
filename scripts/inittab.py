# Make sure we use pygtk for gtk 2.0
import pygtk
pygtk.require("2.0")

# Import the rest of the needed modules
import gtk
import gwp

# Plugin manager class
class PluginManager:
    __module__ = 'gwp'

    # Key-press hooks dictionary
    key_hooks = {}
    
    def manage_event_key (self, event):
        if (event["type"] == gtk.gdk.KEY_PRESS):
            self.key_hooks[event["string"]]()

    def set_hook_key (self, key, action):
        self.key_hooks[key] = action

# Main code execute at load
if __name__ == "__main__":
    # Register clases on 'gwp' module
    gwp.__dict__["PluginManager"] = PluginManager    
    # Initialize a PluginManager and pass it to GameState in C
    gwp.set_plugin_mgr (gwp.PluginManager ())

