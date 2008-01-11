# GWP Infraestructure

import gobject
import inspect
from gwp import plugins

class PluginManager(gobject.GObject):
    def __init__(self):
        super(PluginManager, self).__init__()
        self.__registered_plugins = [] # Plugin instances
        self.__available_plugins = [] # Plugin classes
        self.__load_std_plugins()

    def __load_std_plugins(self):
        """
        Loads GWP standard plugins (built-in)
        """
        for e in dir(plugins):
            obj = eval('plugins.' + e)
            if inspect.isclass(obj) and issubclass(obj, plugins.Plugin):
                self.__available_plugins.append(obj)

    def available_plugins(self):
        """
        Returns the list of plugins and their registration status (aka: active status)
        """
        plugin_list = []
        for p in self.__available_plugins:
            if p in self.__registered_plugins:
                active = True
            else:
                active = False
            # Don't load the abstract class
            if p != plugins.Plugin:
                plugin_list.append((active, p.name, p))
        return plugin_list

    def register(self, plugin_class):
        '''
        Register some plugin
        '''
        if not plugin_class.registered:
            plugin = plugin_class()
            self.__registered_plugins.append(plugin)
            plugin.register(self)
            plugin_class.registered = True

    def unregister(self, plugin_class):
        '''
        Unregister some plugin
        '''
        if plugin_class.registered:
            for plugin in self.__registered_plugins:
                if isinstance(plugin, plugin_class):
                    self.__registered_plugins.remove(plugin)
                    plugin.unregister(self)
                    plugin_class.registered = False
                    break
        
    pass # End of PluginManager class
gobject.type_register(PluginManager)

