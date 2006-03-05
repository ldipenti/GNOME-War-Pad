# Controllers.py: Controller classes

from gtkmvc.controller import Controller
from Models import *
from Views import *

class StarchartController(Controller):
    def __init__(self, model):
        Controller.__init__(self, model)
        model.registerObserver(self)
        return

    def property_planets_change_notification(self, model, old, new):
        for planet in old:
            if planet not in new:
                print "Planeta eliminado:", planet

        for planet in new:
            if planet not in old:
                print "Planeta agregado:", planet
        return

    pass # End of StarchartController class


    
