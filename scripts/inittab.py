# Make sure we use pygtk for gtk 2.0
import pygtk
pygtk.require("2.0")

# Import the rest of the needed modules
import os
import os.path
import gtk
import gwp

#######
# Plugin manager class
#######
# To-Do:
# -----
##
class PluginManager:
    __module__ = 'gwp'

    # Private attributes
    __key_hooks = {}
    __plugins_registered = []
    __plugins_available = []
    
    def __init__(self):
        pass
    
    def manage_event_key (self, event):
        if (event["type"] == gtk.gdk.KEY_PRESS):
            try:
                # FIXME: don't know why I have to substract 16
                self.__key_hooks[event["state"] - 16][event["keyval"]]()
            except KeyError:
                # Debugging message
                print "PluginManager: key name '%s', mask '%d' not binded" % (gtk.gdk.keyval_name(event["keyval"]), event["state"])
            except TypeError:
                # Debugging msg
                print "PluginManager: it seems that you've registered an object that isn't callable!"

    def set_hook_key (self, state, key, action):
        if not self.__key_hooks.has_key(state):
            # Register modifier
            self.__key_hooks[state] = {}
        # Register key event
        self.__key_hooks[state][key] = action

    def unset_hook_key (self, state, key):
        try:
            del(self.__key_hooks[state][key])
        except KeyError:
            # Debugging message
            print "PluginManager: key event '%s' not found when unregistering plugin." % gtk.gdk.keyval_name(key)

    def register_plugin (self, plugin):
        try:
            plugin.register(self)
        except NotImplementedError:
            raise
        else:
            self.__plugins_registered.append (plugin)
            plugin.registered = True
            
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
                raise
            else:
                plugin.registered = False
            # Unregister plugin's remaining events
            for mod, event in self.__key_hooks.items():
                for keyval, action in event.items():
                    try:
                        if action.im_self == plugin:
                            del(self.__key_hooks[mod][keyval])
                    except AttributeError:
                        # Debugging
                        print "PluginManager: '%s' action is not a method!!!" % gtk.gdk.keyval_name(keyval)
                
    def get_plugins_available(self):
        return self.__plugins_available

    def add_plugin_available(self, plugin):
        self.__plugins_available.append(plugin)

#######
# Plugin abstract class
#######
class Plugin:
    """
    GWP's Plugin abstract class: every plugin must be a subclass of this one
    and should implement register() and unregister() methods as part of the
    Plugin API.
    """
    __module__ = 'gwp'

    # Custom attributes
    name = ''
    version = 0
    author_name = ''
    author_email = ''
    desc_short = ''
    desc_long = ''
    license = ''
    registered = False

    # Constructor
    def __init__ (self, name, version, author_name,
                  author_email, desc_s, desc_l, license):
        self.name = name
        self.version = version
        self.author_name = author_name
        self.author_email = author_email
        self.desc_short = desc_s
        self.desc_long = desc_l
        self.license = license

    # Executed at registration time
    def register (self, pm):
        raise NotImplementedError

    # Executed at elimination time
    def unregister (self, pm):
        raise NotImplementedError

##############
# Main code execute at load
##############
if __name__ == "__main__":
    # Register clases on 'gwp' module
    gwp.__dict__["PluginManager"] = PluginManager
    gwp.__dict__["Plugin"] = Plugin

    # Initialize a PluginManager and pass it to GameState in C
    pm = gwp.PluginManager ()
    gwp.set_plugin_mgr (pm)

    ### FIXME!!! The code below really suck, should put everything on
    # PluginManager's constructor, but I have some problem with scopes
    # that I have to solve.
    
    # Load system plugins
    plugins_dir = gwp.plugins_get_dir()
    for plugin in os.listdir(plugins_dir + '/'):
        execfile (plugins_dir + '/' + plugin)
        # Check the plugins and add them to the available plugins list
    for obj in dir():
        try:
            if (isinstance(eval(obj), gwp.Plugin)):
                pm.add_plugin_available(eval(obj))
        except AttributeError:
            # Ignore if 'obj' is not an instance
            pass

    # Check for user plugins
    user_dir = os.path.expanduser('~/.gwp/plugins')
    if (os.path.exists(user_dir)):
        for plugin in os.listdir(user_dir + '/'):
            execfile (user_dir + '/' + plugin)
            # Check the plugins and add them to the available plugins list
        for obj in dir():
            try:
                if (isinstance(eval(obj), gwp.Plugin)):
                    pm.add_plugin_available(eval(obj))
            except AttributeError:
                # Ignore if 'obj' is not an instance
                pass
    else:
        # Print some informational message
        print "If you want to use your own plugins, you should place them on '%s'" % user_dir

    
