#!/usr/bin/env python
# Run GWP, run!!!

import pygtk
pygtk.require('2.0')

import os.path
import gtk

from gwp.models import Game
from gwp.ui import Shell

# Simply, a little stub code to run this...

game = Game(os.path.expanduser('~/VP/ARGF4/'), 7)

shell = Shell()
shell.show_all()
gtk.main()
