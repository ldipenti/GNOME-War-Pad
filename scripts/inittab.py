# Initial script loaded by GWP
class PluginManager:
    __module__ = 'gwp'
    
    def manage_key_event (self, event):
        print "GUACAAAAAAAA"
        
        if (event["type"] == gtk.gdk.KEY_PRESS):
            print "Key press: %s\n" % (event["string"])

if __name__ == "__main__":
    # Register clases on 'gwp' module
    gwp.__dict__["PluginManager"] = PluginManager    
    # Initialize a PluginManager and pass it to GameState in C
    gwp.register_plugin_mgr (gwp.PluginManager())

