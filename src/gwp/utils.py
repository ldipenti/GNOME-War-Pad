# GWP Infraestructure

import gobject
import inspect
from gwp import plugins

class PluginManager(gobject.GObject):
    def __init__(self):
        super(PluginManager, self).__init__(self)
        self.__registered_plugins = []
        self.__available_plugins = []
        self.__load_std_plugins()

    def __load_std_plugins(self):
        """
        Loads GWP standard plugins (built-in)
        """
        for e in dir(plugins):
            obj = eval('plugins.' + e)
            if inspect.isclass(obj) and issubclass(obj, gwp.plugins.Plugin):
                self.__available_plugins.append(obj)

    pass # End of PluginManager class
gobject.type_register(PluginManager)

