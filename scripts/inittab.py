# Initial script loaded by GWP

class PluginManager:
    __module__ = 'gwp'
    
    def manage_key_event (self, event):
        print "Key pressed: " + event

if __name__ == "__main__":
    # Register clases on 'gwp' module
    gwp.__dict__["PluginManager"] = PluginManager    
    # Initialize a PluginManager and pass it to GameState in C
    pass
