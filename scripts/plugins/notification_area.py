import pygtk
import gtk


class NotificationArea(gwp.Plugin):

    name = 'Notification Area'
    version = '0.1'
    author_name = 'Lucas Di Pentima'
    author_email = 'lucas@lunix.com.ar'
    desc_short = 'An area where to add buttons giving alerts to the user'
    desc_long = 'This plugin adds itself to one of the UI slots that GWP provides and allows other plugins to insert their own icons (buttons) to give notices or alerts in a graphic way. This is the equivalent of the desktop system tray.'
    license = 'GPL'

    # Constructor
    def __init__(self):
        gwp.Plugin.__init__(self)
        self.__tooltips = gtk.Tooltips()
        self.__create_gui()

    # Adds a widget to the notification area
    def add_notification(self, widget):
        notification = gtk.ToolItem()
        eventbox = gtk.EventBox() # Tooltips on any widget
        notification.show()
        eventbox.show()
        eventbox.add(widget)
        notification.add(eventbox)
        self.__toolbar.insert(notification, 0) # Prepend (-1 to append)

    # Removes the widget
    def remove_notification(self, widget):
        eventbox = widget.parent
        try:
            notification = eventbox.parent
        except AttributeError:
            pass
        else:
            if (notification.__class__.__name__ == 'ToolItem'):
                self.__toolbar.remove(notification)
                notification.remove(eventbox)
                eventbox.remove(widget)

    # Set a tooltip message to the notification
    def set_tooltip(self, widget, tip):
        eventbox = widget.parent
        try:
            notification = eventbox.parent
        except AttributeError:
            pass
        else:
            if (notification.__class__.__name__ == 'ToolItem'):
                notification.set_tooltip(self.__tooltips, tip)

    # Create the interface
    def __create_gui(self):
        self.__toolbar = gtk.Toolbar()
        self.__toolbar.set_tooltips(gtk.TRUE)
        self.__toolbar.set_show_arrow(gtk.TRUE)
        self.__toolbar.set_orientation(gtk.ORIENTATION_HORIZONTAL)

    # Add itself to the plugin slot
    def register(self, pm):
        self.__toolbar.show()
        pm.add_plugin_slot('panel', self.__toolbar)

    # cleaning up...
    def unregister(self, pm):
        pm.remove_plugin_slot('panel', self.__toolbar)
        
