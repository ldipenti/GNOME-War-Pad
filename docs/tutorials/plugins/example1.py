#!/usr/bin/env python
#ruta='/u/home/cristian/devel/magallanes'
#import sys
#sys.path.append(ruta)
import pygtk
import gtk
import gtk.glade

class Example1:

    # Hide window but not terminate plugin
    def delete_event(self, widget, data=None):
        print "delete event raised"
        return gtk.FALSE

    # Another callback
    def destroy(self, widget, data=None):
        print "destroy event raised"
        gtk.main_quit()

    # Constructor
    def __init__(self):
        fname = 'example1.glade'
        self.main_window = gtk.glade.XML(fname)
        self.main_window.signal_autoconnect(self)

        self.__enlazar_controles()
        self.__create_gui()
        print "Este es el ejemplo1"

    def __enlazar_controles(self):
        #labels
        self.lbl_label1 =  self.main_window.get_widget('label1')
        #Textbox
        self.tb_entry1 =  self.main_window.get_widget('entry1')
        #botones de posesion/raza
        self.btn_button1 = self.main_window.get_widget('button1')
        self.btn_button2 = self.main_window.get_widget('button2')

    def __create_gui(self):
        #self.lst_razas.entry.connect("changed", self.eligio_raza, None)
        self.btn_button1.connect("clicked", self.aplicar, None)
        self.btn_button2.connect("clicked", self.salir, None)
        pass

    def aplicar(self, widget, data=None):
        print "Se oprimio el boton Aplicar"
        pass

    def salir(self, widget, data=None):
        print "Se oprimio el boton Salir"
        self.delete_event(self.main_window)
        pass

    def main(self):
        gtk.main()

#####
# Load code
#####
if __name__ == '__main__':
    example1 = Example1()
    # para modo pruebas lo arranco directo
    example1.main()
