# Make sure we use pygtk for gtk 2.0
import pygtk
#pygtk.require("2.0")

# Import the rest of the needed modules
import os
import os.path
import gtk
import gwp
import re
import inspect

#######
# Plugin manager class
#######
# To-Do:
# -----
##
class PluginManager:
    __module__ = 'gwp'

    def __init__ (self):
        # Private attributes
        self.__key_hooks = {}
        self.__menu_hooks = {}
        self.__plugins_registered = [] # instances
        self.__plugins_available = [] # classes
        self.__menu = None # Plugins menu reference

    # This method runs only once...it's called from C code to assign
    # a reference to the Plugin's GtkMenu widget.
    def set_menu (self, menu):
        if not self.__menu:
            self.__menu = menu
        
    def manage_event_key (self, event):
        if (event["type"] == gtk.gdk.KEY_PRESS):
            try:
                # Call registered method
                # FIXME: why substract 16?
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

    # Creates a plugin menu entry with some action
    def set_hook_menu (self, menu_label, action, data=None):
        # Add new item to menu
        menu_item = gtk.MenuItem(menu_label)
        self.__menu.append(menu_item)
        # Connect signal
        menu_item.connect("activate", action, data)
        menu_item.show()
        # Save references in case unregistering plugin
        self.__menu_hooks[action] = menu_item

    # Deletes the menu entry from a particular handler
    def unset_hook_menu (self, action):
        try:
            menu = self.__menu_hooks[action]
        except KeyError:
            # Debugging message
            print "PluginManager: menu hook not found on list"
        else:
            # Bye bye, menu entry
            menu.hide()
            del (self.__menu_hooks[action])
            menu.destroy()
        
    def register_plugin (self, plugin_class):
        plugin = plugin_class()
        try:
            plugin.register(self)
        except NotImplementedError:
            raise
        else:
            self.__plugins_registered.append (plugin)
            plugin.__class__.registered = True
            
    def unregister_plugin (self, plugin_class):
        # Search plugin instance
        for instance in self.__plugins_registered:
            if isinstance(instance, plugin_class):
                plugin = instance
                break

        # If plugin instance not found, return with message
        if not isinstance(plugin, plugin_class):
            print 'PluginManager: plugin instance not found, couldn\'t unregister' + plugin_class.name
            return
        
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
                plugin.__class__.registered = False
            # Unregister plugin's remaining key hooks
            for mod, event in self.__key_hooks.items():
                for keyval, action in event.items():
                    try:
                        if action.im_self == plugin:
                            del(self.__key_hooks[mod][keyval])
                    except AttributeError:
                        # Debugging
                        print "PluginManager: '%s' action is not a method!!!" % gtk.gdk.keyval_name(keyval)

            # Unregister plugin's remaining menu hooks
            for action, menu_item in self.__menu_hooks.items():
                try:
                    if action.im_self == plugin:
                        self.unset_hook_menu (action)
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

    # Class attributes
    name = 'A Plugin'
    version = "0.0"
    author_name = 'John Doe'
    author_email = 'jdoe@somehost.tld'
    desc_short = 'A generic short description'
    desc_long = 'A generic long description'
    license = 'A license, hopefully GPL compatible'
    registered = False

    # Constructor
    def __init__ (self):
        pass
    
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

    # Load user plugins
    p = re.compile('^.*\.py$', re.IGNORECASE)
    user_dir = os.path.expanduser('~/.gwp/plugins')
    if (os.path.exists(user_dir)):
        for plugin in os.listdir(user_dir + '/'):
            if not p.match(plugin) == None:
                execfile (user_dir + '/' + plugin)
    else:
        # Print some informational message
        print "If you want to use your own plugins, you should place them on '%s'" % user_dir

    # Check the plugins and add them to the available plugins list
    for o in dir():
        obj = eval(o)
        if inspect.isclass(obj) and issubclass(obj, gwp.Plugin):
            # Don't add the Plugin class
            if not(obj == gwp.Plugin):
                pm.add_plugin_available(obj)
