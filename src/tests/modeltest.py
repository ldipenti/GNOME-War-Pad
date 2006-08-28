#!/usr/bin/env python

import Models
import unittest

class TestStarchart(unittest.TestCase):
    '''
    Test the starchart model
    '''

    def setUp(self):
        self.starchart = Models.Starchart(0, 0, 1000, 1000)
        return

    def testAddPlanet(self):
        planet = 'Earth'
        self.starchart.add_planet(planet)
        self.assert_(planet in self.starchart.planets)
        return

    def testRemovePlanet(self):
        planet = 'Terminus'
        self.starchart.add_planet(planet)
        self.failUnless(planet in self.starchart.planets)
        self.starchart.remove_planet(planet)
        self.assert_(planet not in self.starchart.planets)
        return

    pass # End of TestStarchart class

class TestFloatingObject(unittest.TestCase):
    '''
    Test the FloatingObject abstract class
    '''
    def setUp(self):
        self.obj = Models.FloatingObject(0,0)
    
    def testInstantiate(self):
        obj = Models.FloatingObject(100, 200)
        self.assert_(obj.x == 100 and obj.y == 200)
        return

    def testIllegalXCoord(self):
         self.assertRaises(ValueError, self.obj.__setattr__, 'x', -200)
         return

    def testIllegalYCoord(self):
         self.assertRaises(ValueError, self.obj.__setattr__, 'y', -200)
         return

    pass # End of TestFloatinObject class

class TestFlyingObject(unittest.TestCase):
     '''
     Test the FlyingObject abstract class
     '''
     def testInstantiate(self):
         obj = Models.FlyingObject(10, 5, 90, 9)
         self.assert_(obj.x == 10 and obj.y == 5 and
                      obj.heading == 90 and obj.speed == 9)
         return

     pass # End of TestFlyingObject class
         
if __name__ == '__main__':
    unittest.main()
