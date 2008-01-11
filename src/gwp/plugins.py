# Plugin infraestructure

import pygtk
import gobject

import gtk

class Plugin(gobject.GObject):
    """
    GWP's Plugin abstract class: every plugin must be a subclass of this one
    and should implement register() and unregister() methods as part of the
    Plugin API.
    """

    name = 'A Plugin'
    version = "0.0"
    author_name = 'John Doe'
    author_email = 'jdoe@somehost.tld'
    desc_short = 'A generic short description'
    desc_long = 'A generic long description'
    license = 'A license, hopefully GPL compatible'
    registered = False
    
    __gsignals__ = {
        'unregistered' : (gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE,
                          ())
        }

    def __init__(self):
        super(Plugin, self).__init__()

    # Executed at registration time
    def register (self, pm):
        raise NotImplementedError

    # Executed at elimination time, this should be executed from subclasses
    def unregister (self, pm):
        self.emit('unregistered')

    pass # End of Plugin class
gobject.type_register(Plugin)


# TEST PLUGIN
class ExamplePlugin(Plugin):
    '''
    Dumb test plugin example
    '''
    name = 'My first example plugin'
    
    def register(self, pm):
        print "Plugin '%s' activated" % (self.name,)

    def unregister(self, pm):
        print "This plugin is going bye bye!"

