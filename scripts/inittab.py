# Make sure we use pygtk for gtk 2.0
import pygtk
#pygtk.require("2.0")
import gobject

# Import the rest of the needed modules
import os
import os.path
import gtk
import gwp
import re
import inspect
import sys

# I don't understand why gwp_config.py has to exist even if I don't import it
sys.path.append(gwp.get_system_plugins_dir())
import gettext
_ = gettext.gettext



#######
# Plugin manager class
#######
# To-Do:
# -----
##
class PluginManager:
    __module__ = 'gwp'

    # Constructor
    def __init__ (self):
        # Private attributes
        self.__key_hooks = {}
        self.__menu_hooks = {}
        self.__plugins_registered = [] # instances
        self.__plugins_available = [] # classes
        self.__slots = {} # UI slots
        self.__menu = None # Plugins menu reference

        ###
        # Connect to all needed signals to the event hub
        for ship in gwp.ship_get_list().values():
            ship.connect ("selected", self.__event_hub, "ship-selected")
        #
        for planet in gwp.planet_get_list().values():
            planet.connect ("selected", self.__event_hub, "planet-selected")
        ###

    # Event Hub: This concentrates and propagates all events (except the
    # keyboard events) to the active plugins. Each plugin will implement
    # a method called 'notify' that will decide what events to take care of.
    def __event_hub (self, object, event):
        for plugin in self.__plugins_registered:
            try:
                plugin.notify (object, event)
            except NotImplementedError:
                pass

    # This method runs only once...it's called from C code to assign
    # a reference to the Plugin's GtkMenu widget.
    def __set_menu (self, menu):
        if not self.__menu:
            self.__menu = menu

    # This method is called from C code to assign a reference to the
    # plugin UI slots.
    def __set_plugin_slot (self, slot_name, slot):
        self.__slots[slot_name] = slot
        
    def manage_event_key (self, event):
        if (event["type"] == gtk.gdk.KEY_PRESS):
            try:
                # Call registered method
                # FIXME: why substract 16?
                self.__key_hooks[event["state"] - 16][event["keyval"]]()
            except KeyError:
                # Debugging message
                # print "PluginManager: key name '%s', mask '%d' not binded" % (gtk.gdk.keyval_name(event["keyval"]), event["state"])
		pass
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
            #plugin.connect('unregistered', self.__event_hub, 'plugin-unregistered')

            # "Emit" an event to the HUB notifying all plugins that a new
            # plugin is in the 'hood...
            self.__event_hub(plugin, 'plugin-registered')
            
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
            # Delete plugin instance (must be the last thing to do)
            del (plugin)

    def get_plugins_available(self):
        return self.__plugins_available

    def add_plugin_available(self, plugin):
        self.__plugins_available.append(plugin)

    # Returns true if the plugin is available
    def is_plugin_available(self, name):
        for plugin in self.__plugins_available:
            if name == plugin.__name__:
                return True
        # Not found
        return False

    # Returns true is the plugin is registered
    def is_plugin_registered(self, name):
        for plugin in self.__plugins_registered:
            if name == plugin.__class__.__name__:
                return True
        # Not found
        return False

    # Returns the registered plugin's reference to the caller
    def get_plugin(self, name):
        if self.is_plugin_registered(name):
            for plugin in self.__plugins_registered:
                if name == plugin.__class__.__name__:
                    return plugin
        else:
            # Not found
            return None
    
    # This method is used by the GwpGameState C code to store the active
    # plugins list before closing the game.
    def get_plugin_registered_names(self):
        names = []
        for plugin in self.__plugins_registered:
            # The Navigator gets loaded always
            if not plugin.__class__.__name__ == 'PluginNavigator':
                names.append(plugin.__class__.__name__)
        return names

    # Search if the given classes are available on the plugin list
    # and register the ones who are.
    # This function is called from C code, plugin writers shouldn't
    # mess with this.
    def set_plugin_registered_names(self, names):
        for plugin in self.__plugins_available:
            if plugin.__name__ in names:
                self.register_plugin (plugin)

    # UI Slots management
    def add_plugin_slot(self, slot_name, widget):
        try:
            self.__slots[slot_name].add(widget)
        except KeyError:
            print "PluginManager: plugin slot '%s' does not exist!" % slot_name
    
    def remove_plugin_slot(self, slot_name, widget):
        try:
            self.__slots[slot_name].remove(widget)
        except KeyError:
            print "PluginManager: plugin slot '%s' does not exist!" % slot_name

#######
# Plugin abstract class
#######
class Plugin(gobject.GObject):
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
        # Superclass constructor
        gobject.GObject.__init__(self)
    
    __gsignals__ = {
        'unregistered' : (gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE,
                          ())
        }

    # Executed at registration time
    def register (self, pm):
        raise NotImplementedError

    # Executed at elimination time, this should be executed from subclasses
    def unregister (self, pm):
        self.emit('unregistered')

    # Every system event is passed to each plugin
    def notify (self, object, event):
        raise NotImplementedError

# Register new gobject types
gobject.type_register(Plugin)

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
    
    p = re.compile('^.*\.py$', re.IGNORECASE)

    # Load system plugins
    plugins_dir = gwp.get_system_plugins_dir()
    for plugin in os.listdir(plugins_dir + '/'):
        if not p.match(plugin) == None:
            execfile (plugins_dir + '/' + plugin)

    # Load user plugins
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
