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

    def testaddplanet(self):
        planet = 'Earth'
        self.starchart.add_planet(planet)
        self.assert_(planet in self.starchart.planets)
        return

    def testremoveplanet(self):
        planet = 'Terminus'
        self.starchart.add_planet(planet)
        self.failUnless(planet in self.starchart.planets)
        self.starchart.remove_planet(planet)
        self.assert_(planet not in self.starchart.planets)
        return

    pass # End of TestStarchart class

if __name__ == '__main__':
    unittest.main()
