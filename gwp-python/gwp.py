#!/usr/bin/env python

import gtk
from Models import *
from Controllers import *
from Views import *

class Application:
    starchart_model = None
    starchart_controller = None
    starchart_view = None

    def __init__(self):
        self.starchart_model = Starchart(0, 0, 1000, 1000)
        self.starchart_controller = StarchartController(self.starchart_model)
        #self.starchart_view = StarchartView(self.starchart_controller)
        self.starchart_model.add_planet('Trantor')
        self.starchart_model.add_planet('Magrathea')
        self.starchart_model.add_planet('Venus')
        self.starchart_model.add_planet('Terminus')
        self.starchart_model.remove_planet('Magrathea')
        self.starchart_model.remove_planet('Terminus')
        self.starchart_model.remove_planet('Tierra')
        return

if __name__ == '__main__':
    a = Application()
    #gtk.main()
