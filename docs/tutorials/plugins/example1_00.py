#!/usr/bin/env python
import pygtk
import gtk
import gtk.glade

class Example1:

    # Hide window but not terminate program
    def delete_event(self, widget, data=None):
        return gtk.FALSE

    # Another callback
    def destroy(self, widget, data=None):
        gtk.main_quit()

    # Constructor
    def __init__(self):
        fname = 'example1.glade'
        self.main_window = gtk.glade.XML(fname)
        self.main_window.signal_autoconnect(self)
        self.__controls_link()
        self.__create_gui()

    def __controls_link(self):
        # Link the widgets from the glade file for making they
        # availables here.
        pass

    def __create_gui(self):
        # make the dirty work, creating columns in treeviews or
        # connecting special events.
        pass

    def main(self):
        gtk.main()

#####
# Load code
#####
if __name__ == '__main__':
    example1 = Example1()
    example1.main()
